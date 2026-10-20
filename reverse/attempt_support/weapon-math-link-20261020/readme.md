# Weapon math-emission link repair blocked

Base c96cf5c50e, BFME1 a2c8039e, existing flags retained. The published-index
preview b73720bed9 rejects WeaponPrivateFireWeapon.cpp (3,452 non-padding bytes)
for sin(float), cos(float), and _STL::max<int>. All nine rowed bodies pass before
editing. Current successful wrapper recipes were reviewed (strafe-sin-link-
20261013, cylinder-math-link-20261015 and FireLogicNuggetDoEffectPosition.cpp).

Three careful trials each preserve 8/9 rows; no source repair was retained:

1. Before vector, add a TU-local int max overload. Scope inline as static
   inline while including math.h. getLinearPosition and the other seven bodies
   stay exact, but fireWeaponTemplate is 1555 versus 1561 bytes: atan2f now
   inlines to double atan2 with x87 arithmetic instead of retail's float call.
2. Hide only sin/cos during math.h, then redeclare the CRT double functions
   (the FireLogicNugget recipe). Fire stays exact. getLinearPosition is still
   199 bytes, differing at +0x46..+0x4E: retail POP ECX precedes FSTP [EBP-4]
   and MOVSS; candidate schedules that POP after those instructions.
3. Add local float sin/cos overloads narrowing the double result, preserving
   the native float return rounding. Same helper scheduling mismatch, inert.

The final candidate is preserved as candidate.cpp.txt. comdat-delta.json shows
exactly the five unwanted external COMDATs removed and all retained COMDAT
bodies unchanged; the failing free helper occupies ordinary .text and is not
covered by that COMDAT comparison. Byte gate correctly refuses it. Original
source restored and rebuilt; claims released. No gain claimed. Do not repeat
these three recipes unchanged; a future attempt needs a supported declaration
or inlining boundary preserving both atan2f and the helper's POP scheduling.
The canonical function bodies and existing recovery banks are unaffected.
