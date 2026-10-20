# Standing-water buffer builder: real lifetime context

Target: `RenderableStandingWaterArea::AllocateAndFillBuffers`,
RVA `0x0008304A..0x000834CE`, **1,156 bytes**. It remains unmatched.
Input BFME 2 revisions: `dc29e37e9e`, then `9ff5576d09` (no relevant
source/header, instruction, or BFME 1 pointer change during the pass).
BFME 1 pointer: `92f6bbe8e1dcdb46b5d27da0674313efc822b790`.
Model: gpt-6.1-sol; approximately 34 minutes of investigation.

The new primary bank is `reverse/attempts/0x0008304a.cpp`.
Normal repository fitness on the same current inputs improves
**0.8221095 -> 0.9197485**; emitted size **1,167 -> 1,163**; native size
stays 1,156. The old bank's recorded 0.84 is not the current measured score.
Frame **0x94 -> retail 0x88**; complete parent EH **four differing bytes ->
EXACT**. All parent calls resolve. This is partial evidence, not coverage.

## Changes supported by target evidence

- The existing 153-byte cache constructor at `0x00082A53` is genuinely visible
  in the candidate, including both vector initializations, dimensions, origin
  words, spacing, word resize, and record reserve. It compiles to all 153
  retail bytes under the parent's settings, with an EXACT EH graph. No dummy
  callee, fake effect summary, or compiler pragma is used.
- The actual 39-byte `MathCoord2D operator+` body at `0x0007DEC8` is visible.
  It compiles whole-exact and closes the remaining four-byte frame gap.
  Merely declaring it out of line does not preserve these compiler effects.
- The candidate uses the registered `Region2D` header and its `lo/hi` fields.
- Both mask passes use the indexed form the WB `0x0073F580` body shows.
  This reduces the indexed candidate's allocation residue to one register
  line; setup matches through retail offset `+0x18F`.
- The forced-memory `slot` and `records` locals are removed. There are no
  volatile locals, barrier calls, padding objects, or artificial operations.

Identity remains supported by the named WB method/source, existing standing
water texture recovery, native caller/callee relationships, resource-vector
offsets, byte mask, six indices per selected cell, and 44-byte vertex records.
The cache owner and E12/E16/Pod44 names retain the earlier neutral layout-view
status; their original application type names are not newly established here.
The byte resize's original element signedness is likewise not established.

## Remaining differences and alternate

The best body is 7 bytes long. Its first-pass row induction/base reload and
zero-value web differ, followed by cache-argument scheduling and a second-pass
base load. `alignment.txt` is the complete ordinary alignment report; its
six fixed-address literal/global differences are relocation noise. Frame,
all parent calls and complete EH are now correct; size equality alone must
not be treated as completion.

`alternate-vbase.patch` replaces the manual null-checked shape adjustment with
a real C++ virtual-base cast. The existing `Rva0030902EDtor.cpp` establishes
the polymorphic 0x18-byte primary prefix, vbptr +0x18, secondary base +0x30,
and shared virtual shape. This alternate removes an extra conversion branch,
but fitness is 0.9168791, so it does not replace the stronger primary bank.
Its class names describe a structural view; they are not original-name claims.

## Controls already tried

About 150 valid context trials, including repeated controls, covered:

- Real cached-vertex method visibility, constructor/destructor visibility and
  vector constructor/destructor boundaries. The constructor helps; the other
  boundaries alone do not.
- Original by-value byte-resize body; complete legacy byte-vector object and
  real native growth implementation (also reviewed against the newly landed
  byte-vector visibility linking repair). Generic const-reference resize has
  another ABI; do not silently substitute it.
- Real vertex lock constructor/destructor and full 304-byte polygon
  containment body, including its `/Oy-` profile: no further caller gain.
- Continuous/indexed/row-pointer masks in both passes, cached base pointers,
  pre/postincrement, shared counters, and second-pass for/do forms. The compiler
  already canonicalizes the entry-guard variants; there is no new do-loop fix.
- Canonical region, real coordinate views and scopes, const/reference origin
  types, actual pointer-typed cache owner, scalar/count reuse, and WB's explicit
  maximum-vertex local. No stronger candidate.
- `/Ow`, `/Oa`, `/Oi`, `/Ob2`, and disabled global optimization. They do not
  solve the residue. No such flag was added to the bank.
- Matched-sibling `_STLP_USE_MALLOC` and `_STLP_USE_NEWALLOC` profiles leave
  both the best indexed body and complete byte-vector control unchanged.

## Reproduction and landing prerequisites

Run `python3 reverse/attempt_support/water-buffer-lifetimes-20261020/replay.py.txt`.
It uses normal `explain_mismatch.py`, asserts an object exists before ordinary
alignment, and reads fitness/EH without invoking a raw compiler entry point.
`prior.cpp.txt` preserves the replaced bank. `comparison.json` records selected
controls; `ctor-proof.txt` and `plus-proof.txt` preserve whole helper proofs.

No production source, pin, row, gate or baseline changed. Do not paste the whole
bank over current `Water/W3DWater.cpp`: its old unrelated class spellings predate
upstream reconciliations. Integrate the helper/context changes into the current
home and verify every owned row. Before landing, reconcile constructor and plus
provider ownership; a second strong definition is not an acceptable linking
solution. The new bank needs no speculative pin or fabricated helper.
