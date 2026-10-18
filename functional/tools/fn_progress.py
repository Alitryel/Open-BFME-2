#!/usr/bin/env python3
"""Behavioural-equivalence scorecard of the `functional` branch (this branch only).

master measures byte exactness: a function counts when its C++ rebuilds retail's
exact bytes. This branch measures BEHAVIOUR: a function counts when it is byte-exact
(every byte-matched master row does the same thing as retail) OR when a
non-exact body has a recorded differential-execution verdict proving equal
behaviour (functional/ledger.csv). The goal is 100% of retail's real code with
a complete, linking, bootable game.dat.

Figures (all over the same real-code denominator tools/progress.py uses:
.text minus 0xCC padding):

  BEHAVIOUR-VERIFIED  byte-exact rows  UNION  functional rows with a passing verdict
  BYTE-EXACT          master's ledger alone (the same rows tools/progress.py counts)
  FUNCTIONAL-ONLY     verified here and not byte-exact
  CLAIMED             functional rows without a passing verdict (shown, never counted)
  FUNCTIONAL LINKING  matched code in units that link once byte-only link blockers are
                      waived: a kept COMDAT copy that differs from retail's bytes (S) or
                      from the first copy (L) still links and behaves the same, so on this
                      branch only unresolved names (U), duplicate definitions (D) and
                      hard-coded image addresses (A) block a unit. Over all matched bytes,
                      from the last census index (build/link_census/link_index.pkl;
                      `python3 tools/link_check.py --fetch-index`).

A functional row passes when its verdict is `none` or `regalloc-only` from
tools/diffexec.py (retail bytes and rebuilt code executed side by side in an x86
emulator on identical inputs, callees stubbed; `regalloc-only` = equal return
values, writes and call sequence with different bytes), or `tested` with a
receipt under functional/receipts/ (a dedicated differential harness, e.g. the
SegLineRenderer package's 83 renderer scenarios). `logic`, `binding`,
`build_env` and `inconclusive` never pass.

usage (from the checkout root): python3 functional/tools/fn_progress.py [--json]
"""
import argparse
import csv
import json
import sys
from pathlib import Path

ROOT = Path(__file__).resolve().parents[2]
sys.path.insert(0, str(ROOT / "tools"))
import progress  # noqa: E402

LEDGER = ROOT / "functional" / "ledger.csv"
PASS = {"none", "regalloc-only", "tested"}


def functional_rows():
    if not LEDGER.exists():
        return []
    return list(csv.DictReader(LEDGER.open(encoding="utf-8")))


def real_bytes(intervals, image_start, image):
    return sum(end - start - image[start - image_start:end - image_start].count(0xCC)
               for start, end in progress.merge_intervals(intervals))


def functional_linking():
    """(linking bytes under functional rules, linking bytes under master's rules, matched bytes)."""
    import link_check
    import link_rank
    census = link_check.census_blockers()
    blk, sizes = link_rank.blockers()
    total = linked = fn_linked = 0
    for source, size in sizes.items():
        if source.startswith(("Code/gen_asm/", "Code/gen_small/")) and source not in census:
            continue
        total += size
        bl = blk.get(source)
        entry = census.get(source)
        if entry is None:
            continue
        if entry.get("linked") or not bl:
            linked += size
            fn_linked += size
        elif all(kind in ("S", "L") for kind, _ in bl):
            fn_linked += size
    return fn_linked, linked, total


def main():
    ap = argparse.ArgumentParser()
    ap.add_argument("--json", action="store_true")
    a = ap.parse_args()

    text_start, text_size = progress.retail_text()
    padding, denominator = progress.real_code_denominator(text_start, text_size)
    image_start, image = progress._text_image()
    text_end = text_start + text_size

    exact = []
    for (_, rva), (size, _) in progress.matched_at(None).items():
        s, e = max(int(rva, 16), text_start), min(int(rva, 16) + size, text_end)
        if s < e:
            exact.append((s, e))
    passed, claimed = [], []
    for row in functional_rows():
        s = int(row["target_rva"], 16)
        iv = (max(s, text_start), min(s + int(row["target_size"]), text_end))
        (passed if row["verdict"] in PASS else claimed).append(iv)

    exact_b = real_bytes(exact, image_start, image)
    behaviour_b = real_bytes(exact + passed, image_start, image)
    claimed_b = real_bytes(exact + passed + claimed, image_start, image) - behaviour_b
    fn_link, master_link, matched_total = functional_linking()

    fig = dict(denominator=denominator, behaviour_verified=behaviour_b, byte_exact=exact_b,
               functional_only=behaviour_b - exact_b, claimed=claimed_b,
               functional_rows=len(passed), claimed_rows=len(claimed),
               functional_linking=fn_link, master_linking=master_link, matched_total=matched_total)
    if a.json:
        print(json.dumps(fig, indent=1))
        return
    pct = progress.percent
    print(f"BEHAVIOUR-VERIFIED  {behaviour_b:>10,} bytes ({pct(behaviour_b, denominator):6.2f}%)"
          f"  <- byte-exact rows plus behaviour-verified non-exact rows (functional branch)")
    print(f"  BYTE-EXACT        {exact_b:>10,} bytes ({pct(exact_b, denominator):6.2f}%)"
          f"  <- master's ledger")
    print(f"  FUNCTIONAL-ONLY   {behaviour_b - exact_b:>10,} bytes ({pct(behaviour_b - exact_b, denominator):6.2f}%)"
          f"  <- {len(passed)} row(s) in functional/ledger.csv with a passing verdict")
    print(f"  CLAIMED           {claimed_b:>10,} bytes ({pct(claimed_b, denominator):6.2f}%)"
          f"  <- {len(claimed)} row(s) without a passing verdict (not counted)")
    print(f"  remaining         {denominator - behaviour_b:>10,} bytes ({pct(denominator - behaviour_b, denominator):6.2f}%)")
    print(f"FUNCTIONAL LINKING  {fn_link:>10,} bytes ({pct(fn_link, matched_total):6.2f}% of {matched_total:,} matched)"
          f"  <- units linking once byte-only (S/L) blockers are waived")
    print(f"  master's rules    {master_link:>10,} bytes ({pct(master_link, matched_total):6.2f}%)")
    print(f"real code = .text minus {padding:,} bytes of 0xCC padding = {denominator:,} bytes")


if __name__ == "__main__":
    main()
