# Score-row comparator: real STLport bitset controls

Native 0x005EC52E..0x005EC594 is the full 102-byte RET4 comparator.
Read prior 0x005ec52e.md and all current log verdicts first. The barrier primary
bank remains unchanged and is diagnostic only.

The successful Elven Wood recovery justified trying the real checked
std::bitset<218> type and a raised inlining budget. Fifteen complete ScoreRowSort
source trials use its current field/caller contracts, 28-byte bitset at template
+0x108, valid bit90, descending signed record+0x9C key and name+4 comparison.
Explicit noinline on the comparator and AsciiString comparison preserves the
native call boundaries; no synthetic fence, volatile or padding is used.
Three shapes (repeat the mine test on return, named bools, nested conditions)
run under ordinary flags, Ob2 and inlining budgets40/100/200.

No exact result. Budget100/200 repeated-test form is 97 bytes with resolved
calls but still emits shr/shr/xor/test in place of retail's independently
materialized bools, and its tail register allocation differs. Named bools give
88 bytes; nested branches98. Six additional real mutable bitset-reference
read controls give100..106 bytes but introduce an out-of-line private testProxy
call despite forceinline. That helper is45 bytes with two stack locals; those
unresolved calls are introduced by the trial, not missing retail dependencies.
Do not add pins for them or claim the short bodies as progress.

Whole source is frozen from2aaef4ac93; BFME1 pointer92f6bbe8 is current. Replay
score-bitset-inlining-20261020.py.txt and then score-bitset-proxy-20261020.py.txt
from build/. Complete logs and metrics: build/score-bitset-inlining-oct20/.
Existing primary retained. No Code, ledger, pin, header or verifier edits.
