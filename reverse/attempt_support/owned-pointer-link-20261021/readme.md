Owned-pointer destructor linkage, 2026-10-21
==========================================

Paired current-object legacy previews against census c7845fd6e7
(2026-10-21 15:41): Rva005CFEDFOwnedPointerDtors.cpp changes from 0 to
182 linked bytes. Rva005CFAE6Ctor.cpp remains 79 and OwnedPointerResets.cpp
remains 1,927; all three units link cleanly after the repair.

The implicit destructor at 0x005CFEDF must call the five-byte member
destructor at 0x005EBCC9, not clear() at 0x005EBC74. Its inline-visible
member destructor previously emitted a relocation naming clear(), with
the native displacement pointing at the destructor wrapper. The legacy
preview correctly refused that COMDAT as non-retail. Mark the wrapper
noinline, as its adjacent Rva005EC422 sibling already is, to preserve the
retail call relationship. Names and layouts are unchanged; this asserts
no further identity for these address-derived classes.

Acceptance: normal build.sh passes 7/7 rows; frozen-file check passes.
Explicit provider preparation passes 89/89 rows and writes self-strict
reusable receipts. No full census or link cycle was run. These receipts
do not establish closed-strict closure; the measured gain is 182 legacy
preview bytes, with no authored C++ coverage growth.
