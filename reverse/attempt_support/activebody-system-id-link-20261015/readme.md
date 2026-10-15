# ActiveBody particle-system ID emission repair

ActiveBody.cpp emitted an unused `ParticleSystem::getSystemID()` COMDAT that
disagreed with the first census copy. Its matched createParticleSystems caller
already inlined the established ID field at +0xA8. Read that field directly and
remove the getter definition, completing the available fourth consumer of the
repair documented in particle-system-id-link-20261015/readme.md.

The target caller's existing bytes establish the field access. No donor layout,
new class identity, header, compiler setting, global, pin or ledger row changes.
This does not reconcile the other private ParticleSystem views or establish
retail identity for the census's unpinned getter copies.

## Measurement and object evidence

Base checkout: ae53a7d0a89c0031bd99e52fa41ec54b08c46e9b.
Unchanged census: 28269d8e8d, 2026-10-15 09:31 UTC; index SHA-256
6128e4df8c49e7783f07dcf447831cfd3c9850b9bf46249d968878411907b551.

The before object has exactly one finding, the getSystemID COMDAT conflict.
The after object has none: **legacy local preview LINKED 0 -> 5,556 existing
matched bytes**. Both comparisons use the same index and current ledger.
paired-link.json independently evaluates the preserved before object and the
current object through link_check.check_object. The normal CLI preview agrees.

Before and after bounded preparation byte-verify the explicit consumer and
produce self-strict reusable receipts. object-proof.json compares every retained
nondebug section's complete bytes, extent, flags and symbolic relocations.
Local relocation destinations include their section contents and offset;
SafeSEH indices are normalized to bindings. The only removed COMDAT is the
getter; all **127 retained COMDATs** are unchanged. External and weak bindings
are unchanged, and no retained section references the removed getter.
Debug sections are excluded from this comparison.

No new authored bytes, closed-strict closure, executed linker placement or
new census gain is claimed. The index, link_status.csv and history are unchanged.

## Acceptance

- Ordinary byte gate and bounded strict preparation: 33/33 rows, five string
  literals, two empty-string references and 17 float literals pass.
- EH verifier: 5/5 EXACT, no baseline discrepancies or missing objects.
- Local link preview: clean; new-variants admission passes.
- Identity shadow: 33 rows, zero problems. Data enforcement and converged-data
  enforcement: zero findings, zero second names or unjudged rows at eight addresses.
- Frozen-file and canonical-class checks pass.
- place_bodies rescan: zero bodies, zero pins. CSV and whitespace checks pass.

The earlier sibling repair is already committed. Its three consumers were
rechecked without edits: TransitionDamageFXParse and LaserUpdateInitLaser remain
clean; BoneFXUpdateUpdate retains its independent allocator allocate/deallocate
conflicts. These are not additional gains from this change. ScriptActions also
retains its separate unresolved Object command dependency. The queue's
ModuleFactoryInit item already passes its current local preview.

Ignored snapshots, strict-preparation logs, comparison script and local check
outputs are under build/activebody-system-id-link-20261015. Verification used
gpt-6.1-sol. No census build/measure/history, full link cycle, nightly or boot
runner was started; broader verification remains outstanding.

## Donor review and freshness

Retained clean verified BFME 1 gitlink and checkout:
a7c38d3b2597121f178ab5190b3062478823257d. Reviewed its
ParticleSystemSetSlave.cpp: its handle dereference and implementation ID at
+0xAC differ from this target view and are not imported. Reviewed donor linking
repair d3f9000fe08615a100e844adfff57fa4a39cd615 and its verification message:
removing an incidental competing emitter while preserving the exact caller is
applicable; the TileData constructor, ABI and layout are unrelated. The existing
dedicated donor sweep in link-inline-emitters-20261014/readme.md remains relevant.

Fetched official BFME 1 master, resolving to
800b363f6af4a15f064628bff2fc74b15768709f. The reference checkout has a live
foreign file claim, codex-6bc6-20261008, so the verified inputs and pointer were
preserved. Its overdue pointer update still requires the separately owned
comparative full verification; no freshness-success stamp was written.

## Preparation recovery reconciliation

During recovery onto 609e786376, upstream commit 8bcccb00c7 already
suppresses this same getter emitter with an imported forceinline definition.
The file is now claimed by yasinschroeder-codex8. Retain upstream source
without applying the equivalent direct-field rewrite. The measurements above
describe the preserved pre-rebase trial, not a new gain against current
upstream. Original commit 863e4456b8 and snapshots remain available under
refs/runner/preparation/1792063497776013065 and the ignored build directory.
Only the historical evidence and attempt record are replayed from that commit.
