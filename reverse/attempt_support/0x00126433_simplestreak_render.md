# 0x00126433 SimpleStreak render loop: handoff

Target: `?rva00126433@Rva00126314@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAMABVSphereClass@@@Z`
(11984 B; WB twin `SimpleStreakRendererClass::RenderStreak` at va 0xa1e840).
Bank: `reverse/attempts/0x00126433.cpp`. Scores below are `score.py` fitness
(0.5 mnemonic + 0.3 full + 0.2 bytes). "norm" counts instructions that match
once `[ebp-X]` offsets are masked, out of 2637.

## Current best (claudeb4, 2026-10-20): 0.8285, norm 2305/2637, 12022 B

The previous bank scored 0.7808 (norm 1974). The best body is built from that
bank as follows:

1. B1 `shader.h` (`reference/open-bfme-1/game/.../WW3D2/shader.h`, cull at
   bit 20) is included at the top of the TU, wrapped in
   `#define inline __forceinline` / `#undef inline`. Its include guard defeats
   any later include, so it has to come first.
2. `DX8Wrapper::Set_Vertex_Shader` and `Set_Pixel_Shader` are `__forceinline`.
   B1's `dx8wrapper.h` declares them WWINLINE.
3. **BFME2's own matched inline shapes**, which gave the big step (+0.04):
   - `Set_Transform(Matrix4)`: the projection case does
     `ProjectionMatrix=m.Transpose(); DeviceProjectionMatrix=ProjectionMatrix;`
     with static members and no stack temporary. This is the
     `reference/shims/bfmecamera/dx8wrapper.h` form, which compiles to retail's
     out-of-line 0xA68A7 (1349 B, matched).
   - `Get_Transform`: the projection case reads
     `m=DeviceProjectionMatrix.Transpose()`, the default case does
     `m.Make_Identity()`, and there is no `D3DMATRIX` or device call. This is the
     `fxshadernamespacesas.cpp` form, matched at 0x768FE (790 B).
4. `if(Texture) Set_Texturing(ENABLE); else Set_Texturing(DISABLE);`, as in the
   WB twin. Retail has the two-branch `or esi,0x10000` / `and esi,0xfffeffff`.
   The ternary form gave setne/shl instead.
5. A real `Matrix4 view;`. The default ctor is never inlined under /O1, which
   produces retail's out-of-line call at 0x7671F. To land, rename that row to
   `??0Matrix4@@QAE@XZ`; until then the build reports it UNRES. Without the
   rename (the `Rva0007671F` storage hack) the score is 0.8277.

## Inline budget (why the setters stay out of line)

- Under /O1, plain `inline` expansion has a per-function size budget. It counts
  IL from plain statements and from every forceinline expansion, including the
  dead switch cases of the WWINLINE `Set_Transform`/`Get_Transform`, wherever
  they sit in the function.
- Our TU exhausts that budget. `ShaderClass::Set_Cull_Mode`,
  `Set_Primary_Gradient` and `Set_Texturing`, and the VS/PS setters, then stay
  out of line, while retail inlines all of them.
- None of the 30 ShaderClass COMDATs and none of Set_Transform 0xA68A7,
  Transpose 0x6A3D1 and Get_Transform 0x768FE has any E8/E9 caller in retail.
  An out-of-line copy therefore does not prove that a call site failed.
  StreakRendererSetTextureBFME1.cpp also emits out-of-line copies of every
  forceinline function it uses.
- Forcing the setters (item 1 above) is the working answer so far. Retail's real
  header may declare them WWINLINE.

## Remaining residue (v_TR)

- **Frame**: ours is 0x624c, retail 0x6238 (+0x14). The bfmecamera Set_Transform
  alone adds 0x10 (dead-case temporaries still take frame space). Slot map
  (`build/s126/omap.py`):

  | Retail range | Ours | Extra dwords in ours |
  |---|---|---|
  | 0x90..0x1d8 | +4 | 1, in the scalar area below 0x90 |
  | 0x1dc..0x2a4 | permuted (scalar block) | 1 |
  | 0x2bc..0x35c | +8 | — |
  | xformed_pts (retail -0x968) | +0x14 | 3, between 0x35c and 0x954 |

- **Registers**: retail has this=ebx (spilled at -0x180) and zero=esi or edi in
  places; ours has this=esi.
- **Worst regions** (per 0x100, normalized diffs): 0x2 (31), 0x27 (35),
  0x28 (20), 0x1e (16), 0x24-0x26 (17 each), 0x15 (20).
- **Region trade-off**: `v_Tnp` (setters and VS/PS not forced) is better in
  0x5-0xb, but it has out-of-line calls, so it cannot match.

## Disproven (do not repeat)

- ALLOW_TEMPORARIES `operator*` / `modelview=view2*transform`.
- ZH `operator*` by value.
- Non-forceinline submul/mul.
- view `float[16]` vs `char[64]`.
- MIN() for point_cnt.
- The recipe flags.
- Declaration-order-only scalar reorders.
- The k-scan of inert locals on its own.
- VS/PS forceinline without the B1 shader.h.
- Flags: /Ob1, /Ob2, /Oi, /Os change nothing; /O2, /Ot, /Ox give ~0.52.
- Single-statement setter bodies.
- Inert int locals: no effect on the inline budget.
- Unforced setters with the BFME2 Set/Get_Transform shapes: still out of line.

## Scratch layout

`build/s126/`:

- `score.py`, `regsum.py`, `odisr.py`, `omap.py` (ebp slot map), `frm.py`.
- `gen_bf2.py` (Set/Get_Transform shapes) and `gen_f3.py` (T/R/n/p factorial).
