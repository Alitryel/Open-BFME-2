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

usage (checkout root, Python with unicorn): functional/tools/fn_adequacy.py [--jobs 8] [--limit N] [--rva 0x...]
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
    rva, name, size, source = int(row["target_rva"], 16), row["name"], int(row["target_size"]), row["source"]
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
    return dict(rva=f"0x{rva:08X}", name=name, size=size, changed=changed, killed=killed,
                inconclusive=inconclusive, survivors=survivors[:10],
                adequate=changed >= MIN_CHANGED and killed >= KILL_MIN * changed)


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--jobs", type=int, default=8)
    ap.add_argument("--limit", type=int)
    ap.add_argument("--rva")
    a = ap.parse_args()
    os.chdir(ROOT)
    rows = list(csv.DictReader(V.LEDGER.open(encoding="utf-8")))
    todo = [r for r in rows if r["verdict"] in ("none", "regalloc-only") and r.get("isomorphic") != "True"]
    if a.rva:
        todo = [r for r in todo if int(r["target_rva"], 16) == int(a.rva, 16)]
    todo.sort(key=lambda r: -int(r["target_size"]))
    todo = todo[: a.limit or None]
    print(f"{len(todo)} passing, non-isomorphic rows to judge", file=sys.stderr, flush=True)
    results = []
    with concurrent.futures.ProcessPoolExecutor(a.jobs, initializer=_init) as ex:
        for res in ex.map(judge, todo):
            print(json.dumps(res), flush=True)
            results.append(res)
    # write the mutation column (killed/changed); never touches verdicts
    by = {int(r["rva"], 16): r for r in results if "changed" in r}
    fields = list(rows[0].keys())
    if "mutation" not in fields:
        fields.append("mutation")
    for r in rows:
        res = by.get(int(r["target_rva"], 16))
        if res:
            r["mutation"] = f"{res['killed']}/{res['changed']}"
            receipt = ROOT / "functional" / "receipts" / f"0x{int(r['target_rva'], 16):08x}.mutation.json"
            receipt.write_text(json.dumps(res, indent=1))
        r.setdefault("mutation", r.get("mutation", ""))
    with V.LEDGER.open("w", encoding="utf-8", newline="") as f:
        w = csv.DictWriter(f, fields, lineterminator="\n")
        w.writeheader()
        w.writerows(rows)
    ok = [r for r in results if r.get("adequate")]
    print(json.dumps(dict(judged=len(results), adequate=len(ok), adequate_bytes=sum(r["size"] for r in ok))), flush=True)


if __name__ == "__main__":
    main()
