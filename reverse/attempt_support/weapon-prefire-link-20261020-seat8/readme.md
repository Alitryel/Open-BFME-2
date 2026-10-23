# Weapon prefire call ownership

Inputs: BFME2 2b6164c0c1; unchanged retail-truth-2 index 5366c4f808,
2026-10-20 12:21. Reviewed BFME1 callee-owner linking technique from
daf5810bfc2d; the actual bindings below are established by BFME2 rows and calls.

Weapon::getPreAttackDelay (2CCFF0, 168 B) called an undefined semantic alias
for the existing Object::rva0028BE7F wrapper (28BE7F, 20 B). The wrapper's
rowed provisional signature takes Arg1_004DEA70 / Coord3DBase pointers and
returns void*. Bind that existing name with explicit pointer casts; interpret
EAX as signed int at the caller, as the native comparison already does.
The wrapper remains unchanged, and this does not promote its provisional
argument/return types into recovered semantic facts. Remove the old alternate
name pin rather than assigning two names to the same code address.

WeaponTemplate::getPreAttackDelay has a strong definition in Weapon.cpp.
The recovered caller's implicit COMDAT copy collides with it, even though the
separate retail-truth diagnostic marks this unrowed copy unreferenced. Make
the local visible helper inline-only with dllimport/forceinline. This repairs
the actual duplicate-name blocker; it does not suppress a diagnostic-only copy.
There are only these two indexed definers; retain the existing strong owner.

Same-index current-object LEGACY preview: caller 0 -> 168 linked B, unchanged
wrapper 20 -> 20 B. Both rows pass the ordinary byte gate and self-strict
prepare-current receipts. No closed-strict or full-link result is claimed.
No authored-byte growth or new type/layout claim. No shared header changed.
