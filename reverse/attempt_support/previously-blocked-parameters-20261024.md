# Land three parameter agreements after verifier repairs

Base: `1c452bae45dc96cf4f99cbf454e845e1ed105de7`.
This is a naming contribution: **zero new recovered C++ bytes**.

| Source | Selected function | Old | Inferred name | Existing agreement |
|---|---|---|---|---|
| `FamilyDeletingDtors9.cpp` | `famgenDelete#8` | `p` | `palantir` | `nl-4977e291438e` |
| `FamilyDeletingDtors9.cpp` | `famgenDelete#9` | `p` | `selectionDetails` | `nl-7bdf818a6c4f` |
| `INIBfmeSettingsParsers.cpp` | `RvaFireColor` | `b` | `blueValue` | `nl-cf07ec57b1bb` |

The family source is under `Code/GameEngine/Source/Common/`; the INI source
is under its `INI/` directory.
Each agreement already has three independent worker votes spanning
`gpt-6.1-sol` and `gpt-6-astra`. No new votes or naming proposals were made.
The spellings remain inferred, rather than asserted original EA names.

The overload agreements had been withdrawn because `rename.py check` lost
`#8`/`#9` and reported untouched siblings. The prerequisite repair is
`843dfe7e47836813a090a61be0b3caf85754a00b`; the original handoff is
`naming-famgendelete-overload-scope-20261024.md`. The color parameter was
blocked by unrelated `S12::b`; its separate repair is
`1c452bae45dc96cf4f99cbf454e845e1ed105de7` with evidence in
`rename-scoped-members-20261024.md`.

All three dry-runs were reviewed before applying them. An ignored one-off
driver restricted `name_lane.cmd_apply`'s selection to these three keys;
the ordinary lane recomputed all votes and rivals with `--retry-blocked
--min-models 2`, checked the live ownership list, and invoked `rename.run`
with its default claims, byte verifier and commit checks. No checks were
replaced or skipped. Outcomes were appended by the lane itself.

Each edit changes the parameter declaration and its one use only. The two
overload selectors are preserved in `name_basis.csv`; unchanged overloads
retain their original parameters. The matched deleting destructors at
`0x0042D4CF` and `0x0042D53F` are each 28 B; these are emitted-body locators,
not newly established retail addresses of the forcing C++ wrappers.
The color constructor is inline; `0x0030AEB6` (217 B) locates its containing
matched settings constructor and is not a new separate color-body claim.

`previously-blocked-parameter-proof-20261024.json` checks the complete expected
source edits, all three landed statuses and qualified basis records, and the
post-rename scope check. Using the engine's parameter reader (which includes
primitive types), it proves exactly three fewer weak parameter declarations
in these units. Function rows, pins, data rows, tombstones and votes are unchanged.

The lane's individual normal byte gates passed **18/18**, **18/18**, and
**13/13** functions respectively: **31 distinct existing matched rows** across
the two files. The INI gate also verified both data rows, its literal, and all
nine compiler float literals. Every rename passed the ordinary source,
identity, ledger, data and EH checks before the lane recorded it as landed.
No verifier, baseline, ABI, function signature or behavior was changed.

The related `FamilyDeletingDtors2.cpp` agreements were not retried because
another worker held that file's scope claim.
