# B07 destructor wrapper link isolation

Base 2eb25e6208; published census 0393df10e2, 2026-10-23 19:47,
retail-truth-4. Before editing, the indexed B07 unit excluded all 1,415
nonpadding bytes. Unresolved destructor providers were Rva0036B8E6,
MineshaftPortalNetworkManager's two bases, PeerThreadClass and Rva003EE1BE;
the selected Rva003ED1FC destructor was not retail's.

Move those five existing class views and their six matched wrappers/thunks to
OpaqueScalarDeletingDtorsB07Deferred.cpp. Retain their original definitions,
includes, compiler flags, layout and native vtable/call evidence. No new body,
pin, name, layout or ABI claim. All 54 existing rows remain byte-exact. This
uses the same independent-body isolation repair as the preceding weather repair;
BFME1 f5140c1cff6a and the existing BFME2 isolation evidence were reviewed.

Paired legacy current-object prediction for the indexed original unit changes
from excluded to LINKS, 0 -> 1,268 B. The deferred unit is absent from the census
and receives no credit. Its destructor providers remain unresolved or selected
incorrectly; their recovery or canonical class reconciliation is separate work.
This is not self-strict, closed-strict, a census measurement, or an executable
link. New authored C++ bytes: zero.

Acceptance: link_check --prepare-current verifies 54/54 rows across both units
and emits strict reusable receipts; string/float/import gates pass. EH data is
EXACT for all six parents. Fifteen local-label hints resolve through their
verified parent EH graphs. Declared-definition, staged class, pin-admission and
new-variant checks pass. No verifier, baseline, shared header or pin changes.
Scratch evidence: build/link-seat-b07-before.txt and build/link-seat-b07/
(original source/rows, prepare.log, after.log, eh.log, variants.log).

Sibling sweep: B04 has an unchanged recorded canonical-name reconciliation
blocker and was left intact; its temporary claims were released. B11 and B13
already link when their existing rowed providers are supplied (seven-unit probe,
3,330 -> 3,330 B), so no repair gain is attributed to them.
