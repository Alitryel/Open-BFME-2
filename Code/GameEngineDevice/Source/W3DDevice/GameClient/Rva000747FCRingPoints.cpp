// ?rva000747FC@Rva000747FC@@QAEXPAVVector3@@HPBV2@M_N@Z
// cl: /O1 /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Native 0x000747FC..0x000748DF, 227 B, RET 0x14: emits a ring of points.
// For each of `count` steps the angle 2*i/count*PI gives the offset
// (Sin, Cos, 0) scaled by `radius` about `center`; the point is written at
// the even slot (2*i+2) % (2*count) and, unless `skipOdd`, at slot 2*i+1.
// WB 0x007D7DD0 is the same body with Vector3 operator asserts
// (wwmath/vector3.h lines 291..334) and a thiscall entry (this unused).
// Enclosing class and method name are unknown: address-derived owner.
#include "vector3.h"

float Sin(float val);
float Cos(float val);

class Rva000747FC
{
public:
	void rva000747FC(Vector3 *points, int count, const Vector3 *center, float radius, bool skipOdd);
};

void Rva000747FC::rva000747FC(Vector3 *points, int count, const Vector3 *center, float radius, bool skipOdd)
{
	for (int i = 0; i < count; i++)
	{
		// Retail spills the double angle across the Cos call (fst qword) and
		// converts it again for the Sin argument; a second named copy keeps cl
		// from sharing one float conversion between the two calls.
		const double angle = 2 * i / (float)count * 3.14159265358979323846;
		const double angle2 = angle;
		Vector3 offset(Sin(angle2), Cos(angle), 0.0f);
		offset = offset * radius + *center;
		if (!skipOdd)
			points[2 * i + 1] = offset;
		points[(2 * i + 2) % (2 * count)] = offset;
	}
}
