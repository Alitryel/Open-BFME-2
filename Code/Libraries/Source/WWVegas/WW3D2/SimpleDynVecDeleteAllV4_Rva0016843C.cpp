// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload -Ireference/open-bfme-1/game/Libraries/Source/Compression -Ireference/open-bfme-1/inputs/reference/shims/sweep -Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 -Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
//
// SimpleDynVecClass<Vector4>::Delete_All (0x0016843C): retail holds one
// size-optimised (/Os) out-of-line copy of this template body. Retail is
//   and dword [ecx+0x0c], 0      ; ActiveCount = 0   (this+0x0c)
//   cmp byte [esp+4], 0          ; allow_shrink
//   je  skip
//   call 0x00100210              ; Shrink<Vector4>
//   ret 4
// The pointer-to-member anchor emits Delete_All out of line.
// Shrink<Vector4> uses the folded body owned by the matched POD instantiation.
//
#include "simplevec.h"
#include "vector4.h"

// Callers use the Vector4 spelling of the folded helper at 0x00100210.
template bool SimpleDynVecClass<Vector4>::Shrink(void);

extern void (SimpleDynVecClass<Vector4>::*const g_bfmeDynVecV4DeleteAllAnchor)(bool);
void (SimpleDynVecClass<Vector4>::*const g_bfmeDynVecV4DeleteAllAnchor)(bool) =
	&SimpleDynVecClass<Vector4>::Delete_All;