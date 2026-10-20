# Drawable shroud notification: checked bitset recovery

Target `?onComingOutOfShroud@Drawable@@AAEXXZ`, 0x0027893E..0x00278C29,
747 bytes including RET. The new primary bank is still nonexact, but improves
the previous complete body and removes its volatile mask stores. No Code,
function row, pin, verifier or reference pointer was changed.

## Facts and source guide

WB 0x00CA3700 names Drawable::onComingOutOfShroud and Drawable.cpp; the complete
WB and retail bodies were read. Retail independently proves object FC,
template 4, status 114, reported flags 445/446, template kind storage 108 and
event integers 59C/5A0/5A4/5A8. The existing owned caller and pin declare the
method private: the bank now uses AAEXXZ rather than the farm's public QAEXXZ.
The change of access spelling leaves the emitted bytes identical.

The checked std::bitset approach follows the successful Elven Wood recovery,
using the real target STLport 4.5 headers. The 218-bit KindOf interpretation
also has target ledger evidence: named getSingleBitFromName at 2AA2F9, the
218-name table, and xfer at 2AC06A (loop DA, storage 1C). ZH BitFlags.h supplies
the wrapper/test semantic guide; its other class layout is not imported.
Only the observed template prefix and event locations are represented.

## Improvement

| Measurement | Previous bank | New bank |
| --- | ---: | ---: |
| Emitted bytes / retail | 727 / 747 | 740 / 747 |
| align_diff structural regions | 12 | 2 |
| Raw memory / register differences | 26 / 13 | 20 / 7 |
| Memory / register after excluding real COFF relocation sites | — | 8 / 7 |

The raw-memory column includes relocated globals. No positional patched byte
count is used as closeness proof: explain_mismatch's positional fixups after
size divergence can print misleading tail operands. The retained bank has no
unresolved calls, volatile writes, equal-arm conditions, assembly or unused
numbering locals. O1/G7/SSE/MD/EHsc, Ob1 and d2inlS100 inline the actual checked
bitset. Exceptions remain enabled; disabling STL exceptions changes nothing.
Initializing the template before the object, as WB does, gives retail's early
home stores. The object now occupies retail's -10 home and the frame is 18,
instead of the old 14. The template remains in EDI over the first reporting
block, while retail reuses EDI for the holder and reloads the template from
-14. Related reloads and the kind-7 test remain different. This is not an
exact recovery or C++ coverage credit.

## Controls not to repeat unchanged

- Checked test vs const operator[], direct access vs adapter, enum arguments,
  genuine BitFlags-style wrapper, word/byte-mask return views, and bitset-backed
  drawable status. Both kind checks need the checked-header shape to reach the
  best allocation; raw versions and direct member access regress it.
- Ordinary and force-inline adapters, Ob1/Ob2, budgets 0/40/60/80/100/120/200/1000,
  exceptions on/off, actual donor 4.6 headers, SP1/DDK compilers, G5/G6 and
  EHs/EHa/GX. The best regime stays 740 bytes; lower budgets outline test.
- Entry accessors/order, all four event accessors, enum event fields/context,
  shared Thing-prefix and event-window views, status accessors, shared mask,
  ready return carrier and skip carrier. None beats the retained body.
- Context aggregate, value/ref constructors and real std::pair; factoring the
  sighting region through by-value/ref inline helpers; goto and positive-report
  forms; two genuine reporting paths. They stay unchanged or regress. The
  recipe's 1..64 unused-local diagnostic is completely inert and is not retained.
- Whole nearest-object owner context: the real 214-byte rva00272AD5 body remains
  exact beside the 740-byte caller. No stand-in callee was used. Destination
  discovery names Drawable.cpp; the already verified nearest-helper owner is
  another integration lead, with its original receiver-name uncertainty intact.

Across the controls there are only about two dozen distinct parent objects,
not hundreds of independent discoveries. Existing older raw-view trials and
their handoffs were read before testing these changed inputs.

## Pointer-return finding

Rva004A1828Get is declared int, but the reporting, skill-point and defection
callers use its result as a virtual interface pointer. The entire producer and
its consumers were read. In scratch, both void* and holder-pointer return
views reproduce the whole 36-byte producer, including its virtual scan; the
parent remains 740 bytes. No second pin/alias was added and no ABI migration
was landed. A future repair should rename the existing row and reconcile all
three production consumers together, rather than add another name at 4A1828.

## Replay and inputs

Baseline BFME2 90794d89c2; verified BFME1
92f6bbe8e1dcdb46b5d27da0674313efc822b790. Scratch and all normal tool outputs:
build/shroud-stlport-bitset-oct20/. The first MSVC-standard-header control lives
separately in build/shroud-bitset-oct20/; it is not the retained STLport result.
The primary bank and sibling core-replay, whole-owner, holder-return and metrics
drivers preserve the useful resumption artifacts. The fresh before/after
align_diff logs reproduce the table. The final private/Ob1/exception-enabled
source's raw object equals the best earlier public/Ob2 object byte for byte.
No matching or cleanup gate was waived. About 22 minutes, gpt-6.1-sol.
