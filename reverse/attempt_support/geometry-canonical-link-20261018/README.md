GeometryInfoCalcBoundingStuff.cpp: +1,440 B legacy linked preview.

The canonical Coord3D layout and BFME2 AsciiString header replace donor header
copies. The three native clear sites retain the donor component store order via
an internal helper; the helper has no external provider identity. The AsciiString
constructor is now the shared six-byte body; the old Coord3D::zero and two unused
StringBase helpers disappear. No new pin, alias directive in source or hatch.

The paired evidence refreshes only this unit against census c2c5ac8c27. Five
matched bodies and all five float literals pass build.sh. Retained nondebug
bytes and relocations and source data facts are equal, excluding the replaced
helpers. The AsciiString destructor changes alignment only (16 to 1); the shared
header supplies its existing canonical alias directives instead of unused donor
template operator aliases. The unit has a strict current compiler receipt. This
is a legacy preview gain, not a closed-strict measurement. No census was run.

Donor review: BFME1 06a23066 demonstrates declaration/emission reconciliation
for string helpers. No donor code is imported here; existing canonical BFME2
headers and complete target byte checks establish applicability. The clean
BFME1 checkout stays at verified 64d369b90170; upstream 81ee62b0 is newer.
Freshness advancement remains blocked on the old-input comparative full gate;
no success stamp or pointer advance was made.

Nearby trials: W3DShrubBuffer Vector3 helper suppression and NameKeyGenerator
canonical string adoption were restored after two unsuccessful trials each;
reverse/re_attempts.log records the current failures. ReplenishUnitsBehavior's
filter conflict disappears when its current BfmeConv1739 provider is refreshed;
no source repair or gain is claimed for that stale census entry.
