# Define the missing key/value placement copy

Two current consumers declare the same one-parameter `_STL::_Construct`
template but supply no definition: NameKeyGeneratorMapInsert.cpp and
PickAndPlayUnitVoiceResponse.cpp. The existing pin only resolves byte
verification; it cannot supply a definition to the linker.

The native 37-byte allocateNode body at 3ED191 allocates a 12-byte node,
zeros its first word, and passes node+4 and the source to 60C9D9. The whole
23-byte target tests the destination, then copies two words. The existing
value_type view is an integer key followed by a pointer, eight bytes total.
This establishes the placement-copy behavior and storage relationship,
independently of a donor's application names. Existing application/type
identities are retained, not newly inferred from this trivial copy.

Supply the previously declared template with real placement construction:
`new(slot) Element(source)`, using the compiler's normal `<new>` header.
Keep it out of line so its callers retain the native call. The algorithm is
the STLport 4.5.3 placement-copy operation in vendor/stlport/stl/_construct.h;
the existing one-parameter declaration is preserved. The BFME1 reference
review at 0bf534ea7ccde110c456edb9cd2dd5dae823c953 includes its reverse-key
map insertion in game/GameEngine/Source/Common/NameKeyGenerator.cpp. It
supports the subsystem relationship, not identity of this trivial body.

An isolated compile first produced exactly all 23 native bytes and zero
relocations. A separate fresh compile of the original source then proves
that all eight existing bodies and every relocation remain identical to
the production object. The supported add_match --icf-owner path verifies
the new instantiation against the existing pair<const int,int> body at
60C9D9. The row records fold-proof=NameKeyGeneratorMapInsert.cpp. No new
pin, alias, synthetic copy constructor, header or compiler flag is used.

The normal gate passes all 9 provider rows and all 80 unchanged consumer
rows, its one data row, 31 literals and two float constants. The provider
has a strict current receipt. The consumer/provider EH check is 4 EXACT,
with no baseline or missing object. The frozen-file check passes; the
follow-up placement scan serves zero bodies and zero pins.

Paired previews against the same published index change both consumers
from unresolved to LINKS, with no other blocker. Per-file accounting is
8622 bytes. Excluding the newly rowed 23-byte ICF copy, already present
under other linked owners, gives a conservative 8599 existing unique-byte
gain. This is predicted linking progress, not new C++ coverage, a fresh
census, or an executable smoke test. Earlier attempt 59610 warned that
deleting the local insertion bodies changes the large routine's stack;
this repair keeps all of them and leaves that source untouched.
