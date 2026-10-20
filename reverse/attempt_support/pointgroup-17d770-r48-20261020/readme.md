# PointGroupClass 0x17D770 UV helper, r48 (2026-10-20, claude-opus-5-5, ~75 min, ~450 trials)

Bank unchanged (1583 B; align 3 structural / 6 memory (all DIR32) / 2 register).
Residue: quad bounds block in the null-frame path: retail products Y0,X1,Y1 in
copy form (movaps xmm,du; mulss xmm,[eax+off]); ours X1,Y1 in load form
(movss xmm,[mem]; mulss xmm,reg), +1 B each, plus je/padding shifts.
Notation per mulss (C copy, L load): target tris LCLLLL quad LCCCLLLL; bank
LCLLLL|LCLLLLLL. Scratch build/nbr/r48/17d770 (mc.py own-.obj compile + C/L
printer, grid.py, combo.py, extra.py, grid1.txt, combo_*.txt).

1. Copy-form choice is whole-function and chaotic: quad-only edits flip tris
   (Scale bodies make tris Y1 C; Vector2 ctor/Set bodies change tris). Struct
   temp count matters but position-dependent, no clean period (diagnostic
   discarded temps: quad-branch k=4,12,13 -> LCCLCCLL; entry k=2 ->
   CCLLLL|LCCLCCLL, k=6 -> CCLLLL|CCCLCCLL).
2. Reference-returning calls (operator[] in operator=, Vector2::Set in any of
   the 4 copy loops, 32 combos): no shift.
3. Subscripted forms (uv_ptr[j].X/.U, du*X, X*du+u0) ignore temp count, quad
   starts LLCLLC; tail by header: float bounds[] LL, RectClass LC, Vector2
   offset/scale locals or Upper_Left() CL.
4. Pointer/reference forms: only LCLLLLLL, LCCLCCLL, CCLLLLLL, all-L; never Y1 C.
5. Only the Vector2::Scale family gets Y1 copy form: uv->Scale(du,dv);
   uv->X+=u0; uv->Y+=v0. With an extra Vector2 temporary tris stays LCLLLL;
   quad LCLCLCCL (float/RectClass headers) or LCCCCCCC (Vector2 offset/scale
   locals: retail's LCCC prefix, but last element interleave changes, 1575 B).
   Both worse on align_diff than the bank.
6. Mixed forms and RectClass Upper_Left/Lower_Right/Extent headers missed.
No WB twin. Next: Vector2-locals header + Scale-family quad body (LCCC prefix)
while getting X2..Y3 back to load form and retail's tail interleave, paired with
natural struct-temp changes elsewhere. Landing still needs every VertexUV user
in one TU.
