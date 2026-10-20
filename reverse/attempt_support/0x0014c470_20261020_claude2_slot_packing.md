# 0x0014C470 MeshClass::RecolorHouseColor — slot-packing analysis (2026-10-20, claude2)

Start from `reverse/attempts/0x0014c470.cpp` (0.969, 2291 B, /O2 /G7 /arch:SSE).
Every instruction, call and branch matches retail; only the stack homes of
locals in `[ebp-0xF1..-0xD8]` differ (71 bytes). This note records which
variables are in the wrong slot and what has been ruled out.

## Method

Compile the candidate with `/FAs`. The listing's `_name$N = -off` equates give
each local's home exactly. Map each home to retail's home for the same
reference (first instruction that uses it). The scratch scripts were
`build/s29/grp.py` (slot groups from equates) and `build/s29/vmap.py` (ours →
retail per variable). Line numbers below refer to the bank file.

## Slots (ebp offsets), retail vs ours

| off  | retail                                                     | ours (bank)                                   |
|------|------------------------------------------------------------|-----------------------------------------------|
| -237 | bools 325/359                                              | same                                          |
| -236 | **mesh holder**                                            | flags, loopTex 313, singleTex 318, n, key 339, recTex 342 |
| -232 | flags, recTex 342, loopTex 313, singleTex 318              | mesh holder                                   |
| -228 | key 339, n 332, T 344 (rva001360EA), T 346 (Get), legacyTex 360, 2nd 325 temp | FXname 344, 1st 325 temp      |
| -224 | FXname 344, 1st 325 temp                                   | setup, legacyName 363                         |
| -220 | legacyName 363, setup                                      | T 344, T 346, T 359, T 363, T 365             |
| -216 | T 359, T 363, T 365, 3rd 326 temp                          | 2nd, 3rd, legacyTex                           |

Every slot from -212 down (handles, description, newParameters, enable,
newTexture, source, destination) already matches. Retail packs the same pairs
`{FXname,1st}` and `{legacyName,setup}`. The differences are the mesh slot
order and the membership of slot C (n and key with the 344/346 temps, legacyTex
and 2nd).

## Probes (dummy `dummyUse(mesh.pointer)` calls appended)

- In the bank, mesh needs +5 extra references (listing count x16 against x11)
  to take -236. With that boost the slot table is otherwise unchanged: n and
  key still sit with the flags group, and the 344/346 temps still sit with the
  359/363/365 temps.
- With n made static (p1), mesh needs +3. With key's temp removed (p2), it
  needs +3. With both (p12), it needs +0. The threshold therefore grows with
  the **sum** of the slot's members, not with its heaviest member. In this
  function, slot order follows aggregate slot weight. An earlier micro-test
  suggested creation order, so treat the micro rule with caution here.
- Conclusion: retail differs in **grouping**, not just in order. In retail, n
  and key are not packed with the flags group. Once they leave it, the flags
  group's total drops below mesh's, which explains the -236/-232 swap by
  itself.

## Ruled out this session (each one built and slot-mapped)

- Holder dtor zeroing the pointer: changes code (2236 B). Inline
  `operator->` (by value or `T*const&`): inert.
- Moving n to the loop or FX block scope (n2/n3/n5): frame grows. A named key
  local (k1): inert. Making n static or removing key: diagnostic only.
- Micro-TU models of the weight anomaly, all disproven: loop weighting,
  density, nesting depth, RVO init, early-return count, saturation.

## Earlier seats ruled out (see the two sibling notes)

- Callee visibility, handle-type unification and WB accessors (holder
  `operator->`, IsBound).
- Loop forms: `continue` form, textureIndex order, hoisting
  handles/count/description, effect before the condition.
- Scoping and helpers: named handle/key blocks, getter at each use, holder
  ctors, AsciiString as StringBase, forceinline index/key helpers, union
  index/key.
- Flags: /O1, /G6, /G5, /Ob1, /EHs.

## Untested leads

1. WB uses one function-level cleanup-flags word for all conditional temps.
   Bits 1/2 come from the 325 temps, bit 4 from `TextureAsset::Get(...).IsBound()`
   at 346 (mesh.cpp:1622), bit 8 from the 359 temp. Retail sets bit 4 at 359,
   so release does not flag the 346 temp. The original assert-or-return macros
   (mesh.cpp 1596/1622/1627) put the test inside the macro's condition. Try
   reproducing the release expansion exactly (e.g.
   `if(!(x)){return;}` around a bool temp) so that the 344/346 temps and key
   pick up retail's grouping.
2. Ask what makes n and key leave the flags group. A lexical conflict with
   recTex/loopTex/singleTex is impossible for a block-scoped n. Look instead at
   the flags temp's own scope: is it per-condition or function-level, and how
   is it emitted?
3. `tools/permute.py 0x0014C470` currently reports "banked body does not
   compile here". Fix the bank's standalone compile before relying on it.
