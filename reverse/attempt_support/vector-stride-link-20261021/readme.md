Rva005DE5B5 element layout and cleanup linkage, 2026-10-21
========================================================

Paired current-object legacy previews against census c7845fd6e7
(2026-10-21 15:41) measure stlport_vector_rva005de5b5_dtor.cpp from
0 to 118 unique linked bytes. Its cleanup provider,
stlport_vector_stringrecord_5de5b5_dtor.cpp, remains clean at 443 bytes;
together the units change from 443 to 561 linked bytes.

The consumer private view omitted float +0x10 and byte +0x14, making
sizeof(Rva005DE5B5) 16 instead of 24. Consequently its emitted _Destroy
COMDAT advanced by 16 and differed from native cleanup 0x005DE952,
which advances by 24. Restore the two fields from the matched home:
constructor 0x005DE5EA, copy constructor 0x005DE56C and updater
0x005DDB66 independently establish their offsets and types. The existing
pin already identifies the template cleanup as the native loop's twin;
no names, pins or row extents changed. The GameStats view already has
these fields, and Rva005DDE01Finish.cpp uses explicit 24-byte indexing
with a declaration-only view, so neither needs this repair.

Acceptance: build.sh passes 4/4 consumer rows. Explicit preparation of
consumer and provider passes 15/15 byte rows with strict reusable
receipts. EH verification reports EXACT 5, frozen-file check passes,
and check_csv passes. No census or full link cycle was run. The gain
is 118 legacy-preview bytes; self-strict receipts do not establish
closed-strict closure. Authored C++ coverage does not grow.
