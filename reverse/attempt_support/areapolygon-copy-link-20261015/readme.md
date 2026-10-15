AreaPolygon bounds copy-constructor emission repair

BFME2 base: 3f022a294566d1d3418b8d3f4bc07636d34e1c70. Measurement/index:
ac77c85054, 2026-10-15 14:25 UTC; SHA256 recorded in object-proof.json.
No per-row data-back artifact or ranking was inferred.

AreaPolygonUpdateBounds.cpp was the sole losing copy of
??0MathCoord2D@@QAE@ABV0@@Z. The index contains two copies, first in
PathfinderSidewaysAttack.cpp, then this unit, with different digests and
unknown retail verdicts. This repair makes no claim that either standalone
constructor is retail's. The affected bounds method already inlines its copy.
Adding dllimport/forceinline to that local constructor suppresses only its
unused external copy. No global type layout, identity, ABI or provider changes.

Donor review: verified BFME1 pointer a7c38d3b2597121f178ab5190b3062478823257d;
read-only upstream review through 95eeb3bef370a7cd730b0ad5f228c317c8756e72.
BFME1 c1315665a1b22beb7e6d9279548fe5b1c26ed1f9 suppresses unused
DamageInfo constructor copies this way. Its emission principle applies;
no donor layout/identity is asserted for this BFME2 class. Current BFME2
AIHuntStateUpdate and AIClosestEnemySearch already use this principle and
were skipped despite their still-listed census blockers. The BFME1 freshness
pointer update is foreign-claimed (codex-6bc6-20261008). Kept verified inputs;
no freshness success stamp or unverified pointer change was made.

Before AND after, link_check.py --prepare-current on the explicit owned
unit produced strict reusable receipts and passed the normal byte gate:
1/1 row, 478 bytes, seven float references. Saved source, object and receipt
are under build/areapolygon-copy-link-20261015/before. object-proof.json
records their hashes. The scratch proof uses the section/relocation parser
in reverse/attempt_support/moduledata-snapshot-link-20261015/sections.py:
all 19 retained nondebug sections have identical bytes, flags, external
definitions and symbolic relocations. The sole removed section is the 19B
constructor (bytes in JSON); no retained section references it, no import
is introduced. The indexed first peer was neither edited nor recompiled;
its object is unavailable locally, so no provider-current or closure claim.

The paired preview refreshes only the owned before/after object in separate
in-memory copies of the identical index. Legacy findings 1 -> 0; predicted
LINKED 0 -> 478 existing bytes. This is a locally checked legacy improvement,
not a measured census or closed-strict gain. Authored C++ byte growth is zero.
The index and reverse/link_status.csv remain unchanged.

checks.json contains commands, statuses and output for byte, definitions,
class, variant, enforced/converged data, EH, placement, ledger, local link
and whitespace checks: all pass. Placement found zero additional bodies.
No full census, link cycle, nightly or boot operation was invoked.
