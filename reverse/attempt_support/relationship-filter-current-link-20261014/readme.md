# Relationship-filter current-provider acceptance, 2026-10-14

At source revision `98621e6126`, the local index measures `cb660e4d97`
(2026-10-13 04:02 UTC). The committed link-status snapshot instead measures
`67e1365aa9`; it supplied queue leads only. Full source and index hashes are
in object-receipts.json. Neither index nor link-status/history was changed.

The current constructor provider already contains repair
`04948a9a3a3d15cce9d010abc3d3c3df08652e21`: enable /GX so its partition-filter
deleting destructors call the ordinary derived destructor. This session adds
acceptance evidence for two remaining relationship-filter consumers, rather
than changing already-correct production source. The earlier acceptance at
partition-filter-current-link-20261013 covered a different filter class and
explicitly left ObjectBroadcastEvent as a remaining lead.

## Verified improvement

For `??_GRva00260EB1Filter@@UAEPAXI@Z`, the index contains the provider's
29-byte inline-vptr-reset copy (digest e99a253b610c). Its current object and
both consumers contain the same 28-byte call-based copy (2fcefa862559).
Each also emits the same seven-byte ordinary destructor resetting the base
vptr (d3bc83dcfec7). The JSON inventories complete bodies and relocations,
source/object/receipt hashes, and each indexed deleting-copy verdict.
The deleting helper has no retail address in the index: these are compiler
and relationship facts, not a newly recovered helper identity.

Bounded preparation verifies **36/36 rows across three sources** with strict
reusable receipts, zero skipped/baselined references, and no extra providers.
The census-only preview reports 0/3 clean, zero bytes. The current-object
preview against the same index reports 2/3 clean:

- ObjectBroadcastEvent.cpp: **1,689 bytes**.
- GrabPassengerSpecialPowerRva004C51A0.cpp: **640 bytes**.

Thus the local **legacy LINKED preview improves by 2,329 existing bytes**.
Inputs are self-strict; no closed-strict gain or actual link.exe placement is
claimed. Both preview commands exit 1 because the constructor provider still
has thirteen unresolved allow methods, enumerated in both transcripts.
No source, row, pin, alias, marker, compiler flag, hatch or verifier exception
was added; new authored C++ bytes are zero.

## Acceptance commands

```
python3 tools/link_check.py --prepare-current --paths-from sources.txt
python3 tools/link_check.py --census-only --paths-from sources.txt
python3 tools/link_check.py --paths-from sources.txt
python3 tools/data_check.py --converged <the three paths in sources.txt>
python3 tools/find_declared_unmatched.py <the three paths in sources.txt>
python3 tools/check_csv.py
```

Preparation exits 0; each preview exits 1 for the stated provider blockers.
Data checking accepts three sources and eight addresses, with zero second
names or unjudged rows. Declared-definition and ledger checks pass. Ordinary
commit hooks remain required. Source claims were held for all three files at
acceptance and are released at handoff. No full link cycle, census build,
measure/history, nightly, boot or scheduler operation was run.

## Donor review and remaining work

Reviewed BFME 1 donor repairs d3f9000fe08615a100e844adfff57fa4a39cd615
(TileData incidental constructor suppression) and
5093777e8373a843f1f1ccfc648601ae78351aaa (ShareBuffer destructor consistency).
Their emitter-consistency principle is a lead; target objects and receipts
above independently establish this result. No donor layout was imported.
The clean verified BFME 1 pointer remains
cee35b7d8ca077d7255f1c39cb69e9fd9627aa85. The official freshness fetch now
reaches 92a8d854746f059994f8ab370c133f3ba71eec24. The overdue comparative
full-gate update remains pending after previous build-lock/stale-cache
failures (5,337 stale units in build/seat-link-reference-baseline.log).
The pointer and freshness timestamp were preserved; no new update success
is claimed.

The provider's thirteen allow definitions remain unresolved. Other queue
probes found already-fixed units and existing PlayerList duplicate,
unsigned-comparator codegen, hero-comparator and vector-destructor conflicts.
No unchanged deferred reconstruction was retried. The Shroud CDE array helper
still has different /O1 and /O2 copies; it was inspected without editing or
claiming a verified repair. This result does not count other filter consumers.
Unrelated untracked dump and zh_sweep work was preserved.
