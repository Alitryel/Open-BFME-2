# False reject: an unproven COMDAT copy loses although the link keeps retail's

Check: `tools/link_census.py` `keep_rule` (rules `retail-truth-3`), as used by
the census and by `tools/link_check.py`.

## What it does

For a name with a retail address, a copy whose verdict is `unknown` (bytes
match nothing that disproves it, or the address has several ledger claims, so a
`wrong` judgment is downgraded) loses whenever its digest differs from the kept
proven copy. `retail-truth-3` stopped charging copies proven `wrong` when another
object supplies the retail-proven copy, but left these `unknown` copies charged.

The link keeps the first copy in link order. When that copy is the proven
retail body, every other copy of the name, `wrong` or `unknown`, is discarded
and never runs, exactly as the original build discarded its own units'
differing copies. Charging the unit for such a copy blocks it for a body the
image does not contain.

## Evidence (index d7c728a74b, link_check of 1,806 non-linked units)

- `??0Matrix3D@@QAE@XZ`: the first copy in link order
  (DumbProjectileBehavior.cpp) and 50 others are proven retail (22-byte
  `??_H` form at 0x000423C5). The 3-byte `mov eax,ecx; ret` copies of /O2
  units are `unknown` and lose; `HLodUpdateObjSpaceBoundingVolumes.cpp`
  (2,495 B) is blocked by nothing else.
- 31 units (13,141 matched bytes) are blocked only by `unknown` copies of
  names whose kept (first-in-link-order) copy is proven retail, among them
  `HLodUpdateObjSpaceBoundingVolumes.cpp`, `BfmeObject476Copy.cpp`,
  `MeshClassRenderWithFXMaterial.cpp`, `AptStrategicPlayerStatus.cpp`,
  `ShroudManagerImplGetNearestGroupWithValue.cpp` and 18 `StlSweepW5` units.

## Proposed rule (`retail-truth-4`)

An `unknown` copy does not lose when the copy the link keeps, the first in link
order, is proven retail's. Wrong copies keep `retail-truth-3`'s exemption;
`unknown` copies of a name whose first copy is not proven retail, the `first`
rule and the `unreferenced` rule are unchanged. `wrong_selected` still judges
the kept definition for every unit touching the name.
