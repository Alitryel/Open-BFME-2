# W3DCamTransform 0x102F83, r54 (2026-10-21, claude-opus-5-5, ~150 min)

Bank unchanged: reverse/attempts/0x00102f83.cpp (r53 hack-free body, fit 0.878;
permute.py 30 min: start 0.8793, best 0.8798 only with /GX- plus two statement
swaps, "no gain in 600 trials"). Read the r53 readme first; nothing below repeats it.

Residue (unchanged): retail never register-allocates sourcePos/targetPos X/Y
(memory operands such as `subss xmm0,[ebp+0x58]`, tx loaded twice in
`(sx-tx)*r+tx`, no reloads after calls, each result stored immediately). Only
the Z pieces live in registers, from the targetHeight join at +0x7B5 (sz xmm1,
tz xmm0, stores written through). Ours puts X/Y in xmm0-3 from the translate step
on, reloads them after findObjectByID, and sinks the stores. Metric used: the count
of `(sub|add|mul)ss xmm,[ebp+0x58|5c|68|6c]` memops is 32 in retail and 18 in ours.

Trials this session (sc.py fit; the bank scores 0.8684 on the same scale):
- callee visibility: transitionLiveMode body removed from the TU gave no change.
- compiler settings: permute --flags closed 0 of 1.
- variable lifetime: block-local source/target pairs (v1, v3) 0.8075.
- declaration order (v4) 0.8685, no gain.
- types/layout: pointer views (t2) 0.788; Vector3 translate (t5) 0.8036;
  `sourcePos*=factor` (t6) gave the same bytes; partial type-punned XY views
  (a1-a4) 0.76-0.80 with the region unchanged.
- numbering: XY reads only through inline accessors (n1, n2) 0.8047 and 0.852,
  region unchanged.
- control-flow diagnostics: removing the realZoom XY adjust (e4, not semantic)
  gives 0.8900, and the fxPitch>1 adjust then reads sx per statement from memory
  like retail. So the realZoom adjust holding X/Y in registers into the join
  drives the whole-function choice. Removing the near-adjust, the hold or the live
  block (e1/e2/e3/e5) is worse.
- live-block statement order (s4.py): WB order (source XYZ then target) 0.8632;
  WB tz form without targetHeight 0.8545/0.8561; best was
  `sourcePos.Y,Z` += pos before the target updates and `sourcePos.X` += pos last
  (f4) at 0.8719. That matches retail's store order at +0x78A..+0x7C3, which writes
  sy first, then tx and ty, then sx last. It does not change the memop metric.

Next angle: find a semantic realZoom-adjust spelling that keeps tx/ty out of the
held web the way e4 does. Leads: reciprocal reuse shared with the else adjust,
adjust after the join, or a by-value helper.
