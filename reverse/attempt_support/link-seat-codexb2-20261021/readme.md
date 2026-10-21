# Link-repair seat handoff, 2026-10-21

Four independent repairs add **633 non-padding matched bytes** in current-source
link_check previews against the published d08db10acb index (18:42 UTC):

| Commit | Repair | Newly linked B |
| --- | --- | ---: |
| 67f0125001 | Tribute update calls existing Rva0050F0AB owner | 125 |
| 45fd609d5a | Siege ctor view declares actual virtual destructors | 193 |
| f2cce562d3 | Owned-pointer member dtor remains an out-of-line callee | 182 |
| 104197615e | Remove unused donor firing-mask initializer from topple TU | 133 |

Each repair has its own tracked evidence directory. All touched code passed
ordinary build.sh byte gates and explicit-provider --prepare-current strict
receipts, followed by successful paired/current-source link_check previews.
These are self-strict source checks and local previews, **not closed-strict
link-cycle gains**. No full link cycle or census was run. No ledger row, pin,
baseline or verifier rule changed. Existing shadow data-name warnings were not
claimed as repaired. New authored C++ bytes: zero.

`python3 tools/progress.py origin/master` completed: byte-matched 7,917,412 B,
authored game C++ 7,190,067 B, census linking 6,070,618 B, all with +0 delta.
The command reads the unchanged published census, not these local predictions.

## Resume without repeating stale work

The published index is older than the checkout. Current probes already LINK
for memory_pool, mapper, quat_BuildMatrix4, PointGroupClassRender,
Rva00462710ModeCheckForEach, W3DTruckDrawCtor/Dtor, W3DTankDrawConstructor,
AptTimeLineRva00520CD1, and the string-list tree/pair providers. The
HAnimComboDataSetHAnim + W3DMeshHolderHold pair links when both current sources
are supplied (237 B). Do not count these pre-existing gains again.

Map-subscript Rva00534A2A (150 B unit) remains blocked: its private map dtor
calls the owning-tree Rva00053DC5 dtor, unlike the kept canonical map dtor.
A dllimport/forceinline trial retained 4/4 byte rows but left an unresolved
__imp_map_dtor EH reference. Restored the source and strict-verified it, logged
blocked evidence through re_log.py, released all candidate claims. Do not alias
the semantically distinct destructors.

The tribute-row sibling Rva0050FC54 remains blocked by two unrowed virtual
destructors, in addition to the same wrong rva0050F306 owner repaired in the
update caller. Correcting only the call cannot link that unit. Source untouched.

Higher-ranked prerequisites retain recorded banks/evidence: AIPlayer supply
callee; locomotor 1E7ECA; Apt key destructor inline/unwind shape; allocator lock
guard dtor inline/out-of-line Release shape; VectorClass<Vector3> deleting-dtor
compiler shape; PartitionFilter virtual contracts; NetPacket getCommandList;
W3DModelDraw BD6C2; collision sort; VP6 clean-room dependencies. Do not retry
unchanged failed source variants. Other scope-wide class claims remain active.

Checked lanes: link_rank --top 30/--near 2 and kind U/D; class_views --blockers
and header-adoption order; donor linking-repair history at the verified BFME1
pointer; repair_queue link; name_globals --dry-run (0 edits); rehome_rows
(blocked by missing build/link_census/census.log). No matching data-back artifact
was available for data_back_rank, so no ranking was fabricated. Missing census
log was not regenerated. Stop at the session context checkpoint; queues are
not declared exhausted. The next seat should use current-source paired probes
and existing evidence before editing a ranked candidate.
