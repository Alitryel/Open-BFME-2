#!/usr/bin/env python3
"""Scratch: drift-report candidates whose candidate RVA is still unmatched.

The report is heuristic and ages: rows land between runs. Keep only candidates
whose candidate_rva is not covered by any matched ledger row, so what is left is
real queued work.
"""
import bisect
import csv
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
REPORT = ROOT / "reverse" / "zh_sweep" / "drift_report.csv"


def load_matched():
    spans = []
    with open(ROOT / "reverse" / "functions.csv", newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row.get("status") != "matched":
                continue
            try:
                start = int(row["target_rva"], 0)
                size = int(row["target_size"] or 0)
            except (TypeError, ValueError):
                continue
            if size > 0:
                spans.append((start, start + size))
    spans.sort()
    return spans


def main():
    spans = load_matched()
    starts = [s for s, _ in spans]
    limit = int(sys.argv[1]) if len(sys.argv) > 1 else 30

    def covered(rva):
        i = bisect.bisect_right(starts, rva) - 1
        return i >= 0 and spans[i][0] <= rva < spans[i][1]

    out = []
    with open(REPORT, newline="", encoding="utf-8") as fh:
        for row in csv.DictReader(fh):
            if row["class"] not in ("structural", "immediate-only"):
                continue
            try:
                size = int(row["size"])
                pct = int(row["aligned_pct"])
                votes = int(row["votes"])
                rva = int(row["candidate_rva"], 0)
            except (TypeError, ValueError):
                continue
            if not (24 <= size <= 220 and pct >= 85 and votes >= 3):
                continue
            if covered(rva):
                continue
            out.append((size, -pct, rva, row))
    out.sort(key=lambda t: (t[0], t[1], t[2]))
    print(f"{len(out)} unmatched candidate(s); showing {min(limit, len(out))}")
    print(f"{'size':>5} {'pct':>4} {'votes':>5}  {'rva':>10}  {'class':<14} function  [source]")
    for size, negpct, rva, row in out[:limit]:
        print(f"{size:>5} {-negpct:>4} {row['votes']:>5}  {rva:#010x}  {row['class']:<14} "
              f"{row['function']}  [{row['source']}]  {row['hint']}")


if __name__ == "__main__":
    main()
