# AI component-scaling emission repair

AIStatesBfmeOnExit.cpp and AISpecialPowerPickers.cpp now use an imported
forceinline component helper for their existing Coord3D scale expressions.
The arithmetic, object layout, source flags and shared headers are unchanged.
No standalone helper or new import reference is emitted. Each consumer stops
emitting its unused 49-byte Coord3D::scale copy (digest 89f10a4f4b61), which
conflicts with the retail 49-byte body at RVA 0x000036D1 in region.cpp
(digest 9707cccd2882). No row, pin, alias, baseline or class contract changes.

Target evidence is the already rowed complete native AI state and picker bodies,
including their inline component multiplies. State identities, vtable and
WorldBuilder evidence and donor semantics remain in the sources and ledger.
This change establishes no new target identity or layout from equal bytes.
The shared Coord3DCtorView.h arithmetic guides the helper; the native gate and
complete object comparison establish that the emitted computations are retained.

## Measurement and acceptance

Base checkout 858a1765e0. The frozen runner index measures ac77c85054,
2026-10-15 14:25 UTC. The published index fetch retained that same index and
added 22,697 reusable compiled objects. proof.json records its complete hash,
original/repaired strict receipts and object/source hashes. Each source was
file-claimed before editing; the unchanged retail provider was also claimed
for bounded strict preparation.

A paired local preview independently substitutes both original consumers plus
the current retail provider, then both repaired consumers plus that same
provider, into in-memory copies of the identical frozen index. Findings fall
4 -> 3 for AIStatesBfmeOnExit and 5 -> 4 for AISpecialPowerPickers: exactly the
two wrong scale COMDAT findings disappear. Every other finding is unchanged.
region.cpp stays clean. Legacy LINKED remains 1,287 -> 1,287 bytes, consisting
only of the already linked provider; neither repaired consumer links yet.

All 96 and 40 retained consumer COMDATs have identical bodies, extents and
relocation digests. Every retained nondebug section, flag, byte, symbolic
relocation, linker directive, strong/undefined/weak binding is identical.
No retained relocation targets either removed helper. Original/repaired
version-2 receipts have identical command, dependency hashes, include inventory,
retry directories and search roots; only source/object content changes.
The initial static helper trial passed all 26 native rows but emitted an extra
unused local helper; the accepted imported-forceinline form removes that copy
as well. The final normalizer permits only removal of the original wrong scale.

- Final bounded strict preparation and its normal byte gate pass 133/133 rows
  across the two consumers and region.cpp; 12 strings and 32 float literals
  verify, with zero skipped or baselined literal references.
- EH data: 10 EXACT, zero nonexact/baselined/missing-object rows.
- Converged data: eight protected addresses, zero second names/unjudged rows.
  Enforced data check has one pre-existing finding, zero outside baseline;
  identical retained relocations prove the existing data bindings unchanged.
- Local link_check.py exits 1 for the seven retained unresolved bindings;
  the provider remains clean. Admission, class, declared-definition, CSV and
  whitespace checks pass; hooks independently check the staged source scope.
- Placement resweep finds zero bodies and zero pins.

proof.py replays against ignored snapshots in build/ai-scale-link-20261015.
The census index, committed status and history are untouched. Strict receipts
establish compiler input currency, not placement: no new authored C++ bytes,
self-strict placement gain, closed-strict gain or whole-game link is claimed.
No census build/measure/history, full link cycle, nightly or boot runner ran.

## Cohort, donor review and handoff

The same helper was tested once in Rva00544EB1OnEnter.cpp. Its proven 473-byte
body at RVA 0x00544C62 changes its random-scalar SSE schedule and becomes shorter;
the strict byte gate rejects it. Original source restored, restored gate 1/1,
blocked evidence recorded through re_log.py and file claim released. Trial
source/object and detailed mismatch log remain under the ignored snapshot path.
Do not repeat that trial without new codegen evidence. This is not a refusal
of the original matched function or the broader link-repair lane.

Other frozen-index scale emitters include bezier_segment, DeliverPayloadAIUpdate,
SpectreGunshipUpdate, RailroadGuideAIUpdate, DozerAIUpdateCtor,
HordeContainIface11CSlots, PhysicsUpdate and LaserUpdate. Their current object
and dependency scopes require separate checks; this repair does not claim them.
The remaining accepted-consumer blockers are three AI/pathfinder helpers and
four picker/result bindings, enumerated in link-final.log.

Reviewed BFME1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 and
66b19a8e95a4add525ef808fcea088e306798e2b: imported-forceinline suppression of
unused conflicting copies applies as an emission technique; donor names,
layouts, addresses and link gains do not transfer. Existing BFME2 scalar-helper
refusal evidence was read before this trial; those unrelated files were not
retried. The verified BFME1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d; official master fetched to 8df34a475.
The overdue comparative reference update remains under another worker's live
file:reference/open-bfme-1 claim. No pointer advance or freshness success stamp
is asserted. Model: gpt-6.1-sol.

## Preparation recovery, 2026-10-18

Replaying a9f4838af2 onto 384cb143ad found that upstream already replaced
both conflicting Coord3D::scale copies with its own scaleInPlace helper.
The conflict resolution retains those upstream helpers and every newer
provider/caller reconciliation (including IsHordeMeleeLinePassable). The
original scaleStateDirection implementation is not reintroduced. This
commit now preserves the original bounded evidence and deferred harvest
trial only; its historical measurements above are not a new link gain
on the recovered tree. Preparation backup refs/runner/preparation/
1792325105671221266 remains intact. No saved stash was listed.
