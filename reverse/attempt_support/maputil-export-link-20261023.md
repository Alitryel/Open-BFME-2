# Map-cache shared-state linkage repair

MapCacheAddMap.cpp referenced resetMap and worldDict externally, while the
retail-owned definitions in MapUtil.cpp retained their donor TU's static linkage.
Export resetMap and give worldDict C linkage, matching the existing consumer and
_data_ledger.csv_ owner `_worldDict` at RVA 0x009FF140. There is no second datum,
new pin, alias, layout change, or recovered C++ body.

Target evidence: resetMap's 76-byte row is at 0x00303187; worldDict's initializer
and cleanup rows are at 0x007AE5C2 and 0x007B7A55. The existing matched consumer
uses those function/data identities. BFME1 donor 96c88c73a5cd1a58fc2f8db691beea50acd996db
keeps both definitions static inside its unsplit MapUtil TU; its linkage cannot
be reused across BFME2's separately recovered consumer.

Current-object legacy link preview, both units supplied together against census
456ce161c5 (2026-10-23 06:28): before, neither unit links and MapCacheAddMap's
only blockers are resetMap and worldDict; after, MapCacheAddMap LINKS, adding
1,085 non-padding authored bytes. MapUtil still has unrelated unresolved callees
and COMDAT/selected-copy blockers. This is a legacy preview gain, not a measured
self-strict or closed-strict gain. No full link cycle or runtime test was run.

Acceptance: normal build.sh passes 33/33 rows across both units, all four string
literals plus one empty reference, five float references and one named import.
link_check.py --prepare-current also passes both providers with strict reusable
compiler receipts and the same ordinary byte gates; it explicitly does not
establish link closure. find_declared_unmatched accepts MapUtil. Converged data
check and check_csv pass. The shadow data checker retains four unrelated
outside-baseline findings: supply/tech list names in the consumer and MapUtil's
private map dimensions; those definitions/relocations are untouched.

The source-name sweep finds no additional consumers of these two shared names.
