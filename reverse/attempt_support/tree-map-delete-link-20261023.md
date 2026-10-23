# Tree/map deleting-destructor identity repair

Inputs: BFME 2 a34d6be94c plus Player provider repair d1355e6cde;
published census b711de3634 (2026-10-23 14:28), with both named units'
current objects substituted by link_check.py. BFME 1 remains at verified
96c88c73a5cd; no donor code was needed for this repair.

Retail 0x00357E30 is a 28-byte scalar deleting destructor. Its call at +3
targets 0x00357CD9, the rowed unsigned-to-pointer map destructor, whose
five-byte body jumps to the rowed tree destructor at 0x00357C6A. The second
call targets operator delete at 0x0002FD60. The ledger instead assigned
0x00357E30 to the tree's scalar deleting destructor in Rva0034C5E0Dtor.cpp.
That emitted wrapper calls the tree destructor directly. The byte gate could
resolve the tree destructor through the map's jump, but the current link
correctly rejects the wrapper's relocation identity.

Retract that false tree-wrapper claim separately before admitting the actual
map wrapper. The owning Rva0034C5E0 destructor directly calls 0x00357C6A in
retail and remains correct. No authored C++ change or alternative-name alias
is needed there. Once unrowed, its unused implicit tree wrapper has no retail
address and is exempt under retail-truth-2.

Before retraction, current-object legacy preview: Rva0034C5E0Dtor.cpp 0/144 B;
stlport_tree_dtor_00357C6A.cpp 71/71 B. This is a legacy preview against the
published index, not a closed-strict link-cycle measurement.
