# SpecialPowerCreate pool/callback receiver prerequisite — 2026-10-26 codex

Allocated family A / shard 0. Destination:
`Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreate.cpp`.
The runner queue authorizes this destination; its read-only allocation is not
merge approval. No merge, row move, rename, compiler change or debt retirement
is applied here. The constructor and both mixed donors remain unchanged.

## Baseline and bounded repair

`tu_skeleton.py --plan` rebuilds current routing in memory: six approved rows,
three direct donors, two mixed sources (ConstIntGetters4.cpp and
Rva004B8CDEDerived.cpp), no refused sources. The Create-prefix naming planner
records private receiver/compiler discrepancies, constructor hatch and
unledgered-definition constraints, and donor path hints. The callback's own
existing target evidence independently identifies constructor 0x004B9345's
secondary table 0x008596A4 slot 1 as callback 0x004B93EF. A donor same-name hit
alone is not target placement or layout proof. No regenerated TU map is staged.

The baseline normal composition accepts only SpecialPowerCreatePoolKey.cpp,
two rows / 79 bytes. It rejects the constructor with C2511 and the callback
with C2039 (`onBuildComplete` absent from the selected class). Local receipt:
`build/codex-specialpower-before-20261026.txt`. Ordinary baseline verification
passes 4/4 rows / 178 bytes across all three direct donors, including the
constructor. Frozen checks pass; the constructor's existing unmatched
destructor marker remains and is not extended or removed.

The scoped SpecialPowerCreateView.h factors the callback's existing measured
receiver declarations without changing their fields, base offsets or neutral
slot names. The pool unit adopts that receiver and contributes its existing
virtual const key-method declaration. This partial method set is not a full
retail vtable/constructor contract. Neither consumer instantiates the view;
paired object comparison proves neither emits a new vtable. The callback's
flag remains at 0x14, create interface at 0x10, Object module array at 0x244.
No constructor declaration is guessed.

## Verification

`./build.sh` for callback and pool passes **3/3 rows / 136 bytes**, one string
literal and no float/import references. Frozen and class gates pass. Before
and after objects have exactly the same complete non-debug section bytes,
flags, COMDAT selections and normalized relocations; external code/data,
undefined references and aliases are identical (callback 2 sections / 1 code
definition, pool 8 sections / 1 code definition). No shared selected provider
or consumer binding changes. This is complete object comparison, not only
matched function bytes. Scratch evidence:
`build/codex-specialpower-{object-proof,reference-delta,data-delta}.json`.

The pool's existing data baseline key and two data-ledger entries remain in
place. The key's historical wrong-name finding is not fixed by this receiver
repair. The constructor's hatch and unmatched body remain owned there. No
scoped identity-register key is retired. A future merge must carry the pool
register entries through the tool's printed transfer path and verify actual
composed provider/consumer bindings again.

Strict preparation, final composition and publication evidence follow below.
Recovered C++ bytes: 0. Source files removed: 0. Registered debt retired: 0.

Paired `allowed_symbols.scan` results preserve all **4/4 reference facts**,
with no additions/removals, and `data_check.object_facts` definitions and
references are equal. The full-object proof shows no added vtable or helper.

The combined tooling audit covers merge-base 73ffc391c4 through all pending
commits (inherited 92faf73b14, Sway 240fd4de66/a3b9a2d300) plus this trial.
There are no existing source path changes. Searches across active tools, hooks,
workflows, build.sh, source includes, registries and Doxygen find five intended
consumers of the two scoped headers and the existing Doxygen Sway seed input.
Historical structural/dead-end fixtures and original EA/donor path strings
remain unchanged. All five consumers have ordinary byte checks; both Sway and
its selected GameLogicInit provider remain strict-current after this header
addition. No TU map, protected baseline, name register or data owner changes.
The planner is regenerated after the source change; no composition scratch
source is created during planner or strict preparation. Scratch search output:
`build/codex-prerequisite-pending-path-audit.txt`.

## Final acceptance and remaining work

`link_check.py --prepare-current` for both explicit consumers passes 3/3 rows
and strict reusable receipts; the ordinary gates reuse the same objects. The
complete section/definition comparison is repeated after strict preparation and
remains equal. `data_check.py --converged` passes two sources / ten addresses,
zero second names and zero unjudged rows.

The post-repair `tu_skeleton.py --merge ... --dry-run` now accepts pool and
callback together, **3 rows / 136 bytes across 2 sources** instead of only the
pool's two rows / 79 bytes. Receipt:
`build/codex-specialpower-after-20261026.txt`. This demonstrates one additional
existing callback row accepted for future composition, not recovered bytes or a
confirmed Luna landing. Constructor C2511 remains; both mixed sources stay
behind. The future merge still prints one data-baseline and two data-ledger
transfers, with its required Verifier-Change trailer. No debt is retired.

Keep the destination, three direct donor, new header and this handoff file
claims until publication is confirmed. The constructor is unchanged; its claim
covers the bounded coherent trial only. The earlier Sway and inherited
documentation claims also remain held while their commits are pending. No
other worker's claim or cross-family donor was touched.

`link_check.py --new-variants --paths-from
build/codex-specialpower-sources.txt` also exits zero. No census, link cycle,
nightly builder or smoke test was run.

## Session close and publication handoff

The prerequisite is committed as `f1831265b0`. Its header-dependent gate passes
30/30 rows in three sources including Eva.cpp; the final scoped gate passes
3/3 rows plus one EXACT EH graph. Code identity reports zero new findings.
The two existing pool wrong-name findings are at 0x00A03F98 and 0x00A03F9C,
outside the historical-name baseline; complete object/data equality proves
they predate this repair. The baseline key and both ledger entries remain.

At session close the source commits and inherited documentation are local:
`92faf73b14`, `240fd4de66`, `a3b9a2d300`, `f1831265b0`. The last two publish
attempts both returned immediately because another agent was pushing. No
pre-push selected-provider/lost-byte/input-freshness batch audit has yet run
for this outgoing batch; inspect its report at actual publication and carry
inconclusive freshness findings into the next census/obstacle handoff. No
maintainer-only measurements are authorized or run. These are pre-rebase
commit IDs; the runner can rewrite them while publishing.

The compatibility audit covers merge-base `73ffc391c4` through these four
pending commits and this final documentation update. Existing source paths
are unchanged; the only added Code paths are the two scoped headers, with the
five intended consumers verified together. Relevant moves/consumers did not
change after the combined audit above. No protected register or generated map
changes are pending.

Keep these **14 file claims** until actual publication is confirmed, then
release file scopes and run `claims.py release --landed`:

- `docs/linking_obstacles.md`
- `reverse/attempt_support/consolidation-sol-prerequisites-20261026-codex.md`
- `reverse/attempt_support/consolidation-sway-receiver-20261026-codex.md`
- `Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdate.cpp`
- `Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdatePoolKey.cpp`
- `Code/GameEngine/Source/GameClient/Drawable/Update/SwayClientUpdateView.h`
- `Code/GameEngine/Source/GameLogic/Object/Update/SwayClientUpdate_xfer.cpp`
- `Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp` (verification only)
- `Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreate.cpp` (trial destination)
- `Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreateConstructor.cpp` (unchanged)
- `Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreateOnBuildComplete.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Upgrade/SpecialPowerCreatePoolKey.cpp`
- `Code/GameEngine/Source/GameLogic/Object/Create/SpecialPowerCreateView.h`
- `reverse/attempt_support/consolidation-specialpowercreate-view-20261026-codex.md`

Results: two receiver prerequisites demonstrate future composition of Sway's
six rows / 1,218 bytes and SpecialPowerCreate's three rows / 136 bytes. No Luna
landing is confirmed. The separate Sway cleanup removes one divergent helper
copy, leaving its same strict-current selected GameLogicInit provider. File
reduction, recovered bytes and registered debt retirement are each zero.
Remaining work is constructor/virtual-table contracts, mixed donors and the
existing pool data names. AssaultTransportAIUpdate and SupplyWarehouse plans
retain their previously recorded structural blockers; GameMemory has mixed
and cross-family allocator prerequisites. No unchanged blocker was repeatedly
built, and no unrelated lane was used.

Final `python3 tools/progress.py origin/master` passes: BYTE-MATCHED
7,978,500 bytes / 100%, authored C++ and exact covered bytes each delta +0.
The local checkout still carries census f995f30157 while origin has a newer
history; its printed LINKING/LINKED negative comparison is between those
census records, not a measured loss from these source changes. No current
linked-byte gain/loss or NOT OURS change is claimed. Raw local output:
`build/codex-progress-final-20261026.txt`. Publication status after this final
handoff commit is recorded by the runner's session-close metadata.
