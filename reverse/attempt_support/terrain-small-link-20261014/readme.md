# TerrainLogic small-flag helper linkage repair

Base checkout a691a921ba782639d0cb5fce94a78a563d1c5aae. Runner measurement index: 147cfae2cb,
2026-10-14 07:27; SHA256 recorded in object-proof.json. The newer committed
link_status.csv queue measures de7bb30890 and serves discovery only. Neither
index, status nor history is changed; no per-row data-back ranking was used.

TerrainLogicRva0028449F.cpp's private GeometryInfo view implements
getIsSmall as `8a4104c3`, reading +4. The index's first PartitionManager copy
and the unchanged W3DGhostObject witness implement `8a4108c3`, reading +8.
Neither helper has a ledger row or a retail pin. The matched flattenTerrain
caller at 0x0028458F..0x00284AC6 inlines the +4 access; its 1335-byte gate
supports keeping that operation. Rename this local helper and its one use to
terrainShapeIsSmall to distinguish the existing views. This implementation
name does not assert a new retail identity or a canonical GeometryInfo layout.
No flags, ABI, layout, data names, headers, pins or ledger rows change.

Acceptance:

- Before/after bounded link_check.py --prepare-current verifies all three
  rows with strict reusable receipts. Independent ./build.sh passes 3/3:
  240B record sweep, 1335B flattenTerrain and 10B compiler EH handler.
  One string literal, 24 float constants and 20 named imports pass with no
  baselined or skipped string references.
- All 14 retained external COMDAT bodies have identical bytes, extents,
  digests and normalized relocations. The renamed 4B helper remains wholly
  identical. All 21 nondebug sections, including local code/data and
  relocation targets, match after helper-name normalization. Strong,
  undefined and weak bindings are unchanged. Source/object hashes and the
  complete retained digest list are recorded in object-proof.json.
- W3DGhostObject.cpp passes its three-row byte gate and strict receipt
  preparation. Refreshing only this witness and the before/after consumer
  in memory against the SAME index reduces consumer findings 4 -> 3.
  The witness's 43 independent findings remain unchanged. Remaining consumer
  blockers are unresolved rva0028641F/Rva002872BA and rva004DC096/Rva004DC1BF,
  plus a selected nonretail GeometryInfo constructor. Both units still fail
  local link closure; legacy LINKED bytes remain 0 -> 0 for the consumer.
- EH: 2/2 EXACT, no baseline or missing object. Frozen definitions, class
  gate, new-variant admission (shadow), CSV and whitespace checks pass.
  Enforced converged-data checks protect eight addresses with zero second
  names or unjudged rows. Shadow data checks have zero findings; all data
  facts compare equal before/after. Placement resweep finds zero bodies/pins.
- The index has only this one losing getIsSmall copy. The two other copies
  agree on +8; no related-cause consumer requires another source edit.

This is self-strict byte verification and one bounded paired LEGACY finding
removed, with zero authored-byte or linked-byte growth. Closed-strict closure,
actual placement and fresh census gains remain unmeasured. No maintainer-only
verification runner was started. Scratch objects, receipts, snapshots and
comparison scripts remain in build/terrain-small-link-20261014.

Donor review: verified BFME 1 gitlink a7c38d3b2597121f178ab5190b3062478823257d;
reviewed d2e21369067f2f2c762c1c7ec2792c75f1ecf53d (incidental per-unit
implementation ownership) and the existing TerrainLogicFlattenTerrain.cpp
donor. Ownership separation is applicable; donor byte offsets, alias scaffold
and private member-pointer calls are inapplicable. No donor code is imported.
Target byte and object evidence independently prove the helper conflict and
unchanged caller operation. Official upstream still fetches 58ab850fd1f734e310048b2e19c1ecb7ba112a3f.
Freshness remains due: the previously documented old-input full baseline needs
thousands of stale TUs and encountered compiler stalls. That unchanged
multi-hour prerequisite was not repeated in this bounded link seat; verified
checkout/gitlink and success timestamp are preserved.
