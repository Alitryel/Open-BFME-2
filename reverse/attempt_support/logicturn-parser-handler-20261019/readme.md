# LogicTurn parser handler

The native 180-byte parser at RVA 0x003F91A4 is already recovered in
Rva003F877ECtor.cpp. Its retail assertion establishes LogicTurn::ParseINI's
role; the existing opaque accessed-prefix ABI and constructor/layout uncertainty
are preserved. The complete source, all prior parser/handler attempts and
existing donor provenance were read before work; parent, handler and file
reservations were pushed before verification. No game-source, type, pin, alias,
compiler setting, class contract or verifier change is made.

The native parent prologue installs handler RVA 0x00784364. Its complete EH
graph is EXACT, binds FuncInfo RVA 0x009304F4, and independently identifies the
emitted __ehhandler$<parent>. Both relocations and all ten bytes reproduce
retail, including the jump to the existing runtime thunk at RVA 0x00629182.
The attached handler proof records exact bytes, input hashes and strict current
dependency receipts; the cleanup audit checks all external unwind/runtime
references against existing owners. No adjacency or arbitrary masked-byte hit
is used to infer ownership.

Normal build.sh verifies the complete source; frozen-file check passes.
place_bodies finds zero further bodies and zero pins. Normal admission adds ten
unique strict C++ bytes, while both existing ordinary bodies were already
counted. No linked-byte gain, complete subsystem linkability or runtime behavior
is claimed. No maintained verification runner was started.

Base: af5db01a38b60e7352497e9f01e32c504e7fe053; verified BFME 1 pointer
6b9d92bf92debd03e4357462bab41f701651e67c. Model gpt-6.1-sol; about two minutes.
