Shadow Matrix4 constructor link repair
======================================

At source commit c30e1173cc, the dynamic and static shadow volume units
inlined Matrix4(const Matrix3D &) correctly but also emitted its unused
129-byte constructor COMDAT, the 108-byte Init and 12-byte Matrix3D index
helper. The census first selects camera.cpp's different 110-byte constructor,
proven wrong against the rowed retail owner at 0x0006A2CD. Merely defining
the constructor makes both consumers touch that selected-wrong name.

Declaring their existing forceinline constructor dllimport suppresses those
three unused definitions while preserving the inline widening and every
retained body. No import call, new external reference, alias, pin, class field,
shared header, compiler setting or dependency is introduced. The rowed owner
Matrix4FromMatrix3DO1.cpp is unchanged. This repairs surplus-emitter coupling;
it does not repair camera.cpp or establish a new Matrix4 target identity.

Target evidence remains the source/ledger boundaries and call relationships:
RenderDynamicMeshVolume 0x000F42FF..0x000F49D0 (1745 bytes) and
RenderMeshVolume 0x000F200A..0x000F2203 (505 bytes). The two warning-set members,
Geometry::GetPolygonIndex, and dynamic parent's EH funclets retain their rows.
Original BFME1/ZH semantic provenance remains unchanged. The dynamic constructor
copy equals the verified retail owner in bytes, extent and relocations.

Measurement and before/after
----------------------------

Discovery status is committed at 67e1365aa9 (2026-10-13 16:47).
Actual paired comparison uses runner index 147cfae2cb (2026-10-14 07:27),
SHA256 690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a.
Before and after consumers were each substituted into that SAME index along
with current byte-verified camera and constructor-owner providers. Nothing
writes index/status/history; no per-row data-back ranking was used.

- Dynamic consumer: selected-wrong findings 1 -> 0; legacy LINKS
  0 -> 1985 existing authored retail bytes (progress excludes 0xCC padding).
- Static consumer: findings 5 -> 4; legacy LINKS 0 -> 0. Remaining two
  unresolved DX8Wrapper globals and two losing accessor COMDATs are unchanged.
- Camera provider and constructor owner: findings exactly unchanged in both
  paired comparisons. The wrong camera constructor remains selected.
- Dynamic 44 and static 16 retained COMDATs: whole raw bodies, extents and
  relocation digests unchanged. Strong/undefined/weak names, ordinary nondebug
  sections and hatch counts unchanged. No helper or imported reference added.

Acceptance
----------

Both whole-unit build.sh gates pass: dynamic 6/6 and static 1/1; all literals
and import checks complete without baseline/skips. Strict prepare-current
receipts pass before/after consumers and 59/59 provider rows. Dynamic EH graph
is EXACT and its two renumbered funclet labels remain verified by parent state.
Object proof compares every retained emission and both provider findings.
The four-source link_check CLI has exit 1 for the documented remaining static
and provider blockers; dynamic is LINKS. New-COMDAT admission, frozen-file,
class gate, converged data (8 addresses, zero second names), CSV and whitespace
checks pass. Affected-unit place_bodies reports zero bodies and zero pins.

Data shadow reports seven existing wrong-name findings on the warning statics,
lastActiveVertexBuffer and static DX8Wrapper globals; unchanged ordinary sections
and external bindings prove this edit does not alter those references. These
still need owner reconciliation; no data-back gain is claimed.

Donor review
------------

Verified BFME1 pointer 23b143233b5a8664a3bdf8572df6d905c310a5a1 and successful
freshness stamp 2026-10-14 08:17 remain current. Reused this seat's prior broader
linking review, read d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (suppress surplus
constructor emitters) and 35bf0d0b18da30aefe812143de4a8add3ea21565 (retail COMDAT
ownership). Those repair principles apply; donor aliases, pins, class layouts
and source bodies do not. No donor input changed. The previous inverse repair
provided a lead. MeshClassRenderWithFXMaterial's two recorded byte refusals
were not retried. The compatible local static-shadow definition was swept
successfully; other constructor consumers need separate supported codegen work.

New authored C++ bytes: zero. Strict compiler currency and bytes are verified;
1985-byte gain is a legacy local link preview. Self-strict placement,
closed-strict closure and fresh census gains are unmeasured. No full census,
link cycle, nightly, boot or scheduler runner was started. Reproducible proof,
original sources/objects and logs are preserved in build/shadow-matrix-link-20261014.
