# HeaderTemplate canonical-header prerequisite — 2026-10-25, codex

Target: `Code/GameEngine/Source/GameClient/GUI/HeaderTemplate.cpp`.
Allocated by `/opt/runner/consolidation_queue.py --limit 20` to codex, family A,
shard 0/2. This repairs the concrete Luna blocker recorded in
`consolidation-headertemplate-20261025-codex3.md`; it does not apply a merge.

## Demonstrated unblock

Before: `tu_skeleton.py --merge <target> --dry-run` accepted no donors. Every
eligible donor failed with `string_base.h(165): C2953`, a duplicate StringBase.
The seed selected the BFME 1 WWLib string header ahead of the BFME 2 string
shim used by the canonical HeaderTemplate view. Selecting that existing target
shim first exposed duplicate HeaderTemplate and HeaderTemplateManager classes:
the seed was still using the ZH HeaderTemplate header.

The seed now includes the registered `HeaderTemplateView.h`. The canonical
manager declares the two already matched iteration methods and their existing
private iterator alias. No class layout, function body or global name changes.
The include-directory choice uses the existing BFME 2 shim; no linker alias is
written or admitted by this change.

After: `python3 tools/tu_skeleton.py --merge <target> --dry-run` exits 0:

- Seed plus all four eligible donors accepted, 12 ledger rows, no rejection.
- `Common/HeaderTemplateManager_findHeaderTemplate.cpp` accepted.
- `GUI/HeaderTemplateManagerGetFontFromTemplate.cpp` accepted.
- `Common/HeaderTemplateManager.cpp` accepted.
- `GUI/HeaderTemplateParse.cpp` accepted.
- Creation_Rva00201c39 and ManagerRva00201B05 remain refused because they are
  keyed in protected registers. Their debt was neither removed nor transferred.

The run rebuilt stale routing in memory; no TU map was committed. The planner
was regenerated for `Code/GameEngine/Source/GameClient/GUI/` after the edits and
upstream rebase. `name_lane.py consolidate --check build/consolidation` passes.
The planner's original-path alternatives and prerequisites were reviewed;
acceptance above comes from the merge verifier, not the planner.

## Verification and binding evidence

Before edits, `./build.sh` on the five eligible sources passed 12/12 rows.
After the shared-header edit, `./build.sh` on all 11 dependent ledger sources
passed 210/210 rows, two data rows, 31 string literals plus two empty strings,
one float, three imports and the emitted STLport constructor fold. The build
verified 55 renumbered funclet pins against their exact parent EH data.
`find_declared_unmatched.py` passes all 11 consumers. Header adoption accepts
the seed for both registered classes, HeaderTemplate and HeaderTemplateManager.
There were no header-queue entries to retire. `check_csv.py` and
`git diff --check` pass.

Before objects were preserved under `build/codex-headertemplate-objects-before/`
and the original seed in `build/codex-headertemplate-seed-before.obj`.
Read-only `allowed_symbols.Obj`, `_object_defs`, `digest` and census COMDAT
selection APIs compare those objects with the supported-build outputs:

- All 453 external code definitions retain the same sizes, bytes, relocation
  digests and exclusivity. Every external data/code definition and its section
  flags and COMDAT selection policy also agrees across all 11 consumers.
- With funclets located by `build.located_funclet`/the verified parent group,
  all 433 reference sites retain their symbol and retail target. Two existing
  hash-container references classify as certified folds rather than unknown
  in the current scan; none acquires a new wrong binding. The plain identity
  CLI still reads stale local ledger labels, so its raw count is not used to
  infer an EH identity change.
- The seed's `.drectve` changes from three string comparison aliases to the
  seven existing BFME 2 AsciiString aliases. Every old and new alias has an
  unchanged independent provider: GeometryRecordVector.obj for the old three,
  WWLib/ascii_string.obj for the new seven. No effective global alias is lost
  or newly introduced. Other consumers' directive sets are unchanged.
- `link_check.py --new-variants --staged-peers <all 11 sources>` exits 0 without
  a new variant. Combined with the unchanged provider paths, definitions,
  COMDAT policies and reference edges, this establishes the scoped composition
  repair's unchanged shared providers. It is not a new census measurement or
  evidence that the subsequent Luna merge has landed.
- `data_check.py <all 11>` reports the two existing shadow wrong-name findings
  in ConstIntGetters5 (TheWorldDict) and GameClientDrawableTOC (TheMessageStream).
  Their names, data definitions and references are unchanged. Existing code
  identity findings, including the manager's list-base ctor/dtor and the
  creation donor's push_front target, remain. No identity debt is retired.

Local receipts: `build/codex-headertemplate-consumers-build-after.txt`,
`*-canonical-after.json`, `*-binding-comparison.json`, `*-provider-proof.txt`,
`*-eh-binding-proof.json`, `*-link-consumers-after.txt`, and
`*-data-consumers-after.txt`. The preliminary unnormalized reference comparison
in provider-proof.txt differs because ledger-local EH labels were renumbered;
the later EH-aware proof accounts for all 433 sites as described above.

## Publication audit and handoff

Audited `origin/master..HEAD` (the pending Recorder prerequisite, rebased as
0531a74ca3) plus this staged prerequisite. The batch changes existing source and
header contents and adds handoff documents; it has no source deletion, rename,
move, or path-keyed ledger/register change. Active tooling, includes, build
inputs and registries therefore retain their existing paths. Historical EA
paths are preserved. Protected registers are untouched.

Keep the now-compatible donors for Luna. The demonstrated opportunity is four
fewer files in a future verified merge, not four files removed here. This
prerequisite itself removes zero files, retires zero debt keys and recovers
zero C++ bytes. No maintainer-only measurement or link/smoke run was started.

Publication may remain batched by the runner. Until landing, retain the
HeaderTemplate and HeaderTemplateManager class claims and file claims for
HeaderTemplateView.h and these 11 consumers:

- Common/ConstIntGetters5.cpp
- Common/FamilyDeletingDtors_muse-02-238DE4.cpp
- Common/HeaderTemplateManager.cpp
- Common/HeaderTemplateManager_findHeaderTemplate.cpp
- GameClient/GUI/HeaderTemplate.cpp
- GameClient/GUI/HeaderTemplateCreation_Rva00201c39.cpp
- GameClient/GUI/HeaderTemplateManagerGetFontFromTemplate.cpp
- GameClient/GUI/HeaderTemplateManagerRva00201B05.cpp
- GameClient/GUI/HeaderTemplateParse.cpp
- GameClient/GameClientDisplayModeChange.cpp
- GameClient/GameClientDrawableTOC.cpp

All abbreviated consumer paths are under `Code/GameEngine/Source/`. Release
these claims after confirmed publication, then settle landed RVA claims. The
three inherited Recorder file claims also remain held until its commit lands.
