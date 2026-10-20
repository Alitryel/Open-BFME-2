# Distinct placement-copy owners

Starting BFME2 revision: 45da1cc7a9. Verified BFME1 reference remains
92f6bbe8e1dc; no reference input or shared header changes.

Retail 003F7674 and 005FE0F5 are separate 45-byte placement-copy bodies.
Each loads its own EH handler, guards the destination pointer, and calls
the existing record copy constructor (004071F7 and 005F93E3 respectively).
The original application names and record identities remain unknown.
The existing constructor declarations and record views are inherited evidence;
this repair makes no new layout or recovered template-identity claim.

Both former dup rows borrowed an object-symbol template name already owned
by a different retail body (003ED62B and 005F944A). Replace these aliases
with real address-derived, typed placement-copy functions, following the
existing Rva0021781DConstruct in the same unit. The direct 003F7737 new-node
caller now declares and calls the typed owner; remove its obsolete dup pin.
The three inherited pins at 005FE0F5 are outside this repair and unchanged.

Isolated trials copied the owner's effective /O1 /arch:SSE /G7 flags as well
as its explicit /Ob2 /EHsc settings. An initial trial under scratch-path /O2
defaults emitted 66 bytes and was discarded. With the actual owner's flags,
both complete 45-byte bodies and full associated EH graphs are EXACT.
The changed provider and direct caller then passed the normal byte gate
and strict current-object receipt preparation: all nine existing rows exact.

The parent EH graphs place the two existing cleanup bodies at 0078419F and
007A636C; their local labels and parent names are updated from that placement,
not adjacency. The new genuine __ehhandler symbols occupy 007841AD and
007A637A, ten bytes each. Native parent relocations identify their handlers
and FuncInfo, and the whole parent graph verifies EXACT. Each handler loads
its own retail FuncInfo then jumps to CxxFrameHandler at 00629182. Whole
handler bytes verify against strict current objects. No new pin, object alias,
assembly, emitted-byte scaffold or verifier exception is used.

Result: two object-symbol hatches and one synthetic pin removed; 20 unique
retail bytes newly backed by natural compiler output from real C++ owners.
Normal ledger admission, whole-unit byte and EH gates remain required.
