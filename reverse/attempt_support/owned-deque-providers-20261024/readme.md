# Existing owned-record deque providers

BFME2 input 3c6c4f6651; published legacy index 11b3872700 (2026-10-23 23:06,
retail-truth-4). Eleven existing rows move from the blocked owned-deque unit
to four existing consumers emitting the whole retail body and resolved
relocations. No C++, settings, identities, pins, aliases or layouts change.
Original opaque record names remain ABI views; no new original-name claim.

Target source comments establish record extents, alignment and lifetime
relationships. In particular 1408B record's +8 PSPlayerAllStats member is
established by native destruction/assignment and WorldBuilder-backed provider;
BFMENetworkQueue's named constructor provides the 492B deque context. The
receiving Construct-family views claim only the destructor ABI used here.
Reviewed BFME1 f5140c1c network/PersistentStorageThread donor context and the
previous link_library_providers_20261023 donor scan; no donor record layout
or byte body is imported. Several original identities remain uncertain.

All eleven receiving bodies pass complete bytes, resolved relocations and
callee identity preflight with zero unresolved references. Paired current-object
legacy link_check: 4/5 units link, 23,303 -> 23,780 B, **+477 B linked**. The
37B improvement against the frozen index was already present before this
batch and is excluded. ICF twins remain, so ownership/availability is measured;
no newly unique code, self-strict, closed-strict or full-image census gain
is claimed. Source unit remains blocked on independent record840/2148
lifetimes, queue constructor and map initialization/increment copies.

Acceptance: 437/437 byte gates; all strings/floats/imports pass; EH 72/72
EXACT, zero baseline. Code identity findings unchanged at sixteen; no new
finding. Frozen-definition, CSV and whitespace checks pass. The bundled
ModuleFactory handoff records a separate no-change stale-index investigation.

Rows (RVA, extent, receiving source):

- 0x0038A52E, 45 B, Code/Libraries/Source/WWVegas/WWLib/OwnedRecord492Copy.cpp
- 0x0038A930, 87 B, Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp
- 0x00389A07, 33 B, Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp
- 0x00389DA9, 45 B, Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp
- 0x0038A505, 41 B, Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp
- 0x00555ADF, 8 B, Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PersistentStorageThread.cpp
- 0x00553868, 20 B, Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp
- 0x00557B4B, 87 B, Code/Libraries/Source/WWVegas/WWLib/StlportConstructFamilyW3G15.cpp
- 0x00557BA7, 87 B, Code/Libraries/Source/WWVegas/WWLib/StlportConstructFamilyW3G15.cpp
- 0x0055320A, 12 B, Code/Libraries/Source/WWVegas/WWLib/StlportConstructFamilyW3G15.cpp
- 0x00553216, 12 B, Code/Libraries/Source/WWVegas/WWLib/StlportConstructFamilyW3G15.cpp
