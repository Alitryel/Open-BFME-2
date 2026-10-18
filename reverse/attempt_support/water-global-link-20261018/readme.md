# Shared water setting and recovered getter names

Existing data_rows owns TheWaterTransparency, OVERRIDE<WaterTransparencySetting>,
at RVA 9FF488, four initially zero bytes, in INIWaterTransparency.cpp.
The parser allocates and replaces that setting. Both rendering readers use the
same native address and final-override walk, then its measured flag at +50.
Rename their address-derived setting view and global to that existing owner;
keep the measured private layouts and inline walks unchanged.

The query's native REL32 at 7FDFB targets 308DF0. The existing 60-byte owner is
Rva00308DF0::rva00308DF0 returning class Rva00308DF0Ref*. Rename the obsolete
receiver/result declarations accordingly. The result view here only supplies
the target-observed +1C kind read; it does not change the provider layout.
No pins, aliases, definitions or data rows are added.

Against published c2c5ac8c27 index (2026-10-18 11:36), current-source preview:
- before, WaterDraw 0/1443 B; query 0/146 B; getter provider 60/60 B;
- after, WaterDraw 0/1443 B; query 146/146 B; getter provider 60/60 B.
Total legacy LINKED gain +146 B. No self-strict/closed-strict/full-link claim.
The two-unit global-name sweep intentionally retains the same naming repair in
WaterDraw; its unrelated destructor remains blocked and recorded in re_log.
A novtable trial did not remove that blocker and was discarded. Prior particle
binder attempt59179 rules out blindly repeating inline import suppression.

Acceptance: build.sh/prepare-current passes all13 function bodies across the
two consumers and provider, 28 literals, three imports. Strict reusable compile
receipts issued for all three, with no strict link closure implied. EH EXACT3,
class_gate, find_declared_unmatched and diff whitespace checks pass.
Unreferenced OVERRIDE conversion/accessor relocation diagnostics are exempt
under retail-truth-2 and were not suppressed. No authored C++ bytes added.
