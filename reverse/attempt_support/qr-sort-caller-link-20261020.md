# QR sort caller link repair

Base: 87ae58f95d. Published census: 3f413ed3ff (2026-10-20 18:52).
BFME 1 donor reviewed this session: 4483e88da1c2f3b9a273f779baac7458bd8bb891;
this repair uses BFME 2's existing recovered providers and retail call evidence.

Current-object previews before editing showed two unresolved names in each
caller: BfmeRoomQR's copy constructor and bfmeDoQR. Their original pin and
retail calls identify the insertion worker at 0x002176F1, already recovered as
Rva002176F1Insert in MixFileCreatorFileInfoStructAssign.cpp. That provider uses
three 32-bit fields followed by AsciiString at offset 12. The callers' old
opaque record has the same sixteen-byte layout and by-value copy operation.

Replace the opaque string member with AsciiString and bind the calls to the
recovered worker. A call-site function-pointer view preserves the extra unused
comparator word present in retail after the sixteen-byte value; the cdecl
worker consumes the same value and does not access that word. The neutral
caller record names remain; no additional target identity is claimed for them.
No pins, aliases, optimization pragmas or unmatched markers were added.

Measured with link_check.py on both touched units before and after:

| Source | Retail RVA | Legacy linked bytes before | After |
| --- | --- | ---: | ---: |
| BfmeConv1727.cpp | 0x002178FD | 0 | 45 |
| Q3LinearInsert00217F0E.cpp | 0x00217F0E | 0 | 110 |

The provider was also compiled and previewed: its existing 349 linked bytes
remain unchanged and are excluded from the gain. Both callers pass the normal
full-byte gate (2/2 rows, 157 ledger bytes), literal, float and import checks,
find_declared_unmatched, and explicit --prepare-current verification (two
self-strict reusable receipts). The measured improvement is **155 legacy linked
bytes**. Census extents differ from ledger extents; no closed-strict gain or
additional authored C++ coverage is claimed. The old helper names have no
remaining source references.
