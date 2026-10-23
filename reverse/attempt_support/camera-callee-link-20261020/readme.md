Camera product callee binding: blocked (2026-10-20)

The current strict object has unresolved members rva0009AACF and rva0009CD9B. The rowed free __stdcall owner of 0x0009AACF has the same stack arguments and RET 8, but substituting free calls removes retail MOV ECX,ESI instructions in two parent rows (0x0009BC17 and 0x0009C4FC); 16/18 rows still pass. This is not an admissible byte-preserving repair.

The other callee, 0x0009CD9B, is an unmatched 1,984-byte light initializer. Its existing 2026-10-20 attempt bank documents unresolved SSE/trigonometric stack and matrix ordering differences. Thus a callee name repair alone cannot link this unit. Do not repeat that reconstruction here. Original source restored and all 18 rows plus 22 float references pass. No repair gain claimed. Diagnostic logs retain the failed call-shape comparison. Inputs: BFME2 44f33aef2a; BFME1 01b84526fc8a; published census 5366c4f808. t=6 model=gpt-6.1-sol.
