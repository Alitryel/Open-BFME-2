# Link seat handoff, 2026-10-23

Baseline 8ffbef1c3e; published census b711de3634 (retail-truth-4).
No source changes survived: +0 new matched or linked bytes. Only legacy
link previews were run; no self-strict or closed-strict gain is claimed.

## New findings

- Replacement-string pair (Rva008312E0StringReplace.cpp and
  Rva008314E0StringReplace.cpp): generic erase and forward-replace callees
  have real rowed owners, but the second forward provider has stdcall
  spelling and consumes ECX. ABI reconciliation precedes caller repair.
  Logged 0x2AE50; claims released.
- String-record overflow: see [preserved candidate and diagnosis](link-vector-381b7b-20261023.md).
  Three failed byte gates; original restored and reverified 14/14.
  Claims released. No verification bypass or new pins.

## Queues and prerequisites

- link_rank.py --top 30; --near 2 --top 70; --near 4 --top 90,
  class_views.py --blockers, repair_queue.py link: ranked provider/class
  debt reviewed against prior handoffs and claims. Many apparent gains
  already exist in current objects, so do not count census deltas alone.
- Current previews: pod28_allocate_copy already links266 B; narrow-string
  substring, ArmySummary, RankInfo, Hashable cohort, and string-record
  fill-insert repairs are inherited. MapCache pair destructor, production
  prerequisite allocator/assignment/Destroy, DX8Skin vector destructor,
  FormationTemplate element identity, and opaque record constructors retain
  documented blockers. GameLOD and the string-hash first provider are held
  by other seats. AIStatCollector's container identity prerequisite remains.
- name_globals.py --dry-run: 0 files, 0 edits.
- rehome_rows.py --limit 12: cannot run because published census.log is
  absent. Index exists; no full census was started. Restore the matching
  published log before using this lane.
- BFME1 linking repair commits reviewed: 604f6b70, e20610f1, b3070ee7,
  87dbf3e3. No direct additional verified repair found. Official master was
  fetched (f5140c1c); retained verified pointer96c88c73. Freshness update
  still has the preceding handoff's full-gate FireWeaponWhenDeadBehavior
  class-view prerequisite and overlapping claims. No success stamp written.

Checks: check_csv passes98183/15796/2169 rows; restored vector byte gate
14/14, strings/floats/imports pass. progress.py origin/master reports +0
across authored C++, matched coverage and census-linked bytes.
No maintainer-only verification runners used. No claims left by this seat.
