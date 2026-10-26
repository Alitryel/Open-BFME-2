# ModelConditionUpgrade setter prerequisite, 2026-10-26

Allocated target: Code/GameEngine/Source/GameLogic/Object/Upgrade/ModelConditionUpgrade.cpp
(family A, repair shard 1/2, codex4). This addresses the concrete Luna handoff
in consolidation-modelconditionupgrade-binding-blocked-20261025.md. No merge
is applied; leave the compatible donors for Luna.

## Blocker and repair

The normal before trial accepted the seed, constructor and upgrade implementation
(three rows / 337 retail bytes), but the earlier attempted merge's identity gate
reported divergent `?set@WeaponTemplateSetHead@@QAEXH@Z`. Current object evidence
reproduces two selectable copies: GarrisonContainLoadGarrisonPoints.cpp supplies
the first (27 bytes, digest 752aba0fd954); ModelConditionUpgrade supplies 29 bytes,
c8c4e1324edd. They differ in signed versus unsigned indexing and frame-pointer
flags. There are no external referrers to this setter in the object inventory.
The parser's row has six owner references and already inlines the bit update.

Keep that exact update directly in the parser and remove the local storage
view's unnecessary callable setter definition. This removes the non-owner
definition rather than changing the selected Garrison provider, names, flags,
pins or layout. The remaining storage/copy/intersection declarations retain
their existing opaque names; no donor identity or canonical layout is inferred.

## Verification

- Before/after `./build.sh` of the changed source: its 173-byte parser matches;
  the string, float and import checks pass. find_declared_unmatched.py passes;
  class_gate.py accepts the source.
- allowed_symbols.py --source reports six owner references, zero wrong bindings.
  Current allowed_symbols definitions/referrers show the setter now has just
  the unchanged Garrison copy, with no external referrers. Comparing all three
  donor objects before/after, the only definition removed is the parser's
  unused 29-byte setter; every other digest, size, COMDAT selection and undefined
  reference is unchanged. No protected identity/debt register has a key for the
  affected source or setter. No register was edited or debt key retired.
- data_check.py --converged: one source, ten addresses, no second names or
  unjudged rows. The normal after merge dry-run again accepts all three eligible
  donors / three rows / 337 bytes, with no rejected eligible donor. The unchanged
  three mixed files and two protected donors remain outside this repair.
- Scoped composition evidence reads the actual effective trial object
  build/tu_skeleton/d2df7083741b0475.obj: all three rowed definitions retain their
  byte/relocation digests, sizes and COMDAT selections; all 19 undefined external
  references equal the donor union after internal resolution. data_check's
  object_facts on donor versus composed objects gives identical bindings and
  definitions for every row, including four constructor vtables, the parser's
  diagnostic and throw-info, the frame-rate global and the float literal.
- The sole changed incidental definition in composition is the unrowed inline
  test helper, 36 to 33 bytes (114e8dd6ed93 to 8fe51632cdba): the disassembly
  differs only by the frame-pointer prologue/epilogue and argument access. Both
  retain the same unsigned indexing/bit-test logic and no relocations. There
  are no external referrers in the inventory; the parser inlines it and its
  rowed bytes are unchanged. This is an inspected composition difference,
  not an assertion that every incidental definition is identical.

Receipts: build/codex4-modelcondition-{plan,build-before,build-after,
trial-before,trial-after,defs-before,defs-after,provider-before,provider-after,
bindings-after,data-after,composition-evidence} files. The original source
backup stays in build/codex4-modelcondition-before.cpp. No game-source attempt
or manual ledger move remains.

## Planner, path audit and handoff

The scoped Upgrade planner's current packets were reviewed: original-path
evidence has only the existing ModelConditionUpgrade destination alternative;
the committed map was stale, so only the merge tool's in-memory current routing
authorizes its trial. Compiler-setting and internal-linkage warnings were
reviewed through the trial and identity evidence above. No tu_map.csv is staged.

Audited the complete pending origin/master..HEAD range plus this prerequisite.
Upstream advanced after the initial pull, so merge-base..HEAD and the outgoing
log isolate this seat's actual commits from reverse differences to newer
upstream work. No source paths move or disappear in our batch. The inherited
TunnelContain batch adds two private headers with three already verified
consumers. Combined searches through tools, hooks, workflows, Code includes,
docs and build registries find those intended consumers and a historical
ModelConditionUpgrade constructor comment; nothing needs repointing. Header,
MS-header, code/data, gate, hatch and duplicate registers have no affected key.
Historical EA paths are preserved. Receipt:
build/codex4-prerequisite-path-audit.txt.

This demonstrates removal of the setter identity obstacle; it is not a
confirmed Luna landing, census/ownership gain or recovered C++. File reduction
zero, registered identity debt retired zero, recovered C++ bytes zero.
Keep the destination file and 0x004B65E4 claims until publication is confirmed,
then release the file claim and settle landed RVAs. The evidence-file claim
also needs releasing after publication. The earlier TunnelContain claims remain
listed in that batch's handoffs while its commits wait for the publisher.

Final scoped acceptance: `link_check.py --fetch-index` retained the current
2026-10-25 21:36 census index at f995f30157 and imported its 22,800 objects.
`link_check.py --new-variants <destination>` exited zero with no new variant;
this is a prediction/admission check, not a census improvement. `eh_verify.py`
reported zero EH rows, zero absent objects and zero nonexact rows. Receipts:
build/codex4-modelcondition-link-{check,prediction}.txt and
build/codex4-modelcondition-eh.txt.
