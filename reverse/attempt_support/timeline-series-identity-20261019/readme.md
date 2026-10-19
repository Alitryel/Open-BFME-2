# AptTimeLine concrete series and virtual-provider repair

The matched RenderGraph at RVA 0x0051EED7 (2048 bytes) constructed two private
series names, while the existing 22-byte constructor owners used Rva0051E716
and Rva0051E73E. Their consuming views also disagreed on the abstract base's
fields/novtable property. More seriously, the old constructor unit's first
vtable referenced an inline value method which compiled to nine bytes returning
zero. Retail's corresponding slot points at the already recovered 103-byte
value method. The second table inherited that same zero method, where retail
uses the separate 168-byte record evaluator. These are actual provider defects,
not just a missing handler or a diagnostic naming complaint.

Target evidence: the two complete tables at RVAs 0x00867268/0x00867270 contain
the four destinations 0x0051E72C, 0x0051E96B, 0x0051E754, 0x0051E9D2. The
existing constructors at 0x0051E716/0x0051E73E install them and initialize the
word at +4 and selector at +8 in 12-byte concrete objects. RenderGraph stores
the player's row at +4 and calls the two virtual slots as count and float
value. The count/evaluator pairs independently establish 20-byte and 12-byte
record ranges. WorldBuilder 0x013DC050 and the callback registration establish
the renderer's identity, as the existing parent documents. Original series
class names, source inheritance and ownership of fields in an original base
remain unknown: TimelineSeries is a consuming two-slot interface, the existing
address-derived concrete names are retained, and the row pointer is opaque.
The reconstructed concrete layout and both emitted tables are byte-proven;
the source hierarchy is not asserted to be recovered original inheritance.

Use those existing concrete owner names in the renderer. Give the used views
the same abstract interface and concrete declarations, remove the stale zero
method, and put each already recovered evaluator in its actual value slot by
renaming its existing ledger owner in place. No second name, pin or address is
added. Rehome the two existing 22-byte constructor rows to their real inline
caller and remove the redundant strong definitions from the old unit. Count,
point and marker bodies stay there. Remove unused series/data definitions from
the split line-helper unit. No shared header or canonical-class contract is
changed or newly claimed.

The complete five sources and all prior attempts at the affected parent,
handler and evaluator boundaries were read before work. Five bounded normal
trials first proved the renderer, both renamed evaluators, the count accessor
and the 339-byte line helper exact. Normal build.sh then verifies all ten
existing rows across five sources (23 strings, 12 compiler floats). The whole
family audit checks all six emitted constructor/count/value bodies at their
full extents, strict dependency receipts and both entire eight-byte tables
with both DIR32 destinations resolved. before.json preserves the old views;
the old AptTimeLine.cpp object was strictly current and its nine-byte zero
method/table references were read directly from COFF.

Admit the naturally emitted handler at RVA 0x00795FB8 (10 bytes), FuncInfo RVA
0x00949840. Complete EH verification is EXACT, and every cleanup/runtime binding
passes the independent whole-callee audit. Normal add_match verifies all four
renderer rows. This adds ten unique strict C++ bytes only: the 2048-byte parent,
two constructors and two evaluators were already counted. No assembly, volatile
barrier, new alias, pin, marker, verifier or debt-baseline edit is introduced.
Follow-up place_bodies across all five units finds zero bodies and zero pins.

Final identity preflight covers eleven rows with no definition findings. One
pre-existing shadow binding finding remains in the unchanged 339-byte line
helper: its flush target 0x0011A040 is the unowned 7476-byte Render2D routine.
The helper's existing split, name and target are retained; this repair does not
claim to recover that dependency or make the whole screen link. The new-variants
preview passes. A refreshed published-index preview refuses the renderer,
which is absent from census 8eecc93d07. The published index asset was checked
again: unchanged 13:58 UTC, SHA256
3926b37009a549f517f54bff273cf32e64dc97630444b792ac7ba8a3d8441600.
The unchanged index was not downloaded again; no census/link-cycle/runtime
runner or whole-tree preparation was started, and no measured link gain is
claimed. The previously observed current-ledger receipt shortage is not retried
without new compiler evidence.

Input tree: 1341cd19f105556f92a1cbc0a6a892fbce384495; BFME 1 dependency pointer
6b9d92bf92debd03e4357462bab41f701651e67c. Existing source compiler flags and
semantic donor provenance remain unchanged. Source/object hashes and strict
currency are in whole-family-audit.json; native handler bytes are in
handler.json. Raw bounded trials and the transformation/audit scripts remain in
build/timeline-series-repair-oct19. Model: gpt-6.1-sol, about fifteen minutes.
