# 0x102F83 W3DCamTransform::rva00102F83 — round r61 (2026-10-21)

Bank: `reverse/attempts/0x00102f83.cpp` 0.91227 (two-if realZoom, r61 v53: `targetPos+=delta` + translate addXY helper; was 0.91179).
Single-if base `s0` (r60 v32/s0.cpp) 0.88893. Build `/O1 /G7 /arch:SSE /DNDEBUG /MD`.

## Residue (unchanged root cause)
Retail float candidates are {xmm7=1.0, s.Z, t.Z}; s.X/s.Y/t.X/t.Y are memory
operands everywhere (`[ebp+0x58/5c/68/6c]`). Ours promote t.X/t.Y to registers.
Fingerprint (arith/loads per slot 58,5c,60,68,6c,70): retail 9/3 9/3 1/2 7/8 7/8 8/4,
bank 4/4 2/6 3/2 7/7 7/7 8/4. Mem-operand `(add|sub|mul)ss xmm,[ebp+58|5c]`: retail 18, bank 6.

Retail facts read this round:
- realZoom is single-if: `if(realZoom){clamp; fxPitch=..; divss xmm2(1.0 reloaded),xmm0;
  lerp with mem operands; load t.Z; jmp end}` else chain `comiss xmm7,fxPitch`.
- The else adjustPitch is a *separate* lerp copy (`movss s.X; subss t.X; divss xmm7,[fxPitch];
  mulss; addss t.X`): no tail merge. s0 cross-jumps both lerps into one.
- Translate stores sX,sY,tX,tY immediately as pos+piece; ours loads t.Y first, keeps it in a reg.
- WB 0x7E3040: s at ebp-0xc, t at ebp-0x18; ~60 distinct locals in the live arm,
  ~30 from realZoom to tan(); live arm uses Z-zeroed copies + operator- + Length.

## Disproven this round
- v42: callee field access pattern inert; only pointer escape matters.
- F_100001 (visible Look_At) 0.9062, diagnostic only.
- v43/v44 used fillers (`{float a=((float*)v)[i]; ((float*)v)[j]=a*a;}`): at A,B,C,Z,D,F up to 80
  no candidacy flip. At E (before realZoom) >=64 named locals flip t.X/t.Y to memory
  (unnamed temps ~96). `+=1.0f`, int xor, global-sink fillers never flip. Fillers before the
  translate or after the fxPitch chain cancel the flip. Emits code, so not a source shape;
  it shows the candidacy decision is a register-pressure/symbol-count threshold in region E.
- v45-v47,v49 zero-code `__forceinline idf` fillers: never flip candidacy, but late allocation
  (windows 4-5, positionHold..end) has a 32-periodic landscape: E064 0.91622, E032 0.9127,
  non-multiples 0.84-0.90; s0 best H064 0.89339. Symbol numbering affects the tail, not X/Y.
  `build/b4-102f83/v46/E064.cpp` is NOT bankable (fake fillers).
- pr2 probe: flip vs filler count is banded (0 for 0..14, 2 for 15..44, 0 for 45..61, 2 for 62..84).
- v51 2^5 on bank and s0: lerp division form, `(p*.75+.25)*1.0f`, WB Distance on Z-zeroed
  copies, fieldwise m_cameraSource, adjustPitch written out: all inert or worse
  (s-division variants 0.871).
- v52 first-touch field styles, 432-variant factorial on the bank (mode2 targetPos copy x3,
  mode2 `sourcePos=v->pos` x3, realZoom offset copy x3, zoom fieldwise/Set, targetPos
  Set(0,0,0)/direct, fieldwise `*=factor`/operator, explicitTarget Set/fieldwise): targetPos copy,
  Set(0,0,0) and `*=` forms are byte-inert; the others are worse (0.908, 0.890 and below).
  WB 0x7E3040 local map (s local_c, t local_18, factor local_1c, object local_8c, pitchAdjust
  local_12c, capped local_130, distance local_134, Z-zeroed copies local_140/14c, delta local_88)
  has no named local the bank lacks.
- v53 2^7 X/Y-through-inline-members factorial on the bank (realZoom lerp helper, distXY
  helper, `targetPos+=delta`, 90+fxPitch lerp helper, translate `addXY(Vector3&,const Coord3D&)`,
  mode translate helper, `delta=v->source-sourcePos`): **new best 0.91227** =
  `targetPos+=delta` + translate addXY together (each alone 0.854 / 0.842: strong interaction).
  Gain is local to the translate (+0x50d): pos.y now via [edi+4] where retail uses [ebx+0x50];
  t.Y is still held in xmm1 (retail stores each sum at once). X/Y candidacy unchanged.
- v54 addXY forms (ref/pointer/floats/`p.X=p.X+c.x`, one side direct, order swap): ref, pointer
  and expanded forms tie at 0.91227; the rest are worse. Banked body = `build/b4-102f83/v53/x0010100.cpp`.

## Untested next angles
1. Natural source that defeats the tail merge of the two lerps in s0 (retail keeps
   two lerp copies, xmm2 vs xmm7 divisor) — e.g. different divisor expression per arm,
   inline vs macro adjustPitch per arm, a volatile-free distinct temp per arm.
2. Raise float candidate symbols in region E naturally (WB shows ~30 locals there:
   zoom, pitchAdjust, fxPitch, distance, Z-zeroed copies) so the 64-threshold is reached.
3. Marginalize numbering over natural variants (idf landscape is 32-periodic).
