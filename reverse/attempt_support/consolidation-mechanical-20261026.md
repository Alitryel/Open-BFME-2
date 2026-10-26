# Mechanical consolidation handoff, 2026-10-26

Shard 3/5. No source or ledger changes remain; no merge passed the complete
composition checks. `python3 tools/progress.py origin/master` reports all
coverage deltas at zero.

## Trials

- `SupplyWarehouseDockUpdate.cpp` passed its allocation check and current
  scoped planner. Its normal merge dry run admitted no donors: the seed itself
  fails with `reference\\shims\\bfmealloc\\stl\\_alloc.h(446) : error C2950:
  '_STL::allocator<char>' : cannot explicitly instantiate an explicit
  specialization` and `SupplyWarehouseDockUpdate.cpp(293) : error C2227: left
  of '->getSupplyTruckAIInterface' must point`. Another rejected donor reports
  C2039, `rva004A7E43` is not a member of `Rva004A7D55`. Pool-key donor is
  refused because it is keyed in a protected path register. No claim was
  acquired and no source was changed.
- `Display.cpp` passed allocation, planner currency and routing. Its dry run
  accepted no donor. The unchanged composed class view rejects donors with
  missing members, including C2039 `'setDisplayMode' : is not a member of
  'Display'`, C3861 `getHeight: identifier not found`, C2039
  `'setDebugDisplayCallback' : is not a member of 'Display'`, and C2065
  `m_debugDisplayCallback: undeclared identifier`. Four other files are keyed
  in protected path registers. No claim was acquired and no source was changed.
- `HeaderTemplate.cpp` dry run admitted the seed plus four donors, but after
  `tu_skeleton.py --merge` staged them, the destination contained exactly the
  seven bytes `compile`. `./build.sh Code/GameEngine/Source/GameClient/GUI/HeaderTemplate.cpp`
  then failed with C1004, `unexpected end of file found`, at line 2; data checks
  could not compile the source. The trial was restored and all acquired file
  and RVA claims were released. This matches the generated-source write failure
  already recorded for W3DSmudge in
  `consolidation-device-20261025.md`; do not retry without resolving that tool
  failure.
- `dx8polygonrenderer.cpp` now dry-runs with both constructor donors accepted
  (9 rows, no rejected donors). The required scoped provider preview,
  `python3 tools/link_check.py --refresh --current-ledger
  Code/Libraries/Source/WWVegas/WW3D2/dx8polygonrenderer.cpp`, exits 1 because
  48 current-ledger object receipts are missing. The existing DX8 handoff also
  records stale-index duplicate-provider predictions. Do not apply or publish
  until current provider selection and consumer bindings can be verified.
- `AssaultTransportAIUpdate.cpp` passed allocation and a current AIUpdate planner;
  its dry run accepted no donors. `AssaultTransportAIUpdateHelper.cpp` fails
  with C2039 (`Rva0048F365Helper` is not a member of
  `AssaultTransportAIUpdate`); the pool-key donor fails with C2039 (`rva00048F411`
  is not a member). Other donors fail on duplicate `Xfer`/`GameLogic` view
  definitions or missing members. No claims or source changes were made.
- `FramGrab.cpp` passed allocation and a current WW3D2 planner; its dry run
  accepted no donors. Both unchanged trials fail with C2248 because
  `FrameGrabClass::Rva00958570_Flush_Buffered_Frames` is protected. No claims or
  source changes were made.
- `AptRenderingContext.cpp` dry-run accepted three donors (6 rows), carrying
  three data-check keys, one flag override and two data-ledger keys. The scoped
  current-ledger provider preview exits 1 with 50 missing object receipts,
  including the current `FramGrab` object. No merge was applied because selected
  COMDAT and provider/consumer bindings cannot be compared with the missing
  inputs.
- `HighlanderBody.cpp` dry-run accepted only its constructor donor; the pool-key
  donor fails C2039 (`getModuleNameKey` is not a member of `HighlanderBody`) and
  attempt-damage fails C2504 (`BodyModuleInterface` base class undefined). Its
  mixed `ConstIntGetters2.cpp` split dry-run accepted one 6-byte row, but the
  scoped current-ledger provider preview also exits 1 with the same 50 missing
  object receipts. Neither split nor merge was applied.

The fresh planner snapshots for GameLogic/Object/Update, GameClient and
WW3D2 passed `name_lane.py consolidate --check build/consolidation` before
those trials. `find_declared_unmatched.py` passed the staged HeaderTemplate
composition before its build failure; the staged CSV check passed. No
provider, COMDAT or link-clean improvement is claimed.

## Queue and handoff

`/opt/runner/consolidation_queue.py --limit 100000` lists 43 unheld allocated
TUs in this shard. The allocator has more candidates, but selected-COMDAT and
provider/consumer comparison is blocked by missing current-ledger receipts; the
merge-tool write failure also prevents publishing the one accepted HeaderTemplate
composition. The first two additional candidates also had exact compiler
obstacles above. This seat did not change identity/data registers or repair
tools. No file/RVA claims were acquired in this session.

## Follow-up findings — 2026-10-26

Further allocated dry-runs and verification:

- `OneRingPenaltyUpdate.cpp`: no unchanged accepted donors. Rejections include C2039 for `xfer`, `getModuleNameKey`, and `update` absent from `OneRingPenaltyUpdate`; C2248 private access to `m_specialObjectName`; its module-data destructor donor fails byte verification. Planner recommended adopting `Coord3D`; no repair attempted.
- `DetachableRiderUpdate.cpp`: dry-run accepted its pool-key donor only. The staged merge passed `./build.sh`, `find_declared_unmatched.py`, `check_csv.py`, `tu_ownership.py --staged`, `verify-removed`, and staged COMDAT checks, with 6 matched rows preserved and the data-check/data-ledger keys transferred. `code_identity_gate.py --staged` found 0 new findings. However, `data_check.py --staged` reports two outside-baseline shadow findings at 0x00A03D5C and 0x00A03D60: current static-local names encode `getModuleNameKey`, while the transferred baseline/ledger names encode `rva004AE832`.
- `link_batch_audit.py` was inconclusive because the index is at 47e030bafc, older than current `origin/master`, and initially lacked a current object receipt. `link_check.py --refresh` rebuilt 285 stale receipts from that older index. The staged destination then reported `LINKED 699 -> 0 bytes`, duplicate `?getModuleNameKey@DetachableRiderUpdate@@UBE?AW4NameKeyType@@XZ`, and a selected definition that is not retail's. This provisional but concrete provider collision needs Sol's investigation before publishing the move. No census was run.
- Path-consumer search found no active references in tools, hooks, workflows or build configuration to the deleted pool-key donor path. Historical EA path evidence remains.

The failed staged DetachableRider trial was restored, and all its file and RVA claims were released. Other dry-run rejections remain as previously recorded; no rejected donor was repaired or moved. Identity debt was not retired. This handoff records blockers only, not coverage progress.

## TransportAIUpdate binding blocker — 2026-10-26

The allocated `TransportAIUpdate.cpp` dry-run accepted its unchanged three-row `TransportAIUpdatePrivateAttackPosition.cpp` donor; ctor donor was byte-rejected and pool-key donor failed because `getModuleNameKey` is absent from the seed class. The staged move preserved 3/3 matched rows; `find_declared_unmatched.py`, CSV, TU ownership, removed-source, data, and staged COMDAT checks passed. `code_identity_gate.py --staged` reported one new shadow finding: `definition: divergent | ?getContain@Object@@QBEPAVContainModuleInterface@@XZ`. The changed donor's local `Object` view needs identity/provider review by Sol.

`link_check.py --refresh` refreshed 292 rebuilt objects but reports this destination is absent from census 47e030bafc and cannot be previewed until the next census. `link_batch_audit.py` is inconclusive: its index predates current `origin/master`, and the new destination lacks a current link-audit receipt. No selected-provider or consumer-binding improvement is claimed. The staged merge was restored and its file/RVA claims released; no manual source or identity-register repair was attempted.
