# LifetimeUpdate GameLogic header prerequisite, 2026-10-26, codex4

Allocated destination: Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdate.cpp.
Stacks on the module-data and frame-field prerequisites in this outgoing batch.

## Repair and bounded result

Replace the constructor donor's private GameLogic with the registered canonical
GameLogicObjectLookupView.h. Expose the already used Hulk lifetime word at +0xA0
inside the canonical view's padding: five padding bytes, the four-byte word,
then eight padding bytes retain m_firstObject at +0xAC and all subsequent fields.
Retain the donor accessor's dllimport/forceinline shaping.

Target evidence: retail constructor 0x003A4B58 loads TheGameLogic, adds +0xA0,
compares the word with -1 and passes its value twice as calcSleepDelay bounds.
The previously verified donor implements that access. Existing byte-exact
SlowDeathBehaviorUpdate independently uses the same offset. The reference
GameLogic declaration supplies the getHulkMaxLifetimeOverride spelling; the
reference alone does not prove the target offset or full class layout.

The owning command, header_adopt_lane.py accept --class GameLogic
Code/GameEngine/Source/GameLogic/Object/Update/LifetimeUpdateCtor.cpp, passes
and removes its single header_queue.tsv entry. Three existing rows / 183 bytes
remain exact (165-byte constructor, eight-byte unwind and ten-byte EH handler).
No data or code-identity key is retired.

The normal merge dry-run now gets past canonical GameLogic adoption but still
rejects the constructor's incompatible UpdateModule base/setWakeFrame view.
The accepted set remains seed, calcSleepDelay and module-data constructor:
six rows / 329 existing bytes. This commit clears a header prerequisite, not
an additional compatible donor or confirmed Luna landing. Receipt:
build/codex4-lifetime-hulk-trial.txt.

## Verification

- Before: ./build.sh on the 1,006 direct canonical-header consumers passes
  6,539/6,539 functions; the 130 indirect consumers plus the constructor baseline
  pass 663/663. The supported header_dependents.py --staged scan supplies the
  complete 1,137-source closure.
- After: ./build.sh on all 1,137 sources passes 7,186/7,186 functions and 140/140
  data rows, plus 1,478 string literals, 216 empty-string references, 1,919 float
  literals and 383 imports. Receipt:
  build/codex4-lifetime-hulk-full-after-build.txt.
- Complete object snapshots compare code fingerprints/sizes/exclusivity,
  undefined names, external code/data definitions, COMDAT selections and per-row
  data references. The only difference is W3DBuffBufferFill's compiler-generated
  TU-private anonymous-namespace discriminator, ?A0x5eb6c6db@ to ?A0x837a6855@.
  All fifteen renamed definitions retain identical facts and selections; after
  this explicit substitution the entire snapshots compare equal. No named code,
  unresolved-name set or data binding changes. The strict global inventory has
  exactly one provider for each new private name, all in W3DBuffBufferFill, and
  no external referrers; the old private names have no providers. Snapshots:
  build/codex4-lifetime-hulk-full-{before,after}.json.
- Strict allowed_symbols provider snapshots compare equal: getFrame retains
  393 identical four-byte providers and the same selected first provider,
  FiringTrackerXfer; the forced-inline Hulk accessor emits no provider or
  unresolved reference. No new shared getter binding is introduced.
- Constructor allowed_symbols reports four owner, one EH and one alias reference,
  zero wrong bindings. data_check.py --converged reports ten protected addresses,
  zero second names and zero unjudged rows. eh_verify.py reports one exact EH
  graph, no missing object. class_gate.py, find_declared_unmatched.py on both
  changed code/header files, check_csv.py and diff whitespace checks pass.

## Complete outgoing batch audit and handoff

Reviewed the scoped Update planner and current allocation before editing. No
source is moved, split, deleted or renamed; no ledger is repointed and no TU map
is regenerated. The pending commits add one private module-data header, with
its two verified consumers, and this change adds the canonical include in one
donor. Reviewed outgoing commit path changes plus the staged change, including
active tools, hooks, workflows, includes, build inputs and registries. No active
tool/hook/workflow names these paths; no consumer needs repointing. Historical
EA paths remain intact. Existing code/data identity findings and their sources
remain unchanged. Header retirement uses its owning acceptance command.

Other allocated read-only trials: SupplyWarehouseCripplingBehavior accepts its
pool/module-data pair (three rows) but rejects the primary constructor with
C2511; its missing destination is not approval to invent a receiver. OneRingPenalty
accepts no pair: pool/update/Xfer and module-data constructor declarations are
missing, module-data destructor bytes differ, and canonical Coord3D adoption
remains a prerequisite. Receipts: build/codex4-supplywarehouse-current-trial.txt
and build/codex4-onering-current-trial.txt. No edits or claims were taken for them.
The earlier ModelCondition pool trial was reverted because the composed primary
vtable grew from four to eight bytes without a proven slot; its blocked attempt
is recorded in re_attempts.log. Do not repeat unchanged receiver/ABI blockers.

Net recovered C++ bytes zero. File reduction zero (the complete batch adds one
private header). Header debt retired one; data and code-identity debt retired
zero. Leave the demonstrated compatible LifetimeUpdate and LargeGroupAudioUpdate
donors for Luna. Keep outgoing file/class claims until publication is confirmed;
then release them manually and settle landed RVAs.
