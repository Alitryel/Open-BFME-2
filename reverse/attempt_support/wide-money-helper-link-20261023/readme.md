# Wide money formatter helper link attempt, 2026-10-23

Inputs: BFME 2 0647f94c99; BFME 1 donor pointer 96c88c73a5cd1a58fc2f8db691beea50acd996db; published legacy census 0393df10e2, 2026-10-23 19:47. Existing formatter flags and dependencies were retained. This is a link repair investigation; no new identity or layout claim is made.

The ten matched formatter rows total 2,616 bytes. Baseline and every byte-exact trial link zero of those bytes. The mutable-char forward range helper differs from the kept narrow money copy, and the wide `_String_base` destructor emits an 82-byte carrier instead of the existing 14-byte retail body. Nine qualified calls to the empty phantom destructor keep the parent formatter outlining exact. See the earlier df20-exact-true-naming-20261021 handoff for that established codegen constraint.

Trials:

- A fully explicit mutable iterator specialization declaration causes VC7.1 C1001, P2 mainline 148.
- A declaration with a generic inner template parameter suppresses the conflicting range helper, with all ten byte checks passing. Adding an explicit forceinline empty phantom destructor has no effect on the remaining 82-byte carrier. `exact-one-blocker.patch` preserves only the useful declaration. Paired legacy preview remains 101 to 101 bytes for formatter, StlSweepW5Rva000AFF52 provider and narrow range owner; formatter itself stays zero.
- Replacing the nine qualified phantom calls with late-fold null-this guards changes the parent formatter outlining. Nine of ten checks pass; the 2,610-byte parent fails. `guards.cpp.txt` preserves this diagnostic, not a recovery.

All production source is restored. Do not land the exact declaration alone as a repair: it yields no linked bytes. Resume only with a supported way to preserve parent outlining while emitting or binding the complete retail wide-base destructor. No closed-strict gain was measured. Local diagnostics: build/seat-wide-money-trial2-byte.txt, build/seat-wide-money-trial2-link.txt and build/seat-wide-money-guards-byte.txt.
