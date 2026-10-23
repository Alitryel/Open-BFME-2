# Two Geometry bounds-copy helpers

The newly exact W3DVolumetricShadow::updateMeshVolume TU emits complete matches
for two previously unrowed eight-byte functions: 0x000F0FBD adds 0x1C to ECX and
tail-calls the 24-byte box-copy provider; 0x000F0FC5 adds 0x34 and tail-calls the
16-byte sphere-copy provider. Each has one REL32 relocation and no other holes.
The two functions are adjacent and end at 0x000F0FCD, the owned shadow-mesh
GetPolygonIndex function. The existing Geometry constructor occupies
0x000F0F98..0x000F0FB8 and its destructor forwarder occupies F0FB8..F0FBD.

Names and source structure come from the Geometry class in the official
Open-BFME-1 W3DVolumetricShadow.cpp at verified revision
92f6bbe8e1dcdb46b5d27da0674313efc822b790, itself derived from Zero Hour. The target
establishes entry boundaries, calling convention, member adjustments and copy
operations. The exact 3369-byte volume updater independently supports the typed
box/sphere storage relationship; the existing constructor/allocation/destructor
family supports the Geometry owner. Geometry and the setter names remain
**donor-carried identities**, not independently debug-named target facts.
No direct entry xrefs independently prove their original names. Folded callee
names alone would not establish member types.

This supplies the typed source relationship missing from the earlier
Rva000F0FBDPendingIdentity/Rva000F0FC5PendingIdentity records in
reverse/attempt_evidence/crack-j-final-boundaries.json. That attempt considered
canonical Region3D/Region2D guesses and could not legitimately introduce private
copies of those classes. This recovery adds neither Region class nor a new
copy-provider name/pin. Existing AABoxClass copy and SphereClass assignment
bindings already reproduce the two target call destinations.

The definitions live with the already matched Geometry constructor/Create and
volume allocation methods in W3DVolumetricShadowAllocateShadowVolume.cpp. Its
current explicit field views already contain AABoxClass at +0x1C and SphereClass
at +0x34. Only the real external copy declarations and the two setters are added;
the existing compiler flags, layouts and sibling behavior are preserved.
This avoids adding rows to the new updater unit whose existing link blockers
have not yet entered the published census. Before editing, the chosen home
passed find_declared_unmatched and link_check predicted 444/444 bytes linked.

Discovery: normal place_bodies on the two newly landed renderer TUs, without
--apply. Initial normal explain_mismatch from the updater TU verified all eight
bytes of both functions. The official add_match_batch and normal build.sh gates
verify their final home and every existing sibling before admission. No new
pin, alias, absolute datum, canonical header or verification rule is needed.
The finite independent review agreed that the new typed family evidence supports
this qualified donor transfer. No byte-placement-only name inference is claimed.

Final home results: add_match_batch and `bash ./build.sh` both pass all 8/8
rows, including the parent's two compiler EH rows; the EH-derived funclet mapping
accounts for its new compiler label. find_declared_unmatched passes. The normal
link preview reports the home links cleanly with 444 -> 460 matched bytes.
