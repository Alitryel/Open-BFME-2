# Coord3D allocation wrapper link repair

At source baseline `6501f0d3f5`, eight units have one blocker: their emitted
STLport allocation proxy differs from the first retained copy in
`stlport_vector_coord3d_count_fill.cpp` (/Ob0). The copy is referenced by that
owner, so retail-truth-2 still judges the conflict despite having no retail RVA.

Use the stock `vendor/stlport/stl/_alloc.h` forwarding implementation as an
inline-only specialization in these consumers. Explicitly declare the underlying
allocator specialization to preserve the existing allocator call rather than
inline it recursively. No allocator pin, layout, global, ledger or shared header
changes. BFME 1 revision reviewed: `64d369b90170b7e9ec917d646f020b11f13eb0d5`;
its Coord3D vector source confirms the same stock allocation dependency, but the
local paired objects and BFME 2 byte gate establish this repair.

`before-link.txt` and `after-link.txt` use the same published census
(c2c5ac8c27, 2026-10-18 11:36; SHA256 in proof.json). Legacy predicted linked
bytes increase from 0 to 2,387 across eight units. All 17 matched rows pass the
ordinary byte gate, and every object has a strict reusable receipt (self-strict
current). Closed-strict closure and a full link cycle remain unmeasured.

`proof.py` uses scratch baseline objects under `build/link-seat-20261018/before`.
It verifies that only the proxy, allocator, and optionally allocation-rebind
COMDATs disappear, no new COMDAT appears, and every retained nondebug section's
bytes, flags, external definitions and symbolic relocations are identical.
SafeSEH entries compare symbolically, with deleted helper entries excluded.
The paired prediction additionally substitutes the old/new cohort into the same
frozen index. `proof.json` records the result and object hashes.

Acceptance: 17/17 byte rows; link_check 8/8 clean (+2,387 B legacy prediction);
new-variants, class gate, declared-unmatched, data enforce, converged-data,
case-collision and diff checks pass. Remaining proxy conflicts in units with
other independent blockers are not claimed as linked gains.

Publication reconciliation: upstream `bae606442f` independently landed the
identical forwarding expressions in all eight units. On replay of local
`cab036aa79`, retain upstream source verbatim and preserve this independently
verified evidence. Its historical +2,387 B is already upstream, so replay
adds no further linked bytes. The remaining differences were comments,
whitespace and the forwarding argument identifier (`count` versus `n`).
