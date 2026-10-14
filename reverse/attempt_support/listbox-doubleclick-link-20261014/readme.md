# List-box double-click interval data repair

Source base: 6310b60564 (full revision in base-head.txt). Actual local census
index: 147cfae2cb, 2026-10-14 07:27; SHA256 in index-meta.json. Committed
link_status.csv at 67e1365aa9 was discovery evidence only. Neither index,
census, status, history, function rows, pins, headers nor compiler flags changed.

GadgetListBoxMultiInput.cpp reads one DWORD at VA 0x00E01D48; startup
initializer rva007AE9E6 stores GetDoubleClickTime() there. Both objects formerly
referenced an undefined g_00E01D48. Provide one external unsigned-int datum in
the list-box source and bind both existing functions to doubleClickTime.
Keep zero-initialized storage: the already-recovered startup function supplies
the OS interval, without creating another initializer or changing startup order.

Independent target evidence: callback 0x00325635 has a DIR32 reference at
body offset 2271 (instruction 0x00325F14); initializer 0x007AE9E6 has its store
relocation at offset 7. Both retail operands target VA 0x00E01D48. Its four
image bytes are zero in .data; the new object definition is exactly four
uninitialized bytes with four-byte alignment, offset zero, sole external owner.

Donor evidence: verified BFME 1 pointer
23b143233b5a8664a3bdf8572df6d905c310a5a1. Its game/.../GadgetListBox.cpp
line 171 defines doubleClickTime from GetDoubleClickTime(); its verified data
row is at VA 0x012F3640. The pristine GeneralsMD/.../GadgetListBox.cpp line 75
uses the same name, originally with internal linkage. BFME 1's repair makes
the definition external to share it with the separated initializer. This
binding repair applies; BFME 1's address and layouts do not. The source name
is carried from donors, not independently proven BFME 2 debug identity. Homing
the datum in this list-box unit is a structural inference from those donors.

The matched data_rows entry verifies the native four-byte storage. data_ledger.py
generated derived-ledger.csv locally; only its exact 0x00A01D48 row was applied
to the committed generated ledger, preserving unrelated rows from the shared
cache. That row changes unowned/zero definitions to owned/one definition and
two references. No baseline or admission rule changed.

Acceptance: 13/13 matched rows across the two sources remain byte-exact; seven
named imports verified. Both explicit objects have reusable self-strict current
receipts before and after. Object-proof.json records unchanged existing
nondebug sections, directives, code, extents, external symbols and relocations
after normalizing the timer binding and section numbering. The sole added
section is four-byte BSS, with no new code. EH is EXACT 1/1, no baseline/missing
object. Data enforcement has zero findings; converged enforcement covers eight
addresses with zero second names or unjudged rows. Definition/class checks,
CSV validation, new-variant admission and whitespace checks pass. Placement
resweep finds zero bodies and zero pins. Four textual occurrences of the
address-named global are removed. The current hatch scanner does not count
that spelling; its counts are unchanged, with no hatch growth.

Paired same-index local preview replaces both before objects, then both after
objects, in memory. It removes exactly the missing timer name from each unit;
all other categories agree. GadgetListBoxMultiInput retains the incorrect
StringBase<ushort>::getCharAt COMDAT; the initializer unit retains unresolved
g_00DFE718. Legacy linked bytes stay zero, and authored C++ growth is zero.
Compiler currency is self-strict for the two explicit units. Closed-strict
dependency closure, link.exe placement and a new census were not measured;
no maintainer-only runner was started.

Reference freshness: fetched official BFME 1 master
a7c38d3b2597121f178ab5190b3062478823257d, preserving the clean verified gitlink.
The previous old-input full verification remains interrupted with 2806/2982
TUs pending (unicode-comparator-link-20261014/readme.md). This session does
not advance the pointer or mark that comparison successful. Ordinary repairs
above were verified against the preserved committed donor inputs.
