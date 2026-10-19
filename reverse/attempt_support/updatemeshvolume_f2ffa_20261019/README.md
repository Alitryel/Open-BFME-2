# updateMeshVolume 0xF2FFA (3369 B): 3-angle pass 2026-10-19

Result: partial. The bank is size-exact at 31 differing lines plus one call that is
unresolved until a fold pin exists. Before this pass the bank was at 33. Model claude-opus-5-5.

## Change that helps
- `AABoxClass box(meshBox);` uses the real copy ctor, as WB does.
  - It replaces the `Region3D boxCopy` cast and closes the Corner0 addss commute at f3494.
  - This TU emits `??0AABoxClass@@QAE@ABV0@@Z` byte-identical to retail 0x9AC04
    (43 B, no relocs). Landing needs a fold pin with fold-proof (`tools/pin_admission.py --add`).

## WB facts (twin wb 0x806A80; 0x805CA0 is updateVolumes, its caller)
- Function-scope locals are in the same order as the BF1/ZH donor.
- `length` is declared in the reconstruct block.
- `isMeshRotating` is set before `allocationFlags`, followed by a separate `if (!isMeshRotating)`.
- All three rows use plain Dot_Product, so the row-1 fmul order at f3121 is a compiler effect.
- toLight and toPrevLight are the plain `objectCenter - X` temp, copied, then Normalize.

## What the remaining homes are
- `[ebp-0x8]` is the CSE'd history index `lightIndex*0xA0+meshIndex`.
- `[ebp-0x1C..-0x14]` in retail is the second `operator-` temp sharing lightPosObject's slot.
  - f3357 is the inlined Normalize reading that temp.
  - The bank's Subtract-into-lightPosObject can never give this, because lightPosObject is
    address-taken and must be reloaded after Inv_Sqrt.
  - The donor/WB form `toPrevLight = objectCenter - hist;` (donor_form_t1x.cpp.txt, nd 69,
    size-exact) gives retail's reads but homes the temp at +0x30, inside sphere.
- In retail, toLight and lightRay share +0x54.

## Frame-packer model, measured over about 500 variants
- Declaration order is ignored: 12-24 shuffles of each set compiled identically.
- An address-taken local whose scope covers the function never shares a slot.
- An address-taken local in an inner block does share a slot.
- Non-address-taken locals share slots by liveness.
- With lightPosObject declared in the reconstruct block, it pairs with toLight and the temp
  pairs with lightRay. Retail has the opposite pairing: {toLight, lightRay} and {temp, lightPosObject}.
  This looks like greedy first-fit in weight order.
- The count of surviving dead locals only flips the Corner0 add (k mod pattern). It never moves
  frame homes and never flips f3121.

## Ruled out
- Headers: vector3.h is identical between BFME1 and ZH, and a real Matrix4x4 worldToObject is byte-identical.
- Block-2 spellings:
  - `-=` and `Subtract` give 3354 B.
  - A named delta, a const& alias and `Vector3(objectCenter)-h` are identical to the temp form.
  - `-(h-objectCenter)` gives 3389 B.
- Making toLight address-taken gives 3353 B.
- Placements:
  - Moving `length` changes the code but does not help.
  - Putting det, sphere, Corners or lightRay at function scope does not help.

## Next lever
- Keep the donor temp and lightPosObject in the reconstruct block.
- Find a source form where lightRay claims toLight's slot before lightPosObject does, by changing a
  weight or lifetime without adding code. For example, lightPosObject used only through
  Transform_Vector and the calls, or a lightRay that is not scalarized.
- Harnesses are in build/nbr/vs/b1..b3 of the 2026-10-19 seat (untracked).
