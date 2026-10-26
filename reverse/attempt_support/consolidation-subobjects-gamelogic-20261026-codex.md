# SubObjectsUpgrade GameLogic prerequisite, 2026-10-26, codex

Allocated target: Code/GameEngine/Source/GameLogic/Object/Upgrade/SubObjectsUpgrade.cpp, family A shard 0/2. Current runner allocation is unheld. Upgrade-directory name_lane planner reviewed original BFME2 path evidence, alternatives, compiler settings and mixed-donor prerequisites; refreshed after editing and --check passes. No merge, split, rename, TU map regeneration or row move was applied.

## Repair and demonstrated result

The mechanical handoff in consolidation-mechanical-blockers-20261026-codex.md records that its byte-exact constructor merge failed the canonical GameLogic class gate. SubObjectsUpgradeCtor.cpp now includes the registered GameLogicObjectLookupView.h and reads the same word at +0x40 through getFrame(), preserving the existing opaque destination pointer representation. No semantic identity for that destination field is inferred. Removed a stale comment alleging a struct-mangled global; its actual declaration remains GameLogic *TheGameLogic.

header_adopt_lane.py accept --class GameLogic Code/GameEngine/Source/GameLogic/Object/Upgrade/SubObjectsUpgradeCtor.cpp: PASS; retired exactly one header_queue.tsv row through the supported acceptance path. No identity or data key was retired. File reduction 0; recovered/authored C++ bytes 0.

Ordinary tu_skeleton --merge TU --dry-run before accepted the existing seed plus constructor, nine rows. After accepts those plus Common/Rva004B4DBFRates.cpp, ten rows: one additional donor/row, 151 existing retail bytes. The adopt_first GameLogic prerequisite disappears and class_gate.py passes the generated composition. This is demonstrated prerequisite compatibility, not a confirmed Luna landing or a link census gain.

## Verification and provider evidence

- Before/after ./build.sh constructor: 1/1, 64 bytes exact. find_declared_unmatched.py and class_gate.py pass. ./build.sh seed and rate donor: 9/9 exact, one float literal checked, two complete STL constructor folds verified. EH verify on all three sources: one EXACT graph. Declaration scan passes all three.
- Constructor before/after objects retain its original constructor definition, undefined symbols, external data and four alternatename directives exactly. Object section audit found precisely one added four-byte getter COMDAT, bytes 8B4140C3, selection ANY (2); all pre-existing nondebug section payloads, relocations, flags and selections remain identical. Its normalized digest 84449fef877c equals all 394 census copies and the current AutoDepositUpdateCtor provider. link_check --new-variants passes. Thus any provider selection among these copies retains the same body.
- allowed_symbols.scan has one reference fact before/after with no delta. data_check.object_facts is unchanged. --converged: one source, ten addresses, zero second names/unjudged rows. Strict --prepare-current accepts the explicit constructor provider; census/index/status are unchanged and link closure is not claimed. An earlier preparation rejected moving inputs during verification; the sequential retry succeeded.
- Final ordinary composition build/tu_skeleton/17e6e2b8efea253d.obj compared with the pre-repair composition plus the three current standalone objects: all 21 external code definitions, COMDAT policies, aliases and undefined symbols after internal resolution match. The one external data definition, payload, relocations and selections match; per-row data references and owners are equal. No guard normalization is needed. The comparison includes the pre-existing compiler-generated UpgradeModule destructor from the old composition; that definition already existed before this repair and is not silently treated as a standalone provider.

Scratch evidence is build/codex-subobjects-* (saved source/objects, before/after builds and ordinary trial text, object/section/reference/data audits, composition proof and strict provider receipt). The raw object section comparison intentionally reports the added getter; this is explicitly judged above rather than hidden by normalization.

## Remaining prerequisites

The pool-key donor still lacks getModuleNameKey in the seed. Other receiver, transfer and module-data destructor donors still fail constructor declaration reconciliation; mixed foreign rows remain for the supported split lane. The previously recorded wrong texture binding at 0x00211E58 and four unreferenced alternatename directives still need their own identity cleanup before a merge is landable. No gate was weakened and no hatch, pin or invented identity was added. Leave compatible donors for Luna and retain all existing debt keys.

## Complete outgoing compatibility audit

Audited pending 84d78f24f6 plus this staged repair, including git diff --name-status origin/master..HEAD and own log since dfc0c39c28. No source path moves or removals occur. The sole new source-side path is SquishCollideView.h with exactly two verified direct consumers from the prior commit. Combined tools/hooks/workflows/includes/build-input/registry searches found no other active path consumers requiring changes; historical EA paths remain. The constructor include resolves to the unchanged canonical header. Remote origin has advanced independently, so inverse differences for unrelated upstream files are not part of this batch. No protected register changes except the supported one-row header queue retirement.

Keep constructor, rate donor and handoff file claims until publication is confirmed; prior SquishCollide claims also remain pending. Then release file claims and settle landed RVAs. No maintainer-only link cycle, nightly or smoke run was started.
