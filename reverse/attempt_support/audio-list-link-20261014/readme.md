# Audio-completion list comparison repair

Base tree: `e69b477e05f2d4a355b8b451697b459012de7a1b`.
Consumer: `Code/GameEngine/Source/GameLogic/ScriptEngine/Rva00358076AudioComplete.cpp`.
Existing matched rows: 0x00358076 and 0x00357F5E, 280 bytes each.
The file claim covers this repair. No ledger, identity, layout, compiler flag,
header, pin, baseline or measurement history changes.

Both retail loops inline the typed list-node comparison. The unit nevertheless
emitted the unused 18-byte `??9_List_iterator_base@_STL@@QBE_NABU01@@Z`
COMDAT, which the local index judges wrong against retail. An existing BFME 2
pattern adds a TU-local typed `operator!=` that compares the same node pointers.
The resulting private 12-byte helper has no non-debug caller relocations.
All 32 retained COMDATs, their extents and relocation digests are identical;
all remaining ordinary sections, symbolic EH targets and directives are unchanged.

## Provenance and before/after evidence

Discovery used `repair_queue.py link`, `link_rank.py` and current-object checks.
The runner index measures `147cfae2cb`, 2026-10-14 07:27, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
Committed link-status discovery describes another measurement (`de7bb30890`);
these results use the unchanged runner index, replacing only this owned object's
definitions in memory for each side. No census or closure was rebuilt.

Reviewed Open-BFME-1 repair `de59a7e9f891b3ed2d4221d151ca881f4b75a583`
unifies unused inline predicate copies while preserving retail callers.
That principle applies here; the concrete typed-list pattern comes from existing
BFME 2 repairs, including `reverse/attempt_support/list-node-link-20261014/`.
No donor identity or layout claim is introduced. Reference checkout remains
at verified pointer `a7c38d3b2597121f178ab5190b3062478823257d`;
upstream fetch found `46dddb7d5`, but the earlier comparative full-verification
blocker remains unresolved, so the pointer and freshness stamp were retained.

The paired legacy local preview falls from two findings to one. The wrong
iterator-base COMDAT disappears; the existing duplicate
`?rva00357DF8@Rva00357DF8@@QAEXABUBfmeSpecialPowerTimer8@@@Z` remains.
Its inline/noinline definition in the consumer preserves compiler shape;
the owner is `ScriptEngineRva00357DF8.cpp`. A separate supported repair must
reconcile the insertion helper while retaining both caller bodies.

This repair adds 0 authored C++ bytes and gains 0 locally linked bytes.
The two owned bodies have strict current compilation receipts and pass their
byte gates. No self-strict placement or closed-strict gain is claimed.
Broader link/census verification remains a maintainer operation.

## Acceptance checks

- Before and after `link_check.py --prepare-current <source>`: 2/2 byte-exact,
  strict reusable receipts. Saved before/current object and source hashes are
  recorded in `object-proof.json`.
- `./build.sh <source>`: 2/2 rows; string, float and import checks pass.
- `eh_verify.py <source>`: 2 EH rows EXACT, no missing/nonexact rows.
- Full object proof: exactly one external COMDAT removed, one private helper
  added, zero changed retained COMDATs, other sections/directives identical.
- `link_check.py <source>` and paired `link-proof.py`: two findings to one,
  LINKED 0 to 0 of 560 bytes. The CLI correctly exits 1 for the remaining duplicate.
- `link_check.py --new-variants <source>`, `class_gate.py <source>`,
  `data_check.py --enforce <source>` and `data_check.py --converged <source>` pass.
  Converged-data check: 8 addresses, no second names or unjudged rows.
- `find_declared_unmatched.py <source>` passes before and after.
  `place_bodies.py <source>` finds 0 bodies and 0 pins. `git diff --check` passes.

Proof scripts use scratch inputs in `build/audio-list-link-20261014/`.
To reproduce the before object elsewhere, prepare the explicit source at the
base tree with `link_check.py --prepare-current`, save its object before editing,
then prepare the edited source. Do not substitute a raw cache-writing compile.
