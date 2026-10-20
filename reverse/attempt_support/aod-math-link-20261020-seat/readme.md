# AOD math emission repair: +1,560 B in the legacy link preview

Paired current-object checks use published census 5366c4f808, frozen October
20 at 12:21. The original AODHordeContainRva0047AC8F.cpp fails only on its
float sin/cos COMDAT copies. Renaming its visible CRT float wrappers, following
ScreenFilterRva007DB820PostRender.cpp, removes those copies and links the
unit's 1,560 non-padding bytes. No census update, link.exe placement or
closed-strict gain is claimed. Self-strict preparation passes independently.

The calls retain math.h's float-wrapper operation through sinf/cosf; the
full 1,563-byte native row, relocations and 14 float literals verify exactly.
There are no EH-bearing rows. find_declared_unmatched passes. No pin, global,
class layout, compiler flag, shared header or verifier changes are involved.
The first trial used the imported-forceinline pattern of the AerialPathfinder
unit; it preserved body size but rescheduled x87 multiplication at +0x1AC.
It was discarded. The accepted extern inline wrappers preserve scheduling.

The rank's other float sin/cos consumers have independent unresolved blockers
(HordeContainIface11CSlots and pathfinder); no unmeasured sweep is claimed.
Donor method review is inherited from the allocator repair in the preceding
commit: BFME1 92f6bbe8, unique-owner/visible-body commit 51b97cd796. This repair
uses the existing verified BFME2 math wrapper pattern and target byte evidence;
no donor code or target layout inference was added.
