# PlayerTemplate member-copy linkage, 2026-10-25

At BFME2 bf13b70af4, BFME1 0bf534ea7c, published retail-truth-4 census
ce1b975697 (2026-10-25 03:51), paired current-object legacy previews move
BfmeObject476Copy.cpp from 0 to 2,613 authored bytes linked. The census rank
still lists 4,593 historical bytes; that larger number is not credited.
No authored C++ coverage grows, and no self-strict or closed-strict gain is claimed.

The native hashtable copy constructor at 001FDCE1 calls the rowed 192-byte
_M_copy_from at 001FDC0F. This TU previously emitted its own helper under
the Rva001FDCE1Record spelling, requiring an undefined _M_new_node after
StlSweepR3Rva001FDCE1.cpp was deleted by rehome commit 9a911bb5d8.
A declaration-only specialization preserves the caller ABI and suppresses
that extra body. allowed_symbols.py --source ... --alternatenames then
generates the exact alias to the Rva001FDC0FRecord row owner retained here.
No new pin, node stub, second retail owner, or element-layout assertion is used.

The provider already binds its node allocation to the retail 00056E53 owner
(commit 88cc760665), resolving the prerequisite documented in
reverse/attempt_support/link-node-allocator-20261023.md. This repair uses that
new provider evidence rather than repeating the unsuccessful inline wrappers.
Opaque record names/layouts remain existing structural views, not target type facts.

Acceptance: all 137 source rows pass the full byte gate; bounded
--prepare-current verifies the same bodies and writes strict reusable receipts
without asserting LINK closure. --new-variants passes. Frozen-source check passes.
The generated alias is admitted through scoped hatch_counters.py --admit;
code_identity_gate checks its exact derivation during commit. Code identity's
three shadow divergent findings are renamed EH labels resolving the AsciiString
destructor at old label offsets; the byte gate independently rebinds all 104
funclet rows through the verified parent EH graph. They are not waived or
removed from a baseline.

Cause sweep: the current census has just one unresolved _M_new_node consumer
with this spelling. Other integer opaque-record assignment units have distinct
clear/copy conflicts and only 31 own bytes each; they are not imported into
this repair. Full census and maintainer-only runners were not started.
