# River virtual-base reconstruction: 0030C4C6

Owner: astra-s1. Model: gpt-6-astra. Date: 2026-10-23.

## Native identity and layout

The eight bytes at RVA 0030C4C6 are `2b 49 fc e9 d4 f9 ff ff`: subtract
`[this-4]` from ECX and tail-jump to 0030BEA2. All seven neighboring thunks
use the same adjustment. The only native table containing these thunks is
VA 00C088E0, installed by the already-matched river constructor 0030C4DE
and destructor 0030C40A. Its entries, in interface order, are:

| slot | thunk RVA | method RVA | method size |
| --- | --- | --- | --- |
| 0 | 0030C4BE | 0030BE96 | 12 |
| 1 | 0030C4C6 | 0030BEA2 | 68 |
| 2 | 0030C4A6 | 0030BCAE | 4 |
| 3 | 0030C4CE | 0030BEE6 | 19 |
| 4 | 0030C4AE | 002BFBF0 | 7 |
| 5 | 0030C4B6 | 0030BCB2 | 8 |
| 6 | 0030C4D6 | 0030BEF9 | 19 |

The constructor stores the virtual base at +90, its vtordisp at +8C, and
its quad strip at +68. Its vtordisp initialization subtracts 78 from the
vbtable displacement (the vbptr is at +18), so the thunk delivers the
receiver projected to +90. The override bodies consequently access the
quad strip at receiver-28 and m_64 at receiver-2C. The matched constructor
and destructor already establish this inheritance and member layout.

The all-pure interface is VA 00C6EE28. The existing wave and polygon
constructor TUs already spell its seven slots, including by-value point
and Region2D results. Rva00330C50Ctor.cpp emits the same eight-byte
vtordisp idiom with a hidden-result point slot. Thus this is a class and
ABI reconstruction, not a new free-standing wrapper.

## Failed and successful experiments

The existing nonvirtual wrapper spelling forwards a hidden result buffer
through a real call and compiles to 23 bytes. Changing copy construction,
assignment, constructor visibility or same-TU callee visibility does not
remove that ABI forwarding. The successful route declares the actual
virtual overrides on Rva0030C1FCOwner and lets the compiler generate the
construction-vtable thunks. No assembler, fabricated pin, alias body or
encoded byte sequence is used.

An isolated native-layout diagnostic reproduced all seven method bodies
and all seven thunks with REL32 targets resolved to established owners.
The prepared actual constructor and destructor TUs also reproduced their
317-byte, 156-byte and 38-byte bodies and both EH handlers. Raw compiler
funclet labels changed; their placement must be checked through the normal
parent EH graph, not guessed from the new ordinal numbers.

## Supporting ABI corrections

0030BEE6 returns Region2D by value from the +68 member; 0030BEF9 returns
the shared two-float point by value. The former int-returning wrappers
misrepresented their implicit output buffers. Their providers are:

* 0053863E, 35 bytes: refresh when +20 is set, then copy the Region2D at
  +0C through the canonical copy constructor at 0004254E.
* 00538674, 67 bytes: refresh when +20 is set, then return the midpoint of
  the four bounds floats at +0C..+18 through its implicit output buffer.

Both corrected provider bodies reproduce the entire native function.
The existing 0053863E pin is changed in place to the corrected signature.
All old wrapper definitions and their old ledger ownership are removed;
deleted_rows.csv records the superseded names. The canonical shared point
spelling is the one already used by the seven-slot interface views.

002BFBF0 is a genuine shared zero-float body: 28 native table entries and
0030C4AE reach it. Its existing owner remains; the river override requires
an explicitly admitted ICF row after whole-body verification.

## Environment and validation

The seat began with an unpopulated BFME1 submodule. Its original large
fetch was still indexing after 45 minutes. Existing immutable object files
from seat s2 supplied the exact pinned commit without changing s2; the
s1 submodule now checks out 138757e9b74645fbcbb7724a7af2764e34931e11 cleanly.
Initial isolated experiments used extracted RTM cl 13.10.3077 tools and
headers only in ignored scratch. They are diagnostic evidence, not normal
admission receipts. The normal focused build and add_match gates use the
pinned checkout and are required before landing.

Normal pinned-input validation now passes: add_match admitted the ICF override
and 0030C4C6 after checking all 19 constructor-unit rows. The focused build
checks all 287 rows in the six remaining changed TUs. The constructor and
destructor EH graphs prove each renumbered funclet location; no ordinal pin
was added or changed. Total: 306 existing/new rows checked across seven TUs.

Reference freshness check found official BFME1 master at
38cba658aa0945145c3c8afd422a921f44636c2b. The last verified BFME2 pin remains
138757e9b74645fbcbb7724a7af2764e34931e11. No newer donor pointer or successful
freshness receipt is asserted: the original initialization fetch remains
active, and an upstream-reference advance needs its separate full comparison.

## Independent resumption by sol-recovery-20261023-b

The original section above records astra-s1's environment, not a fresh gate.
The implementation was resumed from committed bank 9411bbe0ef, with BFME2
at that same revision and the verified BFME1 pin retained. This seat had
independently reproduced the virtual-inheritance codegen finding in
river-vtordisp-30c4c6-sol-20261023.md before seeing that bank.

Fresh focused verification passed all 306 rows across the seven modified
sources. Normal add_match admission independently verified the complete
eight-byte thunk and seven-byte shared zero-float override, 19/19 constructor
rows each time. No new pin was needed for either body. The existing bounds
provider pin was corrected in place with its return-buffer signature.

The initial scoped link preview exposed an actual interface-definition
conflict: VBase00C6EE28's earlier one-slot copies competed with the corrected
seven-slot table. The river views now adopt the already-established
Rva00330C50Interface from Rva00330C50Ctor.cpp, which represents the same
native C6EE28 table with exactly these seven signatures. Its existing folded
destructor pin already resolves to 57A243. This is the existing native
interface identity, not a new alias, wrapper, or fabricated table.

After that adoption, another focused gate passed 30/30 rows in the constructor,
destructor and bounds-provider units, with unchanged bytes and verified EH
funclet graphs. The paired seven-unit link preview has six units clean,
including the 519-byte river constructor unit and 193-byte destructor unit.
GapForwardersSeat8.cpp still has its unrelated Object::slot unresolved; that
declaration and its caller already exist unchanged in the input tree. The
comparison index is the published 456ce161c5 retail-truth-4 census, not a new
census or a current full-tree link measurement.

Rescanning the constructor, destructor and bounds-provider units with
place_bodies found no additional bodies or pins. Before publication,
progress.py origin/master measured C++ exact +8 and handwritten game C++ +8.
The fourteen ownership/signature corrections retain already-covered ranges;
the shared zero-float override adds no unique bytes. Original semantic class
names remain unknown; address-derived owners and numbered slots preserve that
uncertainty.

## Integration refresh

The root integration rebase onto BFME2 0393df10e2 includes upstream's verified
BFME1 pointer update 4f08dcdb9e to 96c88c73a5cd1a58fc2f8db691beea50acd996db.
The clean root donor checkout was advanced to that committed pin; this is not
a separate freshness success receipt from this seat. The earlier focused
receipts above used 138757e9 and are not asserted as verification of the new
inputs. A fresh complete normal commit gate is required before publication.
The rebased prepublication progress measurement still reports C++ exact +8.
