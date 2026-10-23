# Skirmish preferences link repair, 2026-10-23

Two independent blockers prevented the recovered preferences unit from linking.
The Zero Hour no-argument constructor in SkirmishGameOptionsMenu emitted the
first SkirmishPreferences vtable. BFME2's recovered constructor takes an int
profile index and its table has 13 slots at VA C3D658 (deleting destructor
43C4B6, UserPreferences methods, write override 43C6C7). Remove the unrelated
Zero Hour constructor, retaining the recovered constructor and the menu's
matched bodies. The remaining unmatched Zero Hour menu callers still require
porting; the menu unit is not claimed as linked.

The encoded-name assignment called AsciiString::set, a pin to 366F0 whose
selected ThingFactory copy is not retail. Call the existing rowed
StringBase<char>::set directly, as the other assignments in this same unit
already do. The shared shim establishes the identical four-byte string view;
this changes the symbol spelling of the call, not the native destination.
No pin, alias, header, layout or ledger extent changes are needed.

Paired tools/link_check.py preview of the preferences and menu units, using
published index 491a8b3d87 (2026-10-23 03:12): before 0 -> 0 B, after
0 -> 2175 B. Preferences LINKS; menu remains blocked, with no matched-byte
regression. This is a scoped legacy prediction, not a placed, self-strict,
closed-strict or runtime measurement.

Acceptance: ./build.sh both sources passes 68/68 rows, 13 literals and two
empty-string references; eh_verify reports 14/14 EXACT graphs;
find_declared_unmatched passes. Strict reusable object receipts are prepared
with link_check --prepare-current; this verifies current inputs rather than
link closure. No maintainer-only runner was started.
