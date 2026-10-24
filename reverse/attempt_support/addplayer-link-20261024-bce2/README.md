# AddPlayer linking repair

Native parent: 0x002BA8F1..0x002BAA3D (332 bytes), plus the native 10-byte
unwind action at 0x0077678F and 10-byte handler at 0x00776799.

The published census at 18891aea67 (2026-10-24 11:12) reported four unresolved
legacy player methods and one losing player-vector growth COMDAT. Current
ledger owners already implement all four native targets:

- Constructor 0x002E2903: Rva002E2AAE in LivingWorldPlayerDtor.cpp.
- Color setter 0x002E0F91: LivingWorldPlayer::SetColorIndex.
- AI attachment 0x002E0648: Rva002E0648Owner::rva002E0648.
- Initialization 0x002E3518: LivingWorldPlayer::InitBuildableHeroes.

This consumer uses those existing declarations. The 0x3C8 allocation and
field offsets come from the target body and verified physical constructor;
the address-qualified field view preserves unresolved layout/name questions.
No new identity is inferred from the match. Existing owner evidence includes
reverse/attempt_evidence/player-owners-astra-high-d-20261012.txt and the
provider ledger records; WorldBuilder naming provenance remains with them.

The typed player-pointer vector is retained. The game allocator settings
already used by stlport_moduledatavector_push.cpp remove its nonretail growth
copy and make the three old allocator/clear suppression declarations
unnecessary. The four emitted typed helpers (allocator 28B at 0x00068E15, fill_n 32B
at 0x0007E48F, growth 140B at 0x002DFCF6, and push_back 49B at
0x004DFCB0) are admitted through add_match --icf-owner against their
existing owners. Each complete body and all relocations match. They record
the genuine fold chain behind the old push_back pin, with zero unique-byte
credit. No provider source, new pin, shared header or gate is changed.

An initial diagnostic dispatch through the generic pointer-storage provider
changed pointer alias analysis, stack slots and register allocation. A separate
storage local still added a stack slot. Both variants were discarded. Keeping
the application type and correcting the allocator profile preserves every
native byte and its EH graph, while resolving the linker blocker.

Validation:
- Normal build: 97/97 rows across consumer and four provider files, plus one
  data row; five string literals and four compiler float literals verified.
- The subsequent four ICF admissions pass all 7/7 consumer/helper rows.
- Consumer EH: EXACT (one complete associative graph).
- link_check before fold admissions: LINKS; 342 existing parent/handler bytes.
  After admitting the 249 already-owned helper bytes and refreshing 1,902
  providers: LINKS; the tool reports 591 row-bytes for this unit. This is not
  a claim of 591 newly recovered or uniquely unblocked bytes. The old
  generated unwind row is not included in this linking metric.
- Final code identity check: 7 rows and zero new findings.
- find_declared_unmatched and check_csv pass.
- place_bodies rescan: zero new bodies or pins.

This is a linking repair with zero new unique C++ bytes. No link-cycle or
runtime run was performed. The unchanged global declarations and remaining
address-qualified field views are outside this local call/allocator repair.

The pre-commit shadow data checker also reports the two unchanged store
global spellings as wrong-name. Those declarations predate this repair; the
enforced converged-data check passes. Their broader type reconciliation is
not claimed here. The typed push_back shadow binding was investigated and
resolved by the complete helper-chain admissions above.
