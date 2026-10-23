# Existing rendering, deque and stream providers

Move existing, independently named matched rows from three blocked owners to
already-emitted exact copies in providers which link. The complete emitted
bodies and all relocations were checked against BFME 2 retail, with zero
unresolved relocations. This establishes no new name, donor identity or layout.
Original provenance notes are retained; no source, header, ABI, pin, alias or
compiler flag changes. The receiving basic_stringbuf constructor EH graph is
exact. The BFME 1 donor comparison and pointer verification are recorded in
../link_library_providers_20261023/readme.md.

Before: scoped legacy link_check, 14/17 units link, 13,134 B.
After: 14/17 units link, 14,782 B: +1,648 linked bytes.
The 17-unit preview retains the unchanged rejected allocator provider in
both measurements; it contributes no gain. The 29 moved rows touch 16 units. Index b711de3634, retail-truth-4, SHA256
1707d876c79d52c4e34a88342706796110595063d75abb3d5ed81bd080c08ad7.
No self-strict, closed-strict or full-census gain claimed.

Identity before: eight existing divergent-copy shadow findings over 159 rows.
Acceptance after: all 159 rows across the 17 examined units pass the byte
gate, 10/10 EH graphs exact, the same eight shadow findings with no growth.
find_declared_unmatched passes all examined units; check_csv and
git diff --check pass. Three original owners retain existing blockers;
link_check exits 1 for those units in both measurements.


The 28-byte allocator move was refused before any row change; see
blocked_allocator.md. Its claims were released, and neither existing name
at that RVA was altered. The other 29 moves are independent of that refusal.

Publication of the previous commit rebased onto newer master and then
failed because its new Clang23 compiler is a PE64 executable and this
container defaults to a win32 Wine prefix. The pinned compiler archive and
binaries are intact. A separate ignored build/wine64 prefix runs the exact
same compiler; the normal security_cookie_check.cpp byte gate passes its
whole 14-byte body (wine64_cookie_gate.txt). No tool, source, compiler or
object was modified to solve the environment prerequisite. Publication of
this batch uses that prefix. The prior failed full gate is preserved in
previous_publish_failure.txt; the paired reference-update gates remain
recorded with the previous repair.

Moved rows (RVA, extent, old owner -> receiving owner):

- 0x001964F0, 45 B, render2dsentence.cpp -> FontCharsClassConstructorBFME.cpp
- 0x00196920, 63 B, render2dsentence.cpp -> FontCharsClassConstructorBFME.cpp
- 0x001A3720, 178 B, render2dsentence.cpp -> FontCharsClassConstructorBFME.cpp
- 0x00421B1E, 36 B, stlport_deque_e12_o1.cpp -> Rva00585B16Dtor.cpp
- 0x00421B47, 33 B, stlport_deque_e12_o1.cpp -> Rva004233F5Lookup.cpp
- 0x00421798, 21 B, stlport_deque_e12_o1.cpp -> Rva00585B16Dtor.cpp
- 0x005508CE, 20 B, stlport_deque_e12_o1.cpp -> Rva00585B16Dtor.cpp
- 0x000766E1, 20 B, stlport_deque_e12_o1.cpp -> stlport_vector_e12_o1.cpp
- 0x00585240, 23 B, stlport_deque_e12_o1.cpp -> HordeMeleeFormationFindMeleeAttackPosition.cpp
- 0x0058513B, 69 B, stlport_deque_e12_o1.cpp -> stlport_deque_e12_sort.cpp
- 0x001549A0, 22 B, render2dsentence.cpp -> Render2DSentenceDrawBFME2.cpp
- 0x00584E57, 46 B, stlport_deque_e12_o1.cpp -> stlport_deque_e12_sort.cpp
- 0x004221E6, 49 B, stlport_deque_e12_o1.cpp -> stlport_deque_e12_sort.cpp
- 0x001541D0, 16 B, render2dsentence.cpp -> Render2DSentenceBuildThaiBFME2.cpp
- 0x001883B0, 13 B, render2dsentence.cpp -> Render2DSentenceDrawBFME2.cpp
- 0x0035FF72, 4 B, render2dsentence.cpp -> W3DTerrainBackground.cpp
- 0x00665620, 10 B, render2dsentence.cpp -> W3DTerrainBackground.cpp
- 0x005858F3, 58 B, stlport_deque_e12_o1.cpp -> Rva00585B16Dtor.cpp
- 0x00584CB2, 98 B, stlport_deque_e12_o1.cpp -> Rva004233F5Lookup.cpp
- 0x004218A5, 48 B, stlport_deque_e12_o1.cpp -> Rva004233F5Lookup.cpp
- 0x001F8365, 31 B, stlport_narrow_ostringstream_dtor.cpp -> Rva003A5E78Write.cpp
- 0x001F6647, 22 B, stlport_narrow_ostringstream_dtor.cpp -> stlport_narrow_stringbuf_overflow_setbuf.cpp
- 0x001F665D, 29 B, stlport_narrow_ostringstream_dtor.cpp -> stlport_narrow_stringbuf_overflow_setbuf.cpp
- 0x001F667A, 76 B, stlport_narrow_ostringstream_dtor.cpp -> stlport_narrow_stringbuf_overflow_setbuf.cpp
- 0x001F6813, 63 B, stlport_narrow_ostringstream_dtor.cpp -> stlport_narrow_ostringstream_ctor.cpp
- 0x001F9939, 289 B, stlport_narrow_ostringstream_dtor.cpp -> stlport_narrow_ostringstream_ctor.cpp
- 0x001F9A5A, 237 B, stlport_narrow_ostringstream_dtor.cpp -> stlport_narrow_ostringstream_ctor.cpp
- 0x00585059, 10 B, stlport_deque_e12_o1.cpp -> HordeMeleeFormationFindMeleeAttackPosition.cpp
- 0x001F80F6, 19 B, stlport_narrow_ostringstream_dtor.cpp -> ParticleSystemTemplateWriteINI.cpp
