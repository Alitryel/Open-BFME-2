# updateMeshVolume 0xF2FFA (3369 B): callee visibility closes the frame

Result: closer partial, banked in `reverse/attempts/0x000f2ffa.cpp`. Model claude-opus-5-5.

## What changed and why it works

Retail's unit also defines `buildSilhouette` (0xF2D25), `constructVolume` (0xEFDF6) and `constructVolumeVB` (0xF0251). All three receive `&lightPosObject` and only read through it (the matched home bodies dereference it and compare it with NULL; nothing stores the pointer). When cl 7.1 can see those bodies, it treats `lightPosObject` as unaliased. The plain donor and WB statement `toPrevLight = objectCenter - m_lightPosHistory[...]` then puts its temporary in lightPosObject's slot at EBP-0x1C, the inlined Normalize reloads that slot after `Inv_Sqrt`, and every other stack home falls into retail's place (history index at EBP-8, ray spills at EBP-0xC and EBP-0x10, sphere and extrusion scalars).

A control confirms the mechanism: the same stand-ins with one of them storing the pointer into a global restore the old frame exactly. All three must be visible. With any two visible and one only declared, the old frame returns unchanged. The effect is the same whether the definitions are ordinary or `__declspec(noinline) inline`, and the same whether they come before or after the caller.

The bank now carries three short stand-in definitions so the effect is measurable. They are not the retail bodies and must not land.

## Measurements

Both measured with `BFME_OBJSTORE=off`, objects deleted before each run.

| Candidate | Size | align_diff structural / memory / register | Bytes differing outside relocation fields |
|---|---:|---:|---:|
| Bank before this pass | 3369 | 0 / 45 / 2 | 31 |
| New bank | 3369 | 0 / 20 / 0 | 4 |

Sixteen of the new bank's twenty memory differences are absolute DIR32 operands that the gate fills from retail. The four real ones are the row-1 x87 pair below. The relocation symbol set of updateMeshVolume is unchanged; `??0AABoxClass@@QAE@ABV0@@Z` still needs its fold pin to 0x9AC04 as before.

## Exact remaining mismatch

At 0xF3121..0xF312F retail evaluates the row-1 rotation dot product as `fld [ebp-0x48]; fmul [edi+0x14]; fld [ebp-0x44]; fmul [edi+0x18]` (Y product first, then Z), and the bank emits Z first. Rows 0 and 2 already match.

## Body changes against the previous bank

- `toPrevLight` uses the plain donor subtraction; the `Vector3::Subtract` into lightPosObject plus copy is gone.
- The dead locals `prevPosToLight` and `prevObjPosition` are removed. With visible callees they cost nine structural regions (3372 B) in the Corners block, whatever their count.
- The flag test reads `geometryView->m_meshes[meshIndex].m_field30` instead of the raw address sum (byte-neutral).
- Everything else keeps the WB-literal form the previous bank had.

## Hypotheses tested

Counts in this table exclude relocation operands.

| Test | Observation | Disposition |
|---|---|---|
| H1: three non-leaking visible callees | Frame homes all match; 0 regions, 4 memory and 0 register differences outside relocations | Confirmed |
| H1b: subsets of two, or one | Old frame (65 memory and 3 register differences outside relocations on the donor base) | All three needed |
| Stand-ins that preserve ECX | One missing `mov ecx,ebx` after buildSilhouette | Stand-ins must clobber ECX, as the real bodies do |
| 128-build factorial over WB toggles (dead locals, `length` scope, `allocationFlags` placement, `if (!isMeshRotating)` against `else`, flag-branch order) times four row-1 spellings | No variant fixes row 1; dead locals always regress Corners; `if (!isMeshRotating)` is needed for row 2 under plain Dot_Product rows | Row 1 not reachable this way |
| 48 row-1 spellings with rows 0 and 2 as Dot_Product (direct `operator[]` access or row references, six term orders, two associations, two product operand orders) | Direct access with Y and Z grouped gives retail's Y,Z,X but always adds the same 9-region Corners reschedule; reference and Dot_Product forms keep Corners and emit Z,Y | Coupled tie-breaks |
| Hybrids: prevXForm row through a reference, objectToWorld row read directly per term (and the reverse) | Direct objectToWorld access is what flips the pair to Y first, and it brings the Corners reschedule with it; reference access to objectToWorld keeps Z first | The pair follows the objectToWorld temporaries |
| 216 combinations of six forms for each of rows 0, 1 and 2 (Dot_Product, or direct `operator[]` access in five term orders) | No exact combination; the all-Dot_Product bank stays best at 4. Twelve mixes reach 6 (row 0 and row 1 direct with Y and Z grouped in row 1, row 2 Dot_Product). The one inspected, `x_dL_dYZX_D` (row 0 `X+Y+Z`, row 1 `(Y+Z)+X`, both direct), has all three x87 rows and the Corners block right, but flips the SSE operand order of Transform_Vector row 2 (lightPosObject.Z, 0xF3435..0xF345D, 6 differences); casting worldToObject differently or declaring it as a real Matrix4x4 does not move that | Closest alternative family, not closer |
| Control-flow shapes of the three row tests, a single short-circuit test, one shared `cosAngle`, `det` at function scope, Vector3 copies of the rows | No row-1 flip without regressions | Refuted |
| Visible stand-ins for `allocateShadowVolume` and `rva000F074E` | Byte-identical | No effect |
| Unrelated functions (1 to 12) placed before or after the caller | Byte-identical | Tie-break numbering is per function |
| Real `Matrix4x4 worldToObject`, `(*prevXForm)[i]` spelling, removing the `geometryView` local | Byte-identical, or Corners regression with dead locals | No effect |

## What landing needs

1. Byte-faithful `__declspec(noinline) inline` copies of `buildSilhouette`, `constructVolume` and `constructVolumeVB`, written against the ZH headers this unit uses, in the unit that receives updateMeshVolume. Their homes, `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowSilhouette.cpp` and `.../W3DVolumetricShadowConstructVolume.cpp`, define them as ordinary functions today, so both homes need select-any linkage as in commit 7ebbac515c (anchor lines where nothing in the home calls them) and a rebuild of each home. Those homes use private views (their own Vector3), so the copies cannot be pasted; they must be re-derived and byte-checked in the ZH-header context. `constructVolumeVB` has an EH frame.
2. The fold pin `??0AABoxClass@@QAE@ABV0@@Z` to 0x9AC04 with fold-proof (this unit emits that COMDAT byte-identical to retail, 43 B, no relocations).
3. The row-1 x87 pair. It is a tie-break that moves with updateMeshVolume's own IL: the stand-ins' content and other functions in the unit do not affect it, so replacing the stand-ins should not change it, and the fix has to come from this body's source. The six-difference family above is the nearest lead (it trades row 1 for Transform_Vector row 2).

The six-difference family replaces the first two row tests of the bank with these spellings (row 2 stays `Vector3::Dot_Product`):

```cpp
Real cosAngle = fabs ((prevXForm->operator [](0).X*objectToWorld.operator [](0).X + prevXForm->operator [](0).Y*objectToWorld.operator [](0).Y + prevXForm->operator [](0).Z*objectToWorld.operator [](0).Z));
cosAngle = fabs (((prevXForm->operator [](1).Y*objectToWorld.operator [](1).Y + prevXForm->operator [](1).Z*objectToWorld.operator [](1).Z) + prevXForm->operator [](1).X*objectToWorld.operator [](1).X));
```

`repair_queue.py dest 0x000F2FFA` names `Code/GameEngineDevice/Source/W3DDevice/GameClient/Shadow/W3DVolumetricShadowRenderDynamicMeshVolume.cpp` by neighbour heuristic (tu_map proposes the main W3DVolumetricShadow.cpp). Since the body needs its own flags and include set, a new standalone unit next to them is the likely home.

## Identity and boundary

Target facts: retail decodes 0xF2FFA..0xF3D23 as one body ending `ret 0x14` at 0xF3D20, followed by the prologue of updateVolumes (0xF3D23), which calls 0xF2FFA at 0xF3E73. ECX is `this` with five stack arguments. The calls to buildSilhouette, allocateShadowVolume, constructVolume and constructVolumeVB resolve to their matched rows. The C++ name and statement outline come from the BFME 1 and ZH donor `updateMeshVolume`; the WB twin evidence of the earlier pass (wb 0x806A80) is carried, not re-run.

## Reproduction

Scratch harnesses were in the seat's untracked `build/f2w5/` (`fd.py` prints non-relocation operand differences, `rb.py` counts differing bytes outside relocation fields, `gen.py` produced the factorial). Measure a candidate with `python tools/align_diff.py <file> ?updateMeshVolume@W3DVolumetricShadow@@IAEXHHPBVMatrix3D@@ABVAABoxClass@@M@Z 0x000F2FFA 3369` after deleting its object under `build/match/`.
