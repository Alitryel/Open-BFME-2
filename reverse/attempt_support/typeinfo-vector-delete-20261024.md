# type_info vector deleting destructor: real C++ recovery

BFME2 base: 2c7d0eefe5. Pinned BFME1: 32774ab03393709a7f14331ba8d98d281a55ffd9.
Native ti_inst.obj independently supplies the names and complete extents:
private copy constructor 0062903D,11B; vector deleting destructor00629048,75B.
This replaces the75-byte attached library owner with genuine MSVC7.1 C++.

The TU preserves every shipped typeinfo.h method, access level, field and
12-byte layout. The existing copy constructor remains its native empty body.
A default argument on that same private copy declaration and unreachable
array-new request compiler vector-deletion emission. These are disclosed
source adapters, not original-API or executed-allocation claims. No new
constructor overload, parameter, virtual slot, opcode or assembly is added.
The compiler's unreferenced11-byte default-argument closure and primitive-int
RTTI descriptor have no claimed retail address and add no recovery credit.

Native producer visibility is independently established: the destructor
callback is a direct thunk address and its ordinary call is REL32. Keeping
_CRTIMP dllimport yields77 bytes and IAT references, correctly rejected.
Declaring array delete yields the right instruction shape with the WRONG
free target; the final source keeps CRT producer scalar-delete visibility.
Both free paths reach the already-owned scalar operator delete at0002FD60.

All five final relocations are independently native:

| Offset | Kind | Target |
| --- | --- | --- |
|15|DIR32 callback|type_info destructor thunk00629BBA|
|28|REL32|vector destructor iterator00629110|
|39|REL32|scalar operator delete0002FD60|
|52|REL32|type_info destructor thunk00629BBA|
|63|REL32|scalar operator delete0002FD60|

Retail thunk00629BBA is FF25 through VA00BBA434. The actual PE imports
msvcr71.dll's ??1type_info@@UAE@XZ at that slot. pin_admission accepts this
first real name over the existing generated Ji_type_info placeholder;
no second real identity or weak-name binding is introduced. The tool alone
writes its pin and admission grant. Its incidental register normalization
only shrinks older entries or drops old stamps; no verifier policy changes.

The new compiler-generated type_info vtable is one4-byte slot, pointing to
this vector destructor, exactly matching native VA00C7C730. Its next bytes
belong outside that table. This corrects the old copy-only TU's scalar-G
vtable copy. The vtable is independently checked evidence, not a new data
coverage claim.

Independent worker repeated full75-byte and11-byte comparisons with all
relocations resolved, no masks and no unresolved calls. Normal production
add_match --replace-existing then passed both whole-file rows and all
literal/import checks. find_declared_unmatched passes. Whole-file placement
rescan finds zero additional bodies or pins. Provider/link preview is recorded
separately; no census, final-link runner or runtime execution is claimed here.

## Provider check

Published index a9f880ad06 already marks the original11-byte copy constructor
as a duplicate of the same strong11-byte definition in ti_inst.obj. A /Gy
control preserves both exact bodies but does not resolve that inherited
strong-definition conflict, so the unnecessary flag was removed. The new
ledger retires ti_inst.obj's final row; the complete75-byte function now
belongs to the existing C++ TU. A bounded current-ledger provider overlay
may therefore remove precisely that obsolete archive member. This is an
in-memory preview, not a published census gain.
