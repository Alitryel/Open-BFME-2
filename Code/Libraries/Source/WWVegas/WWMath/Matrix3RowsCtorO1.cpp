// cl: /O1 /Ireference/shims/bfmerendobj /G7 /arch:SSE2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// Size-optimised (/O1) emission of the three-row Matrix3 constructor.
//
#include "obbox.h"
#include "matrix3.h"
#include "vector3.h"
#include "aabox.h"
#include "tri.h"
#include "plane.h"
#include "quat.h"
#include <assert.h>

#pragma inline_depth(0)
// ?_bfmeMatrix3RowsCtorAnchor@@YAXPAVMatrix3@@ABVVector3@@11@Z absent-from-retail
void _bfmeMatrix3RowsCtorAnchor(Matrix3 *matrix3, const Vector3 &r0, const Vector3 &r1, const Vector3 &r2)
{
	matrix3->Matrix3::Matrix3(r0, r1, r2);
}
#pragma inline_depth()
