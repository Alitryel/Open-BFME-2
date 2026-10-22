# FXShaderAsset parameter bindings (2026-10-22)

At BFME2 54a8cbdce5, the published 2026-10-22 17:08 census
(08160bc2c9, retail-truth rules carried by its index) and current explicit
fxshaderasset.cpp object report two undefined calls and a losing record copy
constructor. After this change, the same explicit legacy check reports LINKS,
0 -> 1,007 non-padding authored bytes. No closed-strict gain is claimed.

Target evidence: Load's native calls are already pinned to 0x151597 (default
constructor), 0x2B230F (+4 dword setter), and 0x1513AD (record copy). These have
rowed owners Rva00151248, Rva0042CBB6::rva002B230F(int), and the existing
Rva0007BB16Record copy constructor in StlportVectorGrowthFootprints.cpp.
The constructor provider establishes handles at +0/+8 and fields at +4,
+C..+1F/+20, matching the loader's existing 36-byte record view. This does not
recover an original class name. The folded setter's owner name is a binding,
not a claim that the two original classes were identical.

Use Rva00151248 as the record's storage base and an imported forced-inline
forwarding constructor. An imported forced-inline SetType calls the existing
setter via its rowed view. Declare the copy constructor so the kept retail
copy is used. No pins, aliases, or ledger extents are added.

Trials: forced-inline wrappers without dllimport emitted a non-retail default
constructor COMDAT. A qualified constructor call in the original record body
(as in fxshadersetup.cpp) initialized both string handles again before calling
the native constructor, changing Load and its EH state. The storage-base form
avoids that second initialization and passes the byte gate.

Acceptance: link_check.py --prepare-current on the changed unit passes 7/7
rows, 12 literals plus one empty reference, both named imports, its data row,
and both parent-derived funclet bindings. This is self-strict verification;
provider closure was not certified. find_declared_unmatched and check_csv pass.
The final ordinary explicit link_check reports LINKS +1,007 B. Sibling sweep:
fxshadersetup.cpp already has a constructor binding and copy declaration; it
has unrelated assignment/virtual-signature blockers and live foreign claims.
The record-vector assign/destroy units already link with current objects;
no change or gain is credited for them. Compiler flags remain unchanged.
