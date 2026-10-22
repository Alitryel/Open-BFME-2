# AptShapeContainer::render, 0x000A9F98 / 1471 B (2026-10-22)

The bank improves from 21 differing instructions / 54 differing bytes to **5 / 15**
under one fixed isolated diagnostic. Both bodies are 1471 B, with the same
instruction count. Line and solid regions are exact under that diagnostic. All
five remaining instructions are in textured UV Y rows. This is a partial, not a
matched row or a claim of five differences under the full gate.

The starting bank was commit `b90257f7a90d2a3bedd9cd3062e2329f8b2a6548`,
score 0.96. Its earlier 24-instruction measurement plus three end-list calls
used another comparison. Do not subtract that number from the new one: the
21-to-5 comparison here recompiles both candidates using the same scorer.

## What the comparison establishes

`reproduce.py.txt` copies the bank into an isolated directory, calls
`build.compiler_command`, reads its COFF symbol, resolves calls, and compares
instructions. It never calls `build.compile_source` or writes the shared match
cache. Run from the repository root:

```
python3 reverse/attempt_support/a9f98-grouping-20261022/reproduce.py.txt
```

As `tools/variant.py` does, it masks DIR32 slots using target bytes. It also
supplies explicit **diagnostic-only** maps for the bank's fastcall end-list
names to 0x1100A6 / 0x1100C5. These two mappings are supported by the earlier
WB/native analysis but are not admitted pins. The three end-list call sites
therefore are not unresolved differences in this diagnostic. Run normal pin,
identity, data and full-byte gates before landing anything.

`receipt.json` binds the final saved bank, emitted body, diagnostic body and
retail extent. `residue.txt` gives the remaining native offsets. The bank score
is 0.9898: `1 - differing_bytes/1471`, rounded to four decimals. It is a search
metric.

## Successful new hypothesis

Previous evidence ruled out local-symbol padding for Lb, S3, T2 and T6 because
their comparisons are temporary against temporary. No padding scan was repeated.
The new hypothesis was the recipe in `fp-paren-nodes-20261020.md`: floating
parentheses survive as IL nodes and affect reassociation, hash temporaries and
scheduling. Product staging must be tested jointly with grouping.

Three helper specializations combine successfully:

- First textured UV: group both X products and their sum; group its first Y
  product. This closes the earlier textured differences except the second Y
  multiply's operand direction and the last UV row.
- Second line endpoint: keep two separately named X products (matrix factors
  first, first product parenthesized) and two parentheses around each Y product
  plus one around their sum. This makes the line region exact.
- Third solid vertex: keep both X products separately named, parenthesized,
  matrix factors first. Its Y row stays plain. This makes the solid region exact.

The bank contains these spellings as `aptMatrixMulUVFirst`,
`aptMatrixMulLineSecond`, and `aptMatrixMulSolidThird`. Their names/formatting
and removal of unused experimental accessor methods preserve the emitted body.
The pre-existing thirteen `unusedSlot` declarations are retained only to
preserve the old diagnostic basis. They are not new evidence for original
locals and must not be treated as justified recovery source.

The same-unit scratch integration of the 10-instruction predecessor into the
current home TU emitted the identical candidate body. It required merging the
render-related declarations, avoiding duplicate AptMatrix, and marking
`BfmeHub982::rva00111312` noinline. Stale unrelated bank content does not explain
that residue. The actual home file was not edited.

## Investigated explanations

The prior histories were read through `/opt/runner/pick-hard --rva 0xA9F98`
before experimentation, including the w1/w4 notes and SSE-site-search bank.
Those notes already disprove a uniform symbol-count shift, helper parameter
orders and inline decorations, scalar/named/deferred stores without the new
grouping, simple loop rewrites, direct matrix parameter/union views, G6/O2/SSE2/
Op, DDK and SP1 compiler swaps, and a missing original named local. They establish
an exact out-of-line aptMatrixMul copy at A9192 while its callers still differ.

This session tested the following independent explanations:

- Control flow and argument shape: a 512-way factorial of explicit triangle and
  segment point pointers/references and bases; no improvement from the starting
  bank. Direct UV arithmetic and declaration scope are separately enumerated.
- Lifetime and initialization: 76 valid endpoint-constructor/explicit-init/order
  variants. WB sentinel/default initialization is not removed through an opaque
  draw call; initialized candidates remain longer (typically 1494 B).
- Types and layout: 48 flat/nested vertex, point, triangle and segment views;
  scalar point parameter forms/order; mixed field/array reads; inline field
  value/reference accessors; named scalar reference/copy lifetimes. The declared
  target offsets remain supported; no changed layout explains the residue.
- Callee visibility: the existing matched 462-byte line-draw helper, visible
  noinline before/after render, with/without throw(), did not remove endpoint
  initialization or improve the 10-instruction predecessor. The real BFME1
  Vector2 header and verified include paths compile after the SDK's
  `_OPERATOR_NEW_DEFINED_` guard; they worsen the original bank (34/105).
- Compiler settings: existing negative settings trials were not repeated.
  Successful experiments use the bank's /O1 /G7 /EHsc /MD /arch:SSE flags and
  the normal 7.1 compiler. Grouping/staging, rather than another compiler, gives
  the measured improvement.

Searches are factorial where practical: seven staging forms, independent
product parentheses, sum/whole-expression grouping, independent factor order,
point access forms, and cross-products of region winners. A 12-choice outer
textured-expression search uses a resolution-six 2^(12-2) fraction; translation
leaf and first-product grouping use separate deterministic samples. No arbitrary
constant, instruction injection, pragma or gate modification was used.

`trials.json` records 22,037 compiled family members and their best metrics.
The final 3,136-way Y-depth and 2,049-member global grouping searches both retain
five as their best result. Do not infer that all possible C++ spellings were
exhausted. In particular, a wider retune from an
inferior line-exact mixed-view candidate was interrupted after 384 of its
first site's 659 variants; its other planned sites were not tested. The old
12-instruction loop/getter and spelling searches were skipped when the
five-instruction candidate emerged. A new 512-way range-accessor search uses
the five-instruction basis instead and is complete without improvement. The
512-way predecessor-position search (independent point field/array reads and
product groups before UV1/UV3) also leaves the best result at five. Direct UV
expansion, all ordered scalar-reference subsets and complete four-leaf
value/reference bindings likewise do not improve the bank. The latter family
is materially worse even at its best (26 instructions / 77 bytes).

## Resume here

Continue this body. The unresolved sites are T2's second Y product at +43D/+442
and T6's Y product load/operand schedule at +550/+554/+559. T2 needs point Y
before matrix d; T6 needs that direction and the Y*d term issued before X*b.
Do not start another inert-local scan or repeat the completed families unchanged.
Some worse candidates fix those exact sites while regressing other textured
operations, demonstrating that the desired forms are reachable. Five is the
best combined result in the saved bank.

A next useful angle is temporary provenance across the paired position/UV
transforms, with a different typed iterator or paired transform boundary, or
direct inspection of c2's FactCanonSort keys for those remaining products.
The range-accessor substitutions, predecessor point-view/product grouping and
scalar-leaf bindings above are already tested; do not repeat them unchanged.
Preserve exact line/solid winners while changing UV source; inspect per-site
residues, not only a total score. WB helper 0x8A8BD0 uses direct X/Y expressions
without named product locals; a new equivalent C++ shape must still preserve
the proven matrix operation and ABI.

Integration remains a separate prerequisite: merge only render-related deltas
into `Code/GameEngineDevice/Source/W3DDevice/GameClient/GUI/W3DAptAux.cpp`;
reconcile the end-list fastcall names with the existing placeholder owners at
1100A6/C5 through normal pin admission or naming rules; retain the existing
home's other matches and canonical data names. The address A9F98 currently has
an old placeholder `Rva00785FD0Item::cleanup` pin, not a matched body. WB names
render independently; do not treat that placeholder purpose as target evidence.

## Inputs and checks

Start tree: `2f298e5149097c89d16d4316930a071ed94d6ea0`.
BFME1 pointer: `37c3022de1ab944c7ffe536440d637dc8199091c`.
Its updater lock was live and owned by claudeb3, so this seat left the update to
that seat and did not write a successful freshness marker. The published link
index was fetched successfully. The bank/header trials used the checked-out
inputs; these are not a reference sweep or a reference provenance claim.

`check_csv.py` passed. The unchanged home TU passed `find_declared_unmatched.py`
and `./build.sh` (16/16 functions, six data rows, strings/floats/imports verified).
No nonmatching body was installed in Code, and no ledger row or pin was added.
The final bank was freshly recompiled with the isolated reproducer.
