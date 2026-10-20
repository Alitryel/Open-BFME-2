# Actual compiler ownership for two placement-copy helpers

The two legacy dup rows in stlport_construct_game_structs3.cpp borrow existing
_Construct compiler symbols through object-symbol notes. Neither actual name
has another function-row owner; the opaque-record helper's existing pin is at
the same address. No code or pin needs to be invented to own these bodies.

Strict current-object verification confirms both complete 45-byte bodies and
their entire native EH graphs EXACT, under the original compiler flags.
The source already emits those actual names. Replace the ledger aliases with
them, retaining reference provenance and uncertainty about original source
spelling and application identity. The native null guard and copy-constructor
call establish the placement-copy operation; the STLport helper name is carried
from the reference implementation. The opaque 1432-byte record view is inherited.

BuildListInfo construction at 0032A2AF uses handler 0077B52B, and opaque-record
construction at 00557C36 uses handler 007992B1. Both handler addresses and their
cleanup bodies already have real owners in other units. They are preserved;
no second name, pin or byte claim is added there. No source body or calling
interface changes; the comment is updated to describe current ledger ownership.

Result: two object aliases and their register entries removed, zero new unique
retail bytes. Normal complete-unit and EH verification remain required.
