# AsciiString tree insertion link repair

At BFME 2 44d0196f61, two callers implicitly instantiated the generic
`_M_insert_005014FF` despite its explicit specialization in the owner unit.
Declare that specialization in both callers so all three units use one body.
No class layout, reference input, pins, rows or compiler settings change.
The target ledger establishes the specialized identity and address; unchanged
retail bytes establish that the declaration preserves each caller.

Paired legacy link previews against the same published census b73720bed9
(2026-10-20 05:34) improve from 0/3 units, 0 bytes to 3/3 units, 564 bytes
(136 + 294 + 134). See before.txt and after.txt. This is a legacy predictor
result, not a closed-strict or full-link measurement.

`./build.sh` passes both changed rows; `link_check.py --prepare-current`
passes all three rows with strict self receipts. `--new-variants` reports no
new variants. check_csv and find_declared_unmatched pass. The published
census/index/status are unchanged; closure has not been checked.

The BFME 1 donor linking lane was reviewed at verified pointer a2c8039e61:
its game/Libraries/Source/WWVegas/WWLib/stlport_rb_tree_int_asciistring_insert.cpp
uses a different minimal private view. No donor layout is transferred here;
the repair binds existing BFME 2 specializations in their own STLport view.
