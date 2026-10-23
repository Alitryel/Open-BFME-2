# Integer count-map linking, 2026-10-22

Inputs: BFME2 parent f7cddd1939, published legacy index 08160bc2c9 at
2026-10-22 17:08; BFME1 verified pointer 37c3022de1 (upstream update owned
by another seat). No donor change or new identity assertion.

Landed: represent the two address-derived wrappers in Rva0016E400Ctor.cpp
with hash_map's underlying hashtable storage and pass its default 100-bucket
arguments directly. This preserves layout and semantics for the recovered
constructors; original member type remains inferred. It avoids emitting the
wrong out-of-line default hash_map<int,int> constructor. Both 72-byte bodies,
two 11-byte unwind bodies and two 10-byte handlers remain exact.

Acceptance: ./build.sh Rva0016E400Ctor (6/6 exact, EH labels relocated by verified
parent data); link_check --prepare-current gives a strict reusable self receipt,
including reference gates. Paired legacy current-object previews of this unit,
AIStatCollector.cpp and StlSweepW4Rva004E02B8.cpp: original 0/557 B linked;
final 164/557 B linked. Only the wrapper unit changes. No closed-strict claim.

Unlanded provider trial (patch in link-countmap-provider-20261022.patch.txt):
AIStatCollector's declaration-only int-table destructor preserves all ten rows.
Narrowing W4 to its recovered opaque constructor removes an unused undefined
element comparison. Removing declaration-only vector<void*> default/base
constructors and allocator destructor restores the 64-byte table shape. Its
int-table constructor still calls the independently rowed 106-byte initializer
at 0x00622410 where the retail 0x004E007A body calls 0x00148DDF (59 bytes).
Do not pin that int-table name at 0x004E007A: fresh fold_proof_problems rejects
at +0x2b, with allow_weak both true and false. A pin_admission --add invocation
initially accepted it, but the fresh proof and explain_mismatch contradict that
result; the trial pin and all hatch-register changes were removed. This needs
an independent tooling/cache investigation, not a new alias or second address.
AIStatCollector could preview-link 362 B in the trial, but the provider and
wrapper table copies conflicted; that gain was not landed or credited.

Rejected wrapper variations: import-inline default hash_map constructor and
import-inline primary hashtable constructor add an EH state transition and
change instruction ordering. Two failed builds; do not repeat unchanged.
Best verified wrapper implementation is landed. Best provider trial preserves
all its matched bytes but is blocked by distinct initializer identities.
