# Typed list comparison link repair

Base tree: `8621ea8c53`. Donor pointer reviewed:
`23b143233b5a8664a3bdf8572df6d905c310a5a1` (Open-BFME-1).
Discovery: `repair_queue.py link`, `link_rank.py --top 25`, `--near 1`,
`--kind A --top 20`, and ranked JSON, followed by current-object checks.
No census, status or measurement history was rewritten.

Three consumers emit an unused 18-byte
`??9_List_iterator_base@_STL@@QBE_NABU01@@Z` COMDAT that retail truth judges
wrong. Their retail loops already inline the typed node-pointer comparison.
The existing BFME 2 TU-local typed comparison pattern (including
FireWeaponUpdateBehaviorDtor.cpp and ObjectGuardingHelperDisband.cpp) avoids
emitting that base wrapper. Apply that pattern without changing compiler flags,
headers, layouts, reference declarations, ledger rows or pins.

Consumers and their authored byte totals in the local preview:

| Source under Code/GameEngine/Source/GameLogic | Bytes | Before | After |
| --- | ---: | --- | --- |
| Object/Contain/Rva00466C94.cpp | 163 | wrong comparison COMDAT | clean |
| SkirmishAI/Rva004EC3ACOnUnitCreated.cpp | 132 | wrong comparison COMDAT | clean |
| ScriptEngine/ScriptEnginePositions.cpp | 130 | wrong comparison COMDAT | clean |

The last unit also contains the existing list-erase gen-alias row; it was gated
but is not counted as new authored coverage.

## Provenance and measurement limits

Reviewed donor repair `de59a7e9f891b3ed2d4221d151ca881f4b75a583`:
Open-BFME-1 unified surplus inline `Rva8CD130Value::isUndefined` copies while
preserving all retail callers. That is an applicable linking principle, not
evidence for these BFME 2 identities or layouts. The implementation pattern
comes from existing BFME 2 repairs. Target byte gates and full-object comparison
prove that the matched bodies are unchanged.

The local index measures commit `147cfae2cb`, 2026-10-14 07:27, SHA256
`690c439e363fa77529591edc18a0939404a7a9ca58ec95972585241c9413f53a`.
Committed link_status discovery metadata is older (`67e1365aa9`); use the index
metadata for these paired previews. `object-proof.json` checks the same unchanged
index for both sides, refreshing only these three explicit objects in memory.
The first indexed retail-proven comparison keeper remains `w3d_dep.obj`, digest
`f69a275dde37`, and is outside these consumers. Its source was not changed;
its current build/closure is not asserted by this repair.

This is a legacy local preview improvement from 0 to 425 existing authored
retail bytes, with strict reusable compiler receipts for the edited consumers.
It adds 0 authored C++ bytes. It claims no self-strict placement or closed-strict
gain. A full link/census measurement remains maintainer-run work.

## Acceptance evidence

- Before and after `link_check.py --prepare-current --paths-from <sources>`:
  three owned sources, normal byte gate 4/4, strict reusable receipts.
- `./build.sh <three sources>`: 4/4 rows; string/float/import gates pass.
- `link_check.py <three sources>` and paired object previews: 0/3 to 3/3 clean.
- Complete object comparison: each loses exactly the wrong 18-byte COMDAT;
  every retained COMDAT's raw bytes, extent and relocation digest is unchanged.
  External bindings, ordinary sections (including symbolic EH table targets)
  and hatch counts are unchanged. Before/after object and source hashes are in
  `object-proof.json`. Scratch backups and reproduction code remain under
  `build/list-node-link-20261014/`.
- `eh_verify.py --sources-from <sources>`: 1 EH row EXACT, no nonexact or missing.
- `class_gate.py <three sources>`, `data_check.py --converged <three sources>`
  and `link_check.py --new-variants --staged-peers <three sources>` pass.
- Frozen-source check passes before and after. `place_bodies.py <three sources>`
  reports 0 new placements and 0 pins. No incidental body was introduced.

Logs alongside this record preserve the individual gate and preview results.
