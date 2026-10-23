# Sphere add: remove the surplus scalar-multiply copy

Base: 9dc4a987d8307251798c60a4b2dd2ca73bee15b2. Source:
Code/Libraries/Source/WWVegas/WWMath/SphereClassAddSphere.cpp.
Paired runner index: 19a2565407, 2026-10-15 09:33; underlying census
5986a99448, 04:52. Its SHA256 is recorded in object-proof.json. The committed
link_status.csv is discovery evidence from a different measurement and is
not used for a paired gain. No matching data-back artifact was ranked.

The unit emitted a 55-byte Vector3 scalar-multiply COMDAT
(??D@YA?AVVector3@@ABV0@M@Z) that the retail-truth check rejects against the
54-byte owner at 0x00066382 in vector3.cpp. Add_Sphere already inlines every
use, so there are no nondebug references to the surplus symbol. Apply the
same dllimport/forceinline spelling already used by this unit's Length and
the existing bfme_vector3_full_link view. The multiplication remains real
C++; only the unused competing external definition disappears. No import,
pin, alias, header, compiler flag, datum, range or ledger row is added.
Identity/layout evidence and donor provenance remain those of the existing
277-byte Add_Sphere recovery; this repair does not import donor code or
resolve the existing helper owner's scalar-divide prose discrepancy.

Acceptance and limits:

- Before and after: bounded link_check --prepare-current passes the row's
  full byte gate with strict reusable receipts, one float literal, zero
  skipped string/import references. The ordinary ./build.sh also passes.
- Object comparison removes exactly the 55-byte helper and its external
  binding. All seven retained COMDATs and all eight retained nondebug
  sections have identical full bytes, extents, normalized relocations and
  bindings. Directives and the existing address-taking anchor are unchanged.
  No nondebug caller referenced the removed symbol before or after; no
  external binding is added. Source/object/receipt hashes are in the proof.
- Paired in-memory refresh of this same unit into the unchanged index:
  findings fall 2 -> 1. The wrong helper copy is gone; wrong_selected
  Add_Sphere remains. Ordinary link_check agrees (expected exit 1).
  The unit's 277 existing nonpadding retail bytes remain locally unlinked:
  LINKED 0 -> 0, new authored C++ bytes 0. This is verified blocker reduction,
  self-strict object acceptance and a legacy local preview, not a closed-strict
  gain, census update or executable-placement result.
- Enforced data and converged-data checks: zero findings, second names or
  unjudged rows. Frozen definitions, class gate, CSV, new-variant admission
  and whitespace checks pass. Placement resweep finds zero bodies/pins.

The remaining selected-provider conflict is independent. The index has
three wrong Add_Sphere copies (hlod, composite, collect), followed by this
retail-exact copy. An out-of-line-definition trial still byte-matched but
introduced a duplicate definition and retained the wrong-selected finding;
that trial, including anchor removal, was reverted. Repair those providers
or their shared donor-header emission with appropriate scope and gates;
do not repeat the strong-definition trial. The same-symbol loser scan also
finds Locomotor.cpp (57 findings) and sphereobj.cpp (86 findings). Those
whole-file repairs are left outside this bounded repair; no improvement in
them or their consumers is claimed. Saved objects, receipts and the complete
comparison script remain under ignored build/sphere-add-link-20261015/.

Reference review: clean verified BFME1 pointer/checkout remains
 a7c38d3b2597121f178ab5190b3062478823257d. Reviewed donor d2e21369067f
(remove wrong surplus constructor definitions) and de59a7e9f891 (converge
inline spelling without changing matched callers). The emission principle
applies; donor layouts/addresses do not. Official master was fetched at
fd65b3542; the reference scope is held by another worker, and the existing
old/new full-gate comparison is unfinished. No pointer update or successful
freshness stamp was made. No maintainer-only runner, index/status/history
publication or full link cycle was started.

Initial queue checks also found AptMpGameSetupRefreshMapList already LINKS
at 1713 current bytes and ParticleSystemDebugDisplayBody already LINKS at
1007; neither receives credit. The latter has a foreign live claim.
TerrainLogicWaypointLookups retains its recorded MSVC comparator-shape
blocker; its short-lived file claim was released without another trial.
