# Integer comparison emitter repair, 2026-10-15

FontLibraryFindRecord.cpp, CastleBehaviorPackingEva.cpp and ChatWindowsLan.cpp
now specialize STLport less<int>::operator() as imported and force-inline.
The signed comparison remains the vendor operation; only each unused competing
external copy disappears. No imported comparison reference is added. No identity,
layout, ABI, address, pin, alias, ledger row or shared header is changed.

Base checkout: d9f2e5ddbb27d942b380b25e581ddb0fa9662d34.
The unchanged index measures 825b86983f at 2026-10-15 12:37, derived from census
5986a99448 at 04:52. SHA256 and metadata are in index-meta.json. Committed
link_status.csv at 28269d8e8d is discovery evidence only. Both paired previews
refresh only these three strictly prepared consumers and the unchanged
stlport_list_int.cpp provider in memory against that same saved index.

| Consumer | Retained identical COMDATs | Local findings before -> after |
| --- | ---: | ---: |
| FontLibraryFindRecord.cpp | 43 | 2 -> 1 |
| CastleBehaviorPackingEva.cpp | 30 | 3 -> 2 |
| ChatWindowsLan.cpp | 82 | 3 -> 2 |

The 155 retained consumer COMDATs and all remaining nondebug sections retain
their complete bytes, extents, flags, definitions and symbolic relocations.
No retained relocation targets the removed copies. External bindings change
only by removal of the comparison definitions; no undefined name or directive
is added. The provider object is byte-for-byte unchanged (91 COMDATs).
The selected comparison provider and every other finding are unchanged.
New-variant checks introduce no finding. Data references compare identical.

## Acceptance

- Strict bounded preparation before and after: 13/13 rows across four units,
  two literals, one float and one named import, zero skipped/baselined checks.
- Explicit ./build.sh on the changed consumers: 9/9 rows exact; existing
  orphan-label funclets are rebound by verified parent EH data.
- EH verification: 5/5 EXACT, zero missing objects or baseline use.
- Declared-definition check, class gate, converged data (eight addresses,
  no second names/unjudged rows), and whitespace checks pass.
- data_check.py --enforce reports one pre-existing wrong-name finding at
  0x00A027F4 for Castle's reportPackingEvaEvents local-static guard. The paired
  proof establishes the exact same finding and data binding before and after;
  no baseline was changed. This shadow debt remains for a separate repair.
- Placement resweep: zero bodies and zero pins. No source cleanup was needed.
- Official local link_check.py returns 1: the three consumers retain independent
  blockers. Same-index legacy LINKED is 0 -> 0; authored C++ gain is zero.

Three losing copies are removed across 1,606 existing nonpadding consumer bytes.
Strict receipts prove object currency (self-strict), not dependency closure.
No closed-strict gain, fresh census, actual link.exe placement or runtime result
is claimed. No census/index/status/history is written and no maintainer-only
runner is started. proof.py reproduces the paired checks from repository root
with pre-change source/object/receipt snapshots under ignored
build/less-int-link-20261015/before and the recorded index.

## Remaining blockers and donor review

FontLibrary still needs GameFont::~GameFont. Castle retains the conflicting
Rva00395561 destructor and its wrong-selected provider, plus the guard data-name
debt noted above. ChatWindowsLan needs Rva002EE9B7's constructor and the existing
0x005D5648 fill's member/standalone identity reconciliation. The unchanged
integer-comparison provider retains unrelated list-family conflicts. All findings
are preserved in object-proof.json and link-after.txt. They were not retried.

Verified BFME1 checkout/gitlink remains a7c38d3b2597121f178ab5190b3062478823257d.
Official master was fetched at 4cdfd6e3; file:reference/open-bfme-1 remains held
by another live worker, so the pointer and missing success stamp were preserved.
Its update still requires comparative full byte verification. Reviewed donor
66b19a8e95a4add525ef808fcea088e306798e2b: imported-inline suppression of
unused Apt allocation copies is an applicable emission technique, itself
inherited from BFME2. Apt classes, addresses and bodies are inapplicable here;
no donor code is imported. Existing BFME2 recruitment/autoresolve comparison
repairs and the included vendor comparison establish the local implementation;
target byte/COFF evidence establishes preservation in these three consumers.
