# Narrow-string cleanup ownership: blocked

Nine units share two current blockers: non-retail emitted COMDAT copies of
`_String_base<char>::~_String_base` and `_STLP_alloc_proxy<char*,char>::deallocate`.
The existing row owners are at 0000B3C0 and 006892B0 respectively.

Two careful trials each failed 13 of 24 byte-gated rows: declaration-only
specializations and the imported-forceinline pattern already used for wide
strings in BuddyDefs.cpp. Both make these callers select an external string
destructor instead of retail's inline null-test/free. This changes control
flow, stack locals, unwind actions, and the rowed GameResultsResponse destructor.
These are real byte mismatches, not verifier false rejects. No new pin or
checker exemption is justified. Original source is fully restored; all claims
are released. No linked-byte gain is claimed.

Affected units:

* `Code/GameEngine/Source/Common/NarrowStringRecord0041A5D2Dtor.cpp`
* `Code/Libraries/Source/WWVegas/WWLib/StlportNarrowRecord0054FEF1DequeAux.cpp`
* `Code/GameEngine/Source/Common/Rva0041A9E8PushBackAux.cpp`
* `Code/GameEngine/Source/Common/Rva003896E7Permuted.cpp`
* `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadMatchbot.cpp`
* `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/WideCharStringToMultiByte.cpp`
* `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/PeerThreadLookupStat.cpp`
* `Code/GameEngine/Source/GameNetwork/GameSpy/PeerDefsGameOptions.cpp`
* `Code/GameEngine/Source/GameNetwork/GameSpy/Thread/GameResultsThreadClassThreadFunction.cpp`

Resume only with an inline-preserving ownership mechanism or shared compiler evidence; do not repeat these two trials unchanged.
