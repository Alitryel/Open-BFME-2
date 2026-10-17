// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.917 date=2026-10-17
// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.879 date=2026-10-15
// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.871 date=2026-10-15
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.86647 date=2026-10-14
// ?Base_Update@HTreeClass@@QAEXABVMatrix3D@@@Z
// partial score=0.8 date=2026-09-23
// cl: /G7 /arch:SSE /DNDEBUG /MD /EHsc

class Vector3
{
public:
	Vector3() {}
	Vector3(float x, float y, float z) : X(x), Y(y), Z(z) {}
	Vector3 &operator=(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;return *this;}
 float X, Y, Z;
};

inline Vector3 operator + (const Vector3 &a, const Vector3 &b)
{
	return Vector3(a.X + b.X, a.Y + b.Y, a.Z + b.Z);
}

class Matrix3D
{
public:
	float Row[3][4];
};

class Quaternion
{
public:
	Quaternion() {}
	Quaternion(float x, float y, float z, float w) : X(x), Y(y), Z(z), W(w) {}

	Quaternion &operator=(const Quaternion &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;}
 float X, Y, Z, W;
};

inline Vector3 Rotate_Vector(const Vector3 &v, const Quaternion &q)
{
	float x = q.W*v.X + (q.Y*v.Z - v.Y*q.Z);
	float y = q.W*v.Y - (q.X*v.Z - v.X*q.Z);
	float z = q.W*v.Z + (q.X*v.Y - v.X*q.Y);
	float w = -(q.X*v.X + q.Y*v.Y + q.Z*v.Z);

	return Vector3
	(
		q.W*x - w*q.X + (q.Y*z - y*q.Z),
		q.W*y - w*q.Y - (q.X*z - x*q.Z),
		q.W*z - w*q.Z + (q.X*y - q.Y*x)
	);
}


inline Quaternion operator * (const Quaternion &a, const Quaternion &b)
{
	return Quaternion
	(
		a.W*b.X + b.W*a.X + (a.Y*b.Z - b.Y*a.Z),
		a.W*b.Y + b.W*a.Y - (a.X*b.Z - b.X*a.Z),
		a.W*b.Z + b.W*a.Z + (a.X*b.Y - b.X*a.Y),
		a.W*b.W - (a.X*b.X + a.Y*b.Y + a.Z*b.Z)
	);
}

Quaternion Build_Quaternion(const Matrix3D &mat);

// BFME 2 pivot transform: rotation quaternion plus translation.
struct PivotTransform
{
	Quaternion Rotation;
	Vector3 Translation;
};

inline PivotTransform operator * (const PivotTransform &parent, const PivotTransform &child)
{
	PivotTransform result;
	result.Translation = Rotate_Vector(child.Translation, parent.Rotation) + parent.Translation;
	result.Rotation = parent.Rotation * child.Rotation;
	return result;
}

struct PivotClass
{
	char Name[16];
	PivotClass *Parent;					// +0x10
	PivotTransform BaseTransform;		// +0x14
	PivotTransform Transform;			// +0x30
	int Index;							// +0x4C
	bool IsVisible;						// +0x50
	float m_bfme54;						// +0x54
};

class HTreeClass
{
public:
	void Base_Update(const Matrix3D &root);
	int Capture_Update(int pivot_index);

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
	float ScaleFactor;					// +0x18
	int *CapturedBegin;					// +0x1C
	int *CapturedEnd;					// +0x20
};

void HTreeClass::Base_Update(const Matrix3D &root)
{
	PivotClass *ppiv = Pivot;
	PivotTransform *d = &ppiv[0].Transform;
	const Matrix3D *proot = &root;
	d->Rotation = Build_Quaternion((1 ? *proot : *proot));
	{
		*(int*)&d->Translation.X = *(int*)&proot->Row[0][3];
		*(int*)&d->Translation.Y = *(int*)&proot->Row[1][3];
		*(int*)&d->Translation.Z = *(int*)&proot->Row[2][3];
	}
	Pivot[0].IsVisible = true;
	Pivot[0].m_bfme54 = 1.0f;

	int *pCapEnd = CapturedEnd;
	int *pCapBegin = CapturedBegin;
	_ReadWriteBarrier();
	int captured = (pCapBegin == pCapEnd) ? -1 : *pCapBegin;
	{
		/* single reload to mirror retail's duplicated load */
		int *pCli = pCapBegin;
		(void)pCli;
	}

	for (int piv_idx = 1; piv_idx < NumPivots; piv_idx++) {
		PivotClass *pivot = &Pivot[piv_idx];
		PivotTransform *parent = (1 ? &pivot->Parent->Transform : &pivot->Parent->Transform);
		Vector3 rotated = Rotate_Vector(pivot->BaseTransform.Translation, parent->Rotation);
		rotated = parent->Translation + rotated;
		pivot->Transform.Translation = rotated;
		float rx = parent->Rotation.W * pivot->BaseTransform.Rotation.X + parent->Rotation.X * pivot->BaseTransform.Rotation.W + (parent->Rotation.Y * pivot->BaseTransform.Rotation.Z - parent->Rotation.Z * pivot->BaseTransform.Rotation.Y);
		float ry = parent->Rotation.W * pivot->BaseTransform.Rotation.Y + parent->Rotation.Y * pivot->BaseTransform.Rotation.W - (parent->Rotation.X * pivot->BaseTransform.Rotation.Z - parent->Rotation.Z * pivot->BaseTransform.Rotation.X);
		float rz = parent->Rotation.W * pivot->BaseTransform.Rotation.Z + parent->Rotation.Z * pivot->BaseTransform.Rotation.W + (parent->Rotation.X * pivot->BaseTransform.Rotation.Y - parent->Rotation.Y * pivot->BaseTransform.Rotation.X);
		float rw = parent->Rotation.W * pivot->BaseTransform.Rotation.W - ((parent->Rotation.X * pivot->BaseTransform.Rotation.X + parent->Rotation.Y * pivot->BaseTransform.Rotation.Y) + parent->Rotation.Z * pivot->BaseTransform.Rotation.Z);
		pivot->Transform.Rotation = Quaternion(rx, ry, rz, rw);
		pivot->IsVisible = true;
		pivot->m_bfme54 = 1.0f;

		if (piv_idx == captured)
			captured = Capture_Update(piv_idx);
	}
}
