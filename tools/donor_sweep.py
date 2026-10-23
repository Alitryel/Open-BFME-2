#!/usr/bin/env python3
"""Find BFME 2 bodies in BFME 1 donor sources by recompiling them the BFME 2
way (/O1) and placing each emitted body in retail by masked byte search.

bfme1_sweep.py compares BFME 1's *bytes* with BFME 2's, so it misses every
function whose BFME 1 build used other flags: BFME 1 shipped much of its code
/O2 and BFME 2 rebuilt it /O1. Recompiling a clean donor unit at /O1 and
searching its bodies the way place_bodies.py does (relocation bytes masked,
exactly one hit in .text, not inside a body the ledger already holds) turns
those into leads. A placement is a lead, never proof: the body is ported into
the proper Code/ unit and lands through add_match and the gates like any other.

Resumable: every donor file's outcome is appended to
build/donor_sweep/results.jsonl, and a rerun skips files already there.

  python3 tools/donor_sweep.py [--jobs N] [--limit N]     # sweep (resumes)
  python3 tools/donor_sweep.py --report [--min 20]        # placements as leads
  python3 tools/donor_sweep.py --pins [--apply]           # callee pins from placements
"""
import argparse
import collections
import concurrent.futures
import json
import os
import re
import subprocess
import sys
from pathlib import Path

sys.path.insert(0, os.path.dirname(os.path.abspath(__file__)))
import build  # noqa: E402

DONORS = build.ROOT / "reference" / "open-bfme-1" / "game"
OUT = build.ROOT / "build" / "donor_sweep"
RESULTS = OUT / "results.jsonl"
DUMP = re.compile(rb"__declspec\s*\(\s*naked\s*\)|__emit\b|\b_?_asm\b")
PLACEABLE = re.compile(r"^(\?|_[A-Za-z_]\w*(@\d+)?$)")


def donors():
    """Clean C++ donor units: no dumps, lifts or generated placeholders."""
    out = []
    for path in sorted(DONORS.rglob("*.cpp")):
        rel = path.relative_to(DONORS).as_posix()
        if "gen_" in rel or "masm" in rel.lower():
            continue
        try:
            if DUMP.search(path.read_bytes()):
                continue
        except OSError:
            continue
        out.append(path)
    return out


_TEXT = None


def _text():
    global _TEXT
    if _TEXT is None:
        image, sections = build.exe_image()
        text = next(s for s in sections if s["name"] == ".text")
        _TEXT = (image[text["raw_pointer"]:text["raw_pointer"] + text["size"]], text["rva"])
    return _TEXT


def sweep_one(path, minimum=20):
    """Compile one donor at /O1 and place its emitted bodies. Never raises."""
    rel = path.relative_to(build.ROOT).as_posix()
    obj = OUT / "obj" / (re.sub(r"[^\w.-]", "_", rel) + ".obj")
    obj.parent.mkdir(parents=True, exist_ok=True)
    try:
        command, env = build.compiler_command(path, obj)
        done = subprocess.run(command + ["-O1"], cwd=build.ROOT, env=env, capture_output=True,
                              text=True, errors="replace", timeout=180)
        if done.returncode != 0 or not obj.exists():
            return {"file": rel, "status": "compile failed"}
        blob, text_rva = _text()
        placements = []
        for name in sorted(build.defined_code_symbols(obj)):
            if not PLACEABLE.match(name):
                continue
            try:
                body, relocs = build.read_object_symbol_bytes(obj, name)
            except Exception:
                continue
            body = body.rstrip(b"\xcc")
            if len(body) < minimum:
                continue
            fixed = bytearray(b"\x01" * len(body))
            for offset, _kind, _symbol in relocs:
                fixed[offset:offset + 4] = b"\0" * len(fixed[offset:offset + 4])
            pattern = b"".join(re.escape(bytes([b])) if fixed[i] else b"." for i, b in enumerate(body))
            hits = [m.start() + text_rva for m in re.finditer(pattern, blob, re.DOTALL)]
            if len(hits) == 1:
                # each REL32 in a placed body is a byte-true call site: retail's
                # displacement there is the callee's address
                calls = {}
                for offset, kind, callee in relocs:
                    if kind == 0x0014 and offset + 4 <= len(body):
                        at = hits[0] - text_rva + offset
                        displacement = int.from_bytes(blob[at:at + 4], "little", signed=True)
                        calls[callee] = f"0x{(hits[0] + offset + 4 + displacement) & 0xFFFFFFFF:08X}"
                placements.append({"name": name, "rva": f"0x{hits[0]:08X}", "size": len(body), "calls": calls})
        return {"file": rel, "status": "ok", "placements": placements}
    except Exception as error:  # a sweep over 20k files must not stop on one
        return {"file": rel, "status": f"error: {str(error)[:120]}"}
    finally:
        obj.unlink(missing_ok=True)


def sweep(jobs, limit):
    OUT.mkdir(parents=True, exist_ok=True)
    done = set()
    if RESULTS.exists():
        for line in RESULTS.read_text().splitlines():
            try:
                done.add(json.loads(line)["file"])
            except (ValueError, KeyError):
                pass
    todo = [p for p in donors() if p.relative_to(build.ROOT).as_posix() not in done]
    if limit:
        todo = todo[:limit]
    print(f"donor_sweep: {len(done):,} done, {len(todo):,} to go", flush=True)
    placed = 0
    with concurrent.futures.ProcessPoolExecutor(max(1, jobs)) as pool, RESULTS.open("a") as out:
        for count, result in enumerate(pool.map(sweep_one, todo, chunksize=4), 1):
            out.write(json.dumps(result) + "\n")
            out.flush()
            placed += len(result.get("placements", []))
            if count % 200 == 0:
                print(f"  {count:,}/{len(todo):,} files, {placed:,} placements", flush=True)
    print(f"donor_sweep: swept {len(todo):,} files, {placed:,} placements; --report lists the leads")


def report(minimum):
    """Placements as leads: one name per address, not in a ledger body, not
    already a ledger name, biggest first."""
    rows = build.load_all_function_rows()
    names = {r["name"] for r in rows}
    claimed = sorted((int(r["target_rva"], 16), int(r["target_rva"], 16) + int(r["target_size"])) for r in rows)
    starts = [s for s, _ in claimed]

    def owned(rva):
        import bisect
        i = bisect.bisect_right(starts, rva) - 1
        return i >= 0 and claimed[i][0] <= rva < claimed[i][1]

    by_address = collections.defaultdict(set)
    detail = {}
    for line in RESULTS.read_text().splitlines():
        entry = json.loads(line)
        for p in entry.get("placements", []):
            if p["size"] >= minimum:
                by_address[p["rva"]].add(p["name"])
                detail[(p["rva"], p["name"])] = (p["size"], entry["file"])
    leads = []
    for rva, found in by_address.items():
        if len(found) != 1:
            continue  # folded or ambiguous: picking one would invent an identity
        name = next(iter(found))
        if name in names or owned(int(rva, 16)):
            continue
        size, source = detail[(rva, name)]
        leads.append((size, rva, name, source))
    leads.sort(reverse=True)
    for size, rva, name, source in leads:
        print(f"{rva}\t{size}\t{name}\t{source}")
    print(f"donor_sweep: {len(leads):,} leads, {sum(l[0] for l in leads):,} bytes", file=sys.stderr)


def pins(apply):
    """Callee addresses read from unique placements: a name every placement
    calls at one address, not a ledger name and not already pinned. With
    apply, append them to reverse/symbols.csv, keeping only what
    pin_consistency accepts."""
    import csv as _csv
    rows = build.load_all_function_rows()
    names = {r["name"] for r in rows}
    symbols = build.ROOT / "reverse" / "symbols.csv"
    with symbols.open(encoding="utf-8", newline="") as handle:
        pinned = {r["name"] for r in _csv.DictReader(handle)}
    by_address = collections.defaultdict(set)
    seen = collections.defaultdict(set)
    for line in RESULTS.read_text().splitlines():
        for p in json.loads(line).get("placements", []):
            by_address[p["rva"]].add(p["name"])
    for line in RESULTS.read_text().splitlines():
        for p in json.loads(line).get("placements", []):
            if len(by_address[p["rva"]]) != 1:
                continue  # a folded placement proves no single caller
            for callee, address in p.get("calls", {}).items():
                seen[callee].add(address)
    found = {c: next(iter(a)) for c, a in seen.items()
             if len(a) == 1 and c not in names and c not in pinned and not c.startswith("__imp_")}
    for callee, address in sorted(found.items(), key=lambda kv: kv[1]):
        print(f"{address}\t{callee}")
    print(f"donor_sweep: {len(found):,} candidate pins", file=sys.stderr)
    if not apply or not found:
        return
    import io as _io

    def check():
        return subprocess.run(["python3", "tools/pin_consistency.py", "--check"], cwd=build.ROOT,
                              capture_output=True, text=True).returncode == 0

    def append(items):
        out = _io.StringIO()
        writer = _csv.writer(out, lineterminator="\n")
        for callee, address in items:
            writer.writerow([callee, address, "donor_sweep: call target read from retail at a unique "
                                              "placement of a BFME 1 donor body compiled /O1"])
        text = symbols.read_text(encoding="utf-8")
        symbols.write_text(text + ("" if text.endswith("\n") else "\n") + out.getvalue(), encoding="utf-8")

    original = symbols.read_text(encoding="utf-8")
    append(found.items())
    if check():
        print(f"donor_sweep: {len(found):,} pins added", file=sys.stderr)
        return
    symbols.write_text(original, encoding="utf-8")
    kept = 0
    for item in sorted(found.items()):
        before = symbols.read_text(encoding="utf-8")
        append([item])
        if check():
            kept += 1
        else:
            symbols.write_text(before, encoding="utf-8")
    print(f"donor_sweep: {kept:,} of {len(found):,} pins added (pin_consistency refused the rest)",
          file=sys.stderr)


def main(argv=None):
    ap = argparse.ArgumentParser(description=__doc__.split("\n\n")[0])
    ap.add_argument("--jobs", type=int, default=int(os.environ.get("BUILD_POOL", "4") or 4))
    ap.add_argument("--limit", type=int, default=0)
    ap.add_argument("--report", action="store_true")
    ap.add_argument("--min", type=int, default=20)
    ap.add_argument("--pins", action="store_true", help="list callee pins read from unique placements")
    ap.add_argument("--apply", action="store_true", help="with --pins: add them (pin_consistency-checked)")
    args = ap.parse_args(argv)
    if args.pins:
        pins(args.apply)
    elif args.report:
        report(args.min)
    else:
        sweep(args.jobs, args.limit)
    return 0


if __name__ == "__main__":
    sys.exit(main())
