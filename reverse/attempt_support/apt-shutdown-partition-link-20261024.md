# Apt shutdown ownership partition

BFME2 b5d28bada3; published census a9f880ad06 (2026-10-24 07:31,
retail-truth-4). Verified BFME1 pointer 32774ab03393 remains fresh.
Reviewed the donor BfmeConv1292 source and the existing component-hash
repair; the hash walkers still need their target-specific native providers.
Existing source comments retain donor revision, native boundaries and layout
provenance. No donor update or identity inference is introduced here.

BfmeConv1292.cpp contained the independent Apt shutdown at 0x00411B52,
two resolved teardown thunks, and five rows reaching unresolved or competing
hash/teardown contracts. Move those five rows unchanged into
BfmeConv1292DeferredWalkers.cpp, preserving compiler flags and declarations.
The shutdown owns AptShutdownReceiverInstance in its original unit.
No aliases, pins, function bodies, data values or ABI contracts change.

Paired scoped command:
`python3 tools/link_check.py Code/GameEngine/Source/Common/BfmeConv1292.cpp`
changes from 0 to 809 linked authored bytes, using current objects and the
same frozen index. This is a legacy preview, not a closed-strict result or
new census. The new deferred unit has no index position and earns no gain.
The retained unit has 19 byte-exact rows; the deferred unit has five.
EH verification reports the shutdown graph EXACT. Compiler label renumbering
is resolved by its proven parent EH graph. Source declarations and CSV pass.
Scoped strict reusable input preparation also runs the normal byte gate.

Remaining walker prerequisites: native pointer-table bucket index, node
release and iterator advance providers; the 44-byte mapped value table's
bucket/erase contracts; generic delete callback ownership; and the existing
0x00410C7B duplicate teardown identity. Do not suppress their emitted copies
or replace them with unrelated same-sized helpers. Existing row identities
and notes remain intact for subsequent recovery.
