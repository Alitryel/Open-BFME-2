# Correct the owned map's deleting-destructor identity

Inputs: BFME2 dc623d4c10, MSVC 7.1, committed TU flags; legacy census
b711de3634 (2026-10-23 14:28). BFME1 96c88c73a5cd1a58fc2f8db691beea50acd996db.

Rva0034C5E0Dtor.cpp owns 144 nonpadding bytes and initially links none.
Its 28-byte row at 0x00357E30 was named as the unsigned/void* RB-tree's
scalar deleting destructor based only on masked placement. Native calls
0x00357CD9, the independently rowed map<unsigned,void*>::~map thunk,
which jumps to tree::~tree at 0x00357C6A. The source's tree wrapper calls
0x00357C6A directly and is not the native relocation graph. Retract that
identity separately before admitting the map wrapper; do not alias them.

Verified candidate replaces the private tree specialization with a member
destructor declaration on the actual STL tree, types the owned pointer as
STL map<unsigned,void*> and deletes it normally. The 88-byte parent remains
exact; explain_mismatch confirms the emitted map deleting destructor matches
all 28 bytes including its map-destructor call. Scoped legacy preview links
144/144 bytes with the candidate (before readmission, using census byte count).
No new names inferred for the enclosing owner, pins, aliases or pragmas.

The initial candidate retained the private tree specialization: compilation
failed because map needs its full typedef interface. Replacing that view with
the actual tree destructor declaration resolves the failure. Scratch evidence:
build/map-owner-link/{trial1,trial2,map-delete,after}.txt and verified-map.cpp.
The row retraction is a prerequisite to the separately verified readmission.
