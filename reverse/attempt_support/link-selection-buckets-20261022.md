# SelectionTranslator bucket helpers

BFME 2 input: c56d7477f7; census ae3b3e68e2 (2026-10-22 11:05).
The translator's already matched int/bool membership map emitted two competing
helpers: const vector<void*>::operator[] and the one-argument _M_bkt_num_key.
The first differs from the link's first copy; neither has a retail address.
They are referenced helpers, not the unreferenced diagnostic copies exempted
by retail-truth-2. SelectionIDMap already uses the import-inline subscript
specialization for this identical table. Reuse that body, and declare the
separately provided bucket helper without emitting another copy.

All three rowed translator bodies remain exact (4,145 retail bytes, including
the EBX-list helper and EH handler); eh_verify reports EXACT for its EH graph.
The literal/float/import checks, class gate and declared-definition gate pass.
link_check --prepare-current establishes a strict reusable object receipt.

Paired link_check previews use the same seven current units:
SelectionXlatTranslateGameMessage, Rva0002C7FD, FXListStoreParse, SelectionIDMap,
Armor, StlSweepW4Rva00056BFE and stlport_hash_map_string_uint_resize. Current
provider sources are required because the index predates upstream's proxy-swap
repair. Before this change the translator has exactly the two blockers above;
after it LINKS. Cohort totals rise from 2,175 to 6,320 bytes, a 4,145-byte gain.
The other four clean units were already repaired upstream and are not credited.
The two remaining cohort units retain unrelated string-hash blockers.

This is a legacy link preview plus self-strict object evidence. Closed-strict
closure was not measured and is not claimed. Local logs:
build/seat-selection-final-before.log, build/seat-selection-final-after.log,
build/seat-selection-strict.log. No pin, ledger, shared-header or class-layout
change was needed. ArmorStoreParse has the subscript blocker too but its RVAs
are claimed by another worker, so this seat left that unit untouched.
