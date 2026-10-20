# UpdateShadowCamera, third pass: parentheses lever (2026-10-20, seat w5)

Result: blocked. The bank `reverse/attempts/0x0007c8ae.cpp` stays unchanged (4176 B, 0 regions, 48 memory, 0 register). Nothing was placed in `Code/`. model=claude-opus-5-5.

Target: `?UpdateShadowCamera@W3DShadowMapManager@@QAEXXZ`, RVA `0x0007C8AE`, 4176 bytes. Read `../update-shadow-camera-20261020-w5/readme.md` and `../update-shadow-camera-20261020-w5-pm/readme.md` first; this file only adds to them.

## Hypothesis tested

The 0x000EBFD1 finding (cl 7.1 does not re-associate a float sum across explicit parentheses) applied to the three remaining operand regions: a TU copy of `Matrix3D::Transform_Vector` whose rows carry explicit groupings, so that rows 1 and 2 sum `(X+Y)+Z` as retail does, then combined with chain shift 0 (the only shift at which the normalize region matches). Refutation: no grouping at shift 0 closes the row sites without opening others.

## What the measurements show

Every trial is the bank with only the named change, measured with the same masked `align_diff` comparison as the earlier passes (each trial compiled fresh at its own path). Retail's row trees, read from the disassembly at +0x68A..+0x710:

- row 0: `((vX*m00) + (m02*vZ)) + (m01*vY) + m03`, with the Z product computed before the X product and `v->X` loaded.
- rows 1 and 2: `((m10*vX) + (m11*vY)) + (m12*vZ) + m13`, the X product first.

The bank's row 0 has the same association (only the X product's load/fold pick and the evaluation order differ); its rows 1 and 2 sum `(Y+Z)+X`.

1. **The header spelling is already in use.** The bank includes the WWMath `matrix3d.h` and `vector3.h`, and every copy of `Transform_Vector` in the tree (BFME 1 game, ZH Generals and GeneralsMD, all shims) has the same text. A TU copy of the header body (`tv_H_H_H`) and the `(float)( )` wrapper on row 0 compile identically to the bank.
2. **Parentheses fix the association of rows 1 and 2, but not the order inside the group.** With `((X + Y) + Z + W)` or `(((X + Y) + Z) + W)` on rows 1 and 2, both rows sum `(X+Y)+Z`, but the Y product is evaluated first (retail evaluates X first). Writing the group in the other source order (`(Y + X)`) compiles identically: the order inside a group is canonicalized by operand rank.
3. **Each inner group is a shift of all loop regions, with period 4 groups, and it never touches the normalize region.** Groups placed in any row, or in a grouped copy of `mulVector3Array` at any one of its three call sites, give the same effect for the same count. By group count modulo 4 at chain shift 0 (rows excluded):

| Groups mod 4 | Size | Regions | Windows still wrong besides the rows |
|---|---:|---:|---|
| 0 | 4176 | 0 | `lightDir + p` (+0x7A2..+0x877); some groupings also 4 to 8 lines at +0x9E7..+0xA31 |
| 1 | 4192 | 11 | frustum lerp, first `mulVector3Array`, second corner loop and last `mulVector3Array`, tail; `lightDir + p` matches |
| 2 | 4191 | 18 | lerp, first `mulVector3Array`, `lightDir + p`, late loops |
| 3 | 4176 | 14 | first `mulVector3Array`, `lightDir + p`, late loops, tail |

4. **The chain-local shift and the group shift are independent counters.** Crossing the 54 groupings with chain shifts 1 to 7 (385 trials) shows that the normalize region matches only at chain shift 0, whatever the groups, while the loop regions depend on both counts. In no combination of the two counts are `lightDir + p` and the frustum lerp, first `mulVector3Array` and late loops clean together: the `lightDir + p` window is always one class away from the others.
5. **Using `p` in some statements only** (all 64 masks of `p` against `hullPts[i]` over the six uses in the intersection loop, at each of the four group classes, 256 trials) reproduces the earlier finding: every mask that fixes `lightDir + p` reopens the second corner loop (4184 B, 7 regions, at least 79 memory lines). In the corner loop the flipped site is the X component, which is the displacement-0 element there (`[ebx]`), just as Z is in the intersection loop (`[esi]`); the two loops compare the same `lightDir` components against an induction pointer and move together.
6. Store spellings in the intersection loop (`p + lightDir * t`, `t * lightDir + p` and their mixes, 32 trials on the bank and on a grouped class-0 body) compile identically.

Best grouped bodies at shift 0 stay worse than the bank: for example `tv_H_P2_P2` (rows 1 and 2 grouped) measures 4176 B, 0 regions, 52 memory, 0 register.

## Interpretation for the next attempt

All three remaining regions are operand-rank picks, and the ranks follow at least two global counters: user locals (chain shift; affects the normalize region too) and inner parenthesis groups anywhere in the function, which move only the loop regions (see the `Length2` trial below). The intersection loop and the second corner loop additionally depend on how the induction pointer for `hullPts[i]` is formed. A landing needs a source-level difference that moves the intersection loop's class by one without moving the corner loop, or an evidence-backed change to how `lightDir`'s components are created (they are scalar-replaced and compared against the displacement-0 pointer in both loops). The WorldBuilder twin shows `lightDir` built by the copy constructor from `m_lightDirection` and `Normalize()` inlined, which the bank already does. WB's inlined `Length2` pushes the Z, Y and X products in that order before adding, so a TU copy of `Normalize` was tried with `Length2` spelled `Z*Z + Y*Y + X*X` (identical to the bank: canonicalized), `(X*X + Y*Y) + Z*Z` (exactly the one-group loop shift of the table above, normalize region still clean) and `X*X + (Y*Y + Z*Z)` or `(Z*Z + Y*Y) + X*X` (one group plus 10 lines in the normalize region). So a group in straight-line code counts toward the same loop counter, and this lead is closed.

A last cross scan (two `lightDir + p`-fixing masks, four group classes, chain shifts 0 to 7, 64 trials) found no point where the intersection loop and the second corner loop are both clean.

## Raw logs (untracked)

`build/w5_7c8ae_c/`: `grid1.txt` (groupings by chain shift), `grid3.txt` (p masks by group class), `grid4.txt` (reversed groups), `grid5.txt` (store spellings), `grid7.txt` (masks by class and chain shift), `g6b/` (mulVector3Array footprint), `g8/` (Normalize copies), the generators `gen_tv.py`, `gen_shift.py`, `gen_p.py`, `gen_mva.py`, `gen_st.py`, `gen_n.py`, the window summarizer `sum.py` and the row decoder `rows.py`. The grouping generator is kept beside this file as `groupings.py.txt`.
