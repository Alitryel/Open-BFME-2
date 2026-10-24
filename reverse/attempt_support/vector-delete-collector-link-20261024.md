# Vector-delete collector link repair

Inputs: BFME2 4d4a0a207e; verified BFME1 32774ab03393; published
retail-truth-4 census/index 268f876e3b, 2026-10-24 02:54 UTC, fetched this
session. The prior donor linking review through 32774ab0 remains applicable;
no donor inputs changed.

The V01--V05 collectors mix independently supported wrappers with wrappers
whose opaque complete-destructor names have no link provider. The latter
hold every row in each collector out of the per-unit LINKED metric. Keep the
supported wrappers in the indexed collector and move the unresolved owners,
their unchanged private declarations, array anchors and adjusting thunks to
corresponding `_Unresolved.cpp` units. Each ledger move uses add_match with
byte verification. Existing class identities, sizes, ABI, flags, relocations,
pins and full retail extents are preserved; no new identity is inferred.

Current-object previews before the split report zero linked bytes for each
collector, with respectively 3, 8, 10, 11 and 8 undefined destructor names.
After the split the five indexed collectors link 75, 300, 450, 374 and 312
nonpadding bytes: a paired current-object improvement of 1,511 bytes across
20 retained rows. All 77 moved rows remain matched in the unresolved units.
The new units are not claimed as LINKED; all supported wrappers retain their
existing indexed source path.

Acceptance: link_check --prepare-current on all ten sources passed 97/97
whole-body byte and relocation checks, plus string/float/import reference
checks, with strict reusable compiler receipts. link_check on the five
supported sources reports 5/5 LINKS and 0 -> 1,511 bytes. The staged ten-source
--new-variants --staged-peers check passes. find_declared_unmatched passes
all ten sources (one existing absent-from-retail array anchor per source),
check_csv passes 98,199 function rows, and git diff --check passes. The existing
DefaultPhysicsModuleInfo owner at 0x003A69B4 separately passes its byte gate.

The existing 0x003A69B4 group includes both Rva003A69B4Vec and the named
DefaultPhysicsModuleInfo wrapper. Its source move explicitly names the
existing owner with add_match's --icf-owner; it adds no alias or group member.
Both existing copies must continue passing the byte gate.

Strict reusable compiler receipts establish the touched units' own byte
verification. Link previews use the published legacy provider index; they do
not establish closed-strict closure. New unresolved units pass COMDAT admission
but are not claimed to link. No census, full link cycle, nightly or boot runner
was started, and reverse/link_status.csv remains the published measurement.
No authored C++ coverage growth is claimed.

Remaining work is provider/identity reconciliation for the opaque complete
lifetime names in the unresolved collectors. Retail callback targets and
class extents remain documented in each moved source; the split does not
justify inventing second names at those addresses. Revisit a collector when
its actual complete-destructor provider/ABI is available. Other scalar
collectors and V06 already link in current-object previews and need no repair.
