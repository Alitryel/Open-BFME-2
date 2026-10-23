# FESL message key ownership

At parent 7ffa45b42b the two current units fail the legacy link preview only
on undefined key pointers. Owning the two pointers makes 24 + 77 = 101 existing
matched bytes link. Self-strict reusable receipts cover the changed units;
no closed-strict result or full link is claimed.

Retail VA DD8310 contains the pointer BED340 to the complete string "ID".
The rowed wrapper at RVA 668070 passes it to RVA 655960, whose existing
FeslMessageAccessors body independently establishes integer insertion by key.
The existing canonical data-ledger name g_bfmeWhatBKG and void-pointer ABI
are retained; the donor placeholder spelling is not asserted as a target name.

Retail VA DD8284 contains the pointer CE3148 to the complete string
"localizedMessage". The wrapper at RVA 665470 passes that key and its output
arguments to RVA 655B10. Its rowed getString body establishes the key lookup,
copy and output-size behavior. Again the existing data-ledger spelling is
retained. Both four-byte definitions are independently size-proved, and their
literal relocations and complete NUL-terminated contents are verified by the
normal data gate. /GF makes those literals placeable compiler COMDATs.

The same DD8310 address is still declared under g_rva00668090Key in
VslotSmallBodiesQ.cpp. That unit also needs two other key pointers and a
registry table with an unproven extent. It was inspected but not changed:
renaming just that declaration would not link its unit. This repair adds
no second global at that address.

Acceptance: before/after link_check, --prepare-current (all four code rows and
both data rows), shadow data check (zero findings), frozen-source check,
check_csv, plus normal commit-hook code-identity/EH/converged-data checks.
Native target data and existing rowed callee evidence establish both repairs;
no donor layout or address was imported.
