# AptShapeContainer::render, 0xA9F98 / 1471 B — continuation 2026-10-22

Continue this assigned body. The best emitted body remains **five differing
instructions / 15 differing bytes**, size and instruction count exact, score
0.9898. The line and solid regions remain exact under the isolated diagnostic.
No nonmatching render was installed in Code. The previous grouping handoff
still applies; this note adds compiler evidence and a completed prerequisite.

## Verified prerequisite

Commit `a8f1a0c1af` corrects the existing 0x1100A6 / 0x1100C5 owner signatures
to `void __fastcall method(void *)`, keeping their neutral identifiers. Both
31-/5-byte bodies pass the normal byte gates, and their unit still LINKS
(36 -> 36 bytes). The staged dependency scan found no old-signature consumers
among 23,443 units. See [the ABI evidence](../a9f98-cursor-abi-20261022.md).

The bank now calls those owned classes, instead of adding two unadmitted names
on BfmeHub982. Its raw body hash is unchanged. The new reproducer uses the
ordinary ledger map, with **no supplemental end-list mappings**:

```
python3 reverse/attempt_support/a9f98-c2keys-20261022/reproduce.py.txt
```

This still masks DIR32 fields like variant.py. It is an isolated search
diagnostic, not the identity/data/full-byte acceptance gate. `receipt.json`
binds the source and emitted/diagnostic/target bodies; `residue.txt` gives all
five native offsets. T2 needs point-Y before matrix-d at +43D/+442. T6 needs
that operand direction and the Y*d product issued before X*b at
+550/+554/+559. No unknown callee is currently blocking those comparisons.

## New compiler evidence

The normal c2.dll is 13.10.3077, loaded at 0x10700000. Read-only winedbg
breakpoints inspect the compiler; they do not modify it or its generated code.
`mul-keys.json` preserves the last canonicalized form of all 44 MUL nodes.
`address-creation.json` preserves five early address definitions and three
late ones, with argument nodes and symbols frozen **at creation time**.

For these zero-displacement memory leaves, FactCanonSort gives a named base F
the key `0x10008 + 0x2000*(F&7)`, and a HashVar base H the key
`0x10008 + 0x4000*(H&3)`. Larger keys sort first. The original bank has:

| Address | Base symbol | Leaf key |
| --- | --- | --- |
| UV matrix c | H1436 | 0x10008 |
| UV matrix d | H1466 | 0x18008 |
| UV matrix b | H1473 | 0x14008 |
| UV1 point Y | H2224 | 0x10008 |
| UV3 point Y | H2144 | 0x10008 |
| UV3 point X | H2242 | 0x18008 |

H1436/H1466/H1473 are address additions to named F8 (the UV transform),
respectively +8/+12/+4. H2144 is an early nested address expression on F14
(the triangle iterator), with constants 16 and 4. Its address op is 0x284;
do not label that op SUB merely from its number. Target addressing identifies
this base with the triangle's +20 point-Y coordinate.

The late symbols are **not** created at the classic CSE return breakpoint
0x10761546. SymMakeHashVar returns to 0x107A9EED instead. Snapshots of its
argument array at 0x10882190 prove:

```
H2224 = H2144 + (-8)    // UV1 Y, triangle +12
H2231 = H2144 + (-12)   // UV1 X, triangle +8
H2242 = H2144 + (-4)    // UV3 X, triangle +16
```

The shared matrix-d key beats both point-Y keys, explaining the wrong product
directions. The source choices need to alter early address creation and/or the
later induction aliases relative to one another. A uniform source-local shift
cannot do that. One outer X group in UVFirst changes multiply keys in earlier
line/solid regions too: the effect involves initial/global temporary creation,
not only the immediately adjacent Y expression.

The original scratch graph that re-read old node addresses was misleading:
IR nodes mutate and are recycled. Only the frozen-argument graph supports the
address formulas above. Its full scratch capture has 1,701 early creations;
the compact selected evidence here retains their needed dependencies.

## Completed trials; do not repeat unchanged

`trials.json` records the counts, best result and extent refusals per family.
All use the normal /O1 /G7 /EHsc /MD /arch:SSE configuration in isolated objects,
eight workers per family, without the shared match cache.

- Control flow and lifetime: paired position/UV emit helpers (288), shared
  semantic locals/scopes (640), all position/z-color/UV statement orders (432),
  flat point/float/byte induction with multiple anchors/views (324).
- Types and boundaries: returned V2 helpers (144), nested scalar arithmetic
  controls (eight), output/point/matrix member helpers at every site plus the
  UV pair/all sites, with default/fastcall conventions (78). Nested scalar and
  all member controls are inert; no larger nested-helper family was launched.
- Joint FP/address creation: three-helper whole-X grouping phases with removal
  of old pads (1,152); early Y evaluation with late Y stores (896); ten groups
  across all solid/line rows (2,048); nonzero grouping phases combined with
  typed induction (756); compound/reassignment forms in four UV rows (625);
  independent outer X/Y depths 0..5 for UV1/UV3 (1,296).
- Callee visibility: actual recovered BeginTriangleList, texture setter and
  end-list bodies, singly and combined, before/after render (16). All leave
  five differences. Explicit throw() combinations (16) shrink render to
  1,449 bytes and worsen it; this is diagnostic evidence, not a justified
  exception annotation to land. The previous visible line-draw tests are
  already covered by the older handoff.
- Compiler settings were not re-swept. The verified configuration and earlier
  negative settings evidence remain applicable. The ABI prerequisite's initial
  scratch default /O2 failure was corrected by using that unit's actual flags;
  it does not establish a compiler obstacle for render.

Some inferior candidates fix both T2 and T6 completely. For example,
`phase_4_331` has 47 differences overall but those two full UV regions exact;
it groups NamedProducts' whole X expression and retains only 3/3/1 of the
old 5/3/5 pad groups. The paired emit variant `pair_521120` likewise fixes both
with 52 other differences. The typed-induction/grouping control
`phaseFlat_3_1010_4` fixes both with 53 differences overall. These prove the
needed forms are reachable, but none is a better combined bank.

The thirteen inherited unusedSlot declarations remain solely to preserve this
comparison basis. They are not evidence for original locals and need removal
or a justified semantic source shape before a final recovery. No new pads were
added. Removing old pads in the completed interacting families did not improve
the bank.

## Reproduce the compiler evidence / next work

The trace basis is the **pre-ABI bank**, source SHA256
`d776d4993dfb69f18f6e4bea9dca4cd2e4364272ffd6a3b207d15ebfee8e82f4`.
The bank's new ABI declarations change its source hash but not its raw emitted
body. To reproduce these precise temporary IDs:

```
git show 07a5a34ded:reverse/attempts/0x000a9f98.cpp > build/a9f98-trace-basis.cpp
python3 reverse/attempt_support/a9f98-c2keys-20261022/trace_canon.py.txt build/a9f98-trace-basis.cpp canon-basis
python3 reverse/attempt_support/a9f98-c2keys-20261022/trace_hashgraph.py.txt build/a9f98-trace-basis.cpp hash-basis
python3 reverse/attempt_support/a9f98-c2keys-20261022/trace_late_args.py.txt build/a9f98-trace-basis.cpp
```

The scripts write ignored build/a9f98-c2-trace files and quit their debugger.
The late tracer intentionally filters H2224/H2231/H2242; new source may require
different IDs. The canon tracer freezes node operands, including indirect
bases; the hash tracer freezes creation arguments rather than revisiting them.

The saved search.py/phase.py/outer_depth.py text files preserve the isolated
scorer and two useful generators. Copy to .py files under an ignored scratch
directory before using them. For the old phase control, base.cpp is the
pre-ABI bank above. For the depth generator, owned-abi.cpp is the current bank.
Their diagnostic scorer still contains the old two mappings for reproducing
historical trials; the acceptance-style reproducer does not contain them.

The next useful investigation is the relationship between the early shared
matrix-d address and the later loop-rebased point addresses. Preserve exact
line/solid winners while recombining a region winner, and inspect key changes
before committing to another large source family. Do not repeat uniform pads,
the completed helper spellings, opaque/visible callees or compiler swaps.
This note does not claim all source hypotheses are exhausted.

Inputs: start tree 07a5a34ded; BFME1 verified pointer
37c3022de1ab944c7ffe536440d637dc8199091c, last successful freshness check less
than 24 hours old at session start. No submodule update or broad reference
sweep was needed in this assigned lane. check_csv and the home frozen-file
check passed. The unchanged home TU passed ./build.sh: 16/16 function bodies,
six data rows, string/float/import references. The end-list repair separately
passed its normal gates and link check. No verifier, pin or baseline was edited.
