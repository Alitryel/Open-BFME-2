# DynamicShroud receiver prerequisite — 2026-10-25, codex

Allocated target: `Code/GameEngine/Source/GameLogic/Object/Update/DynamicShroudClearingRangeUpdate.cpp`, family A shard 0/2. The planner's original-path alternatives all point here but remain hints; current `tu_skeleton.py --plan` rebuilds routing in memory and approves the seed and the three remaining clean donors. Thirteen rows are approved overall; two mixed sources and three protected sources remain outside this repair. No TU map is committed.

## Demonstrated prerequisite repair

Before: supported `--merge <target> --dry-run` exits 2 with no accepted donors. Animation loses its method declaration after private classes are composed. Xfer's hoisted include precedes required operands. The update donor also has a different Object/update-interface view.

`DynamicShroudClearingRangeUpdateView.h` shares the existing seed receiver with the animation and Xfer donors. It declares their already matched methods, keeps the seed's incomplete base interfaces unchanged, and keeps Xfer's operand declarations beside its canonical include. The one-byte decals-created member uses the bool spelling already required by the native Xfer overload. There are no function-body, compiler-option, layout-offset or function-identity changes.

After: the same dry-run exits 0, accepts the seed and both animation/Xfer donors, and verifies all seven rows. The update donor remains rejected: its virtual update declaration, state/module-data view and Object methods still need reconciliation against the seed; no anchor/vtable substitution is attempted. Its different compiler flags need checking when that work is undertaken. Constructors and the pool-key source remain protected, and mixed rows stay in their owners.

Leave these two compatible donors for Luna. This commit adds one scoped header, removes zero cpp files, retires zero debt keys and recovers zero C++ bytes. A later merge could absorb two cpp files; no Luna landing is claimed.

## Verification and provider/consumer evidence

- `./build.sh` all three consumers: 7/7 before and after, two compiler float literals, no string/import failures. `find_declared_unmatched.py` passes all three.
- `data_check.py` reports zero findings. `allowed_symbols.py --source` reports 24 references (20 owner, two EH, two aliases), zero wrong bindings. `link_check.py --new-variants --paths-from build/codex-shroud-sources.txt` exits 0.
- Saved before objects compared through the existing allowed_symbols/link_census APIs: all 11 external code definitions have identical bytes, relocation digests, sizes and exclusivity. Undefined references and linker aliases are identical. All 25 non-debug sections (19 seed, four animation, two Xfer) retain their contents, relocations, section flags and COMDAT selection policies after local labels are normalized to section/offset. External data definitions are identical. Provider candidates and their selection rules therefore do not change.
- All 24 ledger reference sites retain the same symbols and retail targets, including the two EH references. No binding changes or newly competing COMDAT variants are hidden by a byte-only check.

Local receipts: `build/codex-shroud-{before,after}-dry-run.txt`, `*-build-{before,after}.txt`, `*-before-{files,objects}/`, `*-object-proof.json`, `*-eh-binding-proof.json`, `*-code-identity.txt`, `*-data.txt`, `*-link-variants.txt`. The supported planner was refreshed after edits/rebase; no source under protected registers is deleted and no identity/debt key disappears.

## Batch audit and handoff

Audited upstream `dbb6a85242` plus all four pending commits and these three staged consumers/new header. No source path is moved, renamed or deleted anywhere in this batch. The two new scoped headers each have only their three direct consumers; active tools, hooks, workflows, source/header includes, build inputs and registries retain their paths. Historical EA paths are preserved. Rebase brought no change to this prerequisite, the earlier three prerequisites, their adopted headers, AGENTS.md or docs/consolidation.md; check_csv passes. Pending commits before this one:

```
00dc6eb795 Share ObjectDefectionHelper receiver declarations for consolidation
a0f96827b9 Adopt canonical GameLogic in production-exit donors
705d451ec3 Make HeaderTemplate donors compose with the canonical header
41da087d77 Reconcile Recorder file-handle donors with CRT declarations
```

The preceding ObjectDefectionHelper commit hook conservatively includes Eva.cpp because EvaVectorABI.h contains `_STLP_NATIVE_HEADER(vector)`, a macro include which header_dependents treats as including every changed header. Eva has no actual ObjectDefectionHelper dependency; the widened hook still passed all 33 rows, including Eva's EH rows. This does not expand the repair's dependency set.

Keep this target's three cpp claims and new-header claim, and the earlier Recorder/HeaderTemplate/production-exit/ObjectDefectionHelper scopes, until publication is confirmed. Then release file/class scopes and settle landed RVAs. No maintainer-only link/census/nightly/smoke run was started.
