# SquishCollide collision callback

The body at RVA `0x004BBA65` remains unmatched. The bank now restores the confirmed HijackerUpdate early return and resolves its four callees through existing providers. This is a semantic repair at unchanged structural alignment, not an alignment improvement. No source under `Code/`, ledger row, pin, compiler override or verifier rule was changed.

The symbol is `?onCollide@SquishCollide@@UAEXPAVObject@@PBUCoord3D@@1@Z`, and the retail extent is 1144 bytes. `repair_queue.py dest` currently recommends `Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollideCtor.cpp` by neighbour heuristic; the approved surrounding TU map identifies `Code/GameEngine/Source/GameLogic/Object/Collide/SquishCollide.cpp`. No nonmatching reconstruction was placed in either unit.

## Identity and semantic evidence

Retail has an EH entry at the given RVA, `RET 12` immediately before the next function at `0x004BBEDD`, and a matching Ghidra inventory boundary. The rowed ctor installs secondary vtable VA `0x00C5A1EC` at offset `0x10`; its first entry is this body. The primary vtable points to the rowed name getter, which returns `SquishCollide`. Receiver minus eight supplies the module's object. These are target identity and ABI facts; the additional field meanings remain address-derived or inferred.

At retail `0x004BBC6F`, the protected Object::findModule provider at `0x0028B6D6` is called for `HijackerUpdate`; a non-null result branches directly to the epilogue. The incoming farm bank instead continued into the geometry copy. The corrected body restores that return. `build/worker_4bba65/branch.raw.log` follows the non-null path in retail, the incoming object and the corrected object: the incoming object reaches the geometry call, while retail and the correction reach `RET 12` without another call.

Existing providers resolve all four previously unresolved names: protected `Object::findModule`, `GeometryInfo::CollidesWith`, `Object::rva0028CECF`, and `Object::rva0028F44C(const Object*) const`. No new pin is needed. `Object::rva002929F9` also has a provider now, so the old dependency warning retained in the bank is stale evidence rather than a current blocker.

## Measurements and ruled-out hypotheses

Each source has a unique scratch path; its object and dependency receipt were removed before measurement. All builds and measurements set `BFME_OBJSTORE=off`. The following values come from each trial's `align_diff.py` output and metrics JSON under `build/worker_4bba65/`.

| Trial stem | Structural regions | Memory differences | Register differences | Emitted bytes | Positional differing bytes | Unresolved callees |
| --- | ---: | ---: | ---: | ---: | ---: | ---: |
| before | 20 | 37 | 12 | 1146 | 972 | 4 |
| hijacker_exit | 20 | 37 | 12 | 1150 | 973 | 4 |
| providers | 20 | 37 | 12 | 1150 | 978 | 0 |
| module_position | 28 | 44 | 12 | 1148 | 894 | 0 |
| fallback_dot | 32 | 45 | 16 | 1134 | 1001 | 0 |
| position_lifetime | 23 | 44 | 17 | 1141 | 944 | 0 |
| dot_only | 23 | 39 | 16 | 1136 | 982 | 0 |
| positions_only | 19 | 43 | 17 | 1149 | 964 | 0 |
| terminal_self | 20 | 33 | 14 | 1132 | 975 | 0 |
| positions_terminal | 20 | 33 | 14 | 1132 | 975 | 0 |
| target_pointers | 25 | 38 | 16 | 1129 | 961 | 0 |
| final | 20 | 37 | 12 | 1150 | 978 | 0 |

Relocation and branch lines are not defects. Positional byte counts are supplemental: the relocation patcher uses retail positions even after instruction streams shift, so these counts do not establish progress. In particular, the smaller positional count for `module_position` is not a gain. The apparent structural gain in `positions_only` increases both other classes; `terminal_self` reduces memory differences but increases register differences. Both tradeoffs fail the assignment's closer-bank criterion and were rejected.

The written pre-experiment hypotheses are in `build/worker_4bba65/hypotheses.md`. Reloading the module object for the initial position, removing the fallback vector stores, caching the two collision positions across callbacks, and using the saved self in terminal weapon/damage operations did not produce an admissible improvement, separately or in the tested evidence-supported combinations. The surviving mismatch is still early EDI retention of self instead of retail's initial ECX use and stack spill, with different spill slots, later register saves, coordinate scheduling and terminal reloads. Repeating previously exhausted hierarchy, flag, aggregate or accessor spelling sweeps is not justified by these results.

## Inputs, comments and validation

The input checkout is BFME 2 `af72028f8f334a7becdfa74206ce7acfe6391b75`, with BFME 1 checkout `a18d9ed50607e9175de4d6568798d7d73119de09`. Flags are `/DNDEBUG /MD /EHsc /O1 /G7 /arch:SSE`, using the normal compiler. All five prior verdicts and the complete incoming bank were read; those verdicts cite no separate prior support paths. The bank retains its original donor reference `874e38488`; no new BFME 1 source transfer or stronger field-name claim is made.

The current GeneralsMD SquishCollide.cpp was compared for applicable EA comments. Ground collision, targeted-object exceptions, hijacking, TNT placement, relationship direction, moving toward the victim and lethal-damage comments were copied at their corresponding operations. The donor's 1.0 radius and self undetected-defector comments do not describe this target. All original bank comment lines remain in order, including historical warnings. `build/worker_4bba65/comments.raw.log` records that assertion.

`align_diff.py` and `explain_mismatch.py` completed successfully for all listed trials; they diagnose divergence and are not passing byte gates. Each has `<stem>.align.raw.log`, `<stem>.explain.raw.log` and `<stem>.measure.raw.log`. A separate measurement of the actual refreshed bank reproduced `final` in `banked.metrics.json` and `banked.align.raw.log`. `branch_probe.py`, `check_csv.py`, and `pin_consistency.py --check` passed; raw outputs are `branch.raw.log`, `check_csv_final.raw.log` and `pin_consistency.raw.log`. `build.sh`, `add_match.py` and `find_declared_unmatched.py` were not run because no exact candidate or changed production source exists. `retail.raw.log` and `identity.raw.log` retain direct target evidence. All trial sources, scripts and raw logs remain under the task scratch directory as requested.
