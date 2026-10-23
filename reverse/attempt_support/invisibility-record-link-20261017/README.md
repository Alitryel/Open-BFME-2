# Invisibility-record list ownership repair

Base: 7d1dac0a. BFME1 linking repair reference reviewed: 5bb8ca80.
BFME2 native bodies establish ownership: the explicit-clear destructor is
0x00438FC5 (47 bytes); element construction at 0x00438E49 calls the nontrivial
copy at 0x00438559; value insertion at 0x004390A2 is 37 bytes.

The size-only Rva004393D6Copy view emitted an implicit destructor and raw POD
copy/insert helpers. Declare the existing destructor and native copy/insert
specializations instead. Suppress the broad list provider's competing insert;
instantiate only the dedicated insertion body rather than the whole class.
No implementation, ledger address, compiler flag or verifier is changed.

All 59 function rows across seven provider/consumer units remain exact;
all seven EH rows are EXACT. Strict new-variant admission passes. Rescanning
the three edited units places no additional body or pin. Every retained
COMDAT is unchanged; no strong symbol or definition is added or lost.

Paired comparison uses the published 2026-10-17 02:26 census at fb06805bf5,
refreshes stale providers, and compares the old and repaired objects in the
same index. All 1875 affected sources were checked; no finding count grows.
Three units become clean: Rva004393D6Copy (140 bytes), stlport_list_int_dtor
(57 bytes including its handler), and stlport_list_pod196_insert (37 bytes).
Net: 234 already-matched bytes become linkable in this scoped preview.
The broad provider loses one wrong insert selection but has other blockers.
The initially ranked two consumers already link after stale-provider refresh;
no gain is attributed to them. This is not a whole-game link or runtime test.

comparison.json preserves changed results and complete object symbol deltas.
Full paired results, original objects, source snapshots and build/EH logs
remain ignored under build/local-macos/invisibility-record-link/.

## Boat wake speed-ratio dependency

The 742-byte W3DBoatWakeModelDraw::doDrawModule at 0x000D0D24 had one
unresolved symbol: g_Va00DB52E8. Its native reads use VA 0x00DB52E8
(RVA 0x009B52E8); retail stores 0A D7 A3 3B in writable .data, exactly
float 0.005. Define the existing Real/float declaration in the consumer TU
and add a four-byte data ownership row. No guessed adjacent extent, extra
alias or pin is used. Normal build verifies the function and the data's
compiler sizeof and complete initial value. All 21 emitted COMDATs stay
identical. The paired refreshed-index comparison removes this sole unresolved
name and adds only the intended strong data definition. No other consumer
of this symbol is found. boat-comparison.json records both results.
This contributes another 742 locally linkable matched bytes, for 976 total;
no census history or global progress counter is rewritten.
