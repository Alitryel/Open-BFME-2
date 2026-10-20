# 0x000A9F98 AptShapeContainer::render - per-site SSE helper search

Session 2026-10-20, claude-opus-5-5, t=90. Bank `reverse/attempts/0x000a9f98.cpp`
updated: size-exact 1471 B, 29 differing instructions (was 41) plus the three
unresolved end-list calls.

Target fact used: WB `aptMatrixMul` (0x8A8BD0) is an out-of-line `__fastcall`
(out in ECX, in in EDX, matrix on the stack) computing
`in.X*m.a + in.Y*m.c + m.tx` / `in.X*m.b + in.Y*m.d + m.ty`; retail inlines all 11
call sites. Calling convention / plain `inline` vs `__forceinline`: inert.

Method: `search.py.txt` replaces the 11 call sites independently with one of 147
semantically identical helper spellings (3 point-access forms: `in.X`,
`const float *q = &in.X; q[0]`, locals x/y; x 7 forms per row: plain, both
products named in either order, one product named, named sum, factor-reversed)
and greedy-descends on differing instructions from `explain_mismatch`. Site
order = source order: textured pos/uv p1, p0, p2 (0-5), solid p0, p2, p1
(6-8), line a, b (9-10).

Best config `[0,0,0,0,49,0,8,0,49,1,49]` (indices in search.py.txt): plain
everywhere except textured pos p2 and solid p1 and line b use the
pointer-indexed point (`q[0]`, `q[1]`), solid p0 names all four products, line a
names the Y products. Greedy single-site descent from here finds nothing among
147^1 moves; 40 min of random 1-3-site moves (plateau accepted) found nothing.

Residue (`residue.txt`): line-case X row products order/operands (+0xF4..+0x12A),
one solid product (+0x292), textured uv sites p1/p0 and pos p2 (+0x433..+0x55E).
Retail sometimes addresses p.X and p.Y of one point through different
registers (edx = iterator, ecx = iterator+0x14 strength-reduced), which no
helper spelling here reproduces.

Landing also needs the end-list callees: 0x001100A6 / 0x001100C5 are owned by
placeholder rows (`Rva001100A6::rva001100A6`, `Rva001100C5::rva001100C5`,
thiscall, body ignores EDX); WB names 0x1100A6's twin
`W3DAptRenderer::EndTriangleList` called with the cursor in EDX. Either pin the
bank's placeholder fastcall names there (admissible: owners are placeholders) or
rename the owner rows. Current W3DAptAux.cpp has diverged from the bank's TU;
merge only the class deltas (AptShapeContainer m_shapes/render, friend,
BfmeHub982 end-list decls) and the render body.
