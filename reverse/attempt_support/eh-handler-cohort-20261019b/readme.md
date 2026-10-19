# Thirteen natural C++ exception handlers

This cohort accounts for thirteen previously unowned 10-byte handlers emitted
by existing verified C++ owners: 130 unique retail bytes. It adds no gameplay
reconstruction. Each native parent prologue directly installs its handler and
the handler names that parent's FuncInfo. The complete handler, parent body,
exception tables and cleanup sections pass the normal byte and EH checks.

`receipts.json` records the parents, handlers, FuncInfo and unchanged source
hashes. `callee-proof.json` separately checks cleanup call destinations, beyond
the EH verifier's masked relocation slots. An emitted cleanup must match the
native callee's entire ledgered extent and its subordinate bindings, even if
the name already has a binding. External-only callees must have an agreeing
existing binding. No new pin, alias or generated source is used.

All thirteen owners pass bounded prepare-current checks with strict reusable
include-inventory receipts. Their current lightweight link preview reports
13/13 LINKS against published census 4ae54b0a4f (2026-10-19 10:38 UTC).
This is a local prediction, not a new census or measured linked-byte gain.
No link cycle or runtime verification runner was started.

The selection excludes seven audited leads whose parent EH graph or emitted
cleanup body does not agree with retail. In particular, a 14-byte private
bucket destructor must not stand in for the native 131-byte vector destructor.
All thirteen accepted source files were read in full and remain unchanged.
There are no header, compiler-setting, verifier or baseline edits.

Raw preparation, link preview, EH checks and normal admissions are retained
under ignored build/handler-cohort-oct19b. Model: gpt-6.1-sol.
