Buildable override map ownership, 2026-10-20

GameLogicSetBuildableStatusOverride emitted a hash_map::operator[] over its
existing 8-byte AsciiString view. That copy differs from rowed retail 002460C3
and displaced the exact provider in VAsciiStringRva002460C3. Declare the existing
specialization and explicitly instantiate the setter unit's three independent
rowed helpers, retaining their established layouts and claims. No identity,
layout, pin, address, baseline or verifier changes. The whole provider object
is unchanged; retained named code and relocations in the setter are unchanged.

Paired legacy-index preview against 3f413ed3ff (2026-10-20 18:52) improves
0/2 to 2/2 units, 0 -> 222 nonpadding matched bytes (91 + 131). Both original
and final providers have self-strict reusable receipts and pass all 8/8 rows,
including EH handler and cleanup. Closed-strict closure, executable placement
and fresh census gains remain unmeasured. Authored C++ coverage +0.

Acceptance: strict normal byte/reference gates before and after; link_check
paired preview and new-variants; class_gate, find_declared_unmatched, converged
data and diff checks. Independent target evidence remains the existing ledger
and native call at 246F71. BFME1 ownership repair review reused at verified
4483e88da1c2 (a411b334c,3313189ad,c54305633; recorded in
special-ability-frame-global-link-20261020); no donor layout imported.
t=8 model=gpt-6.1-sol.
