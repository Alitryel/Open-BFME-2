# Water consumer tree-comparison repair

Both water consumers emitted an unused external STLport base-iterator
inequality that conflicts with the selected copy. The established TU-local
typed node comparison removes that emission without changing the game bodies.
No layout, shared header, compiler flag, ledger, pin or global is changed.

## Controlled measurement

Base tree: e50753fbe2290f994d95cc5f1b62ad5e94808f45. The frozen runner index
measures 19a2565407 (2026-10-15 09:33), based on census 5986a99448 (04:52).
Its SHA256 is in context.json. The committed status queue instead measures
28269d8e8d. No index/status rewrite, census or per-row data-back ranking ran.

Paired local refreshes replace **both** owned objects together in independent
copies of that same index. Each loses exactly its tree-base comparison finding;
every other finding is identical. The comparison provider remains unchanged.

| Consumer | Strict rows before/after | Own nonpadding bytes | Findings before/after | Retained COMDATs |
| --- | ---: | ---: | ---: | ---: |
| Rva00082EF5Ctor | 25/25 | 1,043 | 5 -> 4 | 97 |
| W3DWaterDrawOceanWater | 5/5 | 1,581 | 11 -> 10 | 60 |

Legacy local LINKED remains **0 -> 0** for both. Strict current compilation
receipts are established; no self-strict placement or closed-strict gain is
claimed. This repairs two existing link conflicts, adding zero authored bytes.

All 157 retained COMDATs have identical bytes, extents and relocation digests.
For each object, normalized nondebug sections differ only by replacing an
unused 18-byte external comparison with an unused 12-byte private comparison.
Neither has a nondebug caller relocation. All other normalized sections,
relocations, external bindings and directives are identical. Compiler-generated
local labels are compared by their destinations, and all seven EH graphs are
EXACT. The byte gate verifies renumbered funclet labels from their parent EH.

## Acceptance and remaining work

- Strict before/after preparation and ordinary build gates: **30/30** rows.
  Ocean's two float literals and its data row also verify.
- EH: **7/7 EXACT**, no baseline or missing objects.
- New-variant admission, class and declared-definition checks pass.
- Enforced data checks have zero findings. Eight converged addresses have
  zero second names or unjudged rows. Paired data facts/findings are identical.
- Identity remains shadow mode. Ocean's findings stay 7 -> 7; constructor
  findings change 4 -> 2 as local labels move. No new findings; these diagnostic
  disappearances are not claimed as additional repairs. The retained-body and
  relocation proof is the evidence that bindings did not change.
- Ordinary local link checks still exit 1: constructor has four BfmeE16
  allocator/vector conflicts; ocean has ten duplicate, matrix/transform,
  light and selected-provider findings. Full placement remains outstanding.
- Placement sweeps find zero additional bodies/pins. Ledger and diff checks pass.

BFME1 de59a7e9f891b3ed2d4221d151ca881f4b75a583 supplies the reviewed ownership
principle; BFME2's existing typed-comparison repairs and the target object proof
justify this adaptation. No donor ABI or layout is inferred. New upstream
66b19a8e95a4add525ef808fcea088e306798e2b allocation suppression was reviewed
but is unrelated. The clean donor remains at verified
a7c38d3b2597121f178ab5190b3062478823257d. Reference scope is foreign claimed,
and the recorded old/new full-gate input blocker remains unresolved. No pointer
update or freshness-success stamp was written.

An earlier MapCache attempt failed the retail pointer-selection schedule after
local tree/list and tree-only comparisons. Its original source and 1/1 byte
verification were restored, the unchanged blocker recorded and claims released.
No workaround was landed. Other served entries already link; the camera guard,
MilesAudioCache and Rva000A7E9E blockers have unchanged recorded evidence and
were not retried.

Proof scripts run from the repository root. Run object-proof.py, data-proof.py
and identity-proof.py with the corresponding ignored scratch directory
(`build/water-tree-link-20261015` or `build/ocean-tree-link-20261015`). Run
link-proof.py without arguments. Original objects and source backups stay in
those ignored directories; binaries are not committed.
