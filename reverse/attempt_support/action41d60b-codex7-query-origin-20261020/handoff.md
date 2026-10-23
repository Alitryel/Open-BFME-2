# ActionManager 0x0041D60B: narrow query-helper origins

Continuation of the same unfinished fallback, not a new candidate. Input BFME2
`7950e8ecf0cf7447d3569f722135ff3024129bbd` (after rebase onto
`198f03c15689e0cb99e44440392d499bbe9278a9`); BFME1 checkout
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`. MSVC 7.1 RTM,
`/O1 /arch:SSE /G7 /MD /GX`; model gpt-6.1-sol, owner codex7.

## Hypothesis and scope

The previous handoff ruled out seven whole-case inline origins in combination,
broad lifetime/declaration sweeps, type unification, visible callees, alternate
compiler builds and whole-function EH changes. This continuation tests smaller
inline expression boundaries: creating the filter temporaries inside an inlined
query helper might change their allocation independently of the surrounding
case's named locals. The two-bit-mask helper is a previously known control,
not claimed as a new discovery.

Six binary choices were compiled factorially on both the current farm bank and
the older natural source: geometry query, placement second query, healing
query, case99 closest query, case72 closest query, and two-bit-kind predicate.
All 128 isolated compiles succeeded, yielding 52 distinct primary bodies. No
production source, header, pin, gate or shared compile-cache object was edited.

## Result

No exact body or retail `0x2B4` frame. The geometry/placement/healing query
helpers alter cleanup and instruction structure substantially. Case72's helper
is byte-inert even in combinations; case99's helper changes packing but loses
an instruction. The known kind-mask control gives frame `0x2BC`, still with
wrong stack homes; its natural-source result is 3712B/1034 instructions,
one structural edit plus 41 other diagnostic differences. It does not improve
on the natural source's exact mnemonic sequence. On the farm baseline, however,
this control retains the 1033-instruction sequence and improves strict diagnostic
fitness from 0.96751 to 0.96778, with 50 rather than 51 aligned differences.
That combination is banked as the small best available improvement.

Both the incoming bank and the selected candidate were audited against the
current symbol map with strict
relocation resolution: zero unresolved names, no masking, all 90 direct
callees in retail order. The selected bank is
3709B/1033 instructions/frame `0x2BC`, versus retail's
3709B/1035/frame `0x2B4`. This is an unresolved reconstruction, zero matched
C++ bytes. The diagnostic alignment masks relocation operands and omits direct
call-target comparisons; only the separate strict audit checks callees. Neither
is a full-byte acceptance result.

WB `0x0110D180`'s saved decompilation was reviewed again: it has distinct debug
temporary areas (for example the healing mask/filter chain and late closest
queries). Its unoptimized frame does not establish that any of these helpers
existed in the original source. The ZH BitFlags and PartitionFilter headers
were inspected narrowly; the explicit empty Alive constructor and visible
special-member angle were already covered. No new layout fact was inferred
from Ghidra's overlapping array declarations.

## Resume

Retain `reverse/attempts/0x0041d60b.cpp` and the stronger mnemonic-sequence
source at `125d7a88ce`. The specific remaining problem is selective stack-slot
sharing, not a missing callee. Do not rerun this six-way helper factorial or
the prior whole-case factorial. A useful next investigation must first identify
a source/ABI distinction from the unoptimized WB assembly or original BFME2
header evidence; mere frame-size reductions have repeatedly degraded the
instruction and EH sequence. No impossibility claim is made.

For reproduction, copy `trial.py.txt` from the preceding
`action41d60b-codex7-20261020` evidence directory to
`build/action41d60b-codex8/trial.py`, copy this generator to `query_origin.py`,
and copy `natural-refreshed.cpp.txt` to `providers1_15.cpp` there. Use the incoming bank
from the input commit above (before this continuation), then run the generator from the repository root
with argument `qorigin`. `receipts.json` deduplicates all results by primary
body hash and includes the fresh strict bank audit.

Ledger check passed after pulling; the upstream BFME1 update lock was still
owned by codex5, so this seat deferred freshness updating under the runner rule.
No successful-freshness timestamp was written. The small improvement is banked
and the claim is released for the next continuation.


## Preparation recovery (2026-10-20)

Replayed onto `a127b6f0c1` after upstream `3abdb07125` restored the cleaner
canonical bank. The claimed-by-another-seat canonical bank is retained exactly.
This session's 3709B/1033-instruction/frame-0x2BC candidate is preserved in
`narrow-helper.cpp.txt`, beside the full receipts and natural-refreshed source.
The earlier instruction to retain `reverse/attempts/0x0041d60b.cpp` referred
to this saved candidate before the concurrent upstream change; use the explicit
evidence path to resume those experiments. No trials or improvements were lost,
and no matched ActionManager row is introduced.
