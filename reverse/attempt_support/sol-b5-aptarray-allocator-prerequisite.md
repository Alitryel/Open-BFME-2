# AptArray allocator declaration prerequisite, 2026-10-26

codexb5, family B shard 1/2; allocated AptArray destination. File claims cover
the seed and AptArrayConstructor_Unresolved.cpp. No source or row is moved.

The normal merge trial rejected the existing constructor donor because the
seed's Rva006D2A60 view declared freeBlock but omitted allocBlock(int), already
required by that donor's inline operator new. Add the identical declaration.
The now-compatible constructor view also needs the existing static
CleanNativeFunctions declaration so the previous cleanup donor remains accepted.
No method body, vtable slot, member layout, name or compiler flag changes.

Planner provenance distinguishes target facts (AptArray.cpp assert operands at
6D9254/6D927A/6D92A0 and reserve at6D955B) from the constructor's path hint.
Routing is approved independently by the normal merge tool's fresh in-memory
map. The planner's alternative for this group is AptArray.cpp; mixed and
flag-bound donors remain separate. No regenerated TU map was staged.

Before: normal dry-run accepts the seed plus Rva008B8B80ReleaseAll.cpp, 11 rows.
After: it also accepts AptArrayConstructor_Unresolved.cpp, total 14 rows,
including the existing 103-byte parent and its two existing EH rows. Leave
compatible merging to Luna. Other donors still need canonical base/type ordering
or flag treatment; their exact rejections are included below.

Verification:

- ./build.sh seed, constructor donor and cleanup donor: 14/14 exact, including
  all eight string references. Original and final standalone object facts are
  identical (definitions, undefined names, COMDAT choices, data and 26 bindings)
  after normalizing compiler-local EH labels.
- Normal tu_skeleton.merge(dry_run=True) uses its ordinary Verifier; the final
  composed object has no changed/dropped external code and no new undefined
  names. All 26 bindings remain identical; all 13 globally selected definitions
  and data binding/definition sets are preserved.
- find_declared_unmatched.py and class_gate.py pass. The constructor's three
  existing admitted inline definitions/markers remain unchanged.
- eh_verify.py: EXACT 3. data_check.py: zero findings; --converged: no second
  name at any of the ten converged addresses. Microsoft-header check passes.
- Planner refreshed after final declarations; freshness check passes.

Receipts use upstream allowed_symbols, link_census COMDAT decoding,
data_check.object_facts and the normal merge verifier, retained in
build/sol-b5-aptalloc-{before,after}/ and build/sol-b5-aptalloc-composed.obj.
The scoped scripts and outputs are retained under build/sol-b5-aptalloc-*.
No maintainer-only census, smoke or link cycle was run.

Publication audit covers the entire pending Snow/AptArray batch. There are no
moved/deleted source paths or ledger/register transfers. Existing path consumers
continue resolving, and the only new header has four verified direct consumers.
No active tooling, hook, workflow or build input needs repointing; historical EA
paths remain intact. No debt key is dropped or retired by this prerequisite.

Metrics: source-file reduction 0; recovered bytes 0; identity debt retired 0.
Demonstrated: one additional constructor donor accepted by normal dry-run.
No later Luna merge or census gain is claimed.

```json
{
  "bindings": {
    "aptalloc": {
      "rows": 14,
      "before_refs": 26,
      "after_refs": 26,
      "removed_bindings": [],
      "added_bindings": [],
      "preexisting_divergent_copies": {}
    }
  },
  "selection": {
    "aptalloc": {
      "inspected_names": 13,
      "selected_provider_changes": [],
      "data_binding_sets_equal": true,
      "data_definition_sets_equal": true
    }
  },
  "merge": {
    "aptalloc": {
      "accepted": [
        "Code/Libraries/Source/Apt/AptArray.cpp",
        "Code/Libraries/Source/Apt/AptObject/AptArrayConstructor_Unresolved.cpp",
        "Code/GameEngine/Source/Common/Rva008B8B80ReleaseAll.cpp"
      ],
      "rejected": {
        "Code/Libraries/Source/Apt/AptValue/Rva006D9780Finish.cpp": "its flag override is not carried by the verified merge",
        "Code/GameEngine/Source/Common/AptArray_DestroyGCPointers.cpp": "compile: Code\\Libraries\\Source\\Apt\\.AptArray.36dde4f86b411f9c.tu_skeleton.cpp(103) : error C2027: use of undefined type 'BfmeAptValue006DCD20' | Code\\Libraries\\Source\\Apt\\.AptArray.36dde4f86b411f9c.tu_skeleton.cpp(103) : error C2227: left of '->rva006DD6C0' must point to class/struct/union | Code\\Libraries\\S",
        "Code/GameEngine/Source/Common/Rva006D94A0Cluster.cpp": "compile: Code\\Libraries\\Source\\Apt\\.AptArray.6a9f27fa35f8ce26.tu_skeleton.cpp(102) : error C2027: use of undefined type 'BfmeAptValue006DCD20' | Code\\Libraries\\Source\\Apt\\.AptArray.6a9f27fa35f8ce26.tu_skeleton.cpp(102) : error C2227: left of '->rva006DD6C0' must point to class/struct/union | Code\\Libraries\\S",
        "Code/Libraries/Source/Apt/AptValue/Rva006DA4D0Finish.cpp": "compile: Code\\Libraries\\Source\\Apt\\.AptArray.8f144035cddec793.tu_skeleton.cpp(50) : error C2504: 'Rva006D6470Owner' : base class undefined | Code\\Libraries\\Source\\Apt\\.AptArray.8f144035cddec793.tu_skeleton.cpp(504) : error C2039: 'SetAt' : is not a member of 'BfmeAptValue006DCD20'"
      },
      "rows": 14,
      "standalone_rows": 14,
      "definitions": 13,
      "changed": [],
      "dropped_definitions": [],
      "new_undefined": []
    }
  }
}
```
