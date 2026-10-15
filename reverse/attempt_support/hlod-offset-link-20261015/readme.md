# HLod offset-comparison emitter repair

Source base: af4a9c854d. The runner census index measures 19a2565407,
2026-10-15 09:33 UTC (underlying census 5986a99448, 04:52). The older
committed link_status.csv served discovery only. object-proof.json records
the index hash, strict current-object receipts and paired local previews.
No index, status/history, baseline or data-back artifact was changed.

HLodUpdateSubObjectTransforms.cpp emitted a surplus 60-byte external
Vector3 inequality copy, rejected against the 58-byte retail provider at
0x0007B38C. Its only source use was already inlined in the additional-model
loop. A TU-local forceinline helper keeps the donor component comparison
and short-circuit order while removing that unused external definition.
No shared header, class, compiler option, provider, ledger, pin, global,
marker or escape hatch changes. The file was scope-claimed before editing.

Target proof remains the existing 1,283-byte HLod method row at
0x0019D640..0x0019DB43. The local helper's X/Y/Z semantics are carried from
vector3.h, lines 328-331, in verified BFME1 donor
 a7c38d3b2597121f178ab5190b3062478823257d.
The compiler receipt resolves the actual header under game/Libraries/
Source/WWVegas/WWMath, not a silently substituted include. This repair
adds no identity, layout or recovered-byte claim.

Donor linking repair d3f9000fe08615a100e844adfff57fa4a39cd615 was reviewed:
its verified removal of a surplus TileData constructor supports the
incidental-emitter mechanism; its class/layout changes are inapplicable.
The existing frustum-link-20261013 repair supplies the local-helper
precedent. Official BFME1 master was fetched at
1c4d808dd6a0f2bd514f607f40e9e422db3ab91b.
The overdue comparative full-gate update remains under another worker's
file:reference/open-bfme-1 claim. Clean verified inputs and the old
success stamp are retained; no completed freshness check is claimed.

Acceptance:

- Bounded link_check.py --prepare-current passes before and after: one
  complete row exact; six float literals verified, no skipped/baselined
  references; strict reusable self receipt. The normal ./build.sh passes.
- Whole-object proof removes exactly the rejected inequality COMDAT.
  All sixteen retained COMDATs preserve raw bodies, extents, normalized
  relocations, digests and retail verdicts. Ordinary sections/directives,
  strong definitions, undefined references and weak bindings are unchanged.
- Same-index paired preview: three COMDAT findings become two, with no
  added finding. Ordinary local link_check agrees and returns 1 because
  the Matrix3D default constructor and WeightInfoStruct vector-deleting
  destructor still fail retail truth. New-variant admission passes.
- Declared-definition, class, converged-data (eight addresses, zero second
  names/unjudged rows), shadow-data (zero findings), EH (zero rows), CSV
  and whitespace checks pass. Hooks also check the staged hatch counts.
- place_bodies.py rescans the changed unit: zero new bodies or pins.

Cause sweep: the index lists only meshbuild.cpp as another losing
inequality emitter. Its three color comparisons have the same donor
expression, but the unit retains Vector2 inequality plus Vector3 Length,
Normalize and Normalized_Cross_Product conflicts (five total; six rowed
bytes). This whole reference unit needs separate provider evidence and is
not changed or assigned a new blocked verdict by this repair.

Authored C++ coverage +0; legacy LINKED stays 0 -> 0. This is a verified
reduction of one link-rule finding, not a clean-link gain, closed-strict
gain, measured census gain or actual link.exe placement. Broader linking
requires the maintainer runner; no full census, link cycle, nightly or
boot operation was started. Source/object/receipt snapshots remain under
build/hlod-offset-link-20261015. Unrelated untracked work is preserved.
