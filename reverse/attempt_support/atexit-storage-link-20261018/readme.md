# Initializer storage ownership

At parent 6ab7e5e293 the original Rva007AB85CAtexitInits.cpp and its
split _Rva007ACD90.cpp both define the same twelve unsigned globals.
They have identical names, declarations and four-byte zero initialization.
The original unit already owns their data rows and explicitly constructs
the string objects in that storage. The split unit only registers five
callbacks and does not own or access any of those twelve objects. Changing
its definitions to extern declarations retires twelve strong duplicates.
No new storage, alias, pin, initializer or type is introduced.

Rva004EA2C5Get previously declared E04490 as a separate const StringBase
object under another name. The existing owner is unsigned g_Va00E04490.
The rowed initializer 7B31DF explicitly constructs AsciiString("FarmTemplate")
there and registers its rowed cleanup. The reader now declares that exact
global and casts the accessed view, preserving the full55B retail body and
its data destination. No claim about the original source identifier is made.
The second, larger reader Rva004EA420Init.cpp was inspected but not changed;
it has independent vector/helper blockers and would not link.

The paired same-index legacy preview changes 0 -> 487 linked bytes:
432 in the original initializer and55 in the reader. The split60B remains
unlinked on five existing callback spellings, now without duplicates. Four
callbacks have callable rowed names; 7B796E is currently a source-local
compiler dynamic-initializer symbol in SmudgeRemoveSmudgeFromSet.cpp.
A complete callback/provider reconciliation is needed before counting that
unit. No closed-strict or full-link result is claimed.

Acceptance: all27 function rows and6 data rows byte-verified with strict
reusable receipts for all three units;12 complete literals checked; frozen
source checks pass; data shadow reports zero findings. Normal commit hooks
also check identity, EH, converged data and ledger integrity. The original
provider is unchanged but included in before/after and strict verification.
