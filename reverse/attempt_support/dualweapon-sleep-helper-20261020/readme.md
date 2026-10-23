# DualWeaponBehavior::update: the real normal-sleep helper

Session 2026-10-20, gpt-6.1-sol. BFME2 input `063b128c47`, BFME1 reference
`92f6bbe8e1dcdb46b5d27da0674313efc822b790`. The existing bank
`reverse/attempts/0x0045af14.cpp` is unchanged; no Code definition, pin, or
function row was added. The home unit is
`Code/GameEngine/Source/GameLogic/Object/Behavior/DualWeaponBehaviorCtor.cpp`.
Its existing definitions were all matched before this work.

## Target and additional reference evidence

Native RVA 0x0045AF14..0x0045B123 is the complete 527-byte RET0 update.
The existing constructor/vtable and module-data parse evidence identifies
DualWeaponBehavior and its update receiver. The WB twin at VA 0x0117D920
contains inline BitFlags assertion labels; those labels are not the owner's
method name. All earlier log entries for this RVA were read, including the
retracted old no-boundary verdict and the rejected semantically wrong farm
bank. Only the current corrected bank was used.

The WB twin makes seven calls to VA 0x0117EDF0 at its ordinary sleep returns.
Inspection of that entire 16-byte helper shows an ordinary thiscall prologue,
a load of the global at WB VA 0x021C7174 into EAX, and RET0. The receiver is
saved but unused. Native ordinary returns load the already-established
`BfmeLogicFramesPerSecond` global (VA 0x00DBA4E4). This supports an inlined
class sleep getter instead of the bank's direct global expressions; neither
the original getter spelling nor its const qualification is established.

## Tests and result

The home compiler command supplies region defaults `/O1 /arch:SSE /G7` plus
the source's `/GX /MD /DNDEBUG`. Scratch files do not inherit that region:
the preserved generator explicitly supplies the same flags. A first diagnostic
run without the region flags was discarded, not used as evidence against the
hypothesis. The corrected baseline reproduces 527 bytes, all callees resolved,
and the known 30 differing instruction tuples (fitness 0.91042507 under
`permute.fitness`, a different metric from the bank's aligned 137/167 score).

Tested 40 combinations of:

- direct global return, free inline getter, member getter, or const member getter;
- unchanged action bodies, inline free/member set-close actions, or inline
  free/member ensure-close actions (the latter include the real flag guard);
- ordinary inline versus forceinline.

The genuine getter alone is byte-inert. None of the action helper forms improves
the complete baseline. The generator compares full resolved function bytes;
unresolved outlined helper cases are not successes. No score-only or masked
branch claim was accepted. `results.json` preserves the individual outcomes.

The unresolved native difference is still the location of the shared set-close
block: native hosts it at the mounted/forced-close arm, before the timer block;
the bank hosts it after that block in the live-victim arm. Previous control-flow,
source-field, lifetime, flag, and math-shape experiments already described in
`reverse/re_attempts.log` remain applicable. This new WB-evidenced helper
visibility explanation does not close the gap. Preserve the corrected bank,
release the claims, and do not repeat these helper spellings without new input.

To reproduce, copy `probe.py.txt` to `build/dual_weapon_probe.py` and run it
from the repository root with the normal build environment. It uses official
`permute.Scorer` with isolated objects under `build/dual-weapon-probe`, never
the production object's cache path. No production file needs replacement.
