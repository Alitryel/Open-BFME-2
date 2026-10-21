# Bridge scaffold link repair, 2026-10-21

Baseline 98a005d5fb; published census 17918792f6, 2026-10-21 09:22.
The unchanged BFME1 reference reviewed by the earlier link seat remains
5987fd1b859e86801d093256eadc6fb63d87785f. This follows the established
UpdateModule virtual isolation repair; it asserts no new donor identity.

The active unit owned three matched setter bodies, plus unverified ZH
BridgeScaffoldBehavior destructor, CRC and load-post-process definitions.
The unverified destructor emitted incomplete base/helper copies and vtables
referencing DISABLEDMASK_NONE; the CRC called undefined UpdateModule::crc.
Preserve those two unverified definitions, their flags, includes and license
in BridgeScaffoldBehavior.cpp.txt. No matched definition or row is removed.
The load-post-process body remains because it does not block linking.

All three whole bodies and their references pass self-strict byte checks
before and after (before-gate.log, after-gate.log). Both previews use all seven
related current source units against the same external legacy census:
6/7 -> 7/7 clean, 995 -> 1117 matched nonpadding bytes (+122).
No previously linked related unit regresses. No new COMDAT variant is added.
These are bounded legacy link predictions with strict byte receipts on the
changed unit, not closed-strict closure or runtime measurements.

A separate FireSpread trial preserved all four rows but gained zero: its
matched constructor still emits its own vtable, needing the removed dtor/CRC
plus DISABLEDMASK_NONE. The source is restored and the blocker is recorded
in re_attempts.log; no failed reconstruction is left active.
