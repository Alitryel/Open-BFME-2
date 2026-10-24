# Link-repair seat handoff, 2026-10-24

Production base 49e88f596a; verified BFME 1 input advanced from f5140c1c
to 32774ab0. Published legacy retail-truth-4 census/index remains
268f876e3b (2026-10-24 02:54). No census or full link cycle was run.

Two repairs are committed with paired measurements and normal byte gates:

* fae4415772 removes unused obsolete PartitionManager filter definitions.
  The native constructor now links: 125 -> 209 unique B, **+84 B**.
  Evidence: link-seat-partition-recheck-20261024.md and its sibling directory.
* 6937fbab30 reconciles the two module-data constructor helper copies and
  LargeGroup's native table provider. The existing deleting-destructor row
  moves to its real constructor unit. Five-unit preview: 538 -> 750 unique B,
  **+212 B**; all five units link. Evidence: moduledata-constructor-link-20261024/.

Combined improvement is **+296 B in scoped legacy previews**, excluding
inherited gains and without counting the moved 28-byte row twice. Explicit
strict provider receipts passed; neither self-strict whole-tree closure nor
closed-strict gain is claimed. Authored C++ coverage is unchanged. Both full
reference-update byte gates passed (98,200 function rows, 2,179 data rows).
Complete old/new EH results agree: 11,871 EXACT, 24 existing baseline cases,
zero missing objects. See bfme1-reference-32774ab0-20261024/.

Selection covered top-30 sole/near-2, wider near-6, private-class blockers,
owner gaps, current-object cohorts, donor linking repairs, name_globals and
rehome discovery. Current sole-blocker previews already link five units
totaling 2,722 B; the later ScriptEngine destructor preview already links
883 B. None is this seat's gain. Rehome discovery examined 100 candidates;
the three exact destinations already link, so those moves were not made.
name_globals --dry-run again reports zero files/edits. repair_queue link
repeats the census leads. No matching data-back artifact exists; no ranking
was manufactured from a missing artifact.

Remaining reviewed leads need the recorded native contracts, ownership or
compiler prerequisites. DX8Skin/DynamicVector, GeometryShape, allocator
proxy and string-helper trials are not reopened merely by a model change.
High-byte private-class leaders require broad ABI reconciliation or are
foreign-claimed. BFME 1 ranked/near and refreshed ZH packets have no free
candidates; named lifted bodies remain source leads, not recovered C++.

Two final read-only checks sharpen the handoff:

* Rva006CBF40Siblings.cpp still selects seven empty complete destructors
  against retail. Their target bodies are already rowed at 6D1090,
  6D6340 (two callers), 6D63C0, 6E96D0, 6EB6A0 and 6FE460 under different
  class views. In particular, the 6D1090 owner is nonvirtual while the
  scaffold claims a virtual destructor/base. Removing the empty bodies
  alone cannot reconcile identities, ABI and provider spellings. No new
  aliases, pins, renames, source edits or build trials were attempted.
  This needs native class/ownership reconciliation, not missing-body recovery.
* wide_money_put_string now has only the wide _String_base destructor
  conflict in the scoped current preview. Its exact declaration prerequisite
  and 82-byte-versus-14-byte carrier blocker were already preserved in
  wide-money-helper-link-20261023/. Those failed variants were not repeated.
  ScriptEngine_ctor separately retains SnapshotBlock list construction and
  upgradePair list cleanup prerequisites. ScriptEngine_dtor already links.

check_csv and whitespace checks pass. progress.py origin/master reports
+0 authored C++ and +0 census linked bytes, as expected without a new census.
All production edits are verified and committed; no nonmatching candidate
is left in Code/. Unrelated untracked assembly and ZH scratch are preserved.
The publish wrapper queued the two repair commits under its batch policy;
the runner handles the final unpublished batch. Release this seat's remaining
claims at handoff. No maintainer-only verification runner was started.
