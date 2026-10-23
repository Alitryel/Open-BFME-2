# Network constructor identity and natural exception handler

The existing 65-byte provider at RVA 0x0025DB6D was an ordinary method named
BFME2NativeNetwork::construct. CreateTheNetwork already emitted a new-expression
calling a constructor, but its pinned BFME2NativeNetwork constructor conflicted
with unrelated subsystem-base views carrying that placeholder name. Rename the
existing owner in place to Network::Network and use that constructor in the
caller. All 65 constructor bytes and all 96 caller bytes remain exact. Remove
the obsolete constructor pin: current-object identity analysis reports no
remaining references to its old name. No new pin or alias is introduced.

Target evidence establishes the construction relationship: the native call at
RVA 0x0025E4A8 follows a 0x40-byte allocation and has a failed-construction
operator-delete unwind entry. The installed table at VA 0x00BF6040 supplies the
already rowed Network methods in GameNetwork/Network.cpp. Its field offsets,
including the connection manager at +0x0C, performance counters at +0x18/+0x20,
and last value at +0x3C, agree with this existing constructor view. The
WorldBuilder CreateTheNetwork assertions identify Network.cpp lines 186-191;
its debug object is 0x48 bytes. The constructor name displayed in wb-caller.txt
is a ledger annotation from the intermediate trial, not independent naming
evidence. Pristine GeneralsMD Network::Network is a semantic donor lead; target
table relationships and accesses supply the BFME 2 identity/layout evidence.
No new canonical class header or inheritance relationship is asserted.

With the provider repaired, admit the deferred natural VC6 handler at RVA
0x00772C52: ten new unique strict C++ bytes from the existing clean C++ parent,
not newly reconstructed gameplay logic. The native parent directly installs
that handler; its FuncInfo is RVA 0x0091968C. The complete exception graph is
EXACT, and both external cleanup/runtime destinations agree with existing
bindings. The already rowed ten-byte failed-new cleanup remains unchanged.

Bounded preparation verified the three original rows across both units with
strict current dependency receipts. Normal add_match verified all three rows
of the caller after handler admission. Final identity preflight covers all four
rows with zero findings. Global pin consistency reports no new or stale debt.
Source hashes and native handler bytes are in receipts.json. The whole two
sources were read before editing and again during final review.

The published census at 8eecc93d07 (2026-10-19 13:17 UTC) and current-object link
preview predict these units link: 65 -> 171 rowed bytes, including 96 previously
unlinked caller bytes and the ten new handler bytes. This is a local prediction,
not a measured census gain. No census, link cycle or runtime runner was started.

Isolated constructor trials initially omitted the owner directory's O1/SSE/G7
defaults and emitted 68 bytes. Repeating with the actual effective owner flags
produced the exact 65-byte constructor. Production flags remain unchanged;
the selected change is the minimal direct constructor, not the helper-inlining
or new-inheritance alternatives. No verifier, baseline or header edit is needed.
Normal commit and push gates remain enabled. Model: gpt-6.1-sol.
