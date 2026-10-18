#!/usr/bin/env python3
"""Behaviour-verify a NON-exact body against retail (functional branch only).

Compiles one standalone C++ TU (a banked attempt, a farm best, or a body under
functional/src/), takes the named function out of the object, and runs it next
to retail's bytes in tools/diffexec.py's x86 emulator on identical inputs with
every callee stubbed. Unlike master's gate this accepts a body of a different
LENGTH: the compared extent is the longer of the two and the shorter body is
padded with int3 (a retail jump past its own end, or a rebuilt one past its
own body, would be a divergence anyway).

Verdicts (tools/diffexec.py): none / regalloc-only = same return value, memory
writes and call sequence on every input vector -> passes; logic, binding,
build_env, inconclusive -> does not pass. With --record the result is written
to functional/ledger.csv (one row per RVA, replaced on re-verification) and the
full record to functional/receipts/<rva>.json.

usage (checkout root, a Python with `unicorn`):
  functional/tools/fn_verify.py --bank 0x00191C10 [--record]
  functional/tools/fn_verify.py --source functional/src/X.cpp --name '?f@C@@QAEXXZ' --rva 0x... --size N [--record]
  functional/tools/fn_verify.py --all-banks [--record] [--jobs 8] [--limit N]
"""
import argparse
import concurrent.futures
import csv
import datetime
import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
LEDGER = ROOT / "functional" / "ledger.csv"
RECEIPTS = ROOT / "functional" / "receipts"
WORK = ROOT / "build" / "fn"
PASS = {"none", "regalloc-only", "tested"}
FIELDS = ["name", "target_rva", "target_size", "source", "verdict", "evidence", "date"]


def bank_symbol(rva):
    """(symbol, size) for a banked attempt: the newest re_attempts.log line for the RVA."""
    sym = size = None
    key = f"0x{rva:08x}"
    with open(ROOT / "reverse" / "re_attempts.log", encoding="utf-8", errors="replace") as f:
        for line in f:
            p = line.split("\t")
            if len(p) > 3 and p[1].lower() == key and p[0].startswith("?"):
                sym, size = p[0], int(p[2], 0)
    return sym, size


def compile_body(text, rva, sym, size):
    import build
    import includes
    text, _ = includes.resolve(text, ROOT)
    wd = WORK / f"{rva:08x}"
    wd.mkdir(parents=True, exist_ok=True)
    src = wd / "cand.cpp"
    out = src.with_suffix(".obj")
    src.write_text(text, encoding="latin-1", errors="replace")
    ok, msg, _ = build.try_compile_source(src, out)
    if not ok:
        raise LookupError("compile failed: " + (msg or "")[-300:])
    compiled, relocs, info = build.read_object_symbol_bytes(out, sym, None, detail=True)
    stat = out.stat()
    objdata, sections, _ = build._object_layout(str(out), stat.st_mtime_ns, stat.st_size)
    return bytes(compiled).rstrip(b"\xcc"), relocs, info, objdata, sections


def verify(ctx, name, rva, size, text, source):
    import diffexec
    try:
        compiled, relocs, info, objdata, sections = compile_body(text, rva, name, size)
    except Exception as e:  # noqa: BLE001 - recorded, never hidden
        return dict(name=name, rva=f"0x{rva:08X}", size=size, source=source, verdict="inconclusive",
                    reason=f"{type(e).__name__}: {e}"[:300])
    extent = max(size, len(compiled))
    body = compiled + b"\xcc" * (extent - len(compiled))
    row = {"name": name, "target_rva": f"0x{rva:08X}", "target_size": str(extent), "source": source}
    try:
        rec = diffexec.diff_row(ctx, row, body, relocs, info, objdata, sections, budget_ms=4000)
    except Exception as e:  # noqa: BLE001
        rec = dict(name=name, rva=f"0x{rva:08X}", verdict="inconclusive", reason=f"harness: {type(e).__name__}: {e}"[:300])
    rec.update(size=size, rebuilt_size=len(compiled), source=source)
    return rec


def record(rec):
    RECEIPTS.mkdir(parents=True, exist_ok=True)
    rva = int(rec["rva"], 16)
    receipt = RECEIPTS / f"0x{rva:08x}.json"
    receipt.write_text(json.dumps(rec, indent=1, default=str))
    rows = list(csv.DictReader(LEDGER.open(encoding="utf-8"))) if LEDGER.exists() else []
    rows = [r for r in rows if int(r["target_rva"], 16) != rva]
    rows.append(dict(name=rec["name"], target_rva=f"0x{rva:08X}", target_size=str(rec["size"]),
                     source=rec["source"], verdict=rec["verdict"],
                     evidence=receipt.relative_to(ROOT).as_posix(),
                     date=datetime.date.today().isoformat()))
    rows.sort(key=lambda r: int(r["target_rva"], 16))
    with LEDGER.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, FIELDS, lineterminator="\n")
        w.writeheader()
        w.writerows(rows)


_CTX = None


def _init():
    global _CTX
    import diffexec
    _CTX = diffexec.load_context()


def _bank_job(rva):
    sym, size = bank_symbol(rva)
    path = ROOT / "reverse" / "attempts" / f"0x{rva:08x}.cpp"
    if not sym or not size or not path.exists():
        return dict(name=sym or "?", rva=f"0x{rva:08X}", size=size or 0, verdict="inconclusive",
                    reason="no symbol/size in re_attempts.log or no bank", source=str(path))
    text = path.read_text(encoding="latin-1")
    return verify(_CTX, sym, rva, size, text, path.relative_to(ROOT).as_posix())


def unmatched_banks():
    """Banked attempts whose RVA has no matched ledger row (the work this branch can promote)."""
    matched = set()
    with open(ROOT / "reverse" / "functions.csv", encoding="utf-8", errors="replace") as f:
        for r in csv.DictReader(f):
            if r["status"] == "matched":
                try:
                    matched.add(int(r["target_rva"], 16))
                except ValueError:
                    pass
    out = []
    for p in sorted((ROOT / "reverse" / "attempts").glob("0x*.cpp")):
        rva = int(p.stem, 16)
        if rva not in matched:
            out.append(rva)
    return out


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--bank", help="0xRVA of a banked attempt (reverse/attempts/<rva>.cpp)")
    ap.add_argument("--source")
    ap.add_argument("--name")
    ap.add_argument("--rva")
    ap.add_argument("--size", type=int)
    ap.add_argument("--all-banks", action="store_true")
    ap.add_argument("--limit", type=int)
    ap.add_argument("--jobs", type=int, default=1)
    ap.add_argument("--record", action="store_true")
    a = ap.parse_args()
    os.chdir(ROOT)
    if a.all_banks:
        rvas = unmatched_banks()[: a.limit or None]
        print(f"{len(rvas)} unmatched banks", file=sys.stderr, flush=True)
        with concurrent.futures.ProcessPoolExecutor(a.jobs, initializer=_init) as ex:
            for rec in ex.map(_bank_job, rvas):
                print(json.dumps({k: rec.get(k) for k in ("rva", "name", "size", "rebuilt_size", "verdict", "reason")},
                                 default=str)[:400], flush=True)
                if a.record and rec.get("verdict") in PASS:
                    record(rec)
        return
    _init()
    if a.bank:
        rec = _bank_job(int(a.bank, 16))
    else:
        text = (ROOT / a.source).read_text(encoding="latin-1")
        rec = verify(_CTX, a.name, int(a.rva, 16), a.size, text, a.source)
    print(json.dumps(rec, indent=1, default=str)[:3000])
    if a.record:
        record(rec)


if __name__ == "__main__":
    main()
