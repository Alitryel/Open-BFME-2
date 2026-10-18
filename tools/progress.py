#!/usr/bin/env python3
"""Report how much of game.dat we can rebuild from what the repository holds.

BYTE-MATCHED, GAME CODE C++ and LINKING print first: the three numbers on the
README card and in the daily Discord post (tools/readme_progress.py), computed
the same way. BYTE-MATCHED ("rebuilt from source") is everything that rebuilds
to game.dat's exact bytes (authored and generated C++, vendored source,
attached prebuilt libraries; dumps excluded), over all code. GAME CODE C++ is
the C++ we wrote over the game's own code (all code minus vendored source and
prebuilt libraries); LINKING is the part of it whose files also link cleanly,
over the census tree's game code, both measured and stored by the last
tools/link_census.py run (reverse/link_census_history.csv: linked_authored,
game_code).
LINKED, under them, is all our own source in clean files over all code (the
chart's linked dots). Every figure counts 0xCC padding out, the way the
denominator does, so the breakdown under them adds up to them. Total exact, at
the end, uses the full .text and includes dumps: bounded coverage, not progress.

Every retail byte is counted once. Clean C++ ownership wins when it overlaps an
assembly-backed row (including ICF aliases), leaving "ASM-only" as actionable
porting debt. This reads the ledger but compiles nothing; build.sh is proof.

  python3 tools/progress.py                # HEAD vs worktree
  python3 tools/progress.py REF            # REF vs worktree
  python3 tools/progress.py REF1..REF2     # between two commits
  python3 tools/progress.py --details REF  # include ledger diagnostics
"""
import argparse
import csv
import re
import subprocess
from collections import Counter
from functools import lru_cache
from pathlib import Path

import build
from gaps import padding_split
from list_naked_candidates import NAKED_RE, block_bytes, symbol_comment

ROOT = Path(__file__).resolve().parents[1]
FUNCTIONS = "reverse/functions.csv"
CPP_SUFFIXES = {".c", ".cc", ".cpp", ".cxx"}
ASM_SUFFIXES = {".asm", ".s"}
# A prebuilt static library the game linked. On the code axis it counts with
# assembly, not with clean C++: nobody wrote or ported these bytes, they are
# matched against the shipped binary. On the identity axis vendor/ already
# routes it to the vendored lane.
LIB_SUFFIXES = {".lib"}
# Upstream libraries vendored into the tree. Reproducing their bytes is real
# code, but it is not recovering this game's identity, so they get their own
# lane instead of inflating the reverse-engineered figure. EA-authored
# libraries (EAC, DirtySock, debug) are the game and stay out of this list.
VENDORED_ROOTS = (
    "Code/Libraries/Source/DirectX/",
    "Code/Libraries/Source/CRT/VS2003/",
    "Code/Libraries/Source/Compression/LZHCompress/",
    "Code/Libraries/Source/Compression/ZLib/",
    "Code/Libraries/Source/JPEG/",
    "Code/Libraries/Source/LibPNG/",
    "Code/Libraries/Source/Lua/",
    "vendor/",
    # Microsoft's static CRT, read straight out of the tracked MSVC 7.1
    # toolchain rather than copied under vendor/. Same lane as vendor/d3dx9:
    # Microsoft compiled it, so it is not this game's identity.
    "build/toolchains/",
    # EA's Zero Hour source, compiled verbatim out of the pristine reference
    # tree the project is forbidden to modify. A row sourced here was not
    # written from this game's disassembly -- it is another game's source that
    # happens to compile to the same bytes -- so it belongs beside the other
    # upstreams rather than in the reverse-engineered figure. (EA-authored
    # libraries that BFME itself ships under Code/ are the game and stay out.)
    # Both submodule layouts are listed, not just the current one: these are
    # prefixes of ledger `source` values, so dropping the legacy spelling
    # would silently reclassify any row recorded before upstream's move.
    "reference/open-bfme-1/reference/CnC_Generals_Zero_Hour/",
    "reference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/",
    "reference/open-bfme-1/inputs/toolchains/",
)
# GameSpy's SDK is the one vendored library that cannot be routed by directory:
# EA dropped its C sources straight into the game's own C++ directory, so
# GameSpy/gp/gp.c sits beside this project's GameSpy/GSConfig.cpp. Extension is
# the discriminator EA's layout leaves us -- every one of the 36 .c files under
# this root carries the SDK's own banner, every .cpp beside them is this game's,
# and Code/ holds no other .c outside VENDORED_ROOTS. Checked, not assumed:
#   find Code -name '*.c' | grep -v <the vendored roots>   ->  empty
VENDORED_C_ROOTS = ("Code/GameEngine/Source/GameNetwork/GameSpy/",)
# Files a generator writes: one body per retail funclet, thunk or template
# instance, with a synthetic name. Path and note are both checked so a
# generator cannot move the recovered figure by omitting its own marker.
GENERATED_ROOTS = ("Code/gen_small/", "Code/gen_asm/")
GEN_NOTE_RE = re.compile(r"(?:^|;)\s*gen-[a-z]|identity=generated\b")
# Provenance lanes, best evidence first. Overlapping claims on one byte resolve
# to the earliest lane, so the lanes partition Total exact with no double count.
SOURCE_LANES = ("authored", "vendored", "generated", "library", "dump")
EMIT_RE = re.compile(
    r"\b_{1,2}emit\s+(?:0x([0-9a-fA-F]{1,2})|([0-9a-fA-F]{1,3})h)\b",
    re.IGNORECASE,
)
ASM_BLOCK_RE = re.compile(r"^\s*__asm\b")
# Prefilter for sources worth scanning: naked bodies or emitted bytes. Plain
# "_emit" also hits "__emit"; a false hit only costs reading one extra file.
ASM_MARKER_GREP = r"__declspec[[:space:]]*\([[:space:]]*naked|_emit"


@lru_cache(maxsize=None)
def _functions_text(ref):
    """Return the whole ledger as text for one repository state."""
    if ref is None:
        return (ROOT / FUNCTIONS).read_text(encoding="utf-8")
    proc = subprocess.run(
        ["git", "show", f"{ref}:{FUNCTIONS}"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if proc.returncode != 0:
        raise SystemExit(f"cannot read {FUNCTIONS} at {ref}: {proc.stderr.strip()}")
    return proc.stdout


def matched_at(ref):
    """Return {(name, target_rva): (size, source)} for one repository state."""
    out = {}
    for row in csv.DictReader(_functions_text(ref).splitlines()):
        if row["status"] == "matched":
            out[(row["name"], row["target_rva"])] = (
                int(row["target_size"]), row["source"])
    return out


def notes_at(ref):
    """Return {(name, target_rva): notes} for the matched rows at one state."""
    return {
        (row["name"], row["target_rva"]): row["notes"]
        for row in csv.DictReader(_functions_text(ref).splitlines())
        if row["status"] == "matched"
    }


def retail_text():
    """Return (start RVA, byte size) using the build gate's PE parser/baseline."""
    sections = build.pe_sections(build.EXE.read_bytes())
    text = next((section for section in sections if section["name"] == ".text"), None)
    if text is None:
        raise SystemExit(f"{build.EXE}: no .text section")
    return text["rva"], text["size"]


def merge_intervals(intervals):
    """Return sorted, non-overlapping half-open intervals."""
    merged = []
    for start, end in sorted(intervals):
        if start >= end:
            continue
        if merged and start <= merged[-1][1]:
            merged[-1] = (merged[-1][0], max(merged[-1][1], end))
        else:
            merged.append((start, end))
    return merged


def interval_bytes(intervals):
    return sum(end - start for start, end in merge_intervals(intervals))


def source_kind(source):
    suffix = Path(source).suffix.lower()
    if suffix in CPP_SUFFIXES:
        return "cpp"
    if suffix in ASM_SUFFIXES or suffix in LIB_SUFFIXES:
        return "asm"
    raise SystemExit(
        f"matched source has unsupported suffix {suffix or '<none>'}: {source}")


def _is_naked_declaration(lines, index):
    """True for an explicit-instantiation declaration with no function body."""
    for line in lines[index:]:
        brace = line.find("{")
        semicolon = line.find(";")
        if semicolon >= 0 and (brace < 0 or semicolon < brace):
            return True
        if brace >= 0:
            return False
    return True


def _signature_identity(name):
    """Return a conservative source-level Class::method spelling, when simple."""
    special = re.match(r"^\?\?([014])([A-Za-z_][A-Za-z0-9_]*)@@", name)
    if special:
        code, cls = special.groups()
        method = {"0": cls, "1": f"~{cls}", "4": "operator="}[code]
        return f"{cls}::{method}"
    normal = re.match(r"^\?([A-Za-z_][A-Za-z0-9_]*)@([A-Za-z_][A-Za-z0-9_]*)@@", name)
    if normal:
        return f"{normal.group(2)}::{normal.group(1)}"
    c_name = re.match(r"^_([A-Za-z_][A-Za-z0-9_]*)$", name)
    return c_name.group(1) if c_name else None


@lru_cache(maxsize=None)
def scan_naked_bodies(text):
    """Return proven asm implementation evidence without treating a file as a unit.

    Triggers on __declspec(naked) bodies and on bare __asm blocks. A bare
    __asm block is evidence only when it emits raw bytes: mnemonic-only inline
    asm inside real C++ (the period cpuid idiom) stays C++, and 18 fleet lifts
    proved plain functions can smuggle a full __emit spray past a naked-only
    scan and inflate the C++ figure."""
    lines = text.splitlines()
    bodies = []
    last_end = -1
    for index, line in enumerate(lines):
        if index <= last_end:
            continue
        naked = bool(NAKED_RE.search(line)) and not _is_naked_declaration(lines, index)
        if not naked and not ASM_BLOCK_RE.match(line):
            continue
        _, end = block_bytes(lines, index)
        emitted = []
        for body_line in lines[index:end + 1]:
            for match in EMIT_RE.finditer(body_line):
                emitted.append(int(match.group(1) or match.group(2), 16))
        if not naked and not emitted:
            continue
        last_end = end
        declaration = []
        for declaration_line in lines[index:end + 1]:
            before_brace, brace, _ = declaration_line.partition("{")
            declaration.append(before_brace)
            if brace:
                break
        bodies.append({
            "symbol": symbol_comment(lines, index),
            "signature": " ".join(" ".join(declaration).split()),
            "emitted": bytes(emitted),
            "naked": naked,
        })
    return tuple(bodies)


def naked_cpp_rows(matched, source_texts, target_reader=build.read_target_bytes):
    """Return matched-row keys proven to be naked assembly inside C/C++ files."""
    rows_by_source = {}
    for key, value in matched.items():
        if Path(value[1]).suffix.lower() in CPP_SUFFIXES:
            rows_by_source.setdefault(value[1], []).append((key, value))

    naked = set()
    target_cache = {}
    for source, text in source_texts.items():
        rows = rows_by_source.get(source, [])
        bodies = scan_naked_bodies(text)
        if not rows or not bodies:
            continue
        # Name and signature evidence is only trusted from naked bodies: a
        # bare __asm spray sits inside an ordinary function whose declaration
        # matches its row by construction. Sprays interleave __emit bytes with
        # real mnemonics at relocated call sites, so full byte equality cannot
        # prove them either; the discriminator is emitted mass. The period
        # _emit idiom (cpuid) is a few bytes of a body, a lift is most of it.
        naked_bodies = [body for body in bodies if body["naked"]]
        symbols = {body["symbol"] for body in naked_bodies if body["symbol"]}
        emitted = {body["emitted"] for body in bodies if body["emitted"]}
        signatures = [body["signature"] for body in naked_bodies]
        spray_mass = sum(len(body["emitted"]) for body in bodies if not body["naked"])
        for key, (size, _) in rows:
            name, target_rva = key
            identity = _signature_identity(name)
            proven = name in symbols or (
                identity is not None and any(
                    re.search(rf"(?<![A-Za-z0-9_]){re.escape(identity)}\s*\(", signature)
                    for signature in signatures))
            if not proven and emitted:
                target_key = (int(target_rva, 16), size)
                if target_key not in target_cache:
                    target_cache[target_key] = target_reader(*target_key)
                proven = target_cache[target_key] in emitted
            if proven or (len(rows) == 1 and len(naked_bodies) == 1) or \
                    (len(rows) == 1 and spray_mass * 2 >= size):
                naked.add(key)
    return naked


def _batch_git_texts(ref, paths):
    if not paths:
        return {}
    request = "".join(f"{ref}:{path}\n" for path in paths).encode()
    proc = subprocess.run(
        ["git", "cat-file", "--batch"], cwd=ROOT, input=request,
        capture_output=True,
    )
    if proc.returncode != 0:
        raise SystemExit(f"cannot read naked sources at {ref}: {proc.stderr.decode().strip()}")
    output = proc.stdout
    offset = 0
    texts = {}
    for path in paths:
        line_end = output.find(b"\n", offset)
        if line_end < 0:
            raise SystemExit(f"cannot read {path} at {ref}: malformed git cat-file output")
        header = output[offset:line_end].decode(errors="replace")
        offset = line_end + 1
        fields = header.rsplit(" ", 2)
        if len(fields) != 3 or fields[1] != "blob":
            raise SystemExit(f"cannot read {path} at {ref}: {header}")
        size = int(fields[2])
        texts[path] = output[offset:offset + size].decode("utf-8", errors="replace")
        offset += size + 1  # blob plus cat-file's separating newline
    return texts


def naked_source_texts(matched, ref):
    """Read only matched C/C++ sources containing naked bodies at one state."""
    sources = {
        source for _, source in matched.values()
        if Path(source).suffix.lower() in CPP_SUFFIXES
    }
    if ref is None:
        grep = subprocess.run(
            ["git", "grep", "-l", "-E", ASM_MARKER_GREP, "--", "Code"],
            cwd=ROOT, capture_output=True, text=True,
        )
        if grep.returncode not in (0, 1):
            raise SystemExit(f"cannot scan worktree naked sources: {grep.stderr.strip()}")
        paths = set(grep.stdout.splitlines()) & sources
        tracked = set(subprocess.run(
            ["git", "ls-files", "-z", "--", "Code"], cwd=ROOT,
            capture_output=True, check=True,
        ).stdout.decode(errors="replace").split("\0"))
        changed = set(subprocess.run(
            ["git", "diff", "--name-only", "-z", "HEAD", "--", "Code"],
            cwd=ROOT, capture_output=True, check=True,
        ).stdout.decode(errors="replace").split("\0"))
        disk_paths = paths & (changed | (sources - tracked))
        for source in (changed & sources) | (sources - tracked):
            if not (ROOT / source).is_file():
                raise SystemExit(f"cannot read matched source {source}")
        texts = _batch_git_texts("HEAD", sorted(paths - disk_paths))
        for source in sources - tracked:
            text = (ROOT / source).read_bytes().decode("utf-8", errors="replace")
            if NAKED_RE.search(text) or EMIT_RE.search(text):
                disk_paths.add(source)
        for source in disk_paths:
            texts[source] = (ROOT / source).read_bytes().decode("utf-8", errors="replace")
        return texts

    proc = subprocess.run(
        ["git", "grep", "-l", "-E", ASM_MARKER_GREP, ref, "--", "Code"],
        cwd=ROOT, capture_output=True, text=True,
    )
    if proc.returncode not in (0, 1):
        raise SystemExit(f"cannot scan naked sources at {ref}: {proc.stderr.strip()}")
    prefix = f"{ref}:"
    paths = []
    for line in proc.stdout.splitlines():
        path = line[len(prefix):] if line.startswith(prefix) else line.split(":", 1)[-1]
        if path in sources:
            paths.append(path)
    return _batch_git_texts(ref, sorted(paths))


def naked_cpp_rows_at(matched, ref):
    return naked_cpp_rows(matched, naked_source_texts(matched, ref))


def coverage(matched, text_start, text_size, naked_rows=()):
    """Return absolute .text-byte ownership for clean C++ and assembly rows."""
    text_end = text_start + text_size
    cpp = []
    asm = []
    naked_rows = set(naked_rows)
    for key, (size, source) in matched.items():
        _, target_rva = key
        kind = source_kind(source)
        if kind == "cpp" and key in naked_rows:
            kind = "asm"
        start = max(int(target_rva, 16), text_start)
        end = min(int(target_rva, 16) + size, text_end)
        if start >= end:
            continue
        (asm if kind == "asm" else cpp).append((start, end))

    cpp_bytes = interval_bytes(cpp)
    exact_bytes = interval_bytes(cpp + asm)
    return {
        "cpp": cpp_bytes,
        "asm_only": exact_bytes - cpp_bytes,
        "unmatched": text_size - exact_bytes,
        "exact": exact_bytes,
        "text": text_size,
    }


def source_lane(source, notes, naked):
    """Return the provenance lane for a matched row.

    Provenance asks who wrote the thing the bytes come out of. It is a
    different question from the code axis (which language) and it is the one
    the project is graded on, because only two of these five lanes are source
    anybody recovered.

      authored   C++ we wrote from the disassembly.
      vendored   upstream library source we compile (zlib, JPEG, Lua, STLport,
                 the MSVC CRT sources). Having zlib's source is having it.
      generated  C++ a generator wrote (Code/gen_small/): EH funclets,
                 small thunks, template grids.
      library    a prebuilt .lib we attach (d3dx9, CRT). It links, so it is a
                 real way to reach 1:1, but there is no source in the tree.
      dump       retail re-encoded: MASM `db` bodies and __emit sprays. These
                 fix an address and an extent and say nothing else.

    `generated` is the one arguable lane and it is deliberately NOT recovered.
    Those bodies compile from real constructs -- a tail call is a tail call,
    and the funclets fall out of MSVC's codegen rather than out of a hex dump
    -- so they are not scaffolding either, which is why they get a line of
    their own instead of being buried. They are excluded because a script
    writes them: 85,000 of the ledger's rows came from running tools/gen_uw.py
    once, and a headline a script can move is the exact failure this metric
    exists to prevent. The rule is the authorship of the source, not the
    provenance of the bytes: a human wrote it, or a program did. Flipping this
    means putting the generators under human review first, and `code: C++`
    below already reports authored and generated together for anyone who wants
    the everything-that-compiles number.
    """
    if Path(source).suffix.lower() in LIB_SUFFIXES:
        return "library"
    if naked or source_kind(source) == "asm":
        return "dump"
    if source.startswith(GENERATED_ROOTS) or GEN_NOTE_RE.search(notes):
        return "generated"
    if source.startswith(VENDORED_ROOTS):
        return "vendored"
    if source.startswith(VENDORED_C_ROOTS) and Path(source).suffix.lower() == ".c":
        return "vendored"
    return "authored"


def source_split(matched, notes, text_start, text_size, naked_rows=()):
    """Return .text bytes per provenance lane; the lanes sum to Total exact.

    An ICF alias claimed twice resolves to the earlier lane, the way clean C++
    wins an overlap on the code axis: the byte is credited to whichever claim
    says the most about it.
    """
    text_end = text_start + text_size
    naked_rows = set(naked_rows)
    lanes = {name: [] for name in SOURCE_LANES}
    for key, (size, source) in matched.items():
        start = max(int(key[1], 16), text_start)
        end = min(int(key[1], 16) + size, text_end)
        if start >= end:
            continue
        lane = source_lane(source, notes[key], key in naked_rows)
        lanes[lane].append((start, end))
    split, claimed = {}, []
    for name in SOURCE_LANES:
        before = interval_bytes(claimed)
        claimed += lanes[name]
        split[name] = interval_bytes(claimed) - before
    split["recovered"] = split["authored"] + split["vendored"]
    return split


def real_code_denominator(text_start, text_size):
    """Return (0xCC padding bytes, real code bytes) across the whole section.

    This is the denominator the porting effort is actually measured against:
    3.3 MB of the section is inter-function 0xCC filler that no one will ever
    port, including a single 982,242-byte block at 0xB028EE. Counted over the
    whole section rather than over unclaimed gaps so the denominator does not
    drift every time a function is matched.
    """
    return padding_split(build.read_target_bytes(text_start, text_size))


def percent(count, total):
    return 100.0 * count / total if total else 0.0


def format_delta(current, previous, total):
    byte_delta = current - previous
    return f"{byte_delta:+,} bytes, {percent(byte_delta, total):+.2f} pp"


def print_scorecard(ref1, label2, old_stats, new_stats):
    total = new_stats["text"]
    print(f"\nretail .text exact coverage {ref1} -> {label2} ({total:,} bytes)")
    rows = (
        ("C++ exact", "cpp"),
        ("ASM-only exact", "asm_only"),
        ("Unmatched", "unmatched"),
        ("Total exact", "exact"),
    )
    for label, key in rows:
        value = new_stats[key]
        delta = format_delta(value, old_stats[key], total)
        print(f"  {label:<15} {value:>10,} bytes ({percent(value, total):6.2f}%)"
              f"  delta {delta}")


def rebuildable(split):
    """Bytes we can produce without consulting retail.

    The project is graded on one question: how much of game.dat can we
    rebuild from what we hold? A byte qualifies when its source of truth lives
    in this repo -- C++ someone wrote, upstream library source we compile, a
    deterministic generator we own, or a prebuilt .lib we attach. Who first
    authored it does not enter into it; nobody at EA hand-wrote the unwind
    funclets either, and a 1:1 build does not require us to hand-write d3dx9.

    A byte-true dump is the one lane that fails the test: the source file
    contains retail's own bytes, so deleting game.dat would delete the
    thing we claim to hold. Dumps fix a boundary and say nothing else.
    """
    return split["authored"] + split["vendored"] + split["generated"] + split["library"]


LINK_STATUS = "reverse/link_status.csv"
LINK_HISTORY = "reverse/link_census_history.csv"
# Source somebody recovered: C++ written from the disassembly and upstream
# library source. Generated C++ stays out, for the reason source_lane gives.
DECOMPILED_LANES = ("authored", "vendored")


def _text_at(ref, path):
    if ref is None:
        target = ROOT / path
        return target.read_text(encoding="utf-8") if target.exists() else None
    result = subprocess.run(["git", "show", f"{ref}:{path}"], cwd=ROOT, capture_output=True,
                            text=True, encoding="utf-8", errors="replace")
    return result.stdout if result.returncode == 0 else None


@lru_cache(maxsize=None)
def _text_image():
    start, size = retail_text()
    return start, build.read_target_bytes(start, size)


def real_split(matched, notes, text_start, text_size, naked_rows=(), keep=None):
    """source_split counted the way real_code_denominator counts: 0xCC bytes
    excluded, so numerator and denominator agree (source_split counts a row's
    0xCC bytes, about 0.16 pp of the headline). `keep(key, source)` filters rows."""
    image_start, image = _text_image()
    text_end = text_start + text_size
    naked_rows = set(naked_rows)
    lanes = {name: [] for name in SOURCE_LANES}
    for key, (size, source) in matched.items():
        if keep and not keep(key, source):
            continue
        start, end = max(int(key[1], 16), text_start), min(int(key[1], 16) + size, text_end)
        if start < end:
            lanes[source_lane(source, notes[key], key in naked_rows)].append((start, end))

    def real(intervals):
        return sum(end - start - image[start - image_start:end - image_start].count(0xCC)
                   for start, end in merge_intervals(intervals))
    split, claimed = {}, []
    for name in SOURCE_LANES:
        before = real(claimed)
        claimed += lanes[name]
        split[name] = real(claimed) - before
    return split


def decompiled(split):
    """Recovered source that compiles to retail's bytes, a function at a time."""
    return sum(split[lane] for lane in DECOMPILED_LANES)


def census_rows_at(ref):
    """Every census row that measured LINKED, in physical (append) order."""
    history = _text_at(ref, LINK_HISTORY)
    return [row for row in csv.DictReader(history.splitlines()) if row.get("linked_bytes")] if history else []


def census_at(ref):
    """The last link census that measured LINKED, as of one state, or None.

    LINKED is measured by tools/link_census.py on the tree it linked and stored
    in the history row (linked_bytes); it is not recomputed here, so it holds
    still between censuses instead of dropping with every edit since. The
    last physical row is the current one: rows are appended in order.
    """
    rows = census_rows_at(ref)
    return rows[-1] if rows else None


# The rules a census row was measured under (link_census.py's `rules`
# column). Rows from before the column are link_census.LEGACY_RULES.
LEGACY_CENSUS_RULES = "majority-0"


def census_rules(row):
    return ((row or {}).get("rules") or "").strip() or LEGACY_CENSUS_RULES


def census_prev_figure(row, field):
    """The row's *_prev_rule figure for `field` and the rules it was measured
    under, or (None, None)."""
    value = (row or {}).get(f"{field}_prev_rule")
    if not value:
        return None, None
    return int(value), ((row.get("prev_rules") or "").strip() or LEGACY_CENSUS_RULES)


def census_change(old, new, field, over_field, rows, denominator=None):
    """The change in one census figure from `old` to `new` (history rows),
    compared like for like when the census rules changed in between.

    Returns {"bytes", "pp"} for a same-rules change, plus "rule_changes" (a
    list of (row, before_rules, after_rules, before_pp, after_pp)) when one or
    more re-baseline rows lie in between: the change is then the sum of the
    changes within each rule, the re-baseline's prev_rule figure being the
    old rules' measurement of the same objects. None when no like-for-like
    comparison exists (a rule change without the previous rules' figures)."""
    def pair(row, value=None):
        over = int(row[over_field]) if over_field else denominator
        return (int(row[field]) if value is None else value), over
    if census_rules(old) == census_rules(new) and not _transitions(old, new, rows):
        (a, x), (b, y) = pair(old), pair(new)
        return {"bytes": b - a, "pp": percent(b, y) - percent(a, x), "rule_changes": []}
    changes = _transitions(old, new, rows)
    if not changes:
        return None
    total_bytes, total_pp, current, notes = 0, 0.0, old, []
    for row in changes:
        prev, prev_rules = census_prev_figure(row, field)
        if prev is None or prev_rules != census_rules(current):
            return None
        (a, x), (b, y) = pair(current), pair(row, prev)
        total_bytes += b - a
        total_pp += percent(b, y) - percent(a, x)
        (c, z) = pair(row)
        notes.append((row, prev_rules, census_rules(row), percent(b, y), percent(c, z)))
        current = row
    (a, x), (b, y) = pair(current), pair(new)
    return {"bytes": total_bytes + b - a, "pp": total_pp + percent(b, y) - percent(a, x), "rule_changes": notes}


def _transitions(old, new, rows):
    """The rows after `old`, up to and including `new`, whose rules differ
    from the row before them (re-baselines), in order."""
    keys = [(r.get("date"), r.get("commit")) for r in rows]
    try:
        start = keys.index((old.get("date"), old.get("commit")))
        end = keys.index((new.get("date"), new.get("commit")))
    except ValueError:
        return []
    return [rows[i] for i in range(start + 1, end + 1) if census_rules(rows[i]) != census_rules(rows[i - 1])]


def data_denominator():
    """Bytes of .rdata and .data: the tables, strings and globals."""
    return sum(s["size"] for s in build.pe_sections(build.EXE.read_bytes()) if s["name"] in (".rdata", ".data"))


def game_code(split, denominator):
    """The game's own code: all real code minus vendored library source and
    prebuilt libraries (readme_progress.game_code, the C++ and Linking bars)."""
    return denominator - split["vendored"] - split["library"]


def _line(label, value, denominator, delta, note):
    return (f"{label:<14} {value:>12,.0f} bytes ({percent(value, denominator):6.2f}%)  {delta}  <- {note}")


def print_headline(padding, denominator, old_split, new_split, old_census, new_census, census_rows=()):
    """The README card's and the daily Discord post's three numbers, computed
    the same way, then what they are made of. Every figure counts 0xCC out,
    so the lines below add up to the lines above."""
    matched, before = rebuildable(new_split), rebuildable(old_split)
    game, game_before = game_code(new_split, denominator), game_code(old_split, denominator)
    print(_line("BYTE-MATCHED", matched, denominator, f"delta {format_delta(matched, before, denominator)}",
                "rebuilt from source: rebuilds to game.dat's exact bytes"))
    print(_line("GAME CODE C++", new_split["authored"], game,
                f"delta {format_delta(new_split['authored'], old_split['authored'], game)}"
                if game == game_before else "delta n/a (the game's own code changed size)",
                f"C++ we wrote, over the game's own code ({game:,} bytes: no library source or .lib)"))

    def census_line(label, field, over_field, note):
        """One census figure over its denominator: `over_field` names the
        census column holding it, or None for all code (fixed)."""
        def figure(census):
            if not census or not census.get(field) or (over_field and not census.get(over_field)):
                return None
            return int(census[field]), int(census[over_field]) if over_field else denominator
        now = figure(new_census)
        if now is None:
            print(f"{label:<14} not measured  <- no census stored {field} yet (tools/link_census.py --history)")
            return
        # A range that starts before any census has nothing to compare with;
        # showing the whole figure as a gain would credit it to that range.
        was = figure(old_census)
        if not was:
            delta = f"delta n/a (no {label} figure stored at the start of the range)"
        else:
            # A change of census rules is not progress: compare within rules.
            change = census_change(old_census, new_census, field, over_field, list(census_rows) or
                                   [old_census, new_census], denominator)
            if change is None:
                delta = (f"delta n/a (census rules changed: {census_rules(old_census)} -> "
                         f"{census_rules(new_census)}, no like-for-like figure)")
            else:
                delta = f"delta {change['bytes']:+,} bytes, {change['pp']:+.2f} pp"
                for row, before, after, at_before, at_after in change["rule_changes"]:
                    delta += (f" within rules; RULES CHANGED {row['date'][:10]} ({before} -> {after}: "
                              f"{at_before:.2f}% -> {at_after:.2f}% on the same objects, not progress)")
        print(_line(label, now[0], now[1], delta, f"{note}, census {new_census['date']} at {new_census['commit']}"
                    f" ({census_rules(new_census)})"))
    census_line("LINKING", "linked_authored", "game_code",
                "that C++ in files that link cleanly, over the census tree's game code")
    print("               (the three figures on the README card and in the daily Discord post)")
    census_line("LINKED", "linked_bytes", None, "all our own source in files that link cleanly (the chart)")

    print(f"\nreal code = .text minus {padding:,} bytes of 0xCC padding = {denominator:,} bytes")
    print("  byte-matched, by where its source comes from:")
    for label, key in (("C++ we wrote", "authored"), ("vendored library source", "vendored"),
                       ("generator-written C++", "generated"), ("prebuilt .lib attached", "library")):
        print(f"    {label:<24} {new_split[key]:>10,} bytes ({percent(new_split[key], denominator):6.2f}%)"
              f"  delta {format_delta(new_split[key], old_split[key], denominator)}")
    unclaimed = denominator - sum(new_split[lane] for lane in SOURCE_LANES)
    print("  not byte-matched:")
    print(f"    {'still only retail bytes':<24} {new_split['dump']:>10,} bytes "
          f"({percent(new_split['dump'], denominator):6.2f}%)  <- dumps: a boundary, nothing more")
    print(f"    {'unclaimed':<24} {unclaimed:>10,} bytes ({percent(unclaimed, denominator):6.2f}%)"
          "  <- no boundary proven yet")
    own, own_before = decompiled(new_split), decompiled(old_split)
    print(f"  our own source (C++ we wrote + library source) {own:,} bytes ({percent(own, denominator):.2f}%)"
          f"  delta {format_delta(own, own_before, denominator)}")
    print(f"GAME DATA      not measured  <- {data_denominator():,} bytes of .rdata/.data; no data is byte-verified yet")


def marker_delta(ref1, ref2):
    """Net present-unmatched/absent-from-retail markers added between states."""
    cmd = ["git", "diff", ref1] + ([ref2] if ref2 else []) + ["--", "Code"]
    # Original engine sources include legacy-encoded copyright comments. The
    # markers are ASCII, so undecodable comment bytes must not stop the audit.
    diff = subprocess.run(cmd, cwd=ROOT, capture_output=True, text=True,
                          encoding="utf-8", errors="replace", check=True).stdout
    added = removed = 0
    for line in diff.splitlines():
        if line.startswith("+++") or line.startswith("---"):
            continue
        if "present-unmatched" in line or "absent-from-retail" in line:
            if line.startswith("+"):
                added += 1
            elif line.startswith("-"):
                removed += 1
    return added - removed


def area(source):
    parts = source.split("/")
    return "/".join(parts[:2]) if len(parts) > 1 else source


def asm_diagnostics(matched, naked_rows):
    naked_rows = set(naked_rows)
    sources = {
        source for key, (_, source) in matched.items()
        if Path(source).suffix.lower() in ASM_SUFFIXES or key in naked_rows
    }
    rows = sum(
        1 for key, (_, source) in matched.items()
        if Path(source).suffix.lower() in ASM_SUFFIXES or key in naked_rows
    )
    return rows, len(sources)


def print_details(ref1, ref2, old, new, old_naked=(), new_naked=()):
    added = {name: new[name] for name in new.keys() - old.keys()}
    removed = {name: old[name] for name in old.keys() - new.keys()}
    print("\nledger details (diagnostics, not unique-byte progress)")
    print(f"  matched rows:      {len(old):,} -> {len(new):,}"
          f"  (+{len(added):,}, -{len(removed):,})")
    print(f"  distinct RVAs:     {len({int(rva, 16) for _, rva in old}):,}"
          f" -> {len({int(rva, 16) for _, rva in new}):,}")
    old_asm_rows, old_asm_files = asm_diagnostics(old, old_naked)
    new_asm_rows, new_asm_files = asm_diagnostics(new, new_naked)
    print(f"  ASM-backed rows:   {old_asm_rows:,} -> {new_asm_rows:,}")
    print(f"  ASM-bearing files: {old_asm_files:,} -> {new_asm_files:,}")
    print(f"  unclaimed markers: {marker_delta(ref1, ref2):+d}")

    if added:
        by_area = Counter()
        by_file = Counter()
        for _, source in added.values():
            by_area[area(source)] += 1
            by_file[source] += 1
        print("  added by area: "
              + ", ".join(f"{name} +{count}" for name, count in by_area.most_common()))
        print("  top added files:")
        for source, count in by_file.most_common(10):
            print(f"    +{count:<4d} {source}")
    if removed:
        print("  removed rows:")
        for (name, _), (size, source) in sorted(removed.items())[:10]:
            print(f"    -{size:<5d} {source}  {name[:60]}")


def parse_range(value):
    if ".." in value:
        ref1, _, ref2 = value.partition("..")
        return ref1, ref2 or None
    return value, None


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter)
    parser.add_argument("range", nargs="?", default="HEAD",
                        help="REF (vs worktree) or REF1..REF2")
    parser.add_argument("--details", action="store_true",
                        help="show row, RVA, marker, area, and file diagnostics")
    args = parser.parse_args()

    ref1, ref2 = parse_range(args.range)
    old = matched_at(ref1)
    new = matched_at(ref2)
    text_start, text_size = retail_text()
    old_naked = naked_cpp_rows_at(old, ref1)
    new_naked = naked_cpp_rows_at(new, ref2)
    old_stats = coverage(old, text_start, text_size, old_naked)
    new_stats = coverage(new, text_start, text_size, new_naked)
    label2 = ref2 or "worktree"

    padding, denominator = real_code_denominator(text_start, text_size)
    old_notes, new_notes = notes_at(ref1), notes_at(ref2)
    print_headline(padding, denominator, real_split(old, old_notes, text_start, text_size, old_naked),
                   real_split(new, new_notes, text_start, text_size, new_naked), census_at(ref1), census_at(ref2),
                   census_rows_at(ref2))
    print_scorecard(ref1, label2, old_stats, new_stats)
    if args.details:
        print_details(ref1, ref2, old, new, old_naked, new_naked)
    print("\nledger-derived; a clean build.sh run is the byte-match proof.")


if __name__ == "__main__":
    main()
