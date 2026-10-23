// cl: /O1 /Ireference/shims/bfme2renderobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/
#include "rendobj.h"
#include <float.h>

// rendobj.cpp's LOD sentinels (Zero Hour source; retail .rdata 0x00BD2F58 holds
// FLT_MAX and 0x00BD2F5C holds -1.0f), which every LOD-aware render object reads.
const float	RenderObjClass::AT_MIN_LOD = FLT_MAX;
const float	RenderObjClass::AT_MAX_LOD = -1.0f;

// The primary RenderObj vtable and hierarchy aggregation establish the
// BFME2 additive flag as 0x00400000. Retail compiles this with a shared return.
inline void RenderObjClass::Set_Additive(int onoff)
{
    if (onoff) {
        Bits |= IS_ADDITIVE;
    } else {
        Bits &= ~IS_ADDITIVE;
    }
}

// Set_Additive is a header inline in retail: other units emit select-any
// copies of it, so a strong definition here was a duplicate symbol in the
// linked build. This anchor only makes this unit emit its copy for the ledger
// row; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitRenderObjAccessors@@YAXPAVRenderObjClass@@@Z present-unmatched
void bfmeEmitRenderObjAccessors(RenderObjClass *renderObj)
{
    renderObj->RenderObjClass::Set_Additive(0);
}
#pragma inline_depth()
