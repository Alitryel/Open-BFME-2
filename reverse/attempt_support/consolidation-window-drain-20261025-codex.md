# WindowLayout drain prerequisite, 2026-10-25

Reviewed the current planner, original-path alternatives, Luna handoff and current
in-memory TU plan. WindowLayout.cpp and Rva00538ADCFinish.cpp scopes were unheld
and claimed before editing; frozen checks pass before and after.

The destination now declares the drain donor's existing slot7 and rva00538ADC
callables after its seven existing virtual entries. Both files use that identical
receiver declaration and GameWindow callable view. Slot indices remain 7/8,
head remains at +8, and the donor's loop/null guard/call expressions are unchanged.
Names come from the two rowed BFME2 views; no donor-derived identity or complete
original class recovery is asserted. No new pin, flag, global or hatch.

./build.sh verifies all three rows, 112 retail bytes; string/float/import and
frozen checks pass. The normal tu_skeleton merge dry run accepts both files,
three rows, clearing the prior missing-method/member failure. Exact trial is
build/codex-window-drain/dry-run.txt. Leave the compatible donor for Luna.
The default constructor still lacks its declaration and typed member/base
reconciliation. The other constructor is mixed, and window_layout.cpp is
protected-register refused; neither is changed or bypassed.

No merge applied, path moved, file removed, identity debt retired or new C++ bytes.
Before committing, reviewed origin/master..HEAD plus staged changes: there is no
pending source-path move and no path consumer to repair. Keep the two file claims
until publication; no RVA claims were acquired.
