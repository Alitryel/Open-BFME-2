#!/usr/bin/env python3
"""Replace hard-coded global addresses in sources with the globals defined there.

A unit that reads a global through a cast of its retail address, such as
`#define TheGameLogic (*(GameLogic **)0x00DFE78C)`, byte-matches, but it
cannot link: the census counts the literal address against it (it is
tools/link_debt.py's "hard-coded image address", the largest single class
of link blocker). When some unit in the ledger DEFINES a global at that
address, the fix is mechanical: declare that global and use its name.

The address of each defined global comes from the ledger itself. Every
DIR32 relocation in a matched row's object names a symbol, and the retail
bytes under it give that symbol's address (less the addend). Only symbols
some ledger object defines, with a decorated type this tool can declare
(scalars, and pointers to scalars or to classes), are used, and only
addresses that resolve to exactly one such symbol.

Rewrites, per file:

  (*(T **)0xADDR)  /  (*(T *)0xADDR)   ->  Name           T matches Name's type
  (T *)0xADDR                          ->  (T *)&Name      any other cast

and an `extern` declaration of Name with its own decorated type is added
after the file's leading comment block.

A literal that is the address of exactly one vftable some ledger object
defines (`*vtab = (int)0x00C5EE80;`, a hand-written vptr store) becomes
`((unsigned int)vtbl_00C5EE80)`, an `extern "C"` array the linker aliases to
that vftable (`/alternatename:_vtbl_00C5EE80=??_7...`): the same bytes, but
the store follows the vftable wherever the linked image puts it. An address
several folded vftables share gets the same address-named alias, linked to
the first of them by name: the alias claims no class, and folded tables are
identical slot for slot, so any member yields the same bytes and behaviour.
Each changed file is rebuilt with
./build.sh and restored unchanged unless every row in it still matches.

Usage:
  python3 tools/name_globals.py [--dry-run] [FILE ...]

With no FILE, every authored unit link_debt flags is tried. The address
index is cached in build/name_globals_index.json against the ledger's
mtime; --reindex rebuilds it.
"""
import argparse
import collections
import json
import re
import struct
import subprocess
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parent.parent
sys.path.insert(0, str(ROOT / "tools"))
import build  # noqa: E402
import link_census as lc  # noqa: E402
import link_debt  # noqa: E402

CACHE = ROOT / "build" / "name_globals_index.json"
SCALAR = {"H": "int", "I": "unsigned int", "M": "float", "E": "unsigned char", "D": "char",
          "K": "unsigned long", "J": "long", "F": "short", "G": "unsigned short", "_N": "bool",
          "N": "double", "C": "signed char", "X": "void"}
CV = {"A": "", "B": "const ", "C": "volatile ", "D": "const volatile "}
TYPEDEFS = {"Int": "int", "UnsignedInt": "unsigned int", "Real": "float", "UnsignedByte": "unsigned char",
            "Byte": "char", "Bool": "bool", "Short": "short", "UnsignedShort": "unsigned short",
            "DWORD": "unsigned long", "UINT": "unsigned int", "BYTE": "unsigned char", "BOOL": "int",
            "LONG": "long", "ULONG": "unsigned long", "WORD": "unsigned short", "Int32": "int",
            "UnsignedInt32": "unsigned int", "Real64": "double"}


def declare(symbol):
    """(name, type, key, class name, declaration) for a decorated global, or None.

    `type` is the C type a direct-name rewrite must agree with ('GameLogic *',
    'int'); `key` is 'class'/'struct' for a class pointee."""
    found = re.match(r"^\?(\w+)@@3(.*)$", symbol)
    if not found:
        return None
    name, rest = found.groups()
    scalar = re.match(r"^(_N|[CDEFGHIJKMN])([ABCD])$", rest)
    if scalar:
        kind = SCALAR[scalar.group(1)]
        return name, kind, None, None, f"extern {CV[scalar.group(2)]}{kind} {name};"
    pointer = re.match(r"^P([ABCD])(?:(_N|[CDEFGHIJKMNX])|([VU])(\w+)@@)A$", rest)
    if not pointer:
        return None
    pointee_cv, scalar_code, key_code, cls = pointer.groups()
    if scalar_code:
        kind = SCALAR[scalar_code]
        return name, f"{kind} *", None, None, f"extern {CV[pointee_cv]}{kind} *{name};"
    key = "class" if key_code == "V" else "struct"
    return name, f"{cls} *", key, cls, f"extern {CV[pointee_cv]}{key} {cls} *{name};"


def _object_defs(obj):
    try:
        data = obj.read_bytes()
    except OSError:
        return []
    return [s["name"] for s in lc._coff_symbols(data) if s["storage"] == lc.EXTERNAL and s["section"] > 0]


def build_index():
    """{VA: [decorated symbol, ...]} for defined globals, from ledger DIR32 sites."""
    rows = lc.ledger()
    present, _ = lc.objects(rows)
    defined = set()
    for obj in present:
        defined.update(_object_defs(obj))
    bases = collections.defaultdict(set)
    for row in rows:
        if not row["source"].lower().endswith((".c", ".cpp")):
            continue
        try:
            obj = build.row_object(row)
            if not obj.exists():
                continue
            rva, size = int(row["target_rva"], 16), int(row["target_size"], 0)
            target = build.read_target_bytes(rva, size)
            body, relocs = build.read_object_symbol_bytes(obj, build.ledger_object_symbol(row), size)
        except Exception:  # an unreadable row only means fewer addresses
            continue
        for offset, kind, symbol in relocs:
            if kind != 0x0006 or symbol not in defined or offset + 4 > min(size, len(body)):
                continue
            if not symbol.startswith("?") or not (re.search(r"@@[0-3]", symbol) or symbol.startswith("??_7")):
                continue
            address = (struct.unpack_from("<I", target, offset)[0] - struct.unpack_from("<I", body, offset)[0]) & 0xFFFFFFFF
            bases[address].add(symbol)
    return {str(a): sorted(s) for a, s in bases.items()}


def load_index(rebuild=False):
    stamp = (ROOT / "reverse" / "functions.csv").stat().st_mtime
    if not rebuild and CACHE.exists():
        cached = json.loads(CACHE.read_text(encoding="utf-8"))
        if cached.get("stamp") == stamp:
            return {int(a): s for a, s in cached["index"].items()}
    index = build_index()
    CACHE.parent.mkdir(parents=True, exist_ok=True)
    CACHE.write_text(json.dumps({"stamp": stamp, "index": index}), encoding="utf-8")
    return {int(a): s for a, s in index.items()}


def normalise(kind):
    words = kind.replace("*", " * ").split()
    words = [w for w in words if w not in ("const", "volatile", "class", "struct")]
    text = " ".join(TYPEDEFS.get(w, w) for w in words)
    return text.replace(" *", " *").strip()


DIRECT = re.compile(r"\(\s*\*\s*\(\s*([\w ]+?)\s*(\*?)\s*\*\s*\)\s*(0x[0-9A-Fa-f]{6,8})\s*\)")
CAST = re.compile(r"\(\s*([\w ]+?)\s*(\*+)\s*\)\s*(0x[0-9A-Fa-f]{6,8})\b")
VTABLE = re.compile(r"(?<![\w.])0x([0-9A-Fa-f]{6,8})[uU]?(?![\w.])")
LEAD = re.compile(r"(?:[ \t]*//[^\n]*\n|[ \t]*\r?\n)*")
NON_CODE = re.compile(r'"(?:\\.|[^"\\])*"|\'(?:\\.|[^\'\\])*\'|//[^\n]*|/\*.*?\*/', re.S)


def rewrite(text, index, only=None):
    """(new text, {name: declaration}) for one source; with `only`, rewrite
    just the literals that name those globals (one edit per global)."""
    need = {}

    def unique(literal):
        address = int(literal, 16)
        if address < 0x400000:
            address += 0x400000
        found = [d for d in (declare(s) for s in index.get(address, ())) if d]
        if len(found) != 1 or (only is not None and found[0][0] not in only):
            return None
        return found[0]

    def key_ok(decl):
        name, kind, key, cls, line = decl
        if not cls:
            return True
        other = "struct" if key == "class" else "class"
        return not re.search(rf"\b{other}\s+{cls}\b", text)

    def direct(match):
        decl = unique(match.group(3))
        if not decl or not key_ok(decl):
            return match.group(0)
        cast = normalise(match.group(1) + (" *" if match.group(2) else ""))
        if cast != normalise(decl[1]):
            return match.group(0)
        need[decl[0]] = decl[4]
        return decl[0]

    def cast(match):
        decl = unique(match.group(3))
        if not decl or not key_ok(decl):
            return match.group(0)
        need[decl[0]] = decl[4]
        return f"({match.group(1)} {match.group(2)})&{decl[0]}"

    def vtable(match):
        address = int(match.group(1), 16)
        tables = sorted(s for s in index.get(address, ()) if s.startswith("??_7"))
        if not tables or any(not s.startswith("??_7") for s in index.get(address, ())):
            return match.group(0)
        name = f"vtbl_{address:08X}"
        if only is not None and name not in only:
            return match.group(0)
        # A folded table (several ??_7 at one address) is one retail table the
        # linker merged because every slot is identical; the address-named
        # alias claims no class, and any member gives the same bytes and slots.
        note = tables[0] if len(tables) == 1 else f"folded, {len(tables)} classes; via {tables[0]}"
        need[name] = (f'extern "C" const void *const {name}[];  // {note}' + "\n" +
                      f'#pragma comment(linker, "/alternatename:_{name}={tables[0]}")')
        return f"((unsigned int){name})"

    lines = text.split("\n")
    for i, line in enumerate(lines):
        stripped = line.lstrip()
        if stripped.startswith("//"):
            continue
        line = DIRECT.sub(direct, line)
        line = CAST.sub(cast, line)
        if not stripped.startswith("#"):
            code, _, comment = line.partition("//")
            line = VTABLE.sub(vtable, code) + ("//" + comment if _ else "")
        lines[i] = line
    new = "\n".join(lines)
    if new == text:
        return text, {}
    newline = "\r\n" if "\r\n" in text else "\n"
    # A comment such as "extern spellings above" can otherwise span the
    # rewritten initializer and masquerade as an existing declaration.
    declarations = NON_CODE.sub(" ", new)
    missing = [d.replace("\n", newline) for n, d in sorted(need.items())
               if not re.search(rf"\bextern\b[^;]*\b{n}\s*(\[\])?;", declarations)]
    if missing:
        at = LEAD.match(new).end()
        new = new[:at] + newline.join(missing) + newline + newline + new[at:]
    return new, need


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    parser.add_argument("files", nargs="*")
    parser.add_argument("--dry-run", action="store_true")
    parser.add_argument("--reindex", action="store_true")
    args = parser.parse_args(argv)
    index = load_index(args.reindex)
    files = args.files
    if not files:
        sources = sorted({r["source"] for r in lc.ledger()})
        files = [s for s in sources if s.lower().endswith((".c", ".cpp"))
                 and not s.startswith(("Code/gen_asm/", "Code/gen_small/"))
                 and (ROOT / s).exists()
                 and link_debt.addresses((ROOT / s).read_text(encoding="utf-8", errors="replace"))]
    import bulk_pass
    plan = {}
    for source in files:
        path = ROOT / source
        with path.open(encoding="latin-1", newline="") as handle:
            before = handle.read()
        _after, need = rewrite(before, index)
        if not need:
            continue
        if args.dry_run:
            print("WOULD", source, sorted(need))
            continue
        # one edit per global: a rewrite that breaks the bytes no longer
        # costs the file its other, good rewrites
        plan[source] = [(name, lambda text, name=name: rewrite(text, index, {name})[0]) for name in sorted(need)]
    changed = bulk_pass.run(plan, label="name_globals", log=lambda line: print(line, flush=True))
    print(f"name_globals: {len(changed)} file(s) rewritten")
    return 0


if __name__ == "__main__":
    sys.exit(main())
