Scene constructor 1040D5: class-contract prerequisite, Astra s2, 2026-10-23

Input 7cbf59f151, donor138757e9, census491a8b3d87; existing MSVC7.1 flags.
The prior 82119 attempt reports a duplicate ctor. That blocker is now absent:
Rva001041BDASlot1.cpp already makes its inline ctor dllimport/forceinline.
The current constructor still lacks a destructor provider; the 104BDA caller
also has six unprovided virtual names and a competing table (before-link.txt).

Diagnostic removal of the explicit Rva001040D5 dtor declaration preserves the
18-byte constructor. Legacy preview reports +18, but it is not a valid class
repair: COFF proves the ctor emits a 4-byte table, placing its deleting dtor in
slot0. The caller emits 28 bytes (7 slots) with that same wrong slot0.
Retail BCF6F0 is 112 bytes (28 slots): slot0 is RefCount DeleteThis at6CE57,
slot1 is folded deleting dtor1042CF, and slot23 is the rowed method104956.
The native table equals SimpleScene BD33D0 everywhere except slots1 and23.
The complete slot RVAs and both generated table relocation lists are in
vtables.json. The diagnostic is deliberately reverted; no linked gain claimed.

Native1042CF calls the five-byte destructor740555, already owned under
Rva00740555, then global delete. A different SimpleScene-derived constructor
740157 also uses that folded destruction path, so these classes must not be
merged just because they share the destructor. An honest repair needs full
28-slot views, the native folded destruction relationship, and consistent
slot23 ownership with Rva001049C7AddTriangle.cpp, whose current base view is
also incomplete. The existing shared bfme2scene/scene.h explicitly omits
slots17..19 and says it does not assert a complete table; the constructor
provider SimpleSceneClassConstructorBFME2.cpp has the fuller local contract.

No flag/control-flow/inline trick can supply the missing virtual providers or
correct the observed table extent. This is a concrete class-contract/provider
prerequisite, not a remaining byte-scheduling mismatch. No pins, headers,
ledger functions or production sources retained. Reverted original verified
with the focused byte gate. Next: reconcile the measured complete class views
and independently prove any folded aliases before claiming link closure.
