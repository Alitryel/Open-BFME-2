# Wide-record list cleanup link repair

At BFME 2 56c4560eb0 with donor 74ea60ad41ef and the published index refreshed
to 800e4b6c94, stlport_list_002b8ff3_fill.cpp had 116 matched bytes and did
not link: its declaration-only record-list clear had no provider. The current
paired legacy preview after repair is 425 -> 541 B across that unit and the
two existing UnicodeString providers. The repaired unit contributes 0 -> 116 B;
the providers remain linked at 171 and 254 B respectively.

Target evidence: the 106-byte constructor at 2B8FF3 has a native EH action at
77636A that destroys its temporary through 5B804E. Its list unwind action at
776362 calls 433BD7, whose complete 23-byte list-base destructor calls clear
at 433B65 and frees the sentinel. The 49-byte clear destroys the payload at
node+8 through 5B804E, frees each node through 30830 and resets both links.
The record's separately rowed copy constructor at 2B4DC1 establishes a leading
UnicodeString and two trailing words; the list allocates 20-byte nodes.
The BfmeStringRecord name remains a structural identity, not a recovered
application name. The native initializer sets its two words to 0 and 3.

The repair uses the existing canonical UnicodeString header instead of a
private StringBase view and lets the real record-list clear instantiate.
Explicit /O1 /G7 /arch:SSE settings reproduce the constructor and cleanup;
the bfmelist include follows the existing UnicodeString cleanup provider.
An isolated default-settings trial had a 137-byte constructor and 56-byte
clear; the retained settings emit the complete 106-byte and 49-byte bodies.

The implicit record destructor emits the complete 5-byte jump to releaseBuffer
at 36E70, identical to every existing owner at 5B804E. The typed list clear
emits the entire existing UnicodeString clear body at 433B65, including both
callee relocations. The two rows declare these real ICF folds with exact
gen-alias and fold-proof notes. They add no unique authored byte coverage and
no pins. Each name has no separate native body. Neither fold is an invented
application identity or a substitute for an unresolved native implementation.

Acceptance: 4/4 ordinary byte checks and strict reusable receipts; the one
EH-bearing row is EXACT; strings, floats, imports, source claims, declared
definitions and class gate pass. The paired legacy preview links all three
units. This is self-strict byte evidence plus a legacy link preview, with no
closed-strict, full-link or runtime claim. Same-cause search found no other
declaration-only record-list clear consumers; the insertion units' separate
node-creation declarations remain untouched.
