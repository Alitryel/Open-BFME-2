# 0x00126433 SimpleStreak render loop: handoff

Target: `?rva00126433@Rva00126314@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAMABVSphereClass@@@Z`
(11984 B; WB twin `SimpleStreakRendererClass::RenderStreak` at va 0xa1e840).
Bank: `reverse/attempts/0x00126433.cpp`. Scores below are `score.py` fitness
(0.5 mnemonic + 0.3 full + 0.2 bytes). "norm" counts instructions that match
once `[ebp-X]` offsets are masked, out of 2637.

## Current best (claudeb4, 2026-10-20): 0.9113, norm 2353/2637, 12009 B

0.9113 = the 0.9069 body plus item 9; 0.9069 = the 0.8371 body plus item 8; 0.8371 = the 0.8307 body plus item 7;
0.8307 = the 0.8285 body plus item 6.

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
6. WB twin shape of the shadow pass (WB asserts `!(passesToRender != 1)`,
   line 788): two separate continues,
   `if(!sp->Begin(&passes,0xffff)) continue; if(passes!=1) continue;
   sp->BeginPass(0);` instead of one `||` condition.
7. `Clamp_Color` uses `<=0`, as in BFME2's matched
   `DX8WrapperConvertColorClamp.cpp`. The exact matched form
   `c[i] = c[i] <= 0.0f ? 0.0f : (c[i] > 1.0f ? 1.0f : c[i]);` makes region 0x28
   match exactly (0.8279, `build/s126/g5/c1.cpp`), but it flips regions 5 and
   0x1c into a worse register mode. The banked body splits each lane:
   `{float f=(c[i]<=0)?0:c[i]; c[i]=(f>1)?1:f;}` (0.8371, region 0x28 still has
   8 diffs, but 1b-1d stay in the good mode). Find a form that keeps both.
8. **The shadow holder is an inline smart pointer** (`build/s126/g9/h5.cpp`).
   WB's holder comes from BFME2's `WWLib/refcount.h`: member `m_obj`,
   `operator->` asserts `m_obj != NULL` at refcount.h:308 (wb:0x74a690),
   operator= (wb:0x74a5a0, retail 0x72A94) and the dtor (wb:0x74a4f0, retail
   0x7B724) inc/dec `m_numRefs` at +4 and call vtable slot 0. Declaring
   operator= and the dtor **inline** with those bodies changes everything: the
   exhausted inline budget still leaves them out of line (retail's calls), but
   MSVC no longer treats the holder as escaped. Result: this=ebx with the -0x180
   spill as in retail, the holder at retail's -0x14, the referent cached in esi
   across Begin/BeginPass and EndPass/End, frame +0x10 instead of +0x14.
   Probe proof: `build/s126/pc/b1.cpp` (inline op= and dtor) caches; every
   out-of-line declaration reloads.
   - h5 calls `shadow.m_obj->Begin(...)`. Calling `shadow->` with an inline
     `operator->` (h1, the WB shape) gives 0.8984: it flips c,d,1a-1f into the
     bad mode. `T*p=m_obj;return p;` as the operator-> body (o8, 0.9045)
     makes regions 5, 6 and 24 match and 7 almost match, but keeps c,d,1a-1f bad.
     That mode is a tie-break between equal-weight mulss operands (region d
     swaps `[esi]` and `[esi-0x14]`). It follows a temp or symbol count, so look
     for a second change that flips it back on top of o8.

9. **WB holder API, mirrored** (`build/s126/gen_g10.py`, best `g10/v11100l0.cpp`).
   WB names the two globals `s_AlphaShadowFXShader` (0xDEE870) and
   `s_AdditiveShadowFXShader` (0xDEE86C) and calls `IsBound()`, the static
   `WW3D::Is_Currently_Rendering_Shadow_Map()` and the member
   `Is_Sorting_Disabled()`; the holder ctor takes `(T *obj)`. Factorial over
   seven choices (192 variants, `g10/scores.txt`):
   - `bool sorting = (!Is_Sorting_Disabled()) && ...` (getter instead of the
     field) and operator-> as `{T *p = m_obj; return p;}` with `shadow->` calls
     give 0.9113. `return m_obj;` gives 0.9012; `.m_obj->` calls give 0.8746.
   - The getter/IsBound start (A), `shadow(0)` (C) and the getters in the
     shadow and end blocks (D, E) are neutral; D+E together cost 0.0025.
   - `shadow = additive ? s_Additive... : s_Alpha...;` (holder ternary, G)
     costs 0.0008 against the pointer-cast form.
   rs2 at the bank: 9:15 b:12 11:22 15:20 1d:8 1e:12 1f:14 24:15 25:16 28:8,
   total 202.
10. **Next leads (untried): WB end-block call shapes** (wb.txt 1690-2190,
   helpers read with `tools/wb_show.py wb:0xVA`). Our bank differs from WB here:
   - Texture test: WB calls `0x9a0990` on `this`, an inline bool getter
     returning `[this+0] != 0` (a `Has_Texture()`/`Peek_Texture() != NULL`
     shape). We write `if(Texture)`.
   - Filter writes: WB calls the out-of-line `TextureAsset::GetFilter`
     (`0x9d41a0`, texture.cpp:1515) twice, then the inline setters `0x9d4f40`
     (`[filter+0xc]=arg`) and `0x9d4f60` (`[filter+0x10]=arg`), i.e.
     `Get_Filter().Set_U_Addr_Mode(1)` / `Set_V_Addr_Mode(1)`. We store
     `->u=1` / `->v=1` directly.
   - The shadow texture temp ctor `0x9a00f0` calls a nested init `0x9a0110`
     (`[this]=0`): a two-level inline ctor, not a plain zero member.
   - FVF offsets: `0x9d9d30` takes an argument (`push 0`) for the first
     offset; check which getter it is before changing ours.
   - Color: `sub_a21170(Vector4)` with the Vector4 built by `0x71fd10` from
     `this+0xc..+0x18`, consistent with our
     `Convert_Color_Clamp(Vector4(Color..., Opacity))`.
   - Unidentified end calls: `0x9c1360` (405 B), `0x9a8a60`, `0x9a8aa0`
     (64 B each); also `0x9d9de0`, `0x9a4bf0`, `0x9a4c10`, `0x9a4c20`,
     `0x9dcb00`.
   Plan: a g11 factorial from `g10/v11100l0.cpp` over these shapes (getter,
   GetFilter plus setters, nested temp ctor, FVF getter forms), scored in the
   background, regions read with rs2; the aim is to flip 9/b/11/15/1d-1f/24/25.

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

## Register-mode flip (read before adding anything)

Adding almost any local or inline member flips regions 0xc, 0xd and 0x1a-0x1f
into a worse allocation (about c:3 d:13 1a:11 1b:15 1c:18 1d:23 1e:18 diffs;
region d shows swapped mulss operands `[esi-8]`/`[esi-0xc]`). The good mode is
c:0 d:0 1a:~1 1d:~8. Check every variant with `build/s126/rs2.py` before
trusting the total score. Triggers seen so far: an `operator->` member on the
shadow pointer holder, a local `SimpleShadowPass *sp=shadow.p`, a `bool ok`
temp around Begin.

## WB local evidence (wb.txt frame, unoptimised twin)

- `tex_v` is a direct array `float tex_v[129]` (local_2800, stores
  `fstp [ebp+edx*4-0x2800]`), not a pointer to storage. Trial (g6): region 0x15
  improves 20 -> 11, but 0x1b-0x1d flip to the bad mode (3/1/1 -> 13/12/8).
  Net 0.8339 with the split clamp and 0.8299 with the matched clamp. Keep it in
  mind for recombination.
- WB copies `texture_positions[point_cnt-1]` into its own local (local_480c,
  integer move) before `end = last - TextureLength` (local_60c8). A separate
  `float last` in our source costs about 0.03 (+22 B, x87 spill), so that local
  is probably a WB-only temp or an int-typed copy.
- WB slot sizes: segment array local_5a68 (0x82 x 0x24), intersection
  local_2598 (0x104 x 0x24), switch_edges (byte) local_25a1 sits before the
  segment array, u_values local_f8/f4, view2 local_cc (12-arg ctor), modelview
  local_25d4 (default ctor, then mul).

## Region modes (rs2 diffs per 0x100, g6)

| Variant | 5/6 | 15 | 1b/1c/1d | 1e | 28 | total |
|---|---|---|---|---|---|---|
| split clamp (bank) | 15/25 | 20 | 3/1/1 | 10 | 8 | 252 |
| split + tex_v array | 15/25 | 11 | 13/12/8 | 10 | 8 | 269 |
| matched clamp | 25/25 | 20 | 3/12/8 | 4 | 0 | 265 |
| matched + tex_v array | 25/25 | 11 | 13/7/4 | 4 | 0 | 255 |

## Shadow-pointer caching (region 0x27/0x2b)

Retail keeps `shader_setup.Referent` in esi across Begin/BeginPass and
EndPass/End; ours reloads `[ebp-0x14]` before each virtual call. WB shows
`RefCountPtr<FXShaderSetup> shader_setup(0)` at loop scope after `sorting`,
assigned with the out-of-line operator= 0x72A94 and destroyed with 0x7B724.
Probes in `build/s126/pb/` (loop vs function scope, no dtor, out-of-line copy
ctor, inline operator=, inline dtor, /Oa, /Ow, /Ox) all reload, so the cause is
still open.

## Disproven (do not repeat)

- `operator->` on the shadow holder; member operator= on it; a local
  `sp` alias in the Begin or End block; a `bool ok` temp for Begin
  (all flip the register mode, see above).

- ALLOW_TEMPORARIES `operator*` / `modelview=view2*transform`.
- ZH `operator*` by value.
- Non-forceinline submul/mul.
- view `float[16]` vs `char[64]`.
- MIN() for point_cnt.
- A separate `float last=texture_positions[point_cnt-1]` before `end` (-0.03).
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
- `rs2.py obj...` per-0x100 region diff counts with relocations, call targets
  and immediates masked (better than regsum); `rs2.py obj lo hi` prints the
  diff of one range. `sbs.py obj lo hi` side-by-side, `pdis.py f.cpp sym` probe
  disassembly. `g4/` holds the 0.8307 family (w_A is the bank).
