// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.98 date=2026-10-19
// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// 0x001628A0 bank 2026-10-19 (claude-opus-5-5): hack-free 769/769 (the old bank needed 5 hacks:
// equal-arm root/parent ternaries, a barrier, a dummy block and int-punned copies). 6 aligned
// instruction differences left: the W product's early X*X/Y*Y pair (0x162AB7) and the b.W*[ecx]
// operand order (0x162ADC). Levers: Captured as a real STLport vector with the
// HTreeClassFirstCapturedBone.cpp capture idiom; root via S2CompactTransform *d and
// root.Get_Translation(&d->Position); loop = the landed Slave_Update SlaveCompose with a one-statement
// per component product held in a Quaternion temp; Vector3/Quaternion need WWMath memberwise
// operator= (default operator= gives 838 B). Hypothesis: retail reads the parent quaternion as values
// cl treats as fresh after the translation stores. Home: HTreeClassFirstCapturedBone.cpp (row 0x162290
// stays exact with /G7 /arch:SSE added). Scratch: build/nbr/r2/1628a0/.
// stlport
// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z  retail 0x001628A0, 769 B (ret 4 at 0x162B9E).
// Hack-free candidate: 769/769 B, 6 differing instructions (bank: 6-7 with 5 hacks).
// Root: Build_Quaternion + Matrix3D::Get_Translation through a pointer to Pivot[0]'s
// transform; first captured index via the real STLport vector (empty()/front() give
// retail's +0x1C reload, as in HTreeClassFirstCapturedBone.cpp 0x162290); loop is
// HTreeClassReadPivots.cpp Slave_Update's SlaveCompose (rotate + product) with the
// dot grouped X+(Y+Z) and one-statement product components.
// Residue: W's first X*X/Y*Y pair issued in the other order (0x162AB7) and the
// b.W*a.X product loads a.X instead of b.W (0x162ADC).
#include <vector>

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3 & operator = (const Vector3 & v) { X = v.X; Y = v.Y; Z = v.Z; return *this; }
	float X, Y, Z;
};
inline Vector3 operator + (const Vector3 &a, const Vector3 &b)
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
	float X, Y, Z, W;
};
class Matrix3D
{
public:
	void Get_Translation(Vector3 *set) const { set->X = Row[0][3]; set->Y = Row[1][3]; set->Z = Row[2][3]; }
	float Row[3][4];
};
Quaternion Build_Quaternion(const Matrix3D &mat);

struct S2CompactTransform { Quaternion Q; Vector3 Position; };
struct S2PivotView {
	char Name[16]; S2PivotView *Parent;
	S2CompactTransform Base, Current;
	int Index; bool visible; float factor;
};

static __forceinline void rotate(const Quaternion &q,const Vector3&v,Vector3*out){
 float x=(q.Y*v.Z-q.Z*v.Y)+q.W*v.X;
 float y=-(q.X*v.Z-q.Z*v.X)+q.W*v.Y;
 float z=(q.X*v.Y-q.Y*v.X)+q.W*v.Z;
  float w=0.0f-(q.X*v.X+(q.Y*v.Y+q.Z*v.Z));
 out->X=(q.Y*z-y*q.Z)+(q.W*x-q.X*w);
 out->Y=(q.W*y-q.Y*w)-(q.X*z-q.Z*x);
 out->Z=(q.X*y-q.Y*x)+(q.W*z-q.Z*w);
}
static __forceinline void SlaveProduct(const Quaternion &a,const Quaternion &b,Quaternion &out) {
 Quaternion q;
 q.X=((a.Y*b.Z-a.Z*b.Y)+a.W*b.X)+b.W*a.X;
 q.Y=(a.W*b.Y+a.Y*b.W)-(a.X*b.Z-a.Z*b.X);
 q.Z=((a.X*b.Y-a.Y*b.X)+a.Z*b.W)+a.W*b.Z;
 q.W=a.W*b.W-((a.X*b.X+a.Y*b.Y)+a.Z*b.Z);
 out=q;
}
static __forceinline void SlaveCompose(const S2CompactTransform&a,const S2CompactTransform&b,S2CompactTransform&result){
 Vector3 r;rotate(a.Q,b.Position,&r);result.Position=r+a.Position;
 SlaveProduct(a.Q,b.Q,result.Q);
}

class HTreeClass {
public:
	void Base_Update(const Matrix3D &root);
	int Capture_Update(int pivot_index);
private:
	struct CapturedBone { int Index; Quaternion Rotation; Vector3 Translation; bool WorldSpaceTranslation; };
	char Name[16];
	int NumPivots;
	S2PivotView *Pivot;
	float ScaleFactor;
	std::vector<CapturedBone> Captured;
};

void HTreeClass::Base_Update(const Matrix3D &root)
{
	S2CompactTransform *d = &Pivot[0].Current;
	d->Q = Build_Quaternion(root);
	root.Get_Translation(&d->Position);
	Pivot[0].visible = true;
	Pivot[0].factor = 1.0f;

	int captured = Captured.empty() ? -1 : Captured.front().Index;

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {
		S2PivotView *pivot = &Pivot[piv_idx];
		SlaveCompose(pivot->Parent->Current, pivot->Base, pivot->Current);
		pivot->visible = true;
		pivot->factor = 1.0f;
		if (piv_idx == captured)
			captured = Capture_Update(captured);
	}
}
