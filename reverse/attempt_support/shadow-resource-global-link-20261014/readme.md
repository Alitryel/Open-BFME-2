W3DView shadow-resource global link repair

Base revision: 854c25ee97f2f2cf4c0f7fd8c21de0afa6fc8bf5.
Measurement/index: 147cfae2cb, 2026-10-14 07:27; SHA256 in object-proof.json.
The committed link_status.csv has a newer measurement (de7bb30890); it is
not used to claim this preview's gains. Census/index/status were not changed.

Target evidence: update@W3DView, ledger extent RVA 0x0008C3AC + 2690,
loads native VA 0x00DE1FF8 through DIR32 operands at RVAs 0x0008C43F
and 0x0008C451. reverse/data_ledger.csv owns that datum as
?Rva00DE1FF8Manager@@3PAVRva0007DA23ResourceManager@@A in
Shadow/W3DShadowManagerReAcquire.cpp. The consumer previously called it
?TheWaterRenderObj@@3PAVRva0007BB79Owner@@A, an unresolved second name.
Declare the existing owner's exact pointer type and cast to the unchanged
private accessor views at use sites. No semantic class name is recovered.

Object evidence: every nondebug section's raw bytes, flags, size and ordering
remain identical (consumer 45 sections, 39 COMDAT symbols; owner 14 sections,
9 COMDAT symbols). Only the two consumer DIR32 symbol names change. The
owner's whole object SHA256 is unchanged. Preserved before objects/sources
and the comparison script are in ignored build/shadow-resource-global-link-20261014/.
Data audit on those preserved objects records one wrong-name finding before,
zero after, with no unread rows (data-proof.json).

Acceptance: ./build.sh on consumer and owner passes 10/10 rows and 33 float
literals. link_check --prepare-current gives strict reusable receipts for both
units (consumer 1/1, owner 9/9); object-proof.json confirms strict currency.
EH is exact 2/2; converged-data enforcement reports zero second names and
zero unjudged rows. Ordinary data audit, new COMDAT variant guard, class gate,
declared-definition guard, check_csv and git diff --check pass.
place_bodies consumer finds zero additional bodies or pins.

Same-index local link preview: consumer findings 7 -> 6, unresolved globals
2 -> 1. The removed finding is only the incorrect shadow-resource spelling.
Owner links before/after at 685 bytes; consumer remains at zero linked bytes.
Legacy cohort LINKED is 685 -> 685; authored C++ byte growth is zero.
Self-strict byte/dependency acceptance is proven; closed-strict dependency
closure and linked placement are not claimed. No full link runner was started.
Remaining consumer blockers: CameraShakerSystem unresolved; STL allocator
COMDAT disagreements and selected vector-base/allocator definitions.

Donor review: BFME1 verified pointer a7c38d3b2597121f178ab5190b3062478823257d;
reviewed 0835ab92bef30e3303e729a0ce09cf591368d0cd's Apt payload repair,
which declares an owned global's pointer type then casts its private view.
That repair principle applies; donor layout and identity are not target facts.
Other BFME2 consumers of this manager already use its owner spelling and
local casts; no additional supported correction was needed.

Freshness: official BFME1 master fetched at
16c79ec657766fe5455c4f8fda00eef108080fa5. Retained the verified pointer;
full old/new comparative verification remains outstanding (previous attempts
were interrupted while refreshing thousands of stale objects). No freshness
success stamp or pointer advancement is asserted by this repair.
