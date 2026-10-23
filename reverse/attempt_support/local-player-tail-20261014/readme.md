# Remaining local PlayerList accessor link repair

Base checkout: 189b7eec4c. Discovery used repair_queue.py link and link_rank.py;
the committed link_status.csv measures 67e1365aa9. Paired previews use the
runner-provided index measured at 147cfae2cb, 2026-10-14 07:27. Its SHA256,
source hashes and before/after object hashes are in object-proof.json.
No census index, status, history, baseline, pin or per-row data artifact changed.

This drains the ten consumers handed off by the InGameUI repair in
../local-player-sweep-20261014/readme.md. Each independently inlines a
PlayerList view reading +0x10, but emits a surplus generic getLocalPlayer
COMDAT (8b4110c3). The indexed first copy in PartitionManager.cpp reads
+0x0C (8b410cc3, digest 96acfa69671b); the index has no retail address for
the generic accessor. Different implementations cannot share that linker name.
Each local helper and its inline callers now have a distinct implementation
name. These names establish neither a retail identity nor a canonical layout.
Target evidence for the retained +0x10 accesses is the existing callers' full
byte gates; no donor layout or global binding was imported.

| Consumer | Legacy findings before | After |
| --- | ---: | ---: |
| GUI/parseSpellIndex_Thunk.cpp | 5 | 4 |
| W3DGhostObjectScene.cpp | 38 | 37 |
| SymbioticStructuresBodySlots.cpp | 3 | 2 |
| Tactical/BannerUI.cpp | 7 | 6 |
| BezierProjectileBehaviorFire.cpp | 3 | 2 |
| W3DPropBufferDrawProps.cpp | 8 | 7 |
| W3DRadarRenderObjectList.cpp | 8 | 7 |
| RTS3DSceneFlushOccludedObjectsIntoStencil.cpp | 5 | 4 |
| EvaRva001DDF04.cpp | 3 | 2 |
| W3DBuffBufferFill.cpp | 4 | 3 |

The same-index legacy preview removes ten losing COMDAT findings. All other
finding categories and the generic keeper are unchanged. All ten units still
have independent blockers: clean units remain 0/10, LINKED remains 0 -> 0 bytes,
and new authored C++ bytes are zero. The repair records reduced conflicts,
not a placement gain. Strict reusable receipts establish the ten owned objects
current before and after (self-strict object evidence). Closed-strict provider
closure, actual link.exe placement and a fresh census were not measured.

Full-object comparison preserves every renamed helper's four bytes and extent,
all 386 retained COMDATs' complete raw bytes, sizes and relocation digests,
every nondebug relocation's symbolic target, ordinary nondebug sections,
symbolic EH targets, external undefined/strong/weak bindings and hatch counts.
The proof refreshes only these ten owned objects in separate in-memory copies
of the same index and checks its persisted hash remains unchanged.

Acceptance:

- Bounded link_check.py --prepare-current before and after, in two five-source
  groups: all 92 rows exact, strict reusable receipts, no provider expansion.
- Ordinary ./build.sh: 92/92 exact; 42 string literals and six empty-string
  references, 25 float literals and four named imports verified; none baselined,
  skipped or unverified. Seven existing funclet pins are independently placed
  past renumbered local labels by verified parent EH data.
- EH verification: 24 EXACT, none nonexact, baselined or missing.
- Prescribed local link_check.py and paired before/after previews completed.
  The ordinary check exits 1 because the independent blockers remain; the
  paired proof establishes the ten removals and absence of added findings.
- Frozen-definition, class, new-variant admission, CSV and whitespace checks
  pass. Converged data: ten sources, eight addresses, no second names or
  unjudged rows. Paired data proof preserves every binding and definition;
  nine shadow wrong-name findings are pre-existing and identical.
- Affected-unit place_bodies.py resweep: zero bodies, zero pins.

Remaining blockers are listed fully in paired-link-after.txt: missing spell
store providers; ghost-object duplicate definitions, virtual providers and
selected copies; symbiotic helper declarations; BannerUI vector/global/region
providers; projectile WeaponTemplate methods; prop fog/shroud providers and
Matrix3D copies; radar globals and local getters; stencil duplicate/getters;
Eva's duplicate priority helper and tree iterator; buff mesh providers and
tree iterator. These independent causes were not retried or renamed.

Reference review is inherited from ../local-player-link-20261014/readme.md:
verified BFME1 revision 23b143233b5a8664a3bdf8572df6d905c310a5a1,
link repairs de59a7e9, d2e21369 and b955ec48. The conflicting local emission
cause applies; donor-specific layouts, pins and aliases do not. No unchanged
donor scan was repeated. The 2026-10-14 08:17 freshness success stamp remains
under 24 hours old; the verified reference inputs and pointer are unchanged.

Ten file claims protected the batch. Reproducible proof scripts and exact
source/object/dependency backups remain in build/local-player-tail-20261014.
No full link cycle, census build/measure/history, nightly, boot or scheduler
runner was started. Normal commit hooks and runner publication remain required.
