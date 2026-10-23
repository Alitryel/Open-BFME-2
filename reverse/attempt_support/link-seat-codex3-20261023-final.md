# Link repair seat handoff, 2026-10-23

BFME2 start fc1e27b6f4; published census b711de3634 (2026-10-23 14:28,
retail-truth-4); BFME1 verified 96c88c73a5cd1a58fc2f8db691beea50acd996db.
No production source change survived this session. No new linked, self-strict,
closed-strict or authored C++ byte gain is claimed. Existing unpublished map
repairs predate this session; their gains must not be counted again.

## Tested repair and disposition

The Streak group was claimed (two units and 67 RVAs). Several byte-exact local
header/visibility trials removed the wrong Streak destructor but retained the
float deleting-destructor conflicts and linked zero bytes. Two final compiler
trials failed byte acceptance. Both production files were restored and all 69
claims released. See [the detailed evidence](streak-float-wrapper-link-20261023/readme.md)
for the remaining instruction differences, provider order and rejected variants.
The attempt log records the blocker. Resume only with a new provider/codegen
explanation rather than repeating those trials.

## Checked alternatives

- `link_rank.py --top 30`, `--near 2`, and wider near cohorts; current-source
  `link_check.py` preview of 55 high-ranked units. Sixteen units already link
  using current upstream sources (33,997 bytes in that preview); these are
  inherited changes, not authored repair gains. The published census is stale
  with respect to them.
- `class_views.py --blockers`: remaining useful views require complete ABI/table
  reconciliation. GeometryInfoCtor was held by another worker; GameLOD and
  supply-truck work also had live competing claims. No claimed scope was edited.
- `repair_queue.py link --limit 12`: same census-backed leads, checked against
  current previews rather than treating the stale rank as new repair evidence.
- `name_globals.py --dry-run` on the eligible authored address-blocked getter,
  thunk and destructor units: zero proposed changes. Generated units were left
  to their owning tools.
- `rehome_rows.py` candidate inspection and paired current previews:
  GeometryShapeConstruct/home vector and LadderPreferences comparison/home
  remain zero linked. Other provider/consumer conflicts prevent rehoming alone
  from freeing either unit. No ledger move was retained.
- A filtered unresolved-pin/row-owner audit found additional name leads, but
  direct current previews and prior evidence confirm prerequisite walls below.
- Reviewed existing BFME1 linking-repair handoffs at the unchanged verified
  donor revision. No new donor revision or resolved dependency reopened their
  blocked trials. No census build, full link cycle, nightly or boot runner ran.

## Remaining concrete prerequisites

- PeerDefs/UserPreferences: the 383BAC integer/string-looking insertion chain
  and rowed 500CFE chain are different retail instantiations. See attempt-log
  record for PeerDefs at 2E451B; do not bind the wrong create_node by byte shape.
- SunRays: actual RefCountPtr-reference texture setter versus the rowed raw
  pointer spelling, plus four coordinate-array definitions. Correct provider
  ABI and data ownership together before claiming its unit links.
- OpaqueScalarDeletingDtorsB04: current 499-byte unit still has four undefined
  address-class destructors whose addresses now have real owners. Existing
  class-identity/naming reconciliation is prerequisite (attempt 2035F5).
- CollisionManagerImpl_Update: real UpdateSort is a thiscall but this caller
  preserves ecx implicitly across the preceding call; ordinary member respelling
  inserts an instruction. Existing attempt 75A490 documents the byte failure.
- Rva00066A9ABody: current 371-byte preview remains blocked by both shader/filter
  roots. Prior evidence maps their missing leaf objects and vtables; roots alone
  do not verify the data relocation graph.
- Resolve-battles destructor: current preview has undefined derived phase
  methods rva0057556D and rva00576ACB. These are class/provider prerequisites,
  not grounds to invent empty virtuals.
- Sentence destructor: prior byte-exact native element teardown patch is still
  blocked by the selected pending-surface Resize and private-class access.
  See sentence-binding-link-20261023/readme.md; no unchanged trial was replayed.

Final checks: check_csv passed; the restored Streak unit passes its complete
byte gate. Evidence-only commit hooks passed. Claims were released. The runner
owns publication of any final unpublished commits. Progress reporting remains
census-derived and does not certify a new closed-strict link gain.
