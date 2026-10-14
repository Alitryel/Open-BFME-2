// ?Inverse@Matrix4@@QBE?AV1@XZ
// partial score=0.3146519410977242 date=2026-10-14
// cl: /O2 /G7 /arch:SSE /DNDEBUG /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Donor a7c38d3b2597121f178ab5190b3062478823257d matrix4.h Gauss-Jordan inverse.
// Native call from verified 0x007133F0 proves hidden Matrix4 result ABI.
// Native body starts after13 int3 at715EB0 and ends7166C5; trailing padding
// through7166D0 is excluded. Address-taking only forces header emission.
#include "matrix4.h"
Matrix4 (Matrix4::*bfmeInverseEmissionAnchor)() const = &Matrix4::Inverse;
