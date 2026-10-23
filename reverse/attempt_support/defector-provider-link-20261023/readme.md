Defector constructor and destructor ownership, 2026-10-23

Paired legacy link previews at BFME2 a69e1128b2 against retail-truth-4 census
0fa62a2841 (2026-10-22 23:07 UTC) change four units from 0 to 303 linked
nonpadding bytes. before.txt and after.txt name the units and their blockers.
Self-strict preparation verifies all 8 rows across those four units, including
literal, float and import checks (self-strict.txt). Closed-strict closure, a new
census and executable placement were not measured. Authored C++ coverage is
unchanged; 33 existing destructor bytes move between units.

The obsolete ZH constructor in DefectorSpecialPower.cpp competed with the
rowed flat constructor. The earlier banked layout trial removed the flat
provider but left a stale strong provider in the census. This repair keeps both
units in the overlay: the existing constructor unit uses the actual virtual
class and owns both implicit destructors; the obsolete constructor is removed
from the home unit. Thus neither a deleted-unit overlay nor an artificial
vtable-emission anchor is needed. The flat unit's alternatename is removed.

Target facts: native constructor 0x004C2A6A writes FatCursorRadius at +0x7C;
parse entry 0x00C5C764 independently gives that field offset. Native table
0x00C5E7A8 identifies deleting destructor 0x004C2A84, whose 28-byte body and
relocations match. Ordinary destructor 0x004C8AB0 is the exact five-byte tail
jump to the rowed SpecialPowerModuleData destructor 0x0049334F. The constructor
remains its exact 26-byte body. Both units pass their byte gates after rehoming.

Donor facts: declarations come from verified BFME1 pointer
f36a4db066aa61edeee90085a31d628eb829001d; the scoped SpecialPowerModule header
retains its earlier donor provenance and the already banked layout adaptation
under link-seat-20261022-codex/defector-layout-rehome.patch. Eight additional
base bytes are required by the target offset; their meanings remain unknown.
No donor field identity is asserted for those bytes. The newer donor linking
repairs were reviewed read-only; no reference pointer was advanced.

Claims cover both changed source files and their six original/current row RVAs.
Ledger and undeclared-definition checks pass. No pins, verifier changes, data
aliases or new authored bodies are introduced. t=45 model=gpt-6.1-sol.
