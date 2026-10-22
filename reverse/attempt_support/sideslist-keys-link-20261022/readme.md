# SidesList static name-key providers

At BFME2 4bf2abe4ae, the current object for SidesListDataChunks.cpp fails
legacy link preview solely on TheKey_objectIsABase and
TheKey_teamLibraryMapName. The existing validateSidesRva0032E02BFarm.cpp
consumer already links and is included as a control.

Retail .data proves two eight-byte caches: DB DD 0C holds {0, C09278},
whose string is objectIsABase; DB DC 1C holds {0, C09024}, whose string is
teamLibraryMapName. The adjacent DB DC 24 cache points to
teamTargetThreatFinderName: the unowned data ledger's 16-byte interval
is not the size of teamLibraryMapName. The matched absolute references
establish the two provider names; the existing StaticNameKey::key view
establishes the key/name fields. Aggregate initialization follows the
already verified objectBaseName provider in CastleMemberBehaviorRva00399165.cpp.
The private-to-public access change preserves layout and permits static
initialization without emitting a runtime initializer.

Against unchanged published census ae3b3e68e2 (2026-10-22 11:05 UTC),
paired current link_check before: 1/2 units, 1,098 bytes; after: 2/2 units,
7,824 bytes. Net new linked matched bytes: 6,726. No authored C++ byte growth.
The farm is unchanged and its 1,098 bytes are not a gain.

Checks: build.sh 91/91 byte rows, strings/floats/imports; data_rows --verify
both providers, including exact extent and string relocations;
link_check --prepare-current strict reusable source receipts;
link_check --new-variants --staged-peers; find_declared_unmatched.
This is a legacy current-object link preview with self-strict source
verification. Closed-strict closure remains unavailable: the census input
set lacks 3,469 current-ledger provider objects (see previous Matrix3 repair).
No full link cycle or census was run. BFME1 pointer remains 37c3022de1;
this repair uses target data, not newer unverified donor inputs.
