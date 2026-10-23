# BuddyThread STLport base cleanup

At BFME2 bfe33dc436, BuddyThreadClassThreadFunction.cpp has one current
link blocker: its game-free _String_base<char, allocator<char>> destructor
copy differs from the first no-address copy in link order and is referenced.
The explicit imported, force-inline specialization retains the vendor body
_M_deallocate_block(), with its original throw() contract. This keeps native
inlining and delegates any outlined reference to the common provider.
No import reference is emitted by the matched bodies.

A first trial without throw() changed the main body and three unwind rows
(4/14 failed). Retaining the original nonthrowing contract passes 14/14.
No third variation was needed. The specialization changes neither storage
nor the allocation/free semantics of inlined cleanup.

Against the unchanged published census ae3b3e68e2 (2026-10-22 11:05 UTC),
current legacy preview moves this unit from 0 to 3,052 linked matched bytes.
Checks: scoped build.sh 14/14 with strings/floats/imports;
link_check --prepare-current strict reusable source receipts;
link_check --new-variants. The commit hook also checks declared definitions,
class and data/code identity, EH, and the touched rows.
This is self-strict source verification and legacy current-object link
preview, not closed-strict closure. The published index lacks 3,469 current
ledger provider objects; no full link cycle or census was run.

Sweep: current previews of PeerThread, registry, urlBuilder, PeerThreadStats,
PingThread_Pinger_getPing, PingThread_PingThreadClass_Thread_Function, and
StandingWaterAreaLoadPCA show only PeerThreadStats already links (128 B).
The other six need independent string allocator/constructor/append providers,
PingResponse cleanup, or callees, beyond this base destructor. They were not
changed: suppressing one copy there gives no linked-byte improvement.
Donor inputs remain the verified BFME1 pointer 37c3022de1; this is a local
STLport visibility repair, not a transfer from unverified newer inputs.
