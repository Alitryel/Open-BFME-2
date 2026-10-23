# PlayerTemplate iterator ownership repair, 2026-10-15

At BFME2 base `90990587372ccad25e14ba50484219947440ed57`, give
PlayerTemplate.cpp a TU-local typed list-iterator inequality overload. It
performs STLport's same node comparison and follows existing InGameUI.cpp,
NetPacket.cpp and W3DFXParticleSystem.cpp repairs. The /O1 compilation
otherwise emits an incompatible external list-base comparison. Game bodies,
compiler flags, layout, data bindings, identities and ledger rows are unchanged.

## Controlled evidence

Before and after objects were produced from their genuine source with current
strict byte receipts. Paired checks refresh independent in-memory copies of
the same runner-provided index: update commit `19a2565407`, census commit
`5986a99448`, SHA-256
`a80ba518f5ac1ce70a2a30c3903ad5425a12bf8a0e1b4c91d1a05808ba9957a3`.
The index and census status are unchanged.

The local legacy preview changes from six findings to five across 905
existing authored bytes. The sole removed finding is the nonretail
`_List_iterator_base::operator!=`. Four COMDAT findings remain (AsciiString
scalar deletion, Destroy<AsciiString>, list clear and int-tree insert), plus
the selected nonretail AsciiString-list constructor. Legacy LINKED stays
0 -> 0 bytes; new authored matched bytes are zero. No self-strict placement,
closed-strict gain, new census or executable linkage is claimed.

object-proof.json establishes that all 91 retained COMDATs have identical
bytes and relocation digests. One unreferenced 18-byte external comparison
is replaced with one unreferenced 12-byte local comparison. No nondebug
relocation refers to either helper. Other normalized sections, relocations,
external bindings and directives are identical; only the rejected external
binding disappears. The prior local tree comparison is retained unchanged.
identity-proof.json independently establishes that all three pre-existing
identity-shadow findings are identical before/after (selected list constructor,
list equality definition and AsciiString scalar delete definition).

## Acceptance

- Original strict preparation: 9/9 rows across the two inspected consumers;
  repaired PlayerTemplate strict preparation and build: 8/8 rows.
- String, float and import checks pass; EH 2/2 EXACT, zero baseline/missing.
- Paired local link preview: 6 -> 5 findings; ordinary local check reports
  the five remaining findings (expected exit 1).
- New COMDAT variants, data enforce/converged (8 addresses), class gate,
  declared definitions and diff whitespace checks pass.
- place_bodies: zero additional bodies or pins.
- Session-start check_csv: OK, 91,217 function rows.

Proof scripts remain in build/template-map-iterator-link-20261015 and use
saved genuine baseline objects without replacing shared compiled objects.
JSON preserves exact findings, hashes and section comparisons. Maintainer-only
full link cycles and other broader runners were not started.

## Queue, donor review and blocked sibling

Started with repair_queue.py link and link_rank.py. Fetch-index retained the
newer runner index and restored 22,457 published objects. Compared current
PlayerTemplate and MapCacheWriteCacheINI findings before editing and claimed
both files. MapCache's combined typed list/tree comparison and list-only
variant both failed the byte gate for writeCacheINI (native boundary
303409..3039E8, 1503 bytes); its source was restored, evidence recorded with
re_log.py and file claim released after the second failed build. No recovery
or false-reject claim is made for that unit. Scratch failure log:
build/template-map-iterator-link-20261015/map-list-byte.log. Other existing
MapCache blockers require separate string, tree increment and MapMetaData
provider reconciliation.

Reuse the recorded BFME1 linking-repair review of `63e68aaa567` and
`de59a7e9f89` from horde-iterator-link-20261015: helper ownership is applicable;
no donor ABI, layout, address or body is imported. The directly applicable
recipe already exists in BFME2. Fetched official BFME1 master this session:
`75ff0c1485a68eafb10344670711edbee8679b62`, unchanged since the preceding
review, so no unchanged donor scan repeated. Submodule remains clean at the
committed `a7c38d3b2597121f178ab5190b3062478823257d`. Another worker owns
file:reference/open-bfme-1. Freshness update remains blocked on the previously
recorded stale/missing dependency inputs and stalled MSVC old-input baseline;
no unchanged full attempt repeated, pointer advanced or success marker written.
