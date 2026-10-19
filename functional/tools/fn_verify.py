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
FIELDS = ["name", "target_rva", "target_size", "source", "verdict", "coverage", "isomorphic", "evidence", "date", "mutation"]
NVEC = None   # adaptive: fn_exec.diff_body picks 128/48/16 by size


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


def verify(ctx, name, rva, size, text, source, mutate=None):
    import fn_exec
    if mutate:
        text = mutate(text)
        if text is None:
            return dict(name=name, rva=f"0x{rva:08X}", size=size, source=source, verdict="skipped", reason="no mutation site")
    try:
        compiled, relocs, info, objdata, sections = compile_body(text, rva, name, size)
    except Exception as e:  # noqa: BLE001 - recorded, never hidden
        return dict(name=name, rva=f"0x{rva:08X}", size=size, source=source, verdict="inconclusive",
                    reason=f"{type(e).__name__}: {e}"[:300])
    extent = max(size, len(compiled))
    body = compiled + b"\xcc" * (extent - len(compiled))
    row = {"name": name, "target_rva": f"0x{rva:08X}", "target_size": str(extent), "source": source}
    try:
        rec = fn_exec.diff_body(ctx, row, body, relocs, info, objdata, sections, nvec=NVEC, budget_ms=4000,
                                 retail_size=size)
    except Exception as e:  # noqa: BLE001
        rec = dict(name=name, rva=f"0x{rva:08X}", verdict="inconclusive", reason=f"harness: {type(e).__name__}: {e}"[:300])
    rec.update(size=size, rebuilt_size=len(compiled), source=source)
    return rec


def unrecord(rva):
    if not LEDGER.exists():
        return
    rows = list(csv.DictReader(LEDGER.open(encoding="utf-8")))
    keep = [r for r in rows if int(r["target_rva"], 16) != rva or r["verdict"] == "tested"]
    if len(keep) != len(rows):
        with LEDGER.open("w", encoding="utf-8", newline="") as f:
            w = csv.DictWriter(f, FIELDS, lineterminator="\n")
            w.writeheader()
            w.writerows(keep)


def body_span(text, name):
    """(start, end) of the function body of mangled `name` in text, or None."""
    try:
        import wb_gold
        d = wb_gold.demangle(name)
    except Exception:  # noqa: BLE001
        return None
    head = "::".join(d.scopes[-1:] + [d.name]) if d.scopes else d.name
    i = text.find(head + "(")
    while i >= 0:
        j = text.find("{", i)
        k = text.find(";", i)
        if j >= 0 and (k < 0 or j < k):
            depth = 0
            for p in range(j, len(text)):
                depth += {"{": 1, "}": -1}.get(text[p], 0)
                if depth == 0:
                    return j, p
        i = text.find(head + "(", i + 1)
    return None


MUTATIONS = [(r" < ", " <= "), (r" > ", " >= "), (" == ", " != "), (" != ", " == "), (" + ", " - "), (" && ", " || ")]


def mutants(name):
    """Callables text -> mutated text (one change inside the function body) or None."""
    import re as _re

    def make(pat, rep, nth):
        def f(text):
            span = body_span(text, name)
            if not span:
                return None
            body = text[span[0]:span[1]]
            hits = [m.start() for m in _re.finditer(_re.escape(pat), body)]
            if len(hits) <= nth:
                return None
            at = span[0] + hits[nth]
            return text[:at] + rep + text[at + len(pat):]
        f.label = f"{pat.strip()}->{rep.strip()}#{nth}"
        return f

    def lit(text):
        span = body_span(text, name)
        if not span:
            return None
        m = _re.search(r"(?<![\w.])([2-9]|[1-9]\d+)(?![\w.])", text[span[0]:span[1]])
        if not m:
            return None
        at = span[0] + m.start(1)
        return text[:at] + str(int(m.group(1)) + 1) + text[at + len(m.group(1)):]
    lit.label = "int+1"
    return [make(p, r, 0) for p, r in MUTATIONS] + [lit]


def record(rec):
    RECEIPTS.mkdir(parents=True, exist_ok=True)
    rva = int(rec["rva"], 16)
    receipt = RECEIPTS / f"0x{rva:08x}.json"
    receipt.write_text(json.dumps(rec, indent=1, default=str))
    rows = list(csv.DictReader(LEDGER.open(encoding="utf-8"))) if LEDGER.exists() else []
    def tier(v, iso, cov):
        if v == "tested":
            return 4
        if v in ("none", "regalloc-only"):
            if str(iso) in ("True", "true"):
                return 3
            try:
                return 2 if float(cov or 0) >= 0.5 else 1
            except ValueError:
                return 1
        return 0
    new_t = tier(rec.get("verdict"), rec.get("isomorphic"), rec.get("coverage"))
    for r in rows:
        if int(r["target_rva"], 16) == rva and tier(r["verdict"], r.get("isomorphic"), r.get("coverage")) > new_t:
            return                  # never replace a stronger result with a weaker one
    rows = [r for r in rows if int(r["target_rva"], 16) != rva]
    rows.append(dict(name=rec["name"], target_rva=f"0x{rva:08X}", target_size=str(rec["size"]),
                     source=rec["source"], verdict=rec["verdict"], coverage=str(rec.get("coverage", "")),
                     isomorphic=str(rec.get("isomorphic", "")),
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


def _mutant_job(job):
    rva, name, size, source, label = job
    m = next(f for f in mutants(name) if f.label == label)
    text = (ROOT / source).read_text(encoding="latin-1")
    rec = verify(_CTX, name, rva, size, text, source, mutate=m)
    v = rec.get("verdict")
    if v == "inconclusive" and "compile failed" in (rec.get("reason") or ""):
        v = "compile-failed"
    return (f"0x{rva:08X}", name[:50], label, rec.get("coverage"), rec.get("isomorphic"), v)


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
    ap.add_argument("--mutate", type=int, metavar="N", help="mutation test: N passing ledger rows, every mutant must fail")
    a = ap.parse_args()
    os.chdir(ROOT)
    if a.all_banks:
        fixed = {int(f.stem, 16) for f in (ROOT / "functional" / "src").glob("0x*.cpp")}
        rvas = [r for r in unmatched_banks() if r not in fixed][: a.limit or None]   # a fixed body outranks its bank
        print(f"{len(rvas)} unmatched banks", file=sys.stderr, flush=True)
        with concurrent.futures.ProcessPoolExecutor(a.jobs, initializer=_init) as ex:
            for rec in ex.map(_bank_job, rvas):
                out = {k: rec.get(k) for k in ("rva", "name", "size", "rebuilt_size", "verdict", "coverage", "isomorphic")}
                out["reason"] = str(rec.get("reason") or "")[:200]
                print(json.dumps(out, default=str), flush=True)
                if a.record and rec.get("verdict") in PASS:
                    record(rec)
                elif a.record and rec.get("verdict") not in ("skipped",):
                    unrecord(int(rec["rva"], 16))
        return
    if a.mutate:
        import random as _r
        rows = [r for r in csv.DictReader(LEDGER.open(encoding="utf-8")) if r["verdict"] in ("none", "regalloc-only")]
        _r.Random(7).shuffle(rows)
        jobs = []
        for r in rows[: a.mutate]:
            rva = int(r["target_rva"], 16)
            for m in mutants(r["name"]):
                jobs.append((rva, r["name"], int(r["target_size"]), r["source"], m.label))
        with concurrent.futures.ProcessPoolExecutor(a.jobs, initializer=_init) as ex:
            res = list(ex.map(_mutant_job, jobs))
        caught = sum(1 for x in res if x[-1] not in PASS and x[-1] not in ("skipped", "inconclusive"))
        tested = sum(1 for x in res if x[-1] not in ("skipped",) and not str(x[-1]).startswith("compile"))
        for x in res:
            print(json.dumps(x))
        strong_runs = [x for x in res if x[-1] not in ("skipped",) and not str(x[-1]).startswith("compile")
                       and (x[3] or 0) >= 0.5]
        strong_caught = sum(1 for x in strong_runs if x[-1] not in PASS and x[-1] != "inconclusive")
        print(json.dumps(dict(strong_rows_runs=len(strong_runs), strong_rows_caught=strong_caught)))
        print(json.dumps(dict(mutants=len(res), compiled_and_run=tested, caught=caught,
                              survived=[x[:5] for x in res if x[-1] in PASS])))
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
