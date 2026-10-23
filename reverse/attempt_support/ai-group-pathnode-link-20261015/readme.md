# AIGroup inline-copy link repair

Base BFME2 revision: 1522ab67ca233bc7e8b5e151fed702af66660595.
Fixed local index: a2839ea429, 2026-10-15 13:35 UTC, derived from census
5986a99448, 2026-10-15 04:52 UTC. index-meta.json records its SHA256.
Neither the index nor the committed census/status is modified.

AIGroupGetCenter.cpp emitted unused standalone copies of PathNode::getNext
(4 bytes, dbc10ce76e7d) and ThingTemplate::isKindOf(unsigned mask)
(13 bytes, 178a66cead16). Both lost the index's first-copy selection. The
existing imported-forceinline spelling suppresses these copies and retains
the retail inline operations. Every other definition and reference remains.

The existing identity, ABI and offset evidence remains the two whole retail
bodies at 0x0036D035 (282 bytes) and 0x0036D3A3 (785 bytes), their established
ZH/WB leads and ledger provenance. The former is the centroid calculation;
the latter classifies members and traverses the path. This change asserts no
new standalone accessor address or canonical class layout. The mask overload
is distinct from the rowed enum/bool ThingTemplate::isKindOf overload.

## Acceptance and measured improvement

- Bounded link_check.py --prepare-current before and after: 2/2 complete
  retail rows and strict reusable current-input receipts. Independent
  ./build.sh after: 2/2 exact; four float references verified, no skipped
  string/import references.
- Paired check_object previews refresh each independently verified object into
  separate copies of the same index. Findings fall from four to two, removing
  exactly the two competing copies. No new variants, undefined names or import
  references; every remaining winning provider and selection verdict is equal.
- All 25 retained COMDATs are byte/relocation/extent identical. Every retained
  nondebug section preserves bytes, flags, extent, external definitions and
  symbolic relocations (SafeSEH symbol indices normalized by name). No retained
  section relocates to either removed helper. External/weak bindings and
  data-reference facts are equal. object-proof.json records the comparison.
- EH verification before and after: zero EH rows, missing objects or failures.
  Enforced data check: zero findings; converged check: eight addresses, zero
  second names or unjudged rows. Class, declared-definition, new-variant and
  whitespace checks pass. Placement resweep: zero additional bodies or pins.

Existing nonpadding authored bytes in the unit: 1,060. Legacy predicted linked
bytes stay 0 -> 0. No new authored C++ bytes, closed-strict gain or full-link
measurement is claimed. The current self-strict receipts prove only the scoped
byte gates; dependency closure remains unmeasured.

The remaining duplicate AIGroup::getCenter definition and unresolved
Pathfinder::FindGroundPath provider are unchanged. They need provider/home-unit
reconciliation and are outside this emission repair. No headers, flags, pins,
ledger extents, data identities, layouts or hatch counts change.

proof.py reproduces the paired comparison from repository root using ignored
source/object snapshots in build/ai-group-pathnode-link-20261015/before and
the unchanged fixed index. input-hashes.json records the source/object and
current strict receipt identities. The JSON is local comparison evidence,
not a closed-strict receipt.

## Donor review and boundaries

Reviewed BFME1 repair 66b19a8e95a4add525ef808fcea088e306798e2b, including its
patch and verification message: imported forceinline removes unwanted allocator
copies while preserving full target bodies and adding no imports. The emitter
technique applies; its Apt identities, layouts, addresses and linked-byte
results do not transfer. Existing BFME2 AI siblings already use this spelling.

The clean verified BFME1 checkout/gitlink remains
a7c38d3b2597121f178ab5190b3062478823257d. Official upstream master was fetched
as 84191dc2 during this session. Another worker's live reference/open-bfme-1
file claim blocks the due comparative pointer update; preserve the verified
inputs and write no freshness-success stamp. No unchanged broad donor scan was
repeated. No decoder source, census build/measure/history, link cycle, nightly,
boot runner, scheduler or shadow publisher was used.
