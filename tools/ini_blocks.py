#!/usr/bin/env python3
"""Recover retail game.dat's INI block-type registrations: (token, parse callback) pairs.

BFME 2's INI block table pairs each top-level token ("MusicTrack", "AudioEvent",
...) with the static parser INI::load dispatches to.  Each entry is two adjacent
dwords in an initialised data section: a pointer to the NUL-terminated token
and a pointer into .text.  This tool reads them straight from the retail image
and writes reverse/ini_blocks.tsv, the record tools/rename.py's
canonical:iniblock evidence kind checks against.

A pair is kept only when it is narrow enough to be the registration itself:
  * the token is a bare identifier ([A-Z][A-Za-z0-9_]*, 3..64 chars);
  * the callback is the start of a functions.csv row whose signature is a
    block parser's (one INI* argument, void return:
    @@YAXPAVINI@@@Z, @@SAXPAVINI@@@Z or @INI@@SAXPAV1@@Z);
  * the token is paired with exactly one callback and the callback with
    exactly one token across the whole image;
  * the callback is not a thunk (its first instruction is not a jmp), so the
    registered address is the parser itself, not a forwarder to it;
  * no other functions.csv row shares the callback's address (no folded or
    identical-COMDAT ambiguity about which function the address is);
  * the name it would take is not already spent by a row at another address
    (a collision means one of the two names is wrong; neither is proposed).
Every dropped pair is printed with its reason; nothing is guessed.

The name column is the convention the reference trees use for that token:
the parser Zero Hour's INI.cpp table or BFME 1's REGISTER_BLOCK list registers
for the same token (class qualifier dropped), cited as path:line; otherwise
the derived parse<Token>Definition, the spelling both trees use for their own
blocks (name_source "derived").

Usage: python3 tools/ini_blocks.py [--check]
  --check  regenerate in memory and fail when reverse/ini_blocks.tsv differs.
"""
import csv
import re
import struct
import sys
from collections import defaultdict
from pathlib import Path

ROOT = Path(__file__).resolve().parents[1]
EXE = ROOT / "baselines" / "bfme2" / "workshop-vanilla-1.06" / "files" / "game.dat"
OUT = ROOT / "reverse" / "ini_blocks.tsv"
ZH_INI = "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source/Common/INI/INI.cpp"
BFME1_INI = "reference/open-bfme-1/game/GameEngine/Source/Common/INI/ini.cpp"
HEADER = ["token", "token_rva", "entry_rva", "parse_rva", "current_name", "name", "name_source"]
SIGNATURE = re.compile(r"@@YAXPAVINI@@@Z$|@@SAXPAVINI@@@Z$|@INI@@SAXPAV1@@Z$")
TOKEN = re.compile(r"[A-Z][A-Za-z0-9_]{2,63}")


def sections(data):
    pe = struct.unpack_from("<I", data, 0x3C)[0]
    count = struct.unpack_from("<H", data, pe + 6)[0]
    optional = struct.unpack_from("<H", data, pe + 20)[0]
    base = struct.unpack_from("<I", data, pe + 52)[0]
    out = []
    for i in range(count):
        o = pe + 24 + optional + 40 * i
        name = data[o:o + 8].rstrip(b"\0").decode("ascii", "replace")
        vsize, va, rsize, raw = struct.unpack_from("<IIII", data, o + 8)
        out.append((name, va, rsize, raw))
    return base, out


def reference_names():
    names = {}
    for path, pattern in ((ZH_INI, r'\{\s*"(\w+)",\s*INI::(\w+)\s*\}'),
                          (BFME1_INI, r'REGISTER_BLOCK\(\s*\w+,\s*"(\w+)",\s*(?:\w+::)?(\w+)\s*\)')):
        full = ROOT / path
        if not full.exists():
            continue
        for number, line in enumerate(full.read_text(encoding="utf-8", errors="replace").splitlines(), 1):
            m = re.search(pattern, line)
            if m and m.group(1) not in names:
                names[m.group(1)] = (m.group(2), f"{path}:{number}")
    return names


def extract():
    data = EXE.read_bytes()
    base, secs = sections(data)
    text = next(s for s in secs if s[0] == ".text")

    def offset(va):
        rva = va - base
        for _, start, size, raw in secs:
            if start <= rva < start + size:
                return raw + rva - start
        return None

    def token_at(va):
        o = offset(va)
        if o is None:
            return None
        end = data.find(b"\0", o, o + 65)
        raw = data[o:end] if end > o else b""
        try:
            s = raw.decode("ascii")
        except UnicodeDecodeError:
            return None
        return s if TOKEN.fullmatch(s) else None

    rows, every, spent = {}, defaultdict(set), defaultdict(set)
    with open(ROOT / "reverse" / "functions.csv", encoding="utf-8", errors="replace", newline="") as f:
        for r in csv.DictReader(f):
            try:
                rva = int(r["target_rva"], 16)
            except (KeyError, ValueError):
                continue
            every[rva].add(r["name"])
            word = re.match(r"\??([^@]+)", r["name"])
            if word:
                spent[word.group(1)].add(rva)
            if SIGNATURE.search(r["name"]):
                rows.setdefault(rva, set()).add(r["name"])
    pairs = []
    for name, start, size, raw in secs:
        if name not in (".rdata", ".data"):
            continue
        for o in range(raw, raw + size - 8, 4):
            tva, fva = struct.unpack_from("<II", data, o)
            frva = fva - base
            if not (text[1] <= frva < text[1] + text[2]) or frva not in rows:
                continue
            token = token_at(tva)
            if token:
                pairs.append((token, tva - base, start + o - raw, frva))
    by_token, by_func = defaultdict(set), defaultdict(set)
    for token, _, _, frva in pairs:
        by_token[token].add(frva)
        by_func[frva].add(token)
    refs = reference_names()
    out, seen, dropped = [], set(), []
    for token, trva, erva, frva in sorted(pairs, key=lambda p: (p[0], p[2])):
        if token in seen:
            continue
        seen.add(token)
        name, source = refs.get(token, (f"parse{token}Definition", "derived"))
        first = data[offset(frva + base):offset(frva + base) + 2]
        why = ("token has several callbacks" if len(by_token[token]) != 1 else
               "callback serves several tokens" if len(by_func[frva]) != 1 else
               "callback is a jmp thunk" if first[:1] in (b"\xe9", b"\xeb") or first == b"\xff\x25" else
               "several functions.csv rows share the callback address" if len(every[frva]) != 1 else
               f"{name} is already spent at another address" if spent.get(name, set()) - {frva} else None)
        if why:
            dropped.append((token, f"0x{frva:08X}", why))
            continue
        out.append([token, f"0x{trva:08X}", f"0x{erva:08X}", f"0x{frva:08X}", next(iter(rows[frva])), name, source])
    return out, dropped


def render(rows):
    return "\t".join(HEADER) + "\n" + "".join("\t".join(r) + "\n" for r in rows)


def main(argv):
    rows, dropped = extract()
    text = render(rows)
    for token, rva, why in dropped:
        print(f"dropped {token} {rva}: {why}")
    if "--check" in argv:
        current = OUT.read_text(encoding="utf-8").replace("\r\n", "\n") if OUT.exists() else ""
        if current != text:
            print("reverse/ini_blocks.tsv is stale; run python3 tools/ini_blocks.py")
            return 1
        return 0
    OUT.write_text(text, encoding="utf-8", newline="\n")
    print(f"{text.count(chr(10)) - 1} block registrations -> {OUT.relative_to(ROOT).as_posix()}")
    return 0


if __name__ == "__main__":
    sys.exit(main(sys.argv[1:]))
