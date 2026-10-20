# SegLineRendererClass::Render (0x00191C10): landed; numbering and census link status

Render (16,018 B) landed byte-exact in its home TU, `Code/Libraries/Source/WWVegas/WW3D2/seglinerenderer.cpp`. Three rows landed with it:

- its EH handler, 0x00768996;
- two unwind funclets, `$L` at 0x00768980 and 0x0076898B. These replace the gen_uw scaffolds.

The BFME2 header views are in `reference/shims/bfme_seglinerender`. The earlier bank in this directory and its bank-only shim (`reference/shims/banked_segline_bfme2`) are superseded and removed.

## Source evidence
`python3 tools/wb_show.py 0x191C10` pairs Render with the WorldBuilder debug twin, 0xA454A0, built 2006-01-28.

- **What the twin confirms in the text:**
  - the callee census;
  - every named local's name and size (the /Od frame is name-hashed);
  - every `$T` slot, once WB's missing 12-byte EH record is allowed for;
  - statement and argument order in every block.
- **What it confirms in the DX8Wrapper helpers:** `Set_Transform`, `Get_Transform`, `Set_Shader`, `Set_Material`, `Convert_Color`, the accessors, and `getVertexBuffer`'s /Od frame.

## Numbering: what the source carries beyond the twin text
MSVC 7.1 breaks commutative-operand and register ties by internal numbering. Two inputs set it:

- the per-function symbol count, with a period of about 32;
- the IL order of live code.

The twin text compiles with every section before the triangle emitter exact. To match the emitter as well, the TU deviates from the twin in three numbering-only places, each as plain C++:

1. **Tri-prime bottom line.** It reads `bottom = intersection[1][BOTTOM_EDGE].Direction; Scale_Z_First(bottom, Vector3::Dot_Product(points[0], bottom));` instead of the twin's `Vector3 &bottom_dir = ...; bottom = bottom_dir * Dot(points[0], bottom_dir);`.
   - Dropping the reference and the `operator*` temporary puts the earlier sections in phase.
   - `Scale_Z_First` is a TU-local inline that multiplies Z, then Y, then X. That is the order the twin's `operator*` temporary builds its arguments; `Vector3::operator*=` would build X first.
2. **`getVertexBuffer`'s three named pointers** (`oldBuffer`, `newBuffer`, `buffer`).
   - They compile away in its own body: 0x001912B0's 60 bytes are unchanged.
   - Render inlines `getVertexBuffer`, so the three locals count toward the symbols that set Render's tie-breaks.
   - Any three counted inline locals behave the same, for example locals in `Set_Shader` or `Set_Material`. The twin's /Od `getVertexBuffer` frame has only compiler temporaries, so these locals are a numbering reconstruction, not recovered source.
3. **The tri-prime dot product reads `bottom`**, the copy just made, instead of `Direction`. The value is identical.

Earlier numbering findings and the ruled-out flags, defines and header variants are in git history: this file's 2026-10-20 bank version and `build/s191/NOTES.md` from the matching sessions.

## Census false reject
The re_log entry is `??_H@YGXPAXIHP6EPAX0@Z@Z 0x00001423 blocked`. Before Render, the unit linked 2,490 B; link_check predicts it no longer links.

Seven of the COMDAT copies the census charges cannot change without changing Render:

- **`??_H` (vector constructor iterator):**
  - Retail Render calls it out of line twice, for the Matrix4x4 rows of `view` and of the identity (callback 0x0047A6A9), and inlines it elsewhere.
  - Only the unit's own /O2 iterator reproduces that. An anchor building `??_H` under `optimize("gsy")` makes Render inline both calls, and with `auto_inline(off)` Render calls it 14 times.
- **`??0Matrix3D@@QAE@XZ`, `??0Matrix3D@@QAE@MMMMMMMMMMMM@Z`, `??0Matrix4@@QAE@_N@Z`, `??0Matrix4@@QAE@ABVVector4@@000@Z`, `?Transpose@Matrix4@@QBE?AV1@XZ`:** retail's owners keep `??_H` out of line, while this unit inlines it. dllimport views of them add `??_H` calls to Render.
- **`?Set_Material@DX8Wrapper@@SAXPBVVertexMaterialClass@@@Z`:** a dllimport view moves Release_Ref out of line.

link_census.keep_rule charges a copy proven wrong whatever its link position. link.exe, however, keeps the first copy in link order, and the `??_H` owner at 0x00001423 precedes this unit. EA's own object therefore carried the same discarded copies.
