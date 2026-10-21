Link-repair seat handoff, 2026-10-21
==================================

Four repair commits, six units, +994 B newly linking in paired legacy
link_check.py previews against census c7845fd6e7 (2026-10-21 15:41):

- e78bfb197c: collector ShaderClass vector destructor contract, +173 B.
- c3a3f7aaf0: three list-valued AsciiString pair consumers, +396 B.
- 3c38116b6e: component-table hash provider, +307 B.
- 87bbb592ca: deque iterator comparison provider, +118 B.

Each repair has its own tracked evidence directory: material-vector-link-,
list-pair-link-, component-hash-link- and deque-compare-link-20261021.
All touched rows passed build.sh, EH checks where applicable, frozen-file
checks and link_check.py --prepare-current. Normal commit hooks passed.
These are legacy preview gains, not closed-strict or full-cycle results.
The shadow code-identity findings remain shadow findings; no new target
identity is claimed by the list iterator or PodPayload20 helper repairs.

Final check_csv.py passes (97924 function rows, 15937 symbols, 1381 data
rows). progress.py origin/master reports +0 authored C++ and headline
linking delta, as expected: no new bodies and no new census were recorded.
No maintainer-only verification runner was started. No seat claims remain;
no source reconstruction is left uncommitted. End this seat at its context
reassessment limit rather than repeat the unchanged blocked attempts.

Blocked work and queue caveats
-----------------------------

StlSweepR3Rva00289FBC.cpp: two assignment-bridge trials failed exact native
register and stack ordering. Restored source, recorded blocked evidence in
re_attempts.log and list-pair-link-20261021/readme.md, released claim.

Do not retry the unchanged GeneralAllocatorGuard, vector destructor,
HordeContain list-find, or AptValueWithHash private-view problems: their
existing logs contain extensive compiler-shape trials. Several high-ranked
items already link in current source, despite stale census blockers.
In particular string_base.cpp's two wide-compare duplicates are already
removed by upstream 7a6ad52833 in GameLogicDoXfer.cpp; no repair is needed.

An untried lead is Rva006ABC60Destructor_Rva0005925E.cpp (121 B): its
undefined private array-element destructor may be reconciled with the
member types in MilesAudioVolumeConstructor.cpp. Establish target type and
provider identity first; do not simply pin the private element name.

Reference/linking leads were checked at BFME1 revision
00c2ffbb23e9154fbe9970954afacb04e4943dd7. Freshness update remains blocked
by another seat's reference/open-bfme-1 claim; existing verified inputs were
preserved and no successful freshness stamp was written. The prior
bfme1-refresh-20261021-bce2 handoff records the update blocker.

Checked link_rank.py --top 30 and --near 2, class_views.py --blockers and
repair_queue.py link (1839 indexed units). name_globals.py --dry-run found
zero rewrites. rehome_rows.py --limit 20 lacks build/link_census/census.log;
do not rebuild a census in this seat. No commit-matching data-back artifact
was available. The index is present; many remaining entries need broader
class reconciliation, provider identity or already-recorded codegen work.

Publication must use the runner: each repair was committed with
/opt/runner/publish in the same command. The publisher retained the four
commits at the batch threshold; the handoff commit retries publication.
If publication remains deferred, the runner publishes the final batch.
