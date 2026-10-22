# Link ownership follow-up, 2026-10-22

Inputs: BFME2 21387ea4c9; BFME1 37c3022de1ab944c7ffe536440d637dc8199091c.
Published census index: 2026-10-22 11:05, ae3b3e68e2. All source trials below
were restored. No linked-byte improvement is claimed from refreshing old objects.

## ProductionPrerequisite

The RTS/ProductionPrerequisite.cpp ZH-derived, present-unmatched addUnitPrereq
strong definition duplicates Thing/ProductionPrerequisiteAddUnitPrereq.cpp's
matched method. Paired current-object baseline with those two files and
ThingTemplateParsePrerequisiteUnit.cpp: only the last file links (117 B);
RTS holds 429 B and Thing holds 185 B. RTS has additional string/allocator debt.

Removing the ZH method loses three rowed workers: vector<PrereqUnitRec>::push_back
0x4F5243, __uninitialized_copy 0x4EE1E2 and __uninitialized_fill_n 0x4EE20B.
Explicit push_back member instantiation instead is refused by MSVC 7.1 C2248:
PrereqUnitRec is private in the donor header. An out-of-class dllimport
forceinline definition fails C2375 against the non-imported header declaration.
Plain inline compiles but again loses exactly those three workers (3/6 rows fail).
The body itself is the unchanged donor: assign name, flags and null unit to a
PrereqUnitRec then m_prereqUnits.push_back(info).

Next work needs an owned declaration/access repair or an exact provider to which
these workers can be rehomed. Do not repeat removal/inline without that change.
Flags and all donor dependencies remain those of the committed source.

## Vertex declaration

BfmeFVFDescriptorVertexDeclaration.cpp holds 1,715 B, including the 1,705 B
0x1818C0 body and its EH handler. Local ICoord2D __uninitialized_copy and
vector::_M_insert_overflow copies disagree with retail 0x4C3121 / 0x181770.
Declaration-only copy alone, and copy plus overflow together, both change the
parent (1/2 rows fail). The combined trial changes saved receiver/registers,
overflow argument stores and reloads throughout the parent; copy alone also
changes it. Callee visibility is load-bearing. Source restored after two gates.
MapUtil owns overflow; stlport_vector_e8_o1 owns the native copy body under a
different element spelling. No alias/pin or provider weakening was attempted.

## Stale census leads and limits

Paired checks show the narrow num_get integer helpers, CreateAHero's manager
owner, strategic constructor ownership and quick-match predicate/partition chain
already link with current providers. Pooled Object-list cleanup has a provider in
HordeContainRva00475F61.cpp; inspect it before treating the old selected-copy
finding as new work. PartitionFilter's native versus ZH table split is already
repaired upstream (efe1830c5a); no header access trial emitted another table.

Current-ledger strict preview refuses 143 missing current receipts; the global
census was not rebuilt. name_globals --dry-run reports zero edits. rehome_rows
cannot run without build/link_census/census.log; no matching data-back artifact
was available. These are measurement limits, not proof that all work is exhausted.

## Chat.cpp: verified repair

Static STLport declarations plus the existing bfmealloc headers replace imported
helper references with the rowed native implementations. The unmatched Zero Hour
`GameSpyInfo::addText` body was removed: its unverified audio construction was
unrelated to the four matched rows and pulled in two unavailable providers. Its
source remains in git history, like the previously removed sendChat/addChat bodies.
No matched definition or ledger row was removed.

Same-index explicit-unit legacy preview: before 0/185 B, after 185/185 B linked.
The first static-STL trial still emitted an unproven __new_alloc::allocate; opting
into bfmealloc removed that copy. Both trials passed all 4/4 byte rows, including
the 20-byte INI parser. Final `link_check.py --prepare-current` issued a reusable
strict compile receipt; `--new-variants` passed. This is a legacy local linkage
gain, not a closed-strict or full-link measurement. No census or link cycle ran.
