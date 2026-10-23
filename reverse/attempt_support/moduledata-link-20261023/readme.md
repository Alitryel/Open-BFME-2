# Module-data link repairs, 2026-10-23

## GettingBuiltBehaviorModuleData

Target table VA C40090 contains all 31 slots of the existing
`Code/GameEngine/Include/Common/BfmeModuleData.h` interface: its own deleting
destructor 4534D9, then the shared base entries documented by that header,
with no overrides. The matched destructor restores Snapshot table BBB554.
The constructor previously emitted a one-slot table and the destructor a
four-slot pure table. Adopt the established interface in both units; inline
the Snapshot teardown using the same pattern as AutoAbilityBehaviorModuleData.
This also removes the constructor's artificial EmptyBase and g_emptyBaseSink.
Member layouts and constructor/destructor bodies are unchanged.

Against published census index 491a8b3d87 (2026-10-23 03:12), paired
`tools/link_check.py` previews on the constructor shard and destructor:
before 179 -> 179 B, after 179 -> 388 B. The constructor newly links 209 B;
the destructor's 179 B remain linked. These are scoped legacy predictions,
not measured placed/self-strict/closed-strict link-cycle gains.

Acceptance: `./build.sh` both sources passes 9/9 rows, string and float
references pass; `tools/eh_verify.py` reports EXACT 2/2 graphs;
`tools/find_declared_unmatched.py` passes. `tools/link_check.py
--prepare-current` byte-verifies both with strict reusable receipts (this
establishes current inputs, not link closure). No full link cycle was run.

## CallHelpOnDamageModuleData

The matched destructor at 4BB517 and its EH graph establish a filter at +18,
followed by Snapshot-table restoration at BBB554. Its private UpdateModuleData
view previously emitted a one-slot table and competing destructor/deleter
copies. Use the established novtable ModuleData interface and retain the
intermediate base's +4 field in the derived layout. This consumer does not
change the separately owned UpdateModuleData destructor or its ledger row.

Paired single-file preview on the same index: before 0 -> 0 B, after 0 ->
58 B. Normal byte gate 2/2, EH graph EXACT 1/1, declaration check passes;
`--prepare-current` verifies its strict reusable receipt. This is another
legacy scoped prediction, with no measured closed-strict gain.

## Related triage

BridgeBehaviorModuleDataDtor and the folded destructor at 49B47C are held
by another worker; no edit attempted. CreateCrateDieModuleDataDtor's matching
base repair would touch that same claimed address. Transport's destructor
already links when previewed with its current UpdateModuleDataDeletingDtors
provider (195 -> 312 B without an edit), so no credit is claimed for it.
