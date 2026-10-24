# PeerThread / BFMENetworkQueue deque identity (link lane, 2026-10-24)

Inputs: BFME2 47da7755f1; current objects (`link_check.py --refresh`).
No source or ledger change made: the three files were claimed by another
seat (`file:` claims) when this was found. Evidence for whoever lands it.

PeerThread.cpp blockers on current objects are exactly four:
two unresolved `BfmeOpaqueOwnedRecord840` copy ctor/dtor, and wrong
`_M_initialize_map<BfmeOpaqueOwnedRecord492>` and `queue<492>()` copies.

Target facts (retail disassembly, `RetailTruth._judge` on current objects):

- 0x005532FF (75 B) calls 0x005530D7, the 1432-element map init (0x598
  immediates, rowed `_M_initialize_map<BfmeOpaqueOwnedRecord1432>`). The row
  naming it `_Deque_base<BfmeOpaqueOwnedRecord492>(alloc,n)` (PeerThread.cpp)
  is the wrong instantiation. StlportOwnedRecordDeque.obj's
  `??0?$_Deque_base@UBfmeOpaqueOwnedRecord1432@@...@I@Z` judges retail there.
- 0x00553868 (20 B) calls 0x005532FF: it is `deque<1432>(alloc)`, not the
  `deque<BfmeOpaqueOwnedRecord492>(alloc)` row in BFMENetworkQueueCtor.cpp;
  StlportOwnedRecordDeque.obj's 1432 copy judges retail there.
- `??0BFMENetworkQueue@@QAE@XZ` (0x00558D41) calls 0x005532FF, so the network
  queue's records are 1432 bytes, not the 492 BFMENetworkQueueCtor.cpp declares.
  That unit's 492 helper rows (0x0038995C, 0x003899FE, 0x00389A07, 0x00389DA9,
  0x0038A505, 0x0038A930) are PeerThread's PeerRequest deque helpers;
  PeerThread.obj's copies of all six judge retail at those addresses.
- symbols.csv pin `_M_initialize_map<BfmeOpaqueOwnedRecord492>` -> 0x005530D7
  is the 1432 body; the 492 body (0x1EC immediates) is 0x00388DA8, rowed as
  `BfmePod492`. The pin makes PeerThread's correct copy lose.
- retail `queue<492>()` 0x0038D28E calls 0x00389152 (pinned
  `_Deque_base<BfmeOpaqueOwnedRecord492>(alloc,n)`); it loses only because the
  0x005532FF row outranks that pin in `RetailTruth.addresses`.

Proposed repair: repoint 0x005532FF and 0x00553868 to the 1432 names in
StlportOwnedRecordDeque.cpp, drop the wrong pin, make BFMENetworkQueueCtor's
record 1432 bytes and rehome its six 492 rows to PeerThread.cpp. With no
address, PeerThread's 492 map init is then proven through `_defined_at`
at 0x00388DA8. The 840 pair still needs PeerThread's queue to hold the real
`PeerResponse` (its ctor/dtor rows are `??0/??1PeerResponse@@QAE@XZ`;
the copy row is spelled `ABU0` (struct) while PeerThreadRetail.h declares
`class PeerResponse`).
