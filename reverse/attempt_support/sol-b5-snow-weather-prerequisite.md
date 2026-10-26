# W3DSnow weather-sync prerequisite, 2026-10-26

Seat codexb5, family B shard 1/2. Base c511118e28. Allocation queue lists
`Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DSnow.cpp` for this seat;
normal file claims cover the seed, Rva00093349.cpp and shared header.

## Change and provenance

Move the seed's existing partial declarations into a TU-local resource/weather
view consumed by both files. Expose receiver +58/+5C/+60 and weather +70/+74/+78
from the existing verified 0x00093349 body, retaining the seed's +74/+B0 extents.
Align donor flag/member spelling with the seed and use the shared inline
getFinalOverride directly instead of duplicating its first hop. These are
existing target accesses, not recovered donor names or a complete class layout.
The original seed's reference attribution remains in the header.

The first shared-header trial expanded an extra override hop in the donor;
a declaration-only trial changed seed register allocation. Neither trial is
retained. The final shared inline resolver preserves both bodies exactly.

## Demonstrated unblock

Before: normal `tu_skeleton.py --merge TU --dry-run` accepted no donor.
After: the unmodified normal merge pipeline accepts W3DSnow.cpp and
Rva00093349.cpp, reporting 15 composition rows (16 standalone ledger rows,
including the seed's existing EH aliases). This makes the existing 100-byte
weather-sync parent eligible to join the seed. No merge was applied and no
Luna landing is claimed. Remaining nine donor rejections concern OVERRIDE or
RefCountPtr duplication, missing receiver methods/fields and mixed routing;
the machine-readable full rejection report remains in
build/sol-b5-snow-composition.json. Leave compatible donor merging to Luna.

## Verification and identity

`./build.sh <seed> <donor>`: 16/16 matched; string/float/import checks pass.
`find_declared_unmatched.py <seed> <donor>`: all defined functions matched.
`class_gate.py <seed> <donor> <header>`: pass.
`data_check.py <seed> <donor>`: one existing baseline finding, zero new.
`data_check.py --converged <seed> <donor>`: 10 addresses, no second names.
`eh_verify.py <seed> <donor>`: EXACT 3.
Planner refreshed for GameClient and its input check passes. Its path hint is
only provenance evidence; normal merge routing independently approves the donor.

Scoped receipts use upstream allowed_symbols object/identity/scan APIs,
link_census COMDAT selection decoding, data_check.object_facts, and the normal
tu_skeleton.Verifier through merge(dry_run=True). The original and final
objects are retained under build/sol-b5-snow-sync-{before,after}/. Standalone
and composition checks preserve all 43 masked relocation bindings. The only
standalone symbol delta is a donor copy of the 14-byte getFinalOverride inline
COMDAT, identical to the original seed's code, relocations and selection flags.
All 23 globally selected definitions remain identical before/after the edit and
before/after composition. Composition has no changed/dropped external code or
new undefined symbols; data binding/definition sets are equal. Consequently no
changed consumer binding requires another source repair. This is scoped object
evidence, not a new link census or ownership receipt.

No code identity/header queue key belongs to these two sources. Preserve the
existing data wrong-name key and two address-global hatches on Rva00093349.cpp;
no debt retirement, rename or identity claim is made.

## Publication audit and remaining work

No source path is moved/deleted and no ledger/register is repointed. Search of
tools, hooks, workflows, includes, build inputs and registries found no active
path consumer needing repair. The new quoted header has exactly these two
compiled consumers; historical EA paths remain intact. Audit covers this staged
prerequisite and all pending path changes (none in local outgoing commits before
this change). The branch was behind origin, not carrying uncommitted upstream
source edits; publish performs the required rebase and hook verification.

Other allocated probes: AptRenderingContext already accepts all three donors
(six rows), so leave it to Luna. GhostObject still blocks on private STL/vector
views; PropDraw blocks on private Coord3D and missing PoolKey/module fields.
Shrub remains at the previously demonstrated six-file compatible subset with
allocator/storage/destructor prerequisites unchanged. No blocked body was
repeated or left edited. MessageStream issue #116 is untouched. BFME1 upstream
fetch confirms pinned ff391a5e90 differs from official 0c0e53fa9a; no unverified
reference update or freshness-success receipt was written.

Metrics: recovered retail bytes 0; source-file reduction 0; identity debt retired
0. This prerequisite adds one shared header and unblocks one existing donor.

## Scoped receipts

```json
{
  "standalone": {
    "inspected_selected_names": 23,
    "selected_definition_changes": [],
    "new_inline_provider_identical_to_seed": true,
    "remaining_standalone_facts_identical": true,
    "bindings": 43
  },
  "composition": {
    "snow": {
      "rows": 16,
      "before_refs": 43,
      "after_refs": 43,
      "removed_bindings": [],
      "added_bindings": [],
      "preexisting_divergent_copies": {}
    }
  },
  "selection": {
    "snow": {
      "inspected_names": 23,
      "selected_provider_changes": [],
      "data_binding_sets_equal": true,
      "data_definition_sets_equal": true
    }
  },
  "objects": {
    "build/sol-b5-snow-sync-before/^code_^game^engine^device_^source_^w3^d^device_^game^client_^w3^d^snow.obj": "8a6096bd03b85f62deef6aa5c14736b6fb460a0df3130917d1703b26accdf0b0",
    "build/sol-b5-snow-sync-before/^code_^game^engine^device_^source_^w3^d^device_^game^client_^rva00093349.obj": "d04f4d8ee16a80a2ae1281ce31ba2c3cea25f4d65de827fa8f22c44b0bce4345",
    "build/sol-b5-snow-sync-after/^code_^game^engine^device_^source_^w3^d^device_^game^client_^w3^d^snow.obj": "44448edd1cfbb52bda92c04aafbc4b81a6cbe9e9276b13637486509025de497b",
    "build/sol-b5-snow-sync-after/^code_^game^engine^device_^source_^w3^d^device_^game^client_^rva00093349.obj": "14aefd30245a643ab2ca4cb5c74c2edc9096feac20504cf393c69ceb136ee785"
  }
}
```
