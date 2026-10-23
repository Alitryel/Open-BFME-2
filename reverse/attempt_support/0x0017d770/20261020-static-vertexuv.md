# PointGroup UV helper 0x0017D770: file-static VertexUV

## Result

Closer partial, banked as `reverse/attempts/0x0017d770.cpp` for `?rva00916CD0@PointGroupClass@@QAEXPAEHH@Z` (retail 0x0017D770, 1583 bytes). The body is the BFME1 donor's semantics with `VertexUV` given internal linkage (`static VectorClass<Vector2> VertexUV;`) and no barriers, equal-arm conditions or other steering statements. It emits 1583 bytes and every instruction outside the quad bounds block matches retail.

| Body | Emitted | Structural regions | Memory lines | Register lines |
|---|---:|---:|---:|---:|
| Bank before this run | 1583 | 11 | 5 | 5 |
| New bank | 1583 | 3 | 6 | 2 |

All memory lines in both rows are DIR32 slots (VertexUV+4 and the two frame tables) that differ only because the unlinked object holds the addend; they are relocation lines, not defects. The new bank has one more because the null path's VertexUV load at +0x283 is now aligned instead of sitting in a structural region. Measured with `tools/align_diff.py <file> ?rva00916CD0@PointGroupClass@@QAEXPAEHH@Z 0x0017D770 1583` on fresh objects.

## Remaining mismatch

Only the quad branch of the null-frame path's bounds transform differs. Retail computes the products X1 and Y1 as `movaps xmm4,xmm0 / mulss xmm4,[eax+8]` and `movaps xmm4,xmm1 / mulss xmm4,[eax+0xc]` (copy du or dv, fold the UV element). The bank emits `movss xmm4,[eax+8] / mulss xmm4,xmm0` and the same for Y1, one byte longer each; the branch displacements across the block and the alignment padding before the last remainder loop (`lea ecx,[ecx]` against `nop`) follow from those two bytes.

## The finding: VertexUV is file-static in retail's unit

With `extern VectorClass<Vector2> VertexUV;` (every earlier attempt) or with a non-static definition in the unit, cl hoists the VertexUV load to function entry when both top-level branches read it, and keeps FrameRowColumnCountLog2 hoisted in the null path. Retail does neither. With internal linkage the same source reproduces three retail details at once: the nonnull path loads VertexUV into ECX and copies it to EDX (`mov edx,ecx`) before the PointMode test, then reuses ECX as the +0x14 induction pointer; the null path loads VertexUV into EDX before its PointMode test; and the null path reloads the log2 byte inside each PointMode branch. Measured on the final body: extern and non-static in-unit definition both give 1575 bytes, 16/16/9; static gives 1583 bytes, 3/6/2. This is the seventh pattern in `docs/matching.md` (a global retail schedules around stores is file-static).

Landing consequence: VertexUV is referenced as `extern` by matched rows in `PointGroupClassRender.cpp`, `PointGroupClassRva00179B50.cpp`, `PointGroupClassShutdown.cpp`, `Rva0017f150Cluster.cpp` and `PointGroupClassRenderVolumeParticle.cpp` (all under `Code/Libraries/Source/WWVegas/WW3D2/`). An exact body with a static VertexUV can only land in a unit that also holds every other reader and writer of it (the retail pointgr.cpp), and the static's dynamic initializer and atexit destructor would be emitted there too. That is a coordinator-level consolidation decision; the bank does not attempt it. One sibling check (n=1): the matched `PointGroupClassDiffuseFill.cpp` body (0x0017DDA0, 1135 bytes) compiles to the same bytes with `static VectorClass<Vector4> VertexDiffuse;` as with its `extern`, so internal linkage does not disturb at least that neighbour.

## Body shape that matches the integer skeleton

`vertex_uv` is declared at the top of the nonnull branch, and at the top of each PointMode branch of the null path before `uv_ptr`. The copy loops use the donor's pointer increments. The tris bounds loop uses `uv_ptr[j].X = u0 + uv_ptr[j].X * du;` and fully matches retail. The quad bounds loop uses a per-element pointer (`Vector2 *uv = uv_ptr + j;`); the same subscripted form as tris measures 6/17/9 there (copy form lands on X1 only, and the tail pairs X3 with xmm0 instead of Y3).

## Ruled out in this run (all with static VertexUV unless noted)

- Zero Hour `vertex_uv[vert++]` indexing, `vertex_uv[i*n+k]`, `vert += n`, and per-iteration destination pointers in the copy loops (measured with extern VertexUV): all worse, 1565 to 2035 bytes.
- vertex_uv at function scope (donor) or at null-branch scope hoists the VertexUV load to entry; declaring it after uv_ptr in the tris branch or after the bounds block reorders it. The quad branch is indifferent to the placement.
- Quad bounds spellings: declaration orders of u0/v0/du/dv, `du = bounds[2] - bounds[0]`, `(u1 - u0)` in the product, product written first, compound `*=`/`+=`, Vector2 temporaries and `Set`, reference or `float *` element access, `operator[]`, `Vector2` offset/scale locals, explicit pair loops, reverse and unsigned counters, pointer-increment loops, `const` locals and bounds pointer, bounds pointer at function or null-branch scope, a named frame index, function-scope `i`/`j`/`uv_ptr`/`vertex_uv`, alternative quad table index spellings, and file-static frame tables. The run measured 212 distinct trial sources, most of them on this block; the copy-form products move with spelling (Y0 alone, X1 alone, Y1 alone, X2 alone, or none) but never cover Y0, X1 and Y1 together.
- Flags `/O1` (528 bytes, no unrolling), `/Ox`, `/Ot`, `/Ob2`, `/Oi`, and the pinned `vc71-sp1` and `vc71-ddk-4035` compilers: none closes it.

## Next step

The open question is what makes cl 7.1 fold the UV element for X1 and Y1 in the quad block while folding only Y0 in the tris block. Prefer evidence over another spelling sweep: for example, a sibling body in the same retail unit with an unrolled SSE product loop, or a controlled `/FAsc` study of when cl chooses `movaps reg; mulss reg,[mem]` over `movss reg,[mem]; mulss reg,reg`.

## Provenance and verification

Identity, boundary, ABI and data witnesses are unchanged from `reverse/attempt_support/0x0017d770/readme.md` and the BFME1 identity evidence `reference/open-bfme-1/targets/game/reverse/identity_evidence/00916cd0-pointgroup-uv.md`; retail's body has no calls and ends with `ret 0xc` at +0x62C. The donor is BFME1 `game/Libraries/Source/WWVegas/WW3D2/PointGroupClassUVFill.cpp`; the internal linkage of VertexUV is a structural inference from BFME2 retail codegen, not a donor fact. The address-derived name stays. Compiler: default 13.10.3077, `/O2 /arch:SSE /G7 /DNDEBUG /MD` with the bank's include paths. Model: claude-opus-5-5.
