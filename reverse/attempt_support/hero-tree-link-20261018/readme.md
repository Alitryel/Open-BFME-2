# Hero tree provider repair, 2026-10-18

Replace the whole-tree instantiation with the two recovered insertion members.
Existing explicit copy construction and assignment still instantiate their
required helpers. Declare the already-owned destructor (0x0021E0FC,
CreateAHeroDataDtor.cpp) and non-hinted insert (0x0021D203,
stlport_hero_integer_vector_tree_insert.cpp) so this unit calls their retail
providers instead of emitting nonmatching copies. The latter provider enables
_BFME_RETAIL_TREE_INSERT_LAYOUT; the copy unit needs its existing flags for
its other bodies. No compiler flags or shared headers changed.

All 12 existing rows, including the parent-bound 14-byte unwind funclet,
pass the byte gate with strict reusable receipts. The compiler renumbers its
funclet label; the unchanged parent EH map proves the same retail placement.
No new pins, aliases, object-symbol rows or coverage are introduced.

The same three explicit units and same published c2c5ac8c27 index were measured
before and after, restoring the original source for the before run and then
re-preparing the candidate. Legacy bounded selection preview improves
0/3 -> 3/3, +1507 existing authored bytes (1321 + 134 + 52). Only the copy
unit changes; removing its competing insertion copy also unblocks the two
unchanged insertion units. These are self-strict byte receipts and legacy
selection results, with no closed-strict census or runtime claim.

The current destructor provider was checked too: it still has independent
AsciiString-tree, bool-vector and int-tree blockers, and contributes no gain
to this result. Other consumers of this tree have independent blockers and
were left untouched. Donor review is the same verified BFME 1 64d369b9 and
upstream 95ca17f1/97a7c973/d348fca1 review recorded in the preceding STL-emission
repair. The repair preserves established BFME 2 STL identities and layouts.
