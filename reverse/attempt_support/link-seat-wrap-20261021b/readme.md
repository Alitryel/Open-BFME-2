Link-repair seat handoff, 2026-10-21, yasinschroeder-codexb

Published repairs from this session:

- 1b6f839373: complete tag table and existing slot providers, +263 B legacy
  predicted LINKED (0 -> 263 in VslotSmallBodiesQ.cpp). Companion static-tag
  unit remains linked. Evidence: tag-table-link-20261021/readme.md.
- eb9385ae48: 129 complete native INI registration nodes and corrected 68-byte
  string-pointer table extent, +2,728 B legacy predicted LINKED. Paired units
  105 -> 2,833 B. Evidence: ini-registration-link-20261021/readme.md.

Total session improvement is +2,991 legacy predicted linked bytes, with no new
function rows or authored C++ function bytes. These are current before/after
measurements against the same published index (17918792f6, 09:22 UTC), not the
larger census-to-current changes. Normal gates and strict reusable self receipts
passed for both repairs. No closed-strict closure gain is asserted. No full
census, link cycle, nightly or boot runner was started.

Acceptance: first repair 72/72 code, 38/38 data, six literal references; second
133/133 code and 132/132 data across its two units. Both commits passed normal
hooks and published together through /opt/runner/publish. Existing shadow
wrong-name finding at unchanged parser table g_00837CD8 remains: data_rows uses
?g_00837CD8@@3QBUFieldParse@@B while data_ledger uses its nonconst spelling.
No new pin, baseline growth or hatch was introduced by these repairs.

Next candidate investigated and released:

Rva002D22CAInit.cpp, rva002D2457 (135 B), remains 0/135 current LINKED, with
seven missing table providers. Matched register 2D23ED proves stride 12,
key/name/callback fields and termination on name==0. Independent PE walks give
complete extents including null records:

    VA DBC890: 264 B, 21 entries (Apt screen factories)
    VA DBC998:  36 B,  2 entries (IME draw callbacks)
    VA DBC9C0: 264 B, 21 entries
    VA DBCAC8: 228 B, 18 entries
    VA DBCBAC:  24 B,  1 entry (MapSelectMenuInit)
    VA DBCBC4:  24 B,  1 entry (MapSelectMenuUpdate)
    VA DBCBDC:  24 B,  1 entry (MapSelectMenuShutdown)

All callback addresses have matched rows, but the Messenger.apt entry at
DBC8E4 points to 5114C6. GapBodiesS3L.cpp currently defines this as virtual
Rva005114C6::rva005114C6(void *), returning Rva005114C6Messenger *. Taking
that virtual member's address emits a vcall thunk, not the factory body which
the native table stores. Reconcile the factory's identity/ABI before adding a
complete table; do not invent an alias or raw code pointer. No source trial or
partial table definitions were left. Evidence recorded with re_log.py, file
and RVA claims released. Read-only scratch: build/gui-table-link/.

Queue reassessment:

- link_rank --top 30, --near 2, expanded one-blocker/U lists;
  class_views --blockers; repair_queue.py link. Current probes distinguish
  already-landed repairs from new work. ActionManagerCanDoSpecialPowerAtLocation
  already LINKS 3,710 B and Rva007FCF10DescriptorLookups already LINKS 57 B;
  their indexed blockers are stale. The AptTimeLine caller already uses the
  matched AptTimeLine spelling; its new provider is absent from the old index.
- Shared math, constructor-iterator, Apt vector, partition-filter, allocator,
  LAN and collision campaigns retain their recorded prerequisites. The two
  AI approach filter tables still lose to the ZH one-slot private views;
  current preview 0/1,981 B. See re_attempts entry 80257 for the required BFME2
  PartitionFilter base reconciliation across PartitionManager/Jet/Dozer.
- name_globals.py --dry-run again found zero files/edits. rehome_rows.py
  --limit 15 cannot rank without build/link_census/census.log. No matching
  data-back measurement artifact was available. Do not run a new census here.
- Foreign claims still held the reviewed WaterTracks flush and Apt score/
  collection units. No claim was taken over. All this seat's claims released.

BFME1 freshness remains blocked on the earlier comparative full-gate SDK
failure. Verified clean pointer retained at 5987fd1b859e86801d093256eadc6fb63d87785f;
official master fetched as 3f00bbbe. No success stamp or pointer advance was
claimed. The relevant verified donor INI registration implementation was
reviewed; native BFME2 data independently decided the landed nodes.
