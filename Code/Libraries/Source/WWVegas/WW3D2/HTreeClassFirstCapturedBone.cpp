// cl: /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
// stlport
//
// 0x00162290 (18 bytes, padded to 0x001622B0): the pivot index of the first
// captured bone, or -1 when none is captured. Its callers are the BFME 2
// update loops, which seed their sweep with it and continue with the value
// returned by the pinned HTreeClass::Capture_Update (0x001622B0). The
// captured bones are the sorted 36-byte records at +0x1C that
// htree_control.cpp's Control_Bone and Is_Bone_Captured search, held in a
// real STLport vector: retail reloads +0x1C for front() after empty(), which
// only the vector's own inline accessors reproduce. The method name is
// address-derived; no image names it.
#include <vector>

class Quaternion { public: float X,Y,Z,W; };
class Vector3 { public: float X,Y,Z; };
class PivotClass;

class HTreeClass {
public:
	int rva00162290() const;
private:
	struct CapturedBone { int Index; Quaternion Rotation; Vector3 Translation; bool WorldSpaceTranslation; };
	char Name[16];
	int NumPivots;
	PivotClass *Pivot;
	float ScaleFactor;
	std::vector<CapturedBone> Captured;
};

int HTreeClass::rva00162290() const
{
	if (Captured.empty())
		return -1;
	return Captured.front().Index;
}
