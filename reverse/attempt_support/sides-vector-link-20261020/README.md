SidesList vector call bindings, 2026-10-20
=========================================

Baseline BFME2 2d0c1dbc389c83fc8617feb7f4201e87de986bac; BFME1 inputs remain at verified gitlink
92f6bbe8e1dcdb46b5d27da0674313efc822b790. No donor source imported.
The reference linking repairs reviewed at that revision use the same principle:
call an existing row owner rather than a separately pinned private spelling.
All call and layout facts below come from BFME2 retail and existing matched rows.

The 186-byte assignment at 0032C0E3 calls destroy 0032B580 and clear
0032BF1B. Its alias names selected other emitted, nonretail copies. Casts now
call the existing row owners directly: _Destroy<Rva0032A3A9Element *> and
Rva0032BF1B::~Rva0032BF1B. They express the known callable ABI and do not
identify the assignment's 128-byte element type. The original three linker
aliases are unchanged.

The related record unit now declares the external rowed vector assignment.
Its unused POD destroy specialization remains inline without emitting the
conflicting no-op copy. Its constructor36B and two folded assignments43B
are unchanged; the shared address is counted once (79B total).

Paired proof.json uses one unchanged census index (5366c4f808, retail-truth-2),
current strict receipts and current rowed helper objects in both measurements.
Before: neither unit links. After: both link, +265 nonpadding retail bytes
(186+79). This is a LEGACY link prediction with self-strict current objects;
closed-strict closure/gain was not measured. No authored-byte growth.
Retained nondebug code/data/EH, flags and relocations agree after the two
proven call-name substitutions (including compiler-generated declaration
aliases). Removed COMDATs are listed. The explicit destructor call also emits
an incidental scalar-deleting wrapper; it owns no retail address and is not
counted as recovered code.

Checks: ./build.sh for both touched units; --prepare-current for both plus
destroy/clear providers (6/6 rows, string/float/import checks pass); paired
link_check on touched units (0 -> 265B); EH verifier (no EH graphs in these
units); data/converged, class gate and declared-definition checks pass.
No full link cycle or census run.

Related failed lead: checkIdleTeams 0059AA37, native402B plus EH handler10B,
was restored and released. Its emitted Object* push_back49B differs from the
rowed58B wrapper. An opaque specialization changes the caller's cleanup and
register scheduling; explicit visible default specialization preserves2/2
rows but retains the49B wrapper. A codegen/visibility prerequisite remains;
the detailed verdict is in re_attempts.log. Do not repeat those two trials.
