# LivingWorldEyeTower receiver prerequisite, 2026-10-26

Allocated destination: `Code/GameEngine/Source/GameClient/LivingWorld/LivingWorldEyeTower.cpp`
(Sol prerequisite seat codex4, family A, shard 1/2). No merge or split is applied.
Leave the compatible donors for the allocated Luna seat.

## Blocker and repair

The current normal `tu_skeleton.py --merge TU --dry-run` initially accepted
no files. The frame donor's private LivingWorldEyeTower declaration displaced
the seed's declaration, so the transform could not find `m_eye`/`m_target`.
The state donor likewise displaced the transform/frame declarations. These
reproduce the receiver problems in the earlier GameClient consolidation handoff.

Share the receiver declaration in LivingWorldEyeTowerView.h. The transform's
retail accesses prove hosts at 0x18/0x20 and coordinates at 0x24/0x30; the frame
body separately proves hosts at 0x1C/0x20, copies 0x5C/0x60 to 0x24/0x28, and
calls the transform with the same receiver. These are three distinct host
fields, not an inference that the two helpers use identical host types. Keep
the existing opaque host types and the explicit cast for the second helper.
The state bodies prove the vector words at 0x3C/0x40/0x44 and fields from 0x48
through 0x70. Their existing pair type and field spellings are retained. Original
member names, remaining receiver layout and donor-to-target identity beyond
the existing ledger are not claimed. No class is registered as canonical here.

The frame retains raw word copies, including NaNs and signed zero. All function
names, flags, historical EA filename/line literals, globals and ledger owners
are unchanged. No hatches or protected-register entries are added or retired.

## Acceptance and provider evidence

- Before and after `./build.sh` on the destination, its ProcessFrame donor and
  `Code/GameEngine/Source/GameClient/LivingWorldEyeTowerProcessItems.cpp`:
  **7/7 functions and 1/1 data row exact**, one filename literal and nine float
  literals verified. `find_declared_unmatched.py` passes all three sources.
- Normal after dry-run accepts those three files, **7 rows / 1,404 existing
  retail bytes**, versus no accepted files before. The two remaining clean
  donors fail with allocator/vector specialization/redefinition diagnostics;
  the five mixed files stay untouched. The dry-run would carry the existing
  frame-rate data provider's data-ledger key, not retire it.
- Saved standalone objects compared before/after: every external code
  definition's digest, size and exclusivity, actual COMDAT selection, undefined
  reference, external data definition/relocation and each row's DIR32 reference
  set agree. No shared provider or consumer binding changes in this repair.
- Effective composed object `build/tu_skeleton/21c3a65183c23477.obj`: all **20
  code definitions, 5 external data definitions and 15 unresolved references**
  equal the standalone union after internal resolution; actual COMDAT selections
  agree. Every row's DIR32 data references agree. Composition includes the
  unchanged BfmeClientFramesPerSecond provider from ProcessItems; the transform
  and frame objects alone did not define it. Comparing object-level definition
  sets per individual row would therefore be incorrect; the complete data union
  and each function's references are checked separately.
- `allowed_symbols.py --source` on all three: **30 references, 22 owner / 8
  alias, zero wrong bindings**. `data_check.py`: zero shadow findings.
  `data_check.py --converged`: three sources, ten addresses, zero second names
  and zero unjudged rows. `eh_verify.py`: zero EH rows, zero missing objects.
  `check_csv.py` passes 98,271 functions / 15,683 symbols / 2,215 data rows.

Receipts: `build/codex4-eyetower-{trial-before,trial-after,expanded-trial,
expanded-build,expanded-proof,expanded-identity,expanded-converged,
expanded-data,expanded-eh}.txt`; original source/object snapshots and the
provider comparison script are in `build/codex4-eyetower/`.

## Planner, audit and remaining prerequisites

The current GameClient planner and currency check pass. Its original-path
packets retain the existing destination, placement and stale-map qualifications;
only the normal merge tool's rebuilt in-memory routing authorizes this trial.
No regenerated tu_map.csv is staged. The planner's compiler-setting, internal
linkage, quoted-include and data-ownership warnings were checked through the
normal trial and the object comparisons above.

Audited the entire pending outgoing range plus this prerequisite. There are no
source moves, renames or deletions. The only new source dependency is the private
header, included by the three verified consumers. Combined searches through
tools, hooks, workflows, includes, build inputs, ledgers, queues and documentation
find no consumer needing repointing. Original EA paths and historical receipts
are preserved. Existing data-ledger and math-header audit entries still name
their live owners. Header/MS-header queues and identity/data/hatch registers
are not silently re-keyed or retired. Evidence: `build/codex4-eyetower-path-audit.txt`
and `build/codex4-eyetower-pending-paths.txt`. A reverse difference against a
newer origin data baseline is incoming work, not part of this repair; the
merge-base/outgoing-log check shows no earlier local commits.

Remaining: constructor and Xfer donors need STL declaration reconciliation;
Xfer also retains its canonical-adoption queue prerequisite. Mixed donors need
their own scoped split/identity work. No broad trial is repeated without new
evidence. This is a demonstrated composition unblock, not a confirmed later
Luna landing, census gain or ownership receipt. Files removed **0**, identity
and data debt retired **0**, recovered C++ bytes **0**.

Keep the four source/header file claims, evidence-file claim and six RVA claims
until publication is confirmed; then release the explicit scopes and RVAs and
run `claims.py release --landed` (existing-row prerequisites may not settle
automatically).
