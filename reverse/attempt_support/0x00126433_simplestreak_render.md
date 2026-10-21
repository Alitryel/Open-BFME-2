# 0x00126433 SimpleStreak render loop: handoff

Target: `?rva00126433@Rva00126314@@QAEXAAVRenderInfoClass@@ABVMatrix3D@@IPAVVector3@@PAMABVSphereClass@@@Z`
(11984 B; WB twin `SimpleStreakRendererClass::RenderStreak` at va 0xa1e840).
Bank: `reverse/attempts/0x00126433.cpp`. Scores below are `score.py` fitness
(0.5 mnemonic + 0.3 full + 0.2 bytes). "norm" counts instructions that match
once `[ebp-X]` offsets are masked, out of 2637.

Third session: read "Symbol numbering decides the sum order" first. The
remaining Length2 trees follow c2's symbol numbering, and a padded,
unfaithful body reaches 0.9729 (`0x00126433_v048_padded.cpp.txt`). The bank
below is still the best faithful body.

## Current best (fifth session, 2026-10-20/21): nd 379, 12006 B, permute fit 0.9107

The bank is now the fifth-session body `faithful_bank_GHFABC` (claude-opus-5-5
subagent agAE, LF line endings).
- On the same scorer (`tools/permute.py` fitness, nd from `build/xs/score.py`)
  the previous bank measures fit 0.8959, nd 478, 16/21 Length2 trees. Its
  recorded 0.9134 came from an earlier scorer variant.
- The new bank has 20/21 trees (only 0x1d20 is wrong) and all 8 struct-piece
  sites right. The tail code is unchanged; only its inline wrappers differ,
  each as WB spells it:
  - **G:** Set_Material and Set_Shader without `SNAPSHOT_SAY`. WB 0x9a3dd0 and
    0x44a6d0 never call `Is_Snapshot_Activated`; Set_Shader keeps
    `StringClass str`. This removes one whole 32-symbol pool from the window in
    every base (nd 478 to 415).
  - **H:** the holder's `operator->` is `return m_obj;` (WB refcount.h:308).
    −4 named.
  - **F:** the filter writes are `Set_U_Addr_Mode(1)` / `Set_V_Addr_Mode(1)`.
    +2 named, +4 GlobalOptimize hash vars (E).
  - **A:** sorting goes through a 5-argument inline forwarder (retail COMDAT
    0x12630b).
  - **B:** both tail shadow tests use `Is_Currently_Rendering_Shadow_Map()`.
  - **C:** the Texture holder has `bool Is_Valid()` (WB 0x9a0990).
  - A, B and C are neutral.
- Not used: **S1**, a named pointer for the chosen shadow setup (WB frame slot
  `local_6358`). It gives nd 376 alone, but it is a front-end symbol (see the
  pad-substitution note below).

**Register mode.** The flip of regions c, d and 0x1a–0x25 is the FactCanonSort
key of memory reads through a hash var, `0x10008 + ((H&3)<<14)`. All 91
reordered operands are of that kind. Any change's net E shift must therefore
be ≡ 0 (mod 4). Measured shifts:

| Change | E shift |
|---|---|
| V: setters without the named `d`, D3D9 slots 92/107 | −5 |
| E: WB's `Convert_Color_Clamp` | −5 |
| K2 | −5 |
| D: inline `_Get_D3D_Device8()` | −2 (frame +4, unexplained) |
| F | +4 |

Front-end pools move E only by multiples of 32.

**Convert_Color_Clamp (0x12617C).** WB's spelling and K2 also compile to
retail's 399 B exactly:

```cpp
Clamp_Color(color);
return Convert_Color((Vector3&)color, color[3]);
```

The landed spelling is therefore not the only proven one. E costs +33 window
symbols in this body.

**The v048 tail pad was a stand-in for G.** Its `padf` (m=48) is unnecessary
once G is in: v048's front pads plus G give nd 84.

**What is still missing:**
1. +30 IL-time A symbols (named locals, class temps, pieces) between function
   entry and `Vector3 top_normal` in the segment loop.
   - A post-IL 30-local pad gives nd 93 anywhere in that window except between
     `view2` and `modelview` and right after `offset.Normalize()`.
   - It fails from `bottom_normal` onwards.
   - IL-time pads give nd 100 before the intersection loop and 93 after it.
2. 1–7 fewer tail window symbols with zero E shift. The last `pl` piece site
   needs its Y piece ≤ 6824 at k30 numbering; GH gives 6825.

Diagnostic: the k30 front pad with G and H only (without F, A, B and C) gives
nd 86, 18/21 trees, 11995 B. `0x00126433_k30_GH_pads.patch` applies to the
bank and produces that body.

**Helper forms measured on this bank** (fresh A / E / nd):

| Form | A / E / nd |
|---|---|
| WB flag order in Set_Transform | 0 / 0 / 379 |
| Make_Identity with float or int constants | 0 / 0 / 379 |
| Vector4 init-list ctor | 0 / 0 / 379 |
| Vector4 `op[]` via cast | 0 / 0 / 379 |
| Matrix4(bool) without braces | 0 / 0 / 379 |
| Transpose as 16 floats | −474 / +82 / 1775 |
| Transpose with `.X` fields | +6 / +10 / 1312 |
| Transpose via a named local | +124 / +682 / 1303 |
| Make_Identity as `Row=Vector4()` | +125 / +22 / 901 |
| Make_Identity with direct field stores | −9 / −229 / 690 |
| Init via Set | +240 / 0 / 1333 |

WB's /Od Get_Transform (3 Transposes, 2 identity tests, default Make_Identity)
and Set_Transform (4 Transposes; PROJECTION with `op=`, `op=` and ZFar/ZNear;
default `m2`) have the same arms as ours, so no helper arm is missing.

**Next:**
- Census WB's /Od frame for the window, mapping every slot (named locals and
  by-value class temps) to ours. Unmapped slots are the real +30 candidates.
- Validate each candidate by pad substitution: candidate (k fresh A) plus the
  pad shrunk to 30−k must keep nd ≤ 93 with E ≡ 0 (mod 4). Start with S1 plus
  pad 29.

Fifth-session scratch tools (untracked) are in `build/agAE/`: `alloctrace2.py`
and `zones.py` (symbol accounting), `ctrace.py` and `kdiff.py` (FactCanonSort
operand order), and `objfit.py` and `fit.py` (fitness, nd, Length2 trees).

## Fifth session, continued (2026-10-21): what is settled and what is ruled out

Scratch tools are in `build/agAE/`, `build/agAG/` and `build/agAH/`
(untracked).

**Further faithful edits.**

| Edit | Effect |
|---|---|
| C1: `shadow = additive ? s_AdditiveShadowFXShader : s_AlphaShadowFXShader;` (the class-lvalue ternary's reference $T is WB `local_6358`) | +1 IL-time A, nd 376 |
| `point_cnt = MIN(point_cnt, chunk_size);` (WB ternary temp `local_6774`) | +1 C only, byte-identical |
| Set_Transform in WB's flag order | byte-identical |

The faithful best is `build/agAG/final/f_c1minflag.cpp` (the bank plus these
three): 12006 B, nd 376, fit 0.9108. The bank file is not updated yet.

**The tail is settled.** The faithful, retail-confirmed tail set is
{G, H, F, A, B, C, I, E, D}:
- **I:** `int Is_Sorting_Disabled() const`, as WB 0xa1ad40 and retail COMDAT
  0x12606c (`movzx eax`). E −1.
- **E:** WB's `Convert_Color_Clamp`, which clamps the by-value argument in
  place. Retail's simplestreakrender object emits the Clamp_Color COMDAT
  0x126082 between 0x12606c and RenderStreak, and only the E form references
  it. E −5; +36 C, one pool.
- **D:** inline `_Get_D3D_Device8()`. E −2.
- Net E −8 ≡ 0 (mod 4).

Every WB tail call is accounted for. SegLine's ZH Convert_Color_Clamp
(`const Vector4&` plus a copy) is refuted at 409/399 B. Retail has no
Vertex_Shader/Pixel_Shader stores, and Set_Texture stays out of line (retail
calls 0x11F4B0).

**The front target is exactly 29.** A post-IL pad scan over m = 0..70 on the
full set + C1 + MIN finds only m = 29 good: nd 100, 11988 B, frame 0x6238,
trees 17/21. Diagnostic files: `build/agAE/v/fs/fs_m29.cpp` and
`build/agAG/final/diag_f_pad29.cpp` (nd 93, without I/E/D). With E, the pl
sites additionally need the window (last pl X piece to the Y pieces) to lose
one pool plus 1..30 symbols:
- #537 (1c31) needs its Y piece in [6771, 6824];
- #960 (1f0c) needs it ≤ 6824 (it is 6833/6857).

A-pads move X and Y together.

**The residue of the padded bodies is all front numbering.**
- The +0xc spill-slot shift in regions b–f is caused by the wrong 1f0c tree.
  The extra reload of pl.X raises pl's weight to w19 and ties it with
  top_normal. In v048, where 1f0c is right, the layout is retail's.
- +0xf78 is the sum order of `Dot_Product(first_plane[TOP_EDGE],
  first_point)`. Its MUL keys run through IL-time named locals: first_plane
  F=409, first_point F=408, then S376/S379 and S452/S456.
- So the missing symbols must sit at specific IL positions, not just number
  29.

**Ruled out this session (do not repeat):**
- WB caller frame: all 89 named locals and all 36 $T map one to one, in the
  same first-use order as our IL numbering. /Od never shares stack slots
  between temporaries (verified), so the $T census is complete.
- Declaration order and scope.
- B globals: unchanged at 176 for every tail change except G (−1). Float
  literals are not B.
- Unreferenced locals: never numbered (29 or 30 unused ints at entry are
  byte-identical).
- By-value struct arguments: WB's only one is Convert_Color_Clamp's Vector4,
  which ours matches.
- Every Get/Set_Transform/Matrix4/Vector4/Transpose/Make_Identity header form.
  WB's /Od arms and order are WORLD, VIEW, PROJ, default, the same as ours.
- The SegLine header set: a port onto vector3_full_link + SSE vector4 +
  banked_segline matrix4 + inline `_Get_D3D_Device8` is byte-identical with
  A/C/E +0.
- Flags: /O1 = /O2 /Os, /Oi and /Oy- are inert. /O2, /Ot, /Ox and /G6 are far
  worse.

**c2 3077 inline budget (decoded).** In InlCallGraphDecision (0x8d1aa), for a
plain-inline callee of size S above InlSizeLimit (9 at /O1):
- x = callee tuples (node[0x1c], 11 for `??_H`) + G_b58 (c2 0x10882b58).
- If x > 9000, a penalty floor(S/2)·x/9000 is added to cost = S − benefits,
  and the call inlines iff cost < 9.
- For `??_H` (S = 34) that means it inlines iff G_b58 ≤ 8989.
- G_b58 starts at T0, the whole function's flagged-tuple count (set in
  Inline@4). Each inlined body's tuples are then added once per nesting level.

`??_H` sites in f_c1minflag, by G_b58:
- Get_Transform: 1846, 2486, 3054;
- identity: 4417;
- WORLD ×4: 4671..6490;
- VIEW-WORLD arm: 7945;
- VIEW-VIEW arm (live): 8516, margin +473, inlined;
- VIEW-PROJ: 9087 (−98) and VIEW-default: 9739 (−750), dead and refused;
- arrays 11040+ and the tail, refused.

The exact SegLine Render (IL about 35% larger) refuses one site earlier. That
is its −3 fresh A in Set_Transform(VIEW), not a free-list effect. For this
function no budget move works:
- one more refusal hits the live VIEW arm, which is byte-visible;
- dead acceptances add +3 A, +1 C and +7 E each, which breaks parity and moves
  the window the wrong way;
- WB's arm order rules out a reordering.

**The insertion profile, as far as the model search got** (`build/agAE/xsim.py`,
`km2d.py`, `km3d.py`, and compile checks in `build/agAE/v/k3/` and
`build/agAE/v/fp/`):
- **+0xf78.** At least 3 IL-time A must be created before
  `Vector3 &first_point = points[0];`. Int pads anywhere in that range give
  retail's exact sequence for k = 3..12. k = 1–2 fail, and k = 13 or 29 change
  the registers through a pool crossing.
  - The exact SegLine compile has the same CSE address temps and canon
    structure at this site and still produces retail's (Z+Y)+X. The deciding
    bits are the low key bits of first_plane/first_point (F mod 8).
- **The 8 struct-piece sites.** No combination of k IL-time A (0–12) and m
  post-IL A (0–64) fixes them, because pure A insertions move X and Y
  together. With E they need the tail window to carry about one C pool fewer
  than our full set (29–48 fewer C), or 4–6 fewer A crossing an A-pool
  boundary.
  - Compile check: the set without E (that is, dC = 36) plus 3–7 IL-time int
    pads gets all 8 piece sites and +0xf78 right (19/21 trees). The frame is
    still 0x624c, and E parity is off by one.
- **Still open:** the 0x6238 frame (only the post-IL pad29 reaches it) and E
  parity.

## Confirmed target: byte-exact with three numbering changes (2026-10-21)

Two independent methods give the same answer:
- agAL's key-substitution oracle, `build/agAL/ksub.py`. It hooks c2's leaf-hash
  X loads and maps X to X′ from the pool model.
- agAK's physical allocator patch, `build/agAK/symshift.py` with `batch.py`.
  Spare symbols are injected onto the free lists in the running c2; no pool is
  ever shrunk.

Base: `build/agAL/base.cpp`, which is faithful_fullset plus
`Get_Location_Offset(0)`, without /Oy-. It scores 12017 B, nd 435. With these
three changes it compiles to **11984 B, nd 0, 0 non-relocation byte diffs**:

1. **A −3:** three fewer fresh A. Exact anywhere from IL time (k1017) through
   k5074. It fails at k6005 (nd 94).
2. **A −1:** one fewer fresh A, exact anywhere in about [7700, 15000].

   | k | 5000 | 7501 | 7717 | 9000 | 12000 | 15032 | 20054 |
   |---|---|---|---|---|---|---|---|
   | nd | 111 | 2 | 0 | 0 | 0 | 0 | 56 |

3. **E −12 or −16:** fewer GlobalOptimize hash vars, at any position (k0 and
   k30000 are both exact).

   | E change | −4 | −8 | −11 | −13 | −20 |
   |---|---|---|---|---|---|
   | nd | 10 | 10 | 210 | 124 | 71 |

The counts are exact:

| Variant | nd |
|---|---|
| A −2 instead of −3 | 380 |
| A −4 instead of −3 | 115 |
| without the A −1 | 66 |
| without the E change | 23 |

No IL-time insertion is needed. It is also exact on faithful_fullset at the
fs_m00 positions. After the byte gate resolves REL32s, the only bytes left
differing are 6 calls to names missing from the symbol map: `??0Matrix4@@QAE@XZ`,
the ShadowPtr destructor and operator=, and `?Rva000032B8@@YAMM@Z`.

So the source is complete apart from three numbering effects. The open task is
to find the faithful source forms behind them:
- **The −3 A.** IL-time is allowed, so /Od-invisible IL constructs qualify. One
  example is `u_values` written as element stores, the ZH donor form, which
  gives −1 IL A piece and +1 C.
- **The −1 A.**
- **The −12/−16 E.** Candidates are FP parentheses, which are /Od-invisible and
  add one hash var each, and variables shared across branches (lexical CSE).

0x743700 has the same kind of target (2 fewer fresh A in its identical
Get_Transform/identity/Set_Transform prefix), while SegLine does not. Look for a
cause the two BFME-added renderers share.

**Later 2026-10-21 results.** Scratch is in `build/agAH/`, `build/agAJ/` and
`build/bank126433/`, all untracked.

**WB-attested fix for both renderers (inert here).** WB calls
`fvfinfo.Get_Location_Offset(0)` at a2099b. So BFME2's FVFInfoClass has
`unsigned location_offset[5]` at +0x10, and the getter takes an index. On this
function it adds post-IL C +1 and leaves nd unchanged.

**Retail built this TU without /Oy-.** Retail's orphan COMDATs Get_Tex_Offset
(0x126077, texcoord_offset at +0x24) and Clamp_Color (0x126082) are byte-exact
only without /Oy-. RenderStreak itself is identical either way.

**The compiler version is not the lever.**
- The game.dat Rich header lists 3 C++ objects built with cl 13.10.4035.
- Compiling with the repo's `// compiler: vc71-ddk-4035` profile is identical to
  3077 for both renderers. SP1 is far worse.

**Full /Od comparison against WB 0xa1e840** (`build/agAH/t/odfront.py`):
- From entry to first_point the code is instruction-identical: 12 `op[]` calls
  for view2, Set on intersection[0], and every this-piece trigger.
- Over the full body, the only differences are WB's asserts, EH code,
  relocations and the Get_Location_Offset item.
- Every tail helper body equals its WB /Od twin (`build/agAJ` audit). The
  window's inline content is therefore WB-pinned.

**IL-time-invisible constructs** (about 150 micro-functions,
`build/agAH/micro/`):
- Only aggregate initialisers create IL-time A with no /Od trace: float
  arrays +(n−1).
- Direct field writes, this-pieces, constant-index local-array reads and
  by-value class arguments all leave /Od code differences.
- `(void)local;` reorders IL numbering (by first reference) with no /Od trace.
  It cannot add symbols, though, and only `intersectionIndex` is declared
  before first_point but first used after it. That is at most +1.

**c2 A allocation.**
- There is one allocator (0x73f83), reached only through SymAlloc (0x5a0c5).
- A symbols are kinds 4, 5 and 13.
- In this function they come from three sites:
  - the IL symbol reader 0x6f087, which also reads inlinee IL;
  - symbol duplication / piece split 0x69fdf;
  - SymInit.
- No decision is keyed on numbering. The only count-sensitive input is the
  inline budget.

**Debug-assert residue is refuted.** `(void)(expr)` asserts add C only.
WWASSERT(Is_Valid()) re-added as IL changes the code or the budget.

**Pool-model constraints for the 8 piece sites** (`build/agAJ/kmx.py`, checked
by compiles). With k = 3..9 IL-time A before first_point, any one of these
works:
- window −29..−60 C, or window −32..−62 A;
- front −7..−9 A anywhere up to alloc event 5500;
- −32..−48 B anywhere up to event 10000.

k ≥ 10 has no fix. About 99 B pieces in the window are split-pass pieces of
render_state, DeviceProjectionMatrix and ProjectionMatrix.

**Next:**
- Audit the 176 B symbols and the front A symbols for reconstruction
  artefacts.
- Validate the model end to end by patching c2's allocator during a compile
  (diagnostic) and checking that it gives byte-exact output.
- Find the IL-time-invisible constructs that supply the ≥3 symbols before
  first_point.

## Second-session best (claudeb4, 2026-10-20): 0.9134, norm 2363/2637, 12017 B

The bank is `build/s126/r6/v000010000.cpp`: the 0.9113 body plus item 11. Chain:
0.9113 = the 0.9069 body plus item 9; 0.9069 = the 0.8371 body plus item 8;
0.8371 = the 0.8307 body plus item 7; 0.8307 = the 0.8285 body plus item 6.
**Read "Symbol-count lever" and "Float-sum residue" below first**: a
non-faithful +30-local body reaches 0.9651, and the remaining residue is a
reassociation order in the inline vector math.

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
10. **WB end-block call shapes (tested in item 11)** (wb.txt 1690-2190,
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

11. **Second 2026-10-20 session (r1-r6)**, all kept in the 0.9134 bank:
   - `Convert_Color_Clamp(Vector4 color)` by value with BFME2's matched body
     (`Vector4 *clamped_color = &color; if(!CPUDetectClass::Has_CMOV_Instruction())
     {ternary clamp per lane} else { __asm ... }`), not the B1 Clamp_Color call.
   - `Rva000032B8` (Inv_Sqrt) declared `float (float)`: retail calls it with
     the float on the stack.
   - `float tex_v[129];` direct array (WB local_2800) and
     `float last=texture_positions[point_cnt-1]; float end=last-TextureLength;`
     (WB local_480c, local_60c8): with the by-value clamp neither costs anything.
   - The texture temp is a derived RefPtr temp passed directly:
     `struct SimpleTextureRefPtr : BFME2TextureRef {...}; struct SimpleTextureTemp
     : SimpleTextureRefPtr {SimpleTextureTemp(){}};`
     `BFME2Set_Texture(0,SimpleTextureTemp());` (r6 factor T, +0.002).
   - Item 10 leads, tested in the r6 factorial (`build/s126/gen_r6.py`, 512 variants):
     `MIN()` for point_cnt (M), the static `Is_Currently_Rendering_Shadow_Map()`
     getters (D, E), the holder ternary (G), a `Texture.Is_Valid()` holder (H), an
     int-returning `Is_Sorting_Disabled` (S) and `Get_Location_Offset(0)` (X) are
     all neutral or worse. `getFilter()->Set_U_Addr_Mode(1)/Set_V_Addr_Mode(1)` (F, the WB
     setters 0x9d4f40/0x9d4f60) costs 0.0026 alone (`r10/f_k00.cpp`, 0.9108),
     but it is the base of the 0.9651 body below. Retail calls `getFilter()`
     with no argument, and both calls share edi=1. Retail has no
     IndexBufferExceptionFunc try/catch, and 0x4e6900 is not called.

## Symbol-count lever (r10-r17; not a faithful fix yet)

`build/s126/r10/f_k30.cpp` = `r10/f_k00.cpp` plus 30 `int unusedN=0;` locals
before the intersection loop's `float mid_tex_v` (patch:
`reverse/attempt_support/0x00126433_k30_symbolcount.patch`; it applies to the
bank with its two leading `//` header lines removed. The bank is whitespace-stripped
to fit the 64 KiB stash limit, at the same score).
It scores **0.9651** (norm 2469/2637, 11988 B). Earlier dummy bodies:
`k3/p2_31.cpp` 0.9658 and `r7/k30.cpp` 0.9647. `r9/rpfla.cpp` reaches 0.9589
without parallel_factor and last, so it is unfaithful. What we measured:

- Only *referenced* locals count (initialised or assigned). Type (int, float,
  char) and block scope do not matter. Re-assigning one symbol counts once.
  Unused uninitialised locals, typedefs, enums, struct members, float constants,
  discarded inline calls (`id(j);`) and void inlines with params count nothing.
- k=1 changes nothing. k=30 is best (A4 B41 total 99 in `modes.py`). k=62 gives
  0.8844. Large k repeats with period 32 (94 = 126, 96 = 128, 14 ≈ 46 ≈ 78), but
  the count is not simply mod 32.
- Region 0x15 depends on how many symbols sit between the function start and
  the intersection loop, mod 8: a ≡ 4 or 6 (mod 8) is bad (`r18/regs.txt`).
- So the real source has about 30 more referenced locals or temps than ours.
  Candidates: locals in BFME2's inline helpers (vector3.h Normalize declares
  `len2`/`oolen`; asserts; WB shows 34 twelve-byte `$T` temps, the same as ours),
  or extra named locals in the render loop. Unresolved; find the faithful
  equivalent before landing anything with this lever.

## Float-sum residue (independent of the symbol count)

`r18` moved 0-30 dummies across four positions (function start, before the
segment loop, the segment loop body, the intersection loop). This residue
never moves: **9:15 a:6 b:12 13:4 18:4 1c:8 1d:7 1e:12 1f:14 26:2 27:4**.

- `build/s126/sym.py` is a symbolic SSE evaluator. `python3 sym.py R` (retail) or
  `sym.py file.obj` prints the expression tree at every ucomiss/comiss.
  Retail and ours compute the same values but sum Length2 in a different order. MSVC 7.1
  reassociates float adds:
  - 0xa1a (`offset.Normalize()` after `Cross_Product(segdir, nearest, &offset)`):
    retail `(X²+Z²)+Y²`, ours `(Z²+Y²)+X²`. The first instruction difference is
    at 0x9b2: retail does `mulss xmm1,[edi-4]` (nearest.X product) before
    `addss xmm3,[esi-4]`. The cross components then land in xmm7/xmm3/xmm1
    (stored -0xf8/-0xf4/-0xfc).
  - Other differing trees: 0x1c31, 0x1e0e, 0x1f0c, 0x1ff1. 0x131d and 0x1844
    give the natural `(X²+Y²)+Z²` in both.
- So the inline vector math differs from B1's `vector3.h`. B1 has Length2
  `X*X+Y*Y+Z*Z`, Normalize with `len2`/`oolen`, Cross_Product(a,b,set_result)
  with asserts then X,Y,Z, Dot_Product `a.X*b.X+a.Y*b.Y+a.Z*b.Z`, and
  Normalized_Cross_Product.
- **Tried (claude seat, 2026-10-20): vector3.h variants** (`build/rs/v_*`, a
  ZH GeneralsMD `vector3.h` copied next to the trial and included by quote;
  bank plus include scores 0.9134). None moves the float-sum residue:
  - MSVC 7.1 /arch:SSE canonicalises an unparenthesised sum: Length2 written
    `X*X+Z*Z+Y*Y`, `Z*Z+Y*Y+X*X` or `Y*Y+Z*Z+X*X` is byte-identical. Explicit
    parentheses change the code but never produce retail's `(X²+Z²)+Y²` at 0xa1a.
  - Normalize bodies (Length2 call, inline `X*X+...`, `len2`/`oolen` locals,
    `if (len2 != 0.0f)` guard as WB has it), Cross_Product forms (temps, by
    value, component order) and a Dot_Product local: best n_inl 0.9193, l_loc
    0.9228 (with the ShroudFilter setter change). Neither replaces the symbol
    lever: n_inl+setter+k30 gives 0.9654, l_loc+k30 drops to 0.9161, so the
    lever depends on position, not on header locals.
  - WB twin (`wb_show 0x00126433`, WB va 0xa1e840, 10149 B, real file
    `WW3D2\simplestreakrender.cpp`, `SimpleStreakRendererClass::RenderStreak`):
    Normalize = Length2 (isInitialized assert) then `if(len2!=0.0f){oolen=
    WWMath::Inv_Sqrt(len2); X*=oolen; Y*=oolen; Z*=oolen;}`, out of line x21.
    WB's own standalone Normalize also sums `(Z²+Y²)+X²`.
- **Tried: dead ZH merge block** (`streakRender.cpp` 880-1085,
  `if (Is_Merge_Intersections())`, about 27 named locals, at the position of the
  k30 dummies, adapted to BFME2's 0x24-byte LineSegmentIntersection without
  Fold/Parallel) under `if (false)` or `if (0)`: **0.7038**. Its Vector3 locals
  (new_point, new_direction, pl) keep stack slots, so the frame grows by 0x24
  (0x625c against retail 0x6238). WB also has no code between the intersection
  loop and `vnum`. Refuted as the source of the symbol count.
- **Tried: where the symbol count lives** (claude seat, 2026-10-20):
  - TU scope: a preceding function with K referenced locals, or K file-scope
    globals (K = 8..62), leaves the score at the 0.9108 baseline. The count
    is per function.
  - Named locals: the bank compiled at `/Od` (`build/rs/od`, script
    `build/rs/gen/slots.py`) maps onto WB's 164 frame slots one for one in
    first-use order. The only differences are `/Od` expression temps: WB's
    `MIN()` temp for `point_cnt` (local_6774), operator-> temps, and our
    two-temp `SimpleTextureTemp` pass. A WB-faithful
    `point_cnt=MIN(point_cnt,chunk_size)` or ternary is byte-identical at
    `/O1` (0.9134), so expression temps do not count either.
  - What remains: named locals inside inline helpers from headers that differ
    from BFME2's (ShadowPtr/RefCountPtr, texture ref temps, Matrix4/Matrix3D
    ctors). The Vector3 helpers are already ruled out (n_inl, l_loc), and void
    inlines with parameters were inert in r10. Unresolved.
- WB callees, for shape: 0x71e1f0 Dot_Product, 0x71f9e0 unary `operator-`
  (7 calls, ours has 7), 0x99e0f0 `operator*(Vector3,float)`. WB's helpers are
  optimised copies with NaN validity checks and assert 0x712780. The
  constant-store differences between WB and our /Od build are /arch:SSE artifacts.

## Symbol numbering decides the sum order (claudeb4, 2026-10-20, third session)

Best unfaithful body: `reverse/attempt_support/0x00126433_v048_padded.cpp.txt`
(`build/s126/s16/b_1/v048.cpp`), **0.9729**, resid 68, 11977 B, frame 0x6238
exact. It has three pads: K=29 referenced `int unusedN=0;` locals before the
intersection loop's `float mid_tex_v`, a `__forceinline padf()` with P6=48 int
locals called at the start of the render-submission tail, and `padQ03()`
(one int local) called just before the `Cross_Product` of top_normal. Its
residue is the four Length2 trees plus small scheduling items at 0xb9d,
0x1378, 0x189c, 0x1b16, 0x23d6/0x242c and 0x2a5f.

| Tree | Retail | v048 |
|---|---|---|
| 0xa1a | (X²+Z²)+Y² | (Z²+Y²)+X² |
| 0x1c31 | (Z²+Y²)+X² | (X²+Z²)+Y² |
| 0x1e0e | (Y²+Z²)+X² | (X²+Y²)+Z² |
| 0x1ff1 | (Y²+Z²)+X² | (X²+Y²)+Z² |

The other 16 square sums match (`build/s126/sq.py obj` lists all 20).

**The order of a reassociated float sum is decided by c2's per-function
symbol numbering, not by how the source writes it.** Probe
`build/s126/s21/p0.cpp` (Cross_Product into a local, Normalize, store):

- With n referenced front-end int locals, the order flips only in narrow
  windows: n=564-565 give (YX)Z and n=566 gives (XZ)Y (retail's 0xa1a order).
  The same happens at 575-577, 1236-1238, 1257-1259, 1908-1910 and 1940-1942.
- Front-end locals count the same before or after the site. An inline pad
  *before* the site counts like a front-end local, so inline-created temps are
  numbered after all front-end symbols.
- Locals in other functions of the TU do nothing.
- s26 2D scan (m trailing inline locals after the site × n front-end locals,
  `build/s126/s26/out.txt`): with m>0, (XZ)Y holds from n ≈ (545−m) mod ~683
  up to n=577, after a two-wide (YX)Z window. With m=600, 1300 or 2000 it holds
  for every n from 23 to 577. The order is a function of the total count and
  of the site's position, which looks like hashing on symbol IDs.
- The same numbering drives register allocation. Header-level pads in
  Normalize or Cross_Product (`s24`) cost heavy collateral (best 0.924).

Consequence: no local rewrite of Length2/Normalize/Cross can fix the trees.
They come out right only once the function has retail's symbol count at
retail's positions, i.e. once every shim is replaced by the real inline
wrapper (DX8Wrapper, ShaderClass, ShadowPtr/RefCountPtr, the DynamicVB
access, the BFME2Set_Texture shims, BfmeSortingDispatch, the ShroudTexture
casts). The pads say roughly how many symbols are missing: about 29 in the
front end before the intersection loop and about 48 inline in the
render-submission tail (`v048` lines 1601-1757).

Next angle: scan an m-count `__forceinline` pad placed after the last tree
site (after 0x1ff1, e.g. at the start of vertex generation) in the full body,
reading sq.py for the four trees. Then look for which real inline wrapper
supplies that many temps.

Also established this session:

- WB `Cross_Product` (0x71bce0) computes X = a.Y*b.Z − a.Z*b.Y, then Y, then Z,
  as ZH does, with isInitialized asserts. WB `Normalize` (0x71d310) has Length2
  inlined, NaN sentinel checks, `(Z²+Y²)+X²`, then `if (len2 != 0)` and Inv_Sqrt.
- At 0xa1a retail and v048 emit the Cross subtractions in the same order
  (Y, Z, X); only the sum tree and one schedule at 0x9b2 differ.
- An unparenthesised Length2 in any term order is byte-identical. A
  right-associated `X*X+(Y*Y+Z*Z)` pins the inner pair in the probe, but on the
  full body every right-associated form scores 0.83-0.88.
- WB call shapes at the segment setup (SUB/ASSIGN/NORMALIZE/DOT/fchs/MULF/ADD
  for nearest; CTOR offset, CROSS(segdir, nearest, &offset), NORMALIZE) match
  our source.

## WB call sequence and helper internals (claudeb4, 2026-10-20, fourth session)

Bests unchanged: faithful bank 0.9134, padded v048 0.9729.

**The call sequence matches WB.** A /Od copy of v048 (`build/s126/s43/od.cpp`)
was compared with the WB twin (`s43/cmpseq.py`, sequences in `s43/wb_seq.txt`
and `s43/od_seq.txt`). Through the whole geometry section, WB calls the same
inline helpers in the same order as our source. Helper choice and expression
shape in RenderStreak are therefore right. The only WB-only calls are in the
tail: the 0x9a0990 texture test, 0x9ca0f0 Is_Currently_Rendering_Shadow_Map,
and debug-only `_isnan`/`_finite`/0xdeadbeef asserts. All of these were tested
before or exist only in debug builds.

WB helpers:

| WB address | Helper | Calls |
|---|---|---|
| 0x71bb50 | Vector3 `operator=` | 49 |
| 0x71e1f0 | Dot_Product | 21 |
| 0x71d310 | Normalize | 21 |
| 0x99e0f0 | `operator*(V,f)`, assert line 291, returns `Vector3(...)` via ctor 0x71bb30 | 15 |
| 0x71c1a0 | Matrix4 `operator[]` | 12 |
| 0x71bb90 | binary `operator-` | 11 |
| 0x71bce0 | Cross_Product | 10 |
| 0x71bab0 | `Vector3()` (stores the 0x1dd08e0 sentinel) | 10 |
| 0x71f9e0 | unary `-` (line 171) | 7 |
| 0x722f00 | `operator+` | 5 |
| 0x71e110 | Set | 4 |
| 0x74a690 | ShadowPtr `->` | 4 |
| 0x402527 | vector ctor iterator | 4 |

BFME2's vector3.h is a longer revision with isInitialized asserts. Assert lines:

| Helper | BFME2 | ZH | BFME1 |
|---|---|---|---|
| `operator-` | 356/357 | 266 | 281 |
| Dot | 385 | 293 | 308 |
| Normalize | 581 | 417 | 438 |

**Helper-internal symbols (s44).** `s44/genh.py` writes modified copies of ZH
vector3.h (`s44/h_<name>/vector3.h`) and includes them after the
`#define inline __forceinline` line. Each variant was K-scanned 0..63 at P=48
(`s42/res_h1.txt`, tc2 strings in `s44/perm_h1dot.txt`):

| Variant | Change | Best | tc2 or note |
|---|---|---|---|
| ctl | unmodified copy | 0.9729 | baseline reproduced |
| ctor_il | initializer-list ctor | 0.9729 | byte-identical |
| n_oo | `oolen` at Normalize's outer scope | 0.9729 | byte-identical |
| n_dir | `float len2 = X*X+Y*Y+Z*Z` in Normalize | 0.9661 | `.a?..........ab.b?b.` |
| l2_l | Length2 with a local | 0.9181 | `.a?...?......ab.b?b.` |
| dot_l | Dot_Product with a local | 0.9098 at K36 | `........b...ba?cb?bb` |
| mul_n | `operator*` via a named Vector3 | 0.8375 | |
| crs_l | Cross with locals cx, cy, cz | 0.7403 | |
| n_sq | `1.0f/WWMath::Sqrt` | 0.6021 | |

dot_l is the only change so far that fixes site 1 (0xa1a, the tree the pads
never fix). At 17 K values it fixes sites 0-7 together, but sites 8 and 12
are wrong at every K. Its P-scan 0..126 at K36 (`s42/res_h2.txt`) peaks at
0.9412 (P12), and the late sites stay wrong (P80-102 plateau 0.9354).
Helper-internal symbols therefore move the trees along a third axis, separate
from the K/P pads.

Not yet tried:

- dot_l with a large P (150-700; the s26 period is about 683);
- an extra local in `operator-`, `operator+`, unary `-` and Set, K-scanned
  and combined with dot_l;
- the K≡-3 (mod 32) reading of K=29: retail may have about three fewer
  front-end symbols than our shims (SimpleTextureTemp, BFME2TextureRef,
  padQ03). The s40 K-scan (K28 `.aa..........ab.b.b.`, K29
  `.a...........ab.b.b.`, K30 `.a....?.a...aa?.b.ba`, K61
  `.aaaa??.b...bab.b.bb`) shows K is not exactly periodic.

Variant generator: `reverse/attempt_support/0x00126433_genh.py.txt` (copy of `build/s126/s44/genh.py`). Tools: `build/s126/tc2.py obj` prints one character per Length2 site
(sites 0-19; `.` matches retail). `s44/run.sh tag files` scores and runs tc2
in the background. `s44/show.py res [n]` lists the top n.

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
- The k-scan of inert locals on its own (uninitialised; see the symbol-count
  lever for referenced locals).
- Moving the 30 referenced dummies among four scopes (r18): the float-sum
  residue never changes.
- VS/PS forceinline without the B1 shader.h.
- Flags: /Ob1, /Ob2, /Oi, /Os change nothing; /O2, /Ot, /Ox give ~0.52.
- Single-statement setter bodies.
- Inert int locals: no effect on the inline budget.
- Unforced setters with the BFME2 Set/Get_Transform shapes: still out of line.
- Line numbers, local names and nested inline isInitialized checks: no effect
  on the sum trees.
- Moving one pad symbol between positions (shift sizes 1-24 at 13 positions):
  only 0x1c31 flips, with damage elsewhere.
- Header Length2/Normalize/Cross forms (s22) and header-level pads (s24).
- Pads in other functions of the TU (s23/g).
- Fourth session: these vector3.h variants under a K-scan: initializer-list
  ctor, Normalize `oolen` scope, direct len2, Length2 local, Cross locals,
  `operator*` via a named temp, `1/Sqrt`. Also dot_l with P 0..126.

## Scratch layout

`build/s126/`:

- Third session: `sq.py obj` (the 20 square-sum sites, retail vs obj),
  `s21/pc.py` (parallel probe compile plus tree classifier), probes in `s21`,
  header forms in `s22`, the front-end pad scans in `s23`, header pads in
  `s24`, pad-position probes in `s25`, the 2D scan in `s26`, and the v048
  family in `s16` (`gen.py`).

- `score.py`, `regsum.py`, `odisr.py`, `omap.py` (ebp slot map), `frm.py`.
- `gen_bf2.py` (Set/Get_Transform shapes) and `gen_f3.py` (T/R/n/p factorial).
- `rs2.py obj...` per-0x100 region diff counts with relocations, call targets
  and immediates masked (better than regsum); `rs2.py obj lo hi` prints the
  diff of one range. `sbs.py obj lo hi` side-by-side, `pdis.py f.cpp sym` probe
  disassembly. `g4/` holds the 0.8307 family (w_A is the bank).
