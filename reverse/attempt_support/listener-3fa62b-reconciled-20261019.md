# Listener3FA62B coherent lifecycle

This completes the class repair identified in listener-3fa62b-vtable-20261019.md.
The constructor, destructor, callback, clear, allocating caller and LivingWorld
cleanup consumer now share the20-byte Rva003FA62B declaration. Native210D1D
allocates20 bytes; vector at4 contains8-byte records and owner is at10hex.
RegionTurnObserverView supplies two int-int callbacks and a nonvirtual destructor.
DerivedC378B4 overrides slot0 with119B3FA464 and inherits RET8 at50B238.
BaseC62A20 contains two50B238 entries. Both complete tables are emitted identically
by the constructor and destructor, and all four table copies and full target
bodies were verified from current official objects against retail.

Callback and clear owners are renamed in place; no new pin or alias hides
the earlier wrong vtable. The destructor's two zero-argument alternatename
directives are gone. The allocating caller no longer declares a separate
opaque class; the cleanup consumer uses actual STLport vector declarations
instead of duplicating its template view. Other verified caller behavior
and its existing neutral types are retained.

All10 existing rows in6 changed sources match. Same13:17 census comparison:
5/6 units and783 bytes before;6/6 units and858 bytes after. Constructor75
is newly linkable. Both constructor and destructor install handler78448C
with FuncInfo930668; their entire associative EH graphs match.
Cleanup784479 calls whole7-byte RegionTurnObserverView destructor4EDFFF;
cleanup784481 calls whole14-byte vector<BfmePod8> destructor7FAB3.
Both emitted callees were independently verified, including relocations.
No new unique C++ bytes are claimed by this class repair alone.

Automatic class_contract discovery finds no private views once they move to
the shared header; its empty majority/default size0 was replaced by the
explicit native allocation, field, lifetime and table evidence above.
The header enforces record size8 and complete listener size20.
Original class/interface/record identities remain unknown.
