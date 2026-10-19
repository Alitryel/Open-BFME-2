#!/usr/bin/env python3
"""Per-function mutation adequacy (functional branch).

A dynamic pass (fn_exec: retail and rebuilt executed side by side) is evidence only as far as the
input vectors exercise the function. This measures that, per function: mutate the function's own
body (comparison flips, ==/!=, &&/||, +/-, constants +1, at several places), compile each mutant,
drop equivalent ones (compiled body identical to the original), and run the dynamic check on the
rest. The kill rate = mutants the check rejects / mutants that changed the code.

A row whose body passes the dynamic check and whose vectors kill >= KILL_MIN of >= MIN_CHANGED
changed mutants is recorded as mutation-adequate (`mutation` column `killed/changed`), and
fn_progress.py counts it as strong even when it is not statically isomorphic (restructured but
correct bodies). Rejected-as-`inconclusive` mutants count as NOT killed.

Resumable: each result is written as soon as it is judged; rows that already have a `mutation`
value are skipped (--redo re-judges them).

usage (checkout root, Python with unicorn): functional/tools/fn_adequacy.py [--jobs 8] [--limit N] [--rva 0x...] [--redo]
       functional/tools/fn_adequacy.py --seed results.jsonl
"""
import argparse
import concurrent.futures
import csv
import json
import os
import re
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
sys.path.insert(0, str(Path(__file__).resolve().parent))
import fn_verify as V  # noqa: E402

KILL_MIN = 0.9
MIN_CHANGED = 5
OPS = [(" < ", " <= "), (" > ", " >= "), (" <= ", " < "), (" >= ", " > "), (" == ", " != "), (" != ", " == "),
       (" + ", " - "), (" - ", " + "), (" && ", " || "), (" || ", " && ")]
PLACES = 4
LITERALS = 3


def mutants(name, text):
    """[(label, mutated text)] inside the target function's body."""
    span = V.body_span(text, name)
    if not span:
        return []
    body = text[span[0]:span[1]]
    out = []
    for pat, rep in OPS:
        hits = [m.start() for m in re.finditer(re.escape(pat), body)][:PLACES]
        for k, h in enumerate(hits):
            at = span[0] + h
            out.append((f"{pat.strip()}->{rep.strip()}#{k}", text[:at] + rep + text[at + len(pat):]))
    for k, m in enumerate(re.finditer(r"(?<![\w.])([1-9]\d*)(?![\w.])", body)):
        if k >= LITERALS:
            break
        at = span[0] + m.start(1)
        out.append((f"int+1#{k}", text[:at] + str(int(m.group(1)) + 1) + text[at + len(m.group(1)):]))
    return out


_CTX = None


def _init():
    global _CTX
    V._init()
    _CTX = V._CTX


def judge(row):
    try:
        return _judge(row)
    except Exception as e:  # noqa: BLE001
        return dict(rva=row["target_rva"], error=f"harness: {type(e).__name__}: {e}"[:200])


def _judge(row):
    rva, name, size, source = int(row["target_rva"], 16), row["name"], int(row["target_size"]), row["source"]
    sha = V.source_sha1(source)
    text = (ROOT / source).read_text(encoding="latin-1")
    try:
        base = V.compile_body(text, rva, name, size)[0]
    except Exception as e:  # noqa: BLE001
        return dict(rva=f"0x{rva:08X}", error=f"original does not compile: {e}"[:200])
    changed = killed = 0
    survivors, inconclusive = [], 0
    for label, mtext in mutants(name, text):
        try:
            body = V.compile_body(mtext, rva, name, size)[0]
        except Exception:  # noqa: BLE001
            continue                                    # mutant does not compile: no information
        if body == base:
            continue                                    # equivalent mutant
        changed += 1
        rec = V.verify(_CTX, name, rva, size, mtext, source)
        v = rec.get("verdict")
        if v in ("logic", "binding", "build_env"):
            killed += 1
        else:
            if v == "inconclusive":
                inconclusive += 1
            survivors.append(label)
    return dict(rva=f"0x{rva:08X}", name=name, size=size, source=source, source_sha1=sha, changed=changed,
                killed=killed, inconclusive=inconclusive, survivors=survivors[:10],
                adequate=changed >= MIN_CHANGED and killed >= KILL_MIN * changed)


def write_result(res):
    """Record one judged row at once (main process only): the `mutation` column (killed/changed) and
    its receipt. Re-reads the ledger under fn_verify's lock; never touches verdicts. A row whose
    source changed since it was judged is left alone."""
    if "changed" not in res:
        return False
    rva = int(res["rva"], 16)
    with V.ledger_lock():
        rows = list(csv.DictReader(V.LEDGER.open(encoding="utf-8")))
        hit = [r for r in rows if int(r["target_rva"], 16) == rva]
        if not hit or (res.get("source") and hit[0]["source"] != res["source"]):
            return False
        if res.get("source_sha1") and V.source_sha1(hit[0]["source"]) != res["source_sha1"]:
            return False
        hit[0]["mutation"] = f"{res['killed']}/{res['changed']}"
        receipt = ROOT / "functional" / "receipts" / f"0x{rva:08x}.mutation.json"
        receipt.write_text(json.dumps(res, indent=1))
        with V.LEDGER.open("w", encoding="utf-8", newline="") as f:
            w = csv.DictWriter(f, V.FIELDS, lineterminator="\n", extrasaction="ignore")
            w.writeheader()
            w.writerows(rows)
    return True


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--rva")
    ap.add_argument("--redo", action="store_true", help="re-judge rows that already have a mutation value")
    ap.add_argument("--seed", help="record earlier results (JSON lines from a previous run) and exit; "
                                   "each is stamped with the current source's sha1")
    a = ap.parse_args()
    os.chdir(ROOT)
    if a.seed:
        led = {int(r["target_rva"], 16): r for r in csv.DictReader(V.LEDGER.open(encoding="utf-8"))}
        n = 0
        for line in Path(a.seed).read_text().splitlines():
            res = json.loads(line)
            r = led.get(int(res["rva"], 16))
            if "changed" not in res or not r:
                continue
            res.setdefault("source", r["source"])
            res.setdefault("source_sha1", V.source_sha1(res["source"]))
            n += write_result(res)
        print(f"seeded {n} rows", file=sys.stderr)
        return
    rows = list(csv.DictReader(V.LEDGER.open(encoding="utf-8")))
    todo = [r for r in rows if r["verdict"] in ("none", "regalloc-only") and r.get("isomorphic") != "True"]
    if not a.redo:
        todo = [r for r in todo if not r.get("mutation")]
    if a.rva:
        todo = [r for r in todo if int(r["target_rva"], 16) == int(a.rva, 16)]
    todo.sort(key=lambda r: -int(r["target_size"]))
    todo = todo[: a.limit or None]
    print(f"{len(todo)} passing, non-isomorphic rows to judge", file=sys.stderr, flush=True)
    results = []
    with concurrent.futures.ProcessPoolExecutor(a.jobs, initializer=_init) as ex:
        futs = [ex.submit(judge, r) for r in todo]
        for fu in concurrent.futures.as_completed(futs):
            try:
                res = fu.result()
            except Exception as e:  # noqa: BLE001  (a dead worker breaks the pool: rerun resumes)
                print(json.dumps(dict(error=f"{type(e).__name__}: {e}"[:200])), flush=True)
                continue
            res["recorded"] = write_result(res)
            print(json.dumps(res), flush=True)
            results.append(res)
    ok = [r for r in results if r.get("adequate")]
    print(json.dumps(dict(judged=len(results), adequate=len(ok), adequate_bytes=sum(r["size"] for r in ok))), flush=True)


if __name__ == "__main__":
    main()
