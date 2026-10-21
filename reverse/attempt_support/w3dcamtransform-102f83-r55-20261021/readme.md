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

Later in r55 (all on the r55 bank, none adopted):
- g12: 2-iteration `sourcePos[i]` loops (Vector3::operator[]) in the pitch arms stay real
  loops (best 0.877).
- g13, full 2^10 factorial (translate order, targetPos field zeroing, inline distance,
  held `delta=v->source;delta-=sourcePos`, `targetPos+=delta`, nearAdjust through
  adjustPitch(90+fxPitch), realZoom arm through a multiply helper, field-wise copy-back,
  mode-2 Set, m_cameraSource copy before the flag test): best = bank 0.88522; the memop
  metric (retail 32) never exceeds 18.
- permute.py 30 min: 0.8852 -> 0.8861 (49 regions). Bisected (g14): only two edits act,
  E1 = target XY += pos before the findObjectByID lookup and source XY += pos after it
  (0.88562, 45 regions, mem 19), and E4 = `sourcePos=v->source` before `targetPos+=delta`
  in the hold (with E1 0.88613/49). E1 is not retail's order (retail adds the source XY
  before the call), so it is noted, not banked. `targetZAdjustment+groundLevel` order and
  `Z=Z*(...)` are inert.
- WB 0x7E3040 re-read: realZoom adjust is `(s-t)/fxPitch + t` per axis in WB (fld s; fsub t;
  fdiv; fadd t); the live arm calls Vector3::Distance on Z-zeroed copies (asserts
  vector3.h:1005/1006, operator- 356/357, Length 581) and copies sourcePos to this+0xC
  before them. Both already covered by the r53/r55 trials.

## Session r56 (2026-10-21, claude-opus-5-5): diagnostics only, bank unchanged (0.88522)
Metric: pm = memory-operand sub/add within 12 insns after each divss (retail 10, bank 3);
ebpm = (sub|add|mul)ss xmm,[ebp..] (retail 65, bank 53). Frame (lea ebp,[esp-0x74];
sub esp,0x88) and prologue are already identical.
None of these move pm or make sourcePos/targetPos X/Y memory-resident:
- d1: each single deletion, and cumulative cuts down to tiny bodies;
- d2: volatile touches of the X/Y fields;
- d3: small-probe disqualifiers (shown in the probe, do not carry to the full body);
- d4: `sourcePos*=factor`;
- d5: field and whole-struct addresses escaped to externs at entry or exit;
- d6: int/double/__int64 puns, variable index, memcpy, pass by value, x87 conversion;
- ph: `int dK=K;` meters 0..64: period-32 phase (32 extra meters reproduce the bank
  exactly), never the X/Y residency;
- d7: real WWMath semantics (always.h WWINLINE = __forceinline) on the Vector3 shim's
  copy ctor, operator=, operator=(Coord3D), Set, 3-float ctor, full 2^5: all 32 byte-identical.
Reading: at +0x50D retail stores sourcePos.X before loading v->pos.y (ours schedules
loads above sunk stores and reloads X/Y after findObjectByID). Retail's X/Y are not
candidates in this region, while Z is. Escaping addresses did not reproduce this in ours,
so the cause is not ordinary aliasing. Still untested: X/Y written through a
non-inline/out-of-line Vector3 member at the translate (out-of-line operator+= or Add
with a visible body); a Vector2/Coord2D view of the XY pair from another shared helper.
