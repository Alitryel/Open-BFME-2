# W3DCamTransform 0x102F83, 2026-10-21 (claude-opus-5-5, ~3 h over two contexts)

Symbol `?rva00102F83@W3DCamTransform@@QAEXPAUCameraTransformInput@@@Z`, 4299 B, RET4.
cl line and home file unchanged from `w3dcamtransform-102f83-r53-20261020/readme.md`.
Fitness = permute.Scorer (0.5 mnemonic + 0.3 instruction + 0.2 byte).

Bank: hack-free body, fit 0.8790 (was 0.8782). The only change is that the shaker system
is reached without a `system` local:
`(*(Rva0065CA4 **)&CameraShakerSystem)->rva00065E3C(1.0f/30.0f);` followed by
`(*(CameraShakeSystemClass **)&CameraShakerSystem)->Update_Camera_Shaker(...)`.

## The remaining wall: how sourcePos/targetPos are stored

Retail facts:

- s is sourcePos at [ebp+0x68/0x6c/0x70]; t is targetPos at [ebp+0x58/0x5c/0x60].
- X and Y are never held in registers. In the translate, live, pitch and final-copy
  code, retail reads them from memory and stores each result immediately.
- s.Z (xmm1) and t.Z (xmm0) are split register candidates. They are reloaded at
  +0x85d (s.Z), +0x979 (s.Z after tan) and +0x8b3 (t.Z). At the join +0x7de,
  xmm0 = targetHeight + t.Z and xmm1 = s.Z. The hold block delays the s.Z, t.Y and
  t.Z stores to +0xa3c/a41/a46.

Signature tool: scratch `build/cam/sig.py` (rl / ms / hold). Retail is
`rl=0,0 ms=5 hold=MMR`, ours is `rl=0,4 ms=1 hold=RRR`.

Findings this session:

1. **Escape is per whole struct.** Passing `&s.Z` to an extern call escapes all of
   sourcePos, so escaping both Z fields behaves the same as escaping both structs.
2. **Extern escape (today's source) gives RRR.** s and t become stored-through register
   candidates with sunk stores, because Look_At 0x712150 is extern: it lives in
   Matrix3DUnmatchedSSE.cpp and is not visible in this TU.
3. **No escape gives MMM** (diagnostic `la_def`, a TU-visible noinline
   `Matrix3D::Look_At` stub). X/Y now match retail's memory form, but Z becomes memory
   too, the t slots shift to 0x54..0x5c and the pitch branches tail-merge (fit 0.8389).
4. **Escaping only targetPos** on the la_def base gives **fit 0.8930**, len 4296,
   regions 4/31/38/51/20/19/59. The variant (e3) adds a bogus extern `escf(&targetPos.Z)`
   before `v->transform->Rotate_Y(...)`, so it is NOT bankable. It is still the best
   lead: retail looks like LTCG/cross-TU knowledge of Look_At, with the two structs
   escaping differently.
5. **Pressure is disproven.** Five extra live float locals (p1-p5) never push X/Y into
   memory form; every variant stayed RRR.
6. **Diagnostic only, not bankable:** an 8-byte V2f block write into the s/t X/Y fields
   gives MMR.

## Disproven (never repeat)

- Indexing and copies: operator[] X/Y/Z; V2f copies.
- Earlier trial families: WB factorial A-D; the k-scan of dead locals; 36 mulVector3
  term permutations; four mulVector3 shapes (including inline vs forceinline).
- Callee shape: Set(axis,s,c); two-arg mulVector3; real Make_Identity; row-wise
  operator=; empty 0x7E8450 hook.
- WB forms: WB-order hold delta; WB division fxPitch.
- Distance: Vector3 Distance on Z-zeroed XY copies (WB-confirmed semantics), re-run as
  d1-d5 (0.86-0.875).
- Headers and flags: the full matrix3d.h include; permute --flags.
- Branch structure: removing constraint x; WB liveCamera orders w1-w3.
- Scoping: named temporary matrices; block scopes; a mode-4 helper; an origin helper;
  a namespace frame struct.
- Bulk removals and mixes: R1-R14 and A1-A6; M1-M8; the f1 factorial (144 variants).
- Escape and pressure: la_def as-is (0.8389); la_def_esc (0.8213); k1 float locals;
  e1/e4 (escaping both Z or both structs = RRR); e2 (escaping s.Z only, 0.8242);
  p1-p5 pressure.

## Next angles (untested)

- On the la_def base, find what turns Z into a register candidate while X/Y stay in
  memory. Candidates:
  - hold via operators (`Vector3 delta=v->source-sourcePos; targetPos+=delta;`);
  - `sourcePos*=factor`;
  - `targetPos.Set` vs field writes;
  - targetHeight vs the WB parenthesised form;
  - the form of the final copy.
- A real construct that escapes only targetPos, as e3 does. Examples: transitionLiveMode
  (0x102B83, TU-visible) taking `&targetPos` before Look_At, or a Look_At overload
  taking only the target by reference. A TU-visible Look_At needs identity evidence
  and a rehome of 0x712150 (the Add_Mesh recipe in docs/recipes.md).

Scratch tools (untracked): `build/cam/{rs.py,sig.py,dd.py,sc.py,retail.dis,wb.txt}`;
variant generators `build/cam/y1/gen{,2,3}.py`; best clean body `build/cam/g1/a.cpp`.

## Rebase note (2026-10-21, claude-opus-5-5)

This handoff was written in parallel with r55 (`w3dcamtransform-102f83-r55-20261021/readme.md`),
which banked 0.88522 with the one-arm `adjustPitch` helper. The bank stays r55's body.
Measured on the r55 bank with permute.Scorer:
- the shaker-without-local spelling above: 0.8652 (worse; not adopted);
- the e3 diagnostic patch (its four code hunks apply to r55 by context): 0.8966
  (still diagnostic only: noinline Look_At with a bogus targetPos-escaping extern).
