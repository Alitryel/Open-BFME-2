BFME2 ef1bb71293, census 5366c4f808 (2026-10-20 12:21).
Current paired link preview initially rejects both units solely for the
vector<bool> destructor, which differs from the kept copy and has no proven
retail address. It is referenced, so retail-truth-2 does not exempt it.

Declare that specialization externally in both units, following existing
PartitionManager.cpp, DockUpdateCtor.cpp and BaseHeightMap_Rva00069F4F.cpp.
The already external base destructor and all constructor/unwind code remain
unchanged. No new pin, layout, copied implementation or global is introduced.

Self-strict preparation before/after passes all 10 matched rows, 1 data row,
20 strings and named-import checks. EH: 1 EXACT. Converged-data check clean.
Legacy same-index paired current-object preview: 0 -> 2,057 bytes
(AptOptionsConstructor 1,972; stlport_vector_bool 85), both now LINKS.
This is not a closed-strict/full-link or runtime measurement.

The same-name sweep also finds CreateAHeroDataCopy/Ctor,
AptScoreScreenCallbacks, Rva00441ECEPermuted and BaseHeightMapConstructor.
Those have independent unresolved providers and other COMDAT conflicts;
they are unchanged because this isolated cause would not link them.
BFME1 92f6bbe8e linking evidence and ShroudManagerImpl008FBD00.cpp reviewed:
the donor's explicit inline empty vector destructor is not needed here.
The established BFME2 declaration strategy preserves its own target bytes.
