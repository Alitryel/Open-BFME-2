# MonitorConditionUpdate link reconciliation

Target evidence: retail ctor 0x00491633 and destructor 0x004916AC restore bases
at offsets 0, 0xC and 0x10; the string member is at 0x20. Primary table
0x0084DAD8 starts with deleting destructor 0x00491750. The update-interface
table at 0x0084DACC has three entries: 0x0049176C (update), 0x00253376
(getDisabledTypesToProcess), and 0x0044DF8D (existing address-based method).

The destructor TU inherited a spurious first virtual and declared only one
update-interface slot. The deleting-destructor provider independently used
a single-base-less class view, so its unqualified vtable symbol represented
the primary table while the destructor TU used that symbol for the update
interface. Correcting only the first slot left this duplicate-COMDAT conflict.
Reconcile both TUs to the target-supported multiple inheritance and the three
known update slots. The provider uses the registered ascii_string.h header,
rather than introducing a private StringBase copy. Its existing emission-only
constructor remains explicitly absent from retail.

Verification: focused build passes all five existing rows (73-byte destructor,
10-byte handler, 8-byte unwind, and two 28-byte deleting destructors).
The renumbered unwind label is verified through its parent EH data. Placement
resweep finds zero additional bodies or pins. Paired link_check against the
published index measured at 491a8b3d87 (2026-10-23 03:12 UTC) changes the
destructor unit from 0 to 82 nonpadding linked bytes, while the deleting
provider retains all 56 bytes: paired total 56 -> 138. This is a local
prediction, not a new census, closed-strict link or runtime result.
No pins, new aliases, ledger identities or shared headers changed.

This is a target-supported class-view repair, not a donor transfer. The
read-only s1 donor checkout currently contains no populated source tree.
The seat's pinned BFME1 reference is 138757e9b74645fbcbb7724a7af2764e34931e11;
no donor identity or target layout claim is inferred merely from its bytes.

model=gpt-6-astra seat=s4
