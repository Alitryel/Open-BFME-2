# 0x0017D770 PointGroupClass quad bounds: blocked on IND base hash keys (2026-10-20)

Bank `reverse/attempts/0x0017d770.cpp` is unchanged.
- Score: 1583/1583, bytediff 352, nd 9. Four of the nine lines are DIR32 table operands.
- Real residue: the X1 and Y1 products at +0x489 and +0x49a, plus padding at +0x5ed.
- Effort: about 80 minutes, claude-opus-5-5 subagent.
- Scratch tools in `build/agK/` (untracked):
  - `ktrace.py`: traces the sort and decodes each IND's base and symbol kind.
  - `kpat2.py`: predicts the load/copy pattern.
  - `ktemp2.py`: logs CSE hash-var creation.
  - `krun.py`: traces and scores.

## Compiler facts (traced in c2 3077)
**Where the order is set.** The deciding MUL is sorted for the last time in the final `OptTdCanonTree`, after the last `LoptBuildAddressModes`. Its UV element is an IND leaf: op 594, kind 6.

**Key of a kind-5/6 IND leaf** (handler at c2 0x6C720): `0x10000 | (fold(disp) + 8 + (hash(base) << 8))`.
- disp is 0 there, so only the low byte of the base's hash matters.

**Low byte of the base hash:**

| Base | Hash | Low byte |
|---|---|---|
| Named local (sk4) | 32·F | `(F&7)<<5` |
| CSE hash var (sk3, made by 0x61516 / SymMakeHashVar 0x615BC) | `(X<<6)&0xFFFF` | `(X&3)<<6` |

**Threshold.** du and dv are named locals #25 and #26, with keys 0x10320 and 0x10340. An element therefore folds as a copy only when its base is either a hash var with X ≡ 0 (mod 4) or a named local with F ≡ 0 (mod 8).

## Target requirement
Retail folds only Y0, X1 and Y1:
- Those three bases need a zero low hash byte.
- X0, X2, X3, Y2 and Y3 must not have one.

## Bank state
| Element | Base | Key | Form |
|---|---|---|---|
| X0 | `uv_ptr` #21 | 0x1a008 | load |
| Y0 | t1764 | 0x10008 | copy |
| X1–X3 | named `uv` #28 (shared) | 0x18008 | load |
| Y1–Y3 | t1749 (shared) | 0x14008 | load |

X1–X3 share one base, so they always take the same form. The pointer and reference forms therefore cannot match.

**Donor subscripted form.**
- The bounds bases reuse the CSE values of the following copy loop, 5 per dword: Y0=a, X1=a+5, X2=a+15, X3=a+25.
- Y1–Y3 are spaced 21 apart.
- X1 ≡ X3 (mod 4) and the Y0→X1 gap is 5, so no uniform renumbering can work.

## Ruled out (each traced and keyed)
- 56 address spellings: `[j].X`, `->X`, `[j][0]`, float* `[2j]`/`[j+j]`, `(&.Y)[-1]`, casts.
- Explicit 8 statements.
- Pair loops: `j+=2` is not unrolled, 1527 B.
- `uv=uv_ptr+2j`.
- Pointer-increment and pointer-bound loops.
- Compound operators.
- Y before X.
- Split X and Y loops.
- Element 0 peeled off.
- Vector2 `Set`, ctor and `Scale`+`+=`.
- Inline and forceinline helpers.
- A separate `src` copy loop: gaps 10/10/12, and it changes the code.
- A (u1-u0) multiplier: du becomes hash var 0x1dc40 and every product becomes the copy form, 1575 B. It is a real lever for the threshold, but no structure gives X1 as the unique smallest X key.

## Next
Two directions remain open:
- Copy-loop forms that compile to identical code but number their values differently.
- Named bases at F ≡ 0 (mod 8).

Also try the FP paren lever (`reverse/attempt_support/fp-paren-nodes-20261020.md`). Parenthesized float terms are expression nodes and key by size and depth, not by base hash.
