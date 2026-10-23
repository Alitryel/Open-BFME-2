# Final camera distance: exact canonical-sort decision

Native target: final distance arithmetic at +AA4..ABD is (X squared + Z squared)
+ Y squared. WorldBuilder twin 7E6175..6599 establishes a copied Vector3, -=,
and Length2/Length semantics. It does not independently establish parentheses in
the optimized retail source.

Read-only debugger traces use FactCanonSort at C2 3077 RVA 0x5CC68. Exact function
name matching excludes the local AnimatedTransform constructor. Relevant sort
calls return to RVA 0x6A8C0. All three trace runs exit 0; their complete target
bytes and relocation lists equal ordinary objects (proof.json). No compiler
choices were changed. The unused distance_order.py phase driver was prepared but
never run; actual runs used distance_canon.py and distance_group_canon.py.

## Why ordinary Length2 becomes ZYX

value_reference.cpp calls delta.Length(), whose inline Length2 is X*X+Y*Y+Z*Z.
Final delta X is numbered among earlier inline operands; Y/Z are late pieces.

| Field | Optimized symbol ID | Leaf key | Square key |
|---|---:|---:|---:|
| X | 1778 | 0x1DE40 | 0x1039AF0 |
| Y | 2570 | 0x14141 | 0x103C3F3 |
| Z | 2572 | 0x14181 | 0x103C4B3 |

Record182 in xyz.canon.json explicitly observes XYZ entering FactCanonSort and
ZYX leaving it. Descending square-key order explains the emitted sum before
register allocation. The square low half is (3*leaf_key+0x30)&0xFFFF for all
three values. Thus arithmetic source order alone is not preserved.

## Why spelling XZY directly becomes YZX

Direct field access numbers the scalar pieces early in access order:

| Field | Optimized symbol ID | Leaf key | Square key |
|---|---:|---:|---:|
| X | 517 | 0x140A0 | 0x103C210 |
| Z | 519 | 0x140E0 | 0x103C2D0 |
| Y | 521 | 0x14120 | 0x103C390 |

Record166 in xzy.canon.json explicitly changes XZY to YZX. This explains why the
one source rewrite worsened the distance-region mismatch13->22. Both the inline
context and source order of first direct field uses affect numbering; no random
allocator or profile weight is involved in this decision.

## One authorized grouping probe

WWMath::Sqrt((delta.X*delta.X + delta.Z*delta.Z) + delta.Y*delta.Y)

Ordinary result:4295B, fitness0.9070479670709372 (baseline4286B/0.9311709691110692).
Normalized distance-region changed instructions12 (baseline13; ungrouped direct
XZY22). The emitted arithmetic is (Z squared + X squared) + Y squared.

The trace explains both levels:
- Inner ADD still sorts Z0x103C2D0 before X0x103C210 (record166).
- Parenthesis opcode617 wraps the inner ADD key0x207471E, producing0x208473D.
- The parenthesized sum becomes a real CSE temporary carrying key0x208473D;
  it sorts before plain Y-square0x103C390 (record200).

A minimal predicted next grouping is:
WWMath::Sqrt(((delta.X*delta.X) + delta.Z*delta.Z) + delta.Y*delta.Y)

One extra parenthesis pair around X-square would add0x1001F to its current key,
predicting0x104C22F > Z-square0x103C2D0. The existing outer grouping then keeps
XZ before Y. This was initially a prediction; the separately authorized test below confirmed
it. The grouping expresses native arithmetic without dummy declarations,
fabricated escapes or compiler modification.


## Predicted extra X-product grouping: confirmed

The parent authorized exactly the predicted next probe, compiled ordinarily as
`distance_grouping/x_square_group.cpp` / `.obj`. It emits4295B, all57 relocations
resolve, fitness0.9108856569557671. The whole function is not exact.

The key local result is stronger than the score: native+A54..ACE,122 bytes, occurs
exactly once in the candidate at+A5C, byte-for-byte with no relocations in that
span. This covers all six source/target copies, XZY squared length, sqrt and the
result spill. SHA256 of the span:
7929c7a03a88573d510cb7f8974b9448d6407f31d768ae8e58d3e8443f8ed1f2.

The native-normalized distance mismatch drops13->0. Other measured tail regions
are unchanged: realZoom pitch13, shaker Rotate_X21, final Rotate_Y32, nearAdjust0.
The overall instruction mismatch increases179->213 because the live second
matrix portion changes70->117, consistent with the independently established
field-numbering effect of the direct final-site accesses. No trace proving each
new matrix hash was taken, so that precise attribution remains an inference.
The first matrix and initial scaling regions are unchanged.

Preserve this as an exact122-byte local mechanism for integration with the parent
agent's ongoing matrix/pitch corrections; do not select or reject it solely by
whole-body score. `distance_grouping/predicted-proof.json` records exact bytes,
uniqueness, extent, source hash and all normalized region results. No additional
candidate or trace was run after confirming this result.
