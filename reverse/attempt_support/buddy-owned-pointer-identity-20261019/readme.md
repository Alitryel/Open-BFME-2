# BuddyThread owned-pointer lifetime repair

The already matched 2987-byte BuddyThreadClass::Thread_Function at RVA
0x00552027 used std::auto_ptr<Rva00550918>. Its normal body matched, but the
complete native unwind graph calls a 13-byte destructor at 0x0055076F; the
auto_ptr destructor emitted only nine bytes and omitted the native clearing
store. This was a real lifetime mismatch, not a verifier false rejection.

The native 13-byte body loads the pointer at +0, clears that word, and calls
ordinary scalar operator delete at 0x0002FD60. The planning-phase destructor
at 0x00575F38 already invokes that same lifetime, through a wrapper around an
ordinary method named rva0055076F. A separately recovered Palantir owned-pointer
destructor has the same native destination and behavior. These are target
ownership/lifetime facts; Rva0055076F remains a neutral ABI-view name. Neither
the original holder template nor its source class spelling is established.

Rename the existing 13-byte owner in place to Rva0055076F::~Rva0055076F, and
make the planning-phase view call it directly. Its existing five-byte forwarder
at 0x005753DD remains exact. Give BuddyThread the visible clearing destructor:
the compiler emits all 13 bytes for unwinding, and removes the dead clearing
store when it inlines destruction on the normal path. This reproduces both
native paths without a new pin, alias, volatile barrier, or assembly.

The listener remains a four-byte object with one virtual event callback,
0x00550921, in the table at VA 0x00C6AC08. Its constructor at 0x00550918
installs that table and returns this in nine bytes. Keep the explicit empty
inline constructor visible to Thread_Function and rehome the existing nine-byte
row there, removing the redundant strong definition from the callback unit.
constructor-copies.json records the identical whole body and vtable relocation
from the old and new homes. The 116-byte callback is unchanged. Allocation,
table contents and callback registration establish the relationship; the
listener's original class and callback names remain unknown.

All four sources were read in full before edits. Normal build.sh verifies
19/19 rows across them after admission, including the unchanged 2987-byte
parent, 233-byte planning-phase destructor and 265-byte constructor. Five local
funclet labels changed numbering; the existing gate verifies their locations
through actual parent EH metadata. Complete EH verification is EXACT for all
three parents (buddy-eh-final.json and phase-eh-final.json). callee-audit.json
also checks whole cleanup callees, their extents and subordinate relocations:
the repaired local destructor is exactly 13 bytes with the correct delete
binding. Strings (6+1) and named imports (5) pass the normal byte gate.

Admit the naturally emitted ten-byte handler at RVA 0x00798BAC, FuncInfo RVA
0x0094D1C0. This adds ten unique strict C++ bytes. The 2987-byte parent and
13-byte/9-byte repairs were already counted. The raw 3041-byte parent COFF
section includes its six-byte continuation/catch at 0x00552BD2 and 48-byte jump
table; the catch already belongs to Rva00552BD2Get and is not claimed again.
Source flags and shared headers are unchanged. The original semantic donor
remains BFME 1 a0e8f345a9b22b4b42088e402962287d7015e3c2 as recorded in the
owner; this repair's lifetime, layout and codegen evidence comes from BFME 2.

Identity preflight no longer reports the listener-constructor duplicate or the
new destructor duplicate. Two unchanged shadow findings remain: divergent
allocator<char> rebind definitions and duplicate Base0_00576C4B constructor
definitions. identity-preflight.json records them explicitly. The new-variants
preview passes without a new conflicting COMDAT variant; global pin consistency
and declared-definition checks pass. No verifier, baseline, pin or header was
edited. This is not a claim to have repaired those two existing shadow debts.

The published link index is 8eecc93d07. Its refreshed preview cannot measure
Thread_Function because that source is absent from the census. A guarded
current-ledger preview first refused 30 missing objects. Bounded normal byte
checks prepared those providers (137/137 rows in 29 units, then 1/1 in the
remaining approved LoopDeringBlock unit). The retry refused 10,596 objects
without current compiler evidence. Both refusal outputs are retained; no
whole-tree preparation, census, link cycle or runtime runner was started.
Consequently no link gain or complete current-ledger link success is asserted.

Six genuine source trials distinguish the cause: an opaque clearing method
with inline or external listener construction first diverged at +53/+47;
visible noinline ordinary clearing methods first diverged at +385; the real
destructor, with either implicit or explicit inline listener construction,
reproduced all 2987 bytes. The explicit constructor is selected to match the
existing callback unit's class view. trials.json, visible-trials.json and
real-destructor-trials.json preserve those measurements. receipts.json records
final source/object hashes and strict dependency currency.

Input BFME 2 HEAD: 28b1b5c69e5e4977030ea00bb9252f75edd62102. Verified BFME 1
dependency pointer: 6b9d92bf92debd03e4357462bab41f701651e67c. Model: gpt-6.1-sol.
