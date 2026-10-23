# Two ModuleData interface link repairs, 2026-10-22

Base: 87a274ef4a; census index: 08160bc2c9, 2026-10-22 17:08.
Toolchain and flags remain the source `// cl:` settings; additions select the
existing BFME2 AsciiString shim required by BfmeModuleData.h. No shared headers,
retail pins, destructor identities or verifier rules changed.

## Target evidence and repair

SpawnedModelConditionCreateModuleData's table at VA BF4228 and
AutoAbilityBehaviorModuleData's table at VA C41568 each have the existing shared
31-slot ModuleData interface. Reading 31 little-endian words from game.dat gives:

- slot 0: own deleting destructor, RVA 257C6C / 45A4FB respectively;
- slots 1, 2, 3: B3FD0, 65212, 47A69C;
- slots 4..13 and 15: 47A699;
- slot 14: B69A1;
- slots 16..29: D43D0;
- slot 30: 50B5C6.

Both private constructor views previously declared only Snapshot's four slots,
including three derived callbacks with no provider. Use the existing
BfmeModuleData.h interface in each constructor/destructor pair. Field offsets
and class sizes remain those proven by the rows. The shared view leaves the
intermediate inheritance unresolved: preserve the native Snapshot teardown via
the existing ModuleData destructor pattern, rather than inventing that hierarchy.

AutoAbility's native ehvec constructor callback is 45A1D9, already rowed as
AutoAbilityQueryEntry::init. Its 18-byte body sets state to -1, constructs the
member at +4, and returns this. Bind the compiler's element-constructor reference
to that existing owner with a TU-scoped alternatename; no second pin or renamed
identity is introduced. The target callback ABI and whole body support this
binding; the established source spelling is retained.

The actual AutoAbility constructor object now emits the retail-exact 28-byte
scalar deleting destructor. add_match --replace-existing moved its row from
FamilyDeletingDtors_muse-206f.cpp, which had a competing one-slot vtable and two
synthetic generation helpers. Remove that now-empty split unit. The destructor
unit also replaces its private StringBase template with the existing shim's
public, declaration-only char destructor setting, preserving the exact cleanup.

## Verification and paired measurement

Before/after link_check on the same sources and same index:

| Cohort | Before | After | Gain |
| --- | ---: | ---: | ---: |
| Spawned constructor + destructor | 48 B | 153 B | 105 B |
| AutoAbility constructor + destructor + removed split row | 91 B | 254 B | 163 B |
| Total | 139 B | 407 B | 268 B |

These are **legacy** per-file link predictions, not closed-strict measurements.
The four surviving units all link cleanly. --prepare-current byte-verified all
nine rows and prepared strict reusable receipts; it explicitly did not check
LINK closure or update the census/index/status. No closed-strict gain is claimed.

Normal byte gates: 9/9 exact, including the rehomed destructor; two complete
STL constructor folds verified; literal, float and import checks passed.
find_declared_unmatched passes (Spawned destructor retains its pre-existing
allowed anchor). data_check reports zero shadow findings. No source recovery
bytes were added by this repair.

The same-cause search found OpenContain's constructor also has missing private
ModuleData callbacks, but it has two independent COMDAT blockers, so merely
changing its interface would not yet establish a linked-byte gain. Several other
Snapshot-shaped constructor views already link in current sources; they were
left alone. name_globals --dry-run finds zero rewrites. The automatic rehome
queue cannot run here because the published index has no accompanying
build/link_census/census.log; this repair was verified directly instead.
