# Material-pass pool ownership repair

Inputs: BFME2 4011fba966; unchanged retail-truth-2 index 5366c4f808,
2026-10-20 12:21. BFME1 reference revision 92f6bbe8e1dcdb46b5d27da0674313efc822b790,
GeneralsMD WWLib/mempool.h, confirms the private allocator and null-accepting
operator delete. BFME2 dx8renderer.cpp supplies the existing owner copies.

The procedural-material-pass unit emitted a 16-byte pool delete, missing the
native 1449E0 null guard (20 bytes). Adding the guard preserves the 146130
render body, but alone leaves two different COMDAT copies. Their relocation
names expose a public/private mismatch: allocator access was public (mangled
2V) in this view and private (0V) in dx8renderer.cpp. Align the declaration
with that owner, and remove this view's one-byte explicit allocator definition;
its ObjectPoolClass is declaration-only and must not own pool storage.
The class static member declaration now references the existing pool owner.

Both the 1449E0 delete and 144D30 scalar deleting destructor now have the
owner's full bytes and relocation names. Their unknown retail-truth verdict
still reflects the allocator's lack of a verified data address; do not promote
this local-copy equality into an independently verified global layout/address.
The earlier allocator data-row admission blocker remains recorded separately.

Same-index current-object LEGACY preview: render unit 0 -> 164 linked B
(165-byte ledger extent including padding). Ordinary byte gate 1/1 and
self-strict prepare-current receipt pass. No closed-strict/full-link result,
new authored bytes, pin, data row, or shared header change is claimed.
The indexed blocker map contains no other unit blocked by this AutoPool name.
Diagnostics: build/seat-matpass-before.txt, seat-matpass-delete.txt,
seat-matpass-scalar.txt, seat-matpass-final2-link.txt and final2-strict.txt.
