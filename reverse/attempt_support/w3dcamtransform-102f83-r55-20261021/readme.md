# W3DCamTransform 0x102F83, r55 (2026-10-21, claude-opus-5-5, ~170 min)

Bank improved: reverse/attempts/0x00102f83.cpp fit 0.87820 -> 0.88522,
align 46 -> 48 regions, memory 115 -> 111, register 61 -> 59 (hack-free).
Read r53 and r54 first; nothing below repeats them.

The lever: the fxPitch>1 else arm goes through a one-arm forceinline helper,
`adjustPitch(sourcePos,targetPos,v->fxPitch)` (division form), while the
realZoom arm keeps `inversePitch` multiplies inline. That stops the two pitch
arms from tail-merging (r54 root cause: identical arms merged into `jmp +0x8bb`).

Disproven on the r55 base (each <= 0.88522):
- the helper in both arms (0.871); the WB inline division form in either arm (0.8758);
  by-value or returning helper forms;
- FP parens (ZH `t+((s-t)/p)` spelling) on the realZoom arm, the helper, the nearAdjust
  arm and the height arm, all 15 combinations: byte-identical (inert);
- `Z*=(capped*0.75f+0.25f)` paren form: inert; removing targetHeight with
  parenthesised targetPos.Z+= : 0.86;
- forceinline X/Y/Z field accessors: 0.745-0.872;
- 8-96 extra tracked live locals: X/Y stay globreg candidates, so the
  tracked-symbol limit is not the cause;
- 7 WB Distance-on-copies forms: at most 0.8707;
- transitionLiveMode body moved after the function or removed: inert;
- +0x2ad operand order (retail `zoom*offset.Z`, ours `offset.Z*zoom`, while X/Y are
  `offset*zoom` in both): source swap and parens are inert; Set(), Vector3 ctor,
  copy then `*=zoom`, `float zoom` local and Z-first order give 0.74-0.81.

Open wall (unchanged): retail keeps sourcePos/targetPos X/Y memory-resident
(both structs are address-taken by Look_At at +0x1c3/+0xb7b/+0x1080 in both
builds), while only the Z pieces are register candidates. Ours makes all six
candidates. Untested next: a semantic reason for the X/Y weights to drop, e.g.
the realZoom adjust reading X/Y through an out-of-line or address-taking call,
or the realZoom arm written after the join.
