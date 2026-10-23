# PeerThread existing helper providers (2026-10-23)

Rehome seven existing matched helpers from blocked PeerThread.cpp to its four
existing clean consumers. Real helper names, target boundaries and all code
remain unchanged. No new alias, pin, layout or donor identity is asserted.
The consumer declarations already use the same string, map/tree and owned-record
types. Each moved row passes add_match --replace-existing and the ordinary
provider byte/reference gates. This is ownership repair, not new authored C++.

| RVA | Bytes | Existing provider |
| --- | ---: | --- |
| 0x0038A6BF | 32 | Code/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva0038E4B9Finish.cpp |
| 0x00389A4C | 41 | Code/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva0038E4B9Finish.cpp |
| 0x003899FE | 9 | Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp |
| 0x0038995C | 28 | Code/GameEngine/Source/GameNetwork/BFMENetworkQueueCtor.cpp |
| 0x0038A486 | 5 | Code/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva0038E4B9Finish.cpp |
| 0x00388F09 | 48 | Code/GameEngine/Source/GameNetwork/GameSpy/Thread/BuddyThreadClassThreadFunction.cpp |
| 0x001EFCD7 | 32 | Code/GameEngine/Source/GameClient/GUI/GUICallbacks/Apt/AptOnlineCustomMatchCallbacks.cpp |

Base: c7683c8393; census b711de3634, 2026-10-23 14:28, retail-truth-4.
The unchanged index SHA-256 is
1707d876c79d52c4e34a88342706796110595063d75abb3d5ed81bd080c08ad7.

Current paired `python3 tools/link_check.py` measurements:

| Unit | Before linked | After linked |
| --- | ---: | ---: |
| BFMENetworkQueueCtor.cpp | 21 | 58 |
| Rva0038E4B9Finish.cpp | 467 | 545 |
| BuddyThreadClassThreadFunction.cpp | 3,052 | 3,100 |
| AptOnlineCustomMatchCallbacks.cpp | 8,618 | 8,650 |
| PeerThread.cpp | 0 | 0 |
| Total | 12,158 | 12,353 |

**+195 B in the legacy scoped preview**. No self-strict/closed-strict/full-link
gain is asserted. Strict preparation earlier in this session was blocked by the
shared compiler lock; ordinary dependency-cache objects are reused unchanged.
The SHA-256 of all four provider objects is unchanged across the row moves.
No census/index/status artifact is rewritten.

The normal hooks verify all affected provider rows; check_csv.py and
find_declared_unmatched.py pass. The shadow code_identity_gate checks both
provider groups (ten and 123 rows) with zero new findings. The source/provider
previews report 4/5 clean before and after.

Prior evidence for clearPlayerStats at 0x0038A6BF described duplicate strong
definitions. Both PeerThread.cpp and Rva0038E4B9Finish.cpp now spell the same
definition `__declspec(noinline) inline`, establishing a new current prerequisite
for this repair. The clean provider needs that visible definition for its own
join-room callback. Rehoming keeps it visible and byte-exact.

PeerThread remains blocked by other GameSpy interfaces and STL bindings.
A separate PeerDefs sweep was excluded because another worker holds all seven
retail RVAs; no edits were made to it or its candidate providers. Four GameLogicInit
helper RVAs were likewise held. Folded helper addresses already represented by
other matched rows were excluded from proposed link gains.

A proposed 19B clear@Rva000A8C9B move from MilesAudioManager.cpp to GameClientXfer.cpp
was byte-exact but exposed two shadow divergent definitions: getNextDrawable@Drawable
and testDrawableStatus@Drawable. That row is restored; a blocked attempt is logged
and all three associated claims released. Resolve those definitions before retrying
that provider. No source, pin or gate workaround was retained.
