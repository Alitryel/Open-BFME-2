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

The retraction committed as 6ae33b7319. Its hook passed 2,093 bodies and
293 exact EH records across 95 dependents. It frees the remaining 116 B of
Rva0034C5E0Dtor.cpp without changing that source.

Recovery: extend the existing unretained map-emitting helper with a map-pointer
argument and `delete owned`. MSVC 7.1 emits the genuine map scalar deleting
destructor, including the call to the five-byte map destructor. add_match
verified all four provider rows, no pins or aliases added. Paired legacy preview
is now owner 116/116 B plus provider 99/99 B: 215 B versus the original 71 B,
or +144 B linked across the two separate identity/recovery commits. The recovery
commit itself contributes +28 B linked; the earlier retraction contributed
+116 B. The false 28-byte claim is replaced, so authored coverage is unchanged.
