# OCLUpdate frame receiver prerequisite, 2026-10-25

Scoped planner and current in-memory TU plan approve the frame getter donor for
GameLogic/Object/Update/OCLUpdate.cpp. Current Luna handoff records C2039 because
the seed receiver omits getRemainingFrames. Both file scopes were claimed before
editing; frozen checks pass before and after. No other seat's claim was touched.

The seed and frame donor now declare the same virtual receiver, nonvirtual getter
and timer at +0x20 (four-byte primary vptr plus 0x1C bytes padding). The virtual
name-key declaration already belonged to the seed; the timer offset already
belonged to the rowed frame getter. No function expression or compiler flag changed.
These are existing target facts, not a donor-derived full-class layout claim.

./build.sh passes all four rows, including the name-key EH handler, with string,
float and import checks. The supported normal merge dry run accepts the seed and
frame donor, four rows, clearing the reported declaration blocker. Leave this
compatible donor for Luna. Countdown and xfer still report no destination baseline;
the behavior constructor still needs base/receiver reconciliation. Mixed files
remain intact. Exact trial: build/codex-ocl-frame/dry-run.txt.

No merge applied, source path moved, file removed, debt retired, hatch added or
C++ byte recovered. The publication audit sees no source path moves in the pending
range or staged change, so path consumers need no repointing. File claims remain
until publication; no RVA claim was acquired. The earlier FunctionLexicon handoff's
retail-byte sum is corrected to 371 (108+48+42+77+48+48); its verified rows are unchanged.
