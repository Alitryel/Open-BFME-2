# ProfileHighLevel consolidation blocked by COMDAT identity (2026-10-25)

Destination: `Code/Libraries/Source/profile/profile_highlevel.cpp`.

The allocated TU passed `consolidation_queue.py --check-tu`. The scoped planner/check and TU plan found two accepted unchanged donors plus one protected `ProfileBlock.cpp` entry. `tu_skeleton.py --merge --dry-run` accepted the target, `ProfileIdConstructor.cpp`, and `ConstIntGetters7Addr.cpp` (27 rows, `/MD /EHsc`, no rejected donors). The tool applied the merge, and `./build.sh profile_highlevel.cpp` passed 27/27 with exact string, float, import, and EH checks; `find_declared_unmatched` passed.

The staged scoped checks reported: ownership shadow clean; data converged clean (10 addresses, no second names); EH exact (2); case collision clean; `link_check.py --staged --new-variants --staged-peers --shadow` used the current object receipt and reported no new variant. However, `code_identity_gate.py --staged` found one new shadow diagnostic: `definition: divergent | ??0Id@ProfileHighLevel@@QAE@XZ`. This is an unverified changed COMDAT/provider binding. I therefore restored only this merge trial and released its three file claims and 14 moved RVA claims; no source, ledger, or claim changes from this trial remain. The `--full` identity scan was started for more context but interrupted after it repeatedly scanned cached objects without reaching a result; it is not a verification result.

Sol should compare the selected `ProfileHighLevel::Id` constructor COMDAT/provider for the merged TU against the original object composition before retrying. The trial removed zero files and preserved all 27 merged rows in its verification run. `ProfileBlock.cpp` remains protected by path-keyed debt and was untouched.
