# UpdateUMVBorder row-distance and loop-lifetime follow-up

Approved spec001b96a0 and retail1047B only; no external decoder source read.
Read the complete latest1042B bank, its s9 handoff and all prior log entries.
Normal isolated explain_mismatch reproduces its first difference +43 and
280/353 aligned instructions (501 positional bytes). Keep that stronger bank.

New hypotheses tested with ordinary C++ and isolated objects:

- Express chroma bottom destinations as top + a fixed row distance, either
  directly or as border*stride - (source - bottom). Reusing a named chroma
  border*stride value yields1056B/235 aligned; without reuse1056B/122. The direct
  destination difference yields1019B/127. None beats the1042B/280 bank.
- Explicit signed row guard followed by a do-loop, with either countdown or
  zero-based induction, changes the first-iteration pointer lifetime. These
  emit1039..1055B/106..241 aligned; int-promoted first samples do not fix it.
- Three meaningful local aggregates (left/right edge pairs; one plane edge
  group; paired source/destination edge sets) all emit1042B/229 aligned and a
  different frame, rather than native spill locations.
- A force-inlined read-and-advance cursor reference is identical with byte
  return; int return emits1039B/131. Moving the first source advance immediately
  after its left memset instead of before it emits1055B/133. These do not reach
  native's direct MOVZX plus mid-fill pointer reload.

No compiler sweep, source scheduling barrier, assembly, volatile variable,
equal-arm branch, fabricated helper effect or pin was used. The remaining
native evidence is unchanged: Y loop entry/reload and spill-slot rotation;
chroma SHR timing; repeated border*stride-source+bottom distance; associated
alignment padding. Four concise source patches and the complete measurements
preserve the tested hypotheses. The existing1042B bank remains unchanged and
no failed reconstruction is left in Code. No new emulation claim: these trials
did not improve matching enough to replace the already reviewed bank.
