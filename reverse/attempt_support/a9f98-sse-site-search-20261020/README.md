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

Follow-up (same day): doubled the space with a store form (compute into locals
`rx`/`ry`, then `out.X = rx; out.Y = ry;`, indices 147..293) to change
out/in aliasing; greedy descent from the best config over all 294 spellings per
site finds no improvement (still 29 + 3). Spelling-level levers at the helper
are exhausted; the remaining lever is outside the helper (loop/pointer shape,
which prior seats also swept).

## Round 3 (2026-10-21, claude-opus-5-5, t=150): symbol-number pad lever, 29 -> 24

Mechanism: c2 FactCanonSort (c2_l.dll RVA 0x5CD11) orders commutative SSE
operands by key; a memory leaf keys about `0x10008 + 0x2000*(F&7)` with F the
base symbol number. Locals are numbered in declaration order; compiler temps
(inline-instance symbols of the helper, induction temps) are numbered after all
source locals. Unused `int unusedSlotN = 0;` locals therefore shift every later
symbol, period 8. See also the 0x6227E0 note
(`0x006227e0-reduction-mechanism-20261021.md`).

Bank updated (size-exact, 24 differing insns + the 3 end-list calls): helper
config unchanged `[0,0,0,0,49,0,8,0,49,1,49]`, plus 5 unused locals after
`uvTransform`, 3 at the start of the textured loop body, 5 at the start of the
solid loop body. `pad_combo.py.txt` builds helper-config x pad-map sources;
window and iterative searches (about 19k compiles) find nothing below 24.

Decomposition (`pad_decomp.py.txt`, 512 residue combos of the six
shift-sensitive anchors U=uvTransform, textured/solid/line iterators, segment,
and the temps): only U, t_T, t_S, g, segment and the temps move any site;
`it`, shape, textured, texture, color, v and tri are inert. Sites Lb
(+0xF4..+0x137), S3 (+0x27B..+0x2C0), T2 (+0x401..+0x450) and T6
(+0x524..+0x570) are wrong under EVERY combo: their compares are temp vs temp,
so no source-local pad reaches them. Retail T2: X row `X*a` point-first, `c*Y`
matrix-first; Y row both point-first. Retail Lb: X point higher than the
matrix, Y point lower, both rows.

Refuted this round: helper taking the matrix directly with no cast local
(`const AptMatrix &m` param with call-site casts: 57-63; union-typed
AptRenderTransform with `.a..ty` fields and no local: 63). The cast local is
part of the right shape.

Also refuted: unused locals inside the inlined helper (1-7 `int` before the
cast local, after it, or at the end; each of the 11 sites alone, 231 trials):
best still 24, and no trial changes the wrong-site set {Lb, S3, T2, T4, T6}.
Helper-local numbering does not reach these sites either.

Remaining untried angles: the loop/iterator shape around the Lb/S3/T2/T6
instances (retail strength-reduces `iterator+0x14` into ECX for one point),
e.g. spelling the triangle/segment points through explicit pointer locals
declared in the loop, then re-running the pad search from that base.
