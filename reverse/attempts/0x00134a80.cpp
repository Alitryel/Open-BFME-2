// ?Rva00134A80@CameraClass@@QAEXPAVMatrix4@@@Z
// partial score=1.0 date=2026-10-14
// cl: /I. /O2 /DNDEBUG /MD /EHsc /arch:SSE /G7 /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Matrix types: Open-BFME-1 a7c38d3b2597121f178ab5190b3062478823257d.
// Native 0x00134A80..0x00134AB0 and WB 0x009BD3A0 independently show
// a D3D projection temporary multiplied by CameraInvTransform at +0x3CC.
// CameraClass ownership follows the verified Get_D3D_Projection_Matrix call;
// the original name of this nonvirtual member is unknown.
#include "reference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath/matrix4.h"

class CameraClass
{
public:
	void Get_D3D_Projection_Matrix(Matrix4 *matrix);
	void Rva00134A80(Matrix4 *matrix);

private:
	char prefix[0x3CC];
	Matrix3D CameraInvTransform;
};

void CameraClass::Rva00134A80(Matrix4 *matrix)
{
	Matrix4 projection;
	Get_D3D_Projection_Matrix(&projection);
	Matrix4::Multiply(projection, CameraInvTransform, matrix);
}
