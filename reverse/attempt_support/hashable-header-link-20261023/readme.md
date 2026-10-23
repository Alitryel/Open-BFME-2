# Hashable header compilation repair

Inputs: BFME2 489357406c; published census b711de3634 (2026-10-23
14:28); verified BFME1 reference 96c88c73a5cd1a58fc2f8db691beea50acd996db.
The unchanged donor hash.h supplies the empty virtual destructor and NextHash
contract. No new donor change applies; the supported repair is already used by
BFME2 hcanim.cpp. Target constructor EF9C2, destructor EF9CF, deleting destructor
EF9D6 and vtable BCEF94 establish the native class relationship independently.

hanim.cpp and HRawLoadW3D_Unresolved.cpp previously first included hash.h
after their size-optimization scope. Their deleting destructor copies had
digest 34c535925a6d, proven wrong against the rowed native body. hanim sorts
first and poisoned every consumer. Include hash.h alongside refcount.h inside
the existing size scope; both now emit retail's 82cbaf7637a7 copy. No new pragma,
pin, alias, layout, marker or ledger row is introduced.

Paired current-object preview across all eleven consumers:
before 0/11, 0 linked bytes; after 9/11, 9,940 linked bytes. These are legacy
scoped preview gains, not closed-strict closure. Two independent blockers
remain: hanimmgr lacks HMorphAnimClass methods and Is_Excluded; the raw-animation
unit retains differing HAnimClass/HRawAnimClass RefCount vtables. Neither was
hidden or suppressed. The changed hanim unit itself links 908 bytes.

Acceptance: build.sh 26/26 exact; string/float/import checks pass;
link_check --prepare-current verifies both sources with strict reusable
receipts (self-strict preparation only); EH 3/3 EXACT with zero baseline debt;
find_declared_unmatched and git diff --check pass. The preview consumer list
also includes the native deleting-destructor owner and both geometry ctor/dtor
providers. No authored C++ byte increase is claimed.
