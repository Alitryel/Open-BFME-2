String-record vector copy binding
================================

At 99b579bc20, Rva003371B1Copy.cpp loses its local vector allocation
constructor and __uninitialized_copy COMDATs. Declaring only these two
helpers preserves all five rowed bodies but exposes a third conflict: its
local vector copy constructor. Declare that constructor instead and bind to
the existing row at 0x0033629E in
stlport_vector_stringrecord_331962_allocate_copy.cpp. The native caller's
REL32 to that row already established the relationship. Preserve the record's
existing provisional identity, 12-byte layout and all field declarations.
No new pin, alias, imported symbol, or type substitution is used.

Paired legacy predictor, index 3f413ed3ff (2026-10-20 18:52): saved original
object versus repaired object, refreshing the unchanged vector provider on
both sides. The edited unit improves 0 -> 122 B. Provider remains 0/273 B:
it has an unresolved record default constructor and a nonretail assignment
copy. These independent blockers preclude a closed-strict claim. The
unreferenced vector-destructor difference is diagnostic only and is retained.
See paired.json for object/index hashes and exact findings.

Other family units were checked: Rva0033269B (115 B), vector overflow
(183 B), partial sort (646 B), and Lua ProcessEventList (799 B) already link.
Their 1,743 B are not new gains. The provider needs its own supported repair.

Validation: ./build.sh 5/5 MATCH; --prepare-current 5/5 strict reusable
receipts; EH EXACT 2/2; converged-data zero second names/unjudged rows;
class and declared-definition gates pass; check_csv and diff --check pass.
Authored-byte growth is zero; paired legacy linked-byte gain is 122 B.
