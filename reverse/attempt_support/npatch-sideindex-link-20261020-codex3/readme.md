N-patch SideIndexInfo linking repair

Parent 36d4c662e6. The 663-byte Init_For_NPatch_Rendering row at 0x00172F90
passes strict current-object preparation before and after this change.
The consumer's empty SideIndexInfo default constructor disagrees with the
retail 15-byte constructor at 0x00171AD0, already byte-verified in
meshmdl_sidehash.cpp. That provider zeroes vidx1, vidx2 and polygon_index;
the consumer now uses the same definition. The resulting Entry constructor
and Re_Hash copies also reproduce their retail owners (0x00171E50 and
0x00172600), removing all three COMDAT blockers. The parent sets every field
of each local SideIndexInfo before use, so those initializations disappear
there and the entire parent remains byte-exact.

Donor review: BFME1 92f6bbe8e1dcdb46b5d27da0674313efc822b790,
game/Libraries/Source/WWVegas/WW3D2/meshmdl.cpp, has the empty constructor.
It establishes the record's purpose and shape; the zero initialization is
established independently by BFME2's rowed constructor, not the donor.
An rg sweep finds only these two defining BFME2 units, completing this cause.

Acceptance: strict preparation and normal byte/literal/import gates 1/1,
no EH rows, converged data check clean, declared-definition check clean.
Paired legacy closure prediction against unchanged census 5366c4f808
(2026-10-20 12:21): 0 -> 663 nonpadding bytes; one clean unit.
This is strict self verification and legacy closure prediction, not a
closed-strict link measurement. No new authored coverage, rows or pins.
