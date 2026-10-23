#!/usr/bin/env python3
"""Refuse a function row that stops short of the body it compiles.

Byte verification compares the first `target_size` bytes of the compiled
function with retail, so a row claiming fewer bytes than the function has
still passes: the tail it leaves out is never compared, and the next row (or
the gap report) inherits bytes nobody verified. Two rows landed 2 bytes short
this way. This gate measures each new or changed row's compiled function
(from its symbol to the next symbol in the section, or the section end, less
trailing int3 padding) and refuses a row shorter than that.

    row_extent.py --staged   rows the staged functions.csv adds or changes
    row_extent.py --audit    every matched row whose object is already built
Objects come from the build cache; run after the byte verification that
built them. A row whose object is missing or not current for its source, or
whose symbol is unavailable, is skipped (an --audit over stale objects once
flagged two rows whose source had since changed).
"""
import argparse
import csv
import io
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, str(Path(__file__).resolve().parent))
import build  # noqa: E402

ROOT = build.ROOT
LEDGER = "reverse/functions.csv"


def natural_length(output, symbol):
    """Compiled length of `symbol` in object `output`, or None."""
    stat = output.stat()
    data, sections, symbols = build._object_layout(str(output), stat.st_mtime_ns, stat.st_size)
    for sym in symbols:
        if sym["name"] != symbol or sym["section"] <= 0:
            continue
        section = sections[sym["section"] - 1]
        if not section["characteristics"] & 0x20:  # not code
            return None
        start = sym["value"]
        following = [s["value"] for s in symbols
                     if s["section"] == sym["section"] and s["value"] > start]
        end = min(following) if following else section["raw_size"]
        body = data[section["raw_pointer"] + start:section["raw_pointer"] + end]
        return len(body.rstrip(b"\xcc"))
    return None


def rows_of(text):
    return {(r["name"], r["target_rva"].lower()): r
            for r in csv.DictReader(io.StringIO(text)) if r.get("status") == "matched"}


def git_show(spec):
    out = subprocess.run(["git", "show", spec], cwd=ROOT, capture_output=True, text=True)
    return out.stdout if out.returncode == 0 else ""


def checked(row):
    """(row size, compiled length) when the row can be measured, else None."""
    source = row.get("source", "")
    if not source.lower().endswith((".cpp", ".c")) or source.startswith(("Code/gen_asm/", "Code/gen_small/")):
        return None
    if "gen-alias" in (row.get("notes") or ""):
        return None  # a second address for a body measured at its first
    symbol = build.ledger_object_symbol(row)
    if build.is_funclet_row(row, symbol):
        return None
    output = build.row_object(row)
    if not output.exists():
        return None
    import link_census
    if not link_census.object_current(ROOT / source, output):
        return None  # a cached object from older source: its length is not this row's
    length = natural_length(output, symbol)
    if length is None:
        return None
    return int(row["target_size"]), length


def main(argv=None):
    parser = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    mode = parser.add_mutually_exclusive_group(required=True)
    mode.add_argument("--staged", action="store_true")
    mode.add_argument("--audit", action="store_true")
    args = parser.parse_args(argv)
    now = rows_of(git_show(f":{LEDGER}") if args.staged else (ROOT / LEDGER).read_text(encoding="utf-8"))
    if args.staged:
        before = rows_of(git_show(f"HEAD:{LEDGER}"))
        rows = [r for k, r in now.items() if before.get(k) != r]
    else:
        rows = list(now.values())
    short = []
    for row in rows:
        measured = checked(row)
        if measured and measured[1] > measured[0]:
            short.append((row, *measured))
    for row, size, length in short:
        print(f"  SHORT {row['name']} @{row['target_rva']}: the row claims {size}B but its "
              f"compiled function is {length}B ({row['source']}); the last {length - size} "
              "byte(s) are never verified. Check retail's real end and set target_size.",
              file=sys.stderr)
    if args.audit:
        print(f"row_extent: {len(short)} short row(s) of {len(rows)} matched")
    return 1 if short and args.staged else 0


if __name__ == "__main__":
    sys.exit(main())
