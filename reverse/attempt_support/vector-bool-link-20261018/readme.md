# vector<bool> transfer link repair

BFME 2 before/after source at 8f590175f7; published census c2c5ac8c27 (2026-10-18 11:36), retail-truth-2 rules. Restored the HEAD source and strictly prepared its object before measuring; restored the preserved repair and strictly prepared again. `link_check.py` changes from 0 to 309 LINKED bytes. These are local legacy predictions with self-strict byte-verified objects, not closed-strict or runtime evidence.

The transfer helper uses the existing rowed vector<bool>::_M_insert_aux provider rather than emitting an unused local insertion implementation and its conflicting allocator helpers. An explicit instantiation keeps the independently rowed postincrement iterator body. Both rows (283 and 26 bytes) pass the ordinary body, relocation, string, float and import checks.

Reviewed donor 64d369b90170b7e9ec917d646f020b11f13eb0d5: game/Libraries/Source/WWVegas/WWLib/RvaVectorBoolAssignment.cpp uses the node allocator; this is an applicable allocator lead, not proof that BFME 2 layouts or addresses agree. No donor source was imported. Freshness fetch found official master d348fca17814122303884ebe194cbc877a2c0bb0; reference scope is claimed by another seat. Kept the committed clean inputs; no pointer advance or success stamp.

Sibling CreateAHeroVectorBoolAssign, stlport_vector_bool_insert_aux and stlport_vector_bool_reserve still have a referenced competing _M_deallocate helper. The preserved forceinline trial did not remove it; no unchanged failed trial repeated and no improvement claimed for those units. Their claims are released for further investigation.
