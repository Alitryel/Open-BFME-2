// cl: /G7 /arch:SSE /EHsc /MD /DNDEBUG /D_STLP_USE_STATIC_LIB
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
//
// 0x001628A0 (769 bytes): HTreeClass::Base_Update, ZH htree.cpp's root-down
// pivot sweep over BFME 2's compact quaternion/translation pivots (0x58-byte
// PivotClass: Parent +0x10, BaseTransform +0x14, Transform +0x30, IsVisible
// +0x50, PivotFade +0x54). Shape from WorldBuilder HTreeClass::Base_Update
// (0x00A164F0, htree.cpp:498): the root goes through the transform's
// Matrix3D assignment (Build_Quaternion, then Get_Translation), the sweep is
// seeded by the first-captured accessor above (WB calls it, retail inlines
// it), and each pivot calls a static cdecl Multiply(parent, base, &result)
// that rotates base's translation by the parent quaternion, adds the parent
// translation, then multiplies the quaternions through WWMath's by-value
// operator* (WB 0x0071C0E0). cl orders the products' commutative operands
// by its own temporaries, so the accessor call and the verbatim WWMath
// operator* grouping are both needed for retail's operand order.
#include <vector>

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3 & operator = (const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	float X, Y, Z;
};
inline Vector3 operator + (const Vector3 & a, const Vector3 & b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

class Quaternion
{
public:
	Quaternion() {}
	Quaternion(float a, float b, float c, float d) : X(a), Y(b), Z(c), W(d) {}
	float & operator [](int i) { return (&X)[i]; }
	const float & operator [](int i) const { return (&X)[i]; }
	Quaternion & operator = (const Quaternion & source) { X = source[0]; Y = source[1]; Z = source[2]; W = source[3]; return *this; }
	void Rotate_Vector(const Vector3 & v, Vector3 * result) const;
	float X, Y, Z, W;
};

inline Quaternion operator * (const Quaternion & a, const Quaternion & b)
{
	return Quaternion
	(
		a.W*b.X + b.W*a.X + (a.Y*b.Z - b.Y*a.Z),
		a.W*b.Y + b.W*a.Y - (a.X*b.Z - b.X*a.Z),
		a.W*b.Z + b.W*a.Z + (a.X*b.Y - b.X*a.Y),
		a.W * b.W - (a.X * b.X + a.Y * b.Y + a.Z * b.Z)
	);
}

inline void Quaternion::Rotate_Vector(const Vector3 & v, Vector3 * result) const
{
	float x = W*v.X + (Y*v.Z - v.Y*Z);
	float y = W*v.Y - (X*v.Z - v.X*Z);
	float z = W*v.Z + (X*v.Y - v.X*Y);
	float w = -(X*v.X + Y*v.Y + Z*v.Z);

	result->X = W*x - w*X + (Y*z - y*Z);
	result->Y = W*y - w*Y - (X*z - x*Z);
	result->Z = W*z - w*Z + (X*y - Y*x);
}

class Matrix3D
{
public:
	void Get_Translation(Vector3 * set) const { set->X = Row[0][3]; set->Y = Row[1][3]; set->Z = Row[2][3]; }
	float Row[3][4];
};
Quaternion Build_Quaternion(const Matrix3D & mat);

class CompactTransform
{
public:
	CompactTransform & operator = (const Matrix3D & m)
	{
		Q = Build_Quaternion(m);
		m.Get_Translation(&Position);
		return *this;
	}
	static void Multiply(const CompactTransform & a, const CompactTransform & b, CompactTransform * res)
	{
		Vector3 tmp;
		a.Q.Rotate_Vector(b.Position, &tmp);
		res->Position = tmp + a.Position;
		res->Q = a.Q * b.Q;
	}
	Quaternion Q;
	Vector3 Position;
};

class PivotClass
{
public:
	char Name[16];
	PivotClass * Parent;
	CompactTransform BaseTransform;
	CompactTransform Transform;
	int Index;
	bool IsVisible;
	float PivotFade;
};

class HTreeClass {
public:
	int rva00162290() const;
	int Capture_Update(int pivot_index);
	void Base_Update(const Matrix3D & root);
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

void HTreeClass::Base_Update(const Matrix3D & root)
{
	PivotClass *pivot;

	Pivot[0].Transform = root;
	Pivot[0].IsVisible = true;
	Pivot[0].PivotFade = 1.0f;

	int captured = rva00162290();

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {

		pivot = &Pivot[piv_idx];

		CompactTransform::Multiply(pivot->Parent->Transform, pivot->BaseTransform, &(pivot->Transform));
		pivot->IsVisible = 1;
		pivot->PivotFade = 1.0f;

		if (piv_idx == captured) captured = Capture_Update(captured);
	}
}
