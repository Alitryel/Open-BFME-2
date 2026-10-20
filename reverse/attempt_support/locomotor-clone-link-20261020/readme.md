# Tree clone call ownership

The 115-byte copy at 0x002D0DA1 calls 0x002D0B9A twice in retail. Its existing
private declaration used a LocomotorSetType/vector tree name, but the rowed
30-byte clone owner is an address-derived Rva002D0B9AElement/int tree. A pin
already connects the former declaration to that target; there is no second
body to own the former name. Bind the calls directly through the owner's
view, retaining the original caller's node traversal and type spelling.
Pointer casts do not establish that the opaque element is LocomotorSetType.

Cross-instantiation friendship preserves the protected clone ABI without an
extra helper body. An initial forceinline public bridge still emitted a wrapper;
it was removed. No new pin, alias or external definition remains. A source
search found no other use of the missing Locomotor clone declaration to sweep.
BFME1 a2c8039e has no corresponding named recovered clone/copy unit.

Paired preview against published index b73720bed9 (2026-10-20 05:34) gives
0 -> 115 linked non-padding bytes. All emitted COMDAT names and code bytes are
identical, and only the two clone call relocation names change. proof.json
records the paired findings, index hash and object hashes. The byte gate,
strict self receipt, EH (no EH-bearing rows/missing objects), data enforcement
and declared-unmatched checks pass. No closed-strict gain is claimed.
