# Army swapper vtable prerequisite

At cc4948c0b1, the current legacy preview leaves the 132 nonpadding bytes
in Rva005F4DC4Create_Rva005F4EE8.cpp blocked by its vtable COMDAT.
No source change or compiler trial was made.

Retail data at VA C794E4 contains six function pointers, independently read
from game.dat: 9F4ECC, 9F4B48, 9F4B52, 9F52C0, 9F5331, 9F53A2.
The constructor unit's private class view emits only two entries; the first
kept copy from OpaqueScalarDeletingDtorsB17.cpp emits only its destructor.
The ArmyUnitSwapperMovieClip base's six-slot contract is already visible in
Rva005FD9FFDtor.cpp and Rva005FD788Apt_ArmyUnitSwapperMovieClip.cpp. Its native
table at C7A2E8 contains FDA1D followed by five B3FD0 no-op entries (RVAs).
Consequently, merely adding the four base declarations would give the derived
table the wrong inherited targets.

The remaining derived overrides are already matched, but under independent
address-derived owners: Rva005F4B52::rva005F4B52 in VslotSmallBodiesAJ.cpp,
Rva005F52C0::rva005F52C0 and rva005F5331 in StrategicUiArmyDragDrop.cpp, and
Rva005F53A2::rva005F53A2 in StrategicInGameUIArmyUnitSwapperValidation.cpp.
Resume with a shared class contract and reconcile those provider identities
and all competing vtable views together. New aliases or pins would conceal
the conflict. Native slots establish relationships, while the original
derived class identifier remains unknown.

The census index is retail-truth-2 at 5366c4f808, dated 2026-10-20 12:21.
This investigation claims no linking gain or closed-strict result. Scope and
destructor claim attempts returned unconfirmed origin errors; the confirmed
constructor/EH/synthetic-provider claims were submitted for release. No dirty
code or banked reconstruction remains. Current session's verified improvements
are separate commits fb344ec7fb (+663 B) and cc4948c0b1 (+384 B), with paired
self-current legacy evidence in their respective attempt_support directories.
