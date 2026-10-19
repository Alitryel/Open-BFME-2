// cl: /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include
// HTree compact-pivot lookup and base-pose evaluation.
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

// HTreeClass::Simple_Evaluate_Pivot at 0x001606E0 (1144 bytes): walk from
// the pivot up to the root accumulating rotation and translation, build
// the matrix, then post-multiply by the object transform.
//
// Layout (proven by the HTreeClassCopyConstructor / HTreeClassInitDefault
// units): 0x58-byte pivots, rotation-plus-translation blocks at +0x14 and
// +0x30, Index at +0x4C.  Only Matrix3D::Multiply is called (matched
// WWMath unit); all of the quaternion math is inline.

// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it; retail links the
// /O1 body at 0x00001423. Instantiate it first in an unemitted anchor (the
// lookuptable.cpp pattern) so this unit's copy is that body.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)

#include <string.h>
#include <assert.h>
#include "quat.h"
#include "matrix3d.h"
#include "vector3.h"

struct S2CompactTransform
{
	Quaternion Q;
	Vector3 Position;
	explicit S2CompactTransform(bool init) : Q(init), Position(0.0f, 0.0f, 0.0f) {}
};

struct PivotClass
{
	char Name[16];
	PivotClass *Parent;
	S2CompactTransform Base, Current;
	int Index;
	bool IsVisible;
	float PivotFade;
};
typedef char CompactPivotSize[(sizeof(PivotClass) == 0x58) ? 1 : -1];

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2/htree.h
class HTreeClass
{
public:
	bool Simple_Evaluate_Pivot(int pivot_index, const Matrix3D &obj_tm, Matrix3D *end_tm) const;
	int Get_Bone_Index(const char * name) const;
	const char * Get_Bone_Name(int boneidx) const;
	int Get_Parent_Index(int bone_indx) const;

private:
	char Name[16];
	int NumPivots;						// +0x10
	PivotClass *Pivot;					// +0x14
};

int HTreeClass::Get_Bone_Index(const char * name) const
{
	int i = 0;
	if (NumPivots > i) {
		do {
			if (_strcmpi(Pivot[i].Name, name) == 0) {
				return i;
			}
			++i;
		} while (i < NumPivots);
	}
	return 0;
}

const char * HTreeClass::Get_Bone_Name(int boneidx) const
{
	assert(boneidx >= 0);
	assert(boneidx < NumPivots);

	return Pivot[boneidx].Name;
}

int HTreeClass::Get_Parent_Index(int bone_indx) const
{
	assert(bone_indx >= 0);
	assert(bone_indx < NumPivots);

	if (Pivot[bone_indx].Parent != NULL) {
		return Pivot[bone_indx].Parent->Index;
	} else {
		return 0;
	}
}

static __forceinline Matrix3D &S2PivotMatrix(const Quaternion &Q, const S2CompactTransform &q, Matrix3D &m)
{
	const float xx = Q.X * Q.X * 2.0f, xy = 2.0f * (Q.X * Q.Y), xz = Q.Z * Q.X * 2.0f, wx = Q.W * Q.X * 2.0f;
	const float yy = Q.Y * Q.Y * 2.0f, yz = Q.Z * Q.Y * 2.0f, wy = Q.W * Q.Y * 2.0f;
	const float zz = Q.Z * Q.Z * 2.0f, wz = Q.W * Q.Z * 2.0f;
	m[0][0] = 1.0f - yy - zz;
	m[0][1] = xy - wz;
	m[0][2] = xz + wy;
	m[1][0] = xy + wz;
	m[1][1] = 1.0f - zz - xx;
	m[1][2] = yz - wx;
	m[2][0] = xz - wy;
	m[2][1] = yz + wx;
	m[2][2] = 1.0f - yy - xx;
	m[0][3] = q.Position.X;
	m[1][3] = q.Position.Y;
	m[2][3] = q.Position.Z;
	return m;
}

static __forceinline void baseRotate(const Quaternion &q, const Vector3 &v, Vector3 *out)
{
	float x = (q.Y * v.Z - q.Z * v.Y) + q.W * v.X;
	float y = -(q.X * v.Z - q.Z * v.X) + q.W * v.Y;
	float z = (q.X * v.Y - q.Y * v.X) + q.W * v.Z;
	float w = 0.0f - (q.X * v.X + q.Y * v.Y + q.Z * v.Z);
	float rx = q.Y * z - y * q.Z;
	rx += q.W * x - q.X * w;
	out->X = rx;
	out->Y = (q.W * y - q.Y * w) - (q.X * z - q.Z * x);
	float rz = q.X * y - q.Y * x;
	rz += q.W * z - q.Z * w;
	out->Z = rz;
}

static __forceinline void baseCompose(const S2CompactTransform &a, const S2CompactTransform &b, S2CompactTransform &result)
{
	Vector3 r;
	baseRotate(a.Q, b.Position, &r);
	result.Position = r + a.Position;
	result.Q = a.Q * b.Q;
}

/***********************************************************************************************
 * HTreeClass::Simple_Evaluate_Pivot -- Returns the transform of a pivot at the given frame.	  *
 *                                                                                             *
 * INPUT:                                                                                      *
 *                                                                                             *
 * OUTPUT:                                                                                     *
 *                                                                                             *
 * WARNINGS:                                                                                   *
 *                                                                                             *
 * HISTORY:                                                                                    *
 *   04/13/2000 PDS  : Created.                                                                *
 *=============================================================================================*/
bool HTreeClass::Simple_Evaluate_Pivot(int pivot_index, const Matrix3D &obj_tm, Matrix3D *end_tm) const
{
	if (end_tm == NULL) {
		return false;
	}
	end_tm->Make_Identity();
	if (pivot_index < 0 || pivot_index >= NumPivots) {
		return false;
	}
	S2CompactTransform total(true);
	//
	//	Loop over the hierarchy of pivots that this pivot is
	// attached to and transform each.
	//
	for (PivotClass *p = &Pivot[pivot_index]; p != NULL && p->Parent != NULL; p = p->Parent) {
		//
		//	Transform the return value by this transform
		//
		baseCompose(p->Base, total, total);
	}
	S2PivotMatrix(total.Q, total, *end_tm);
	//
	//	Transform the return value by the object's transform
	//
	Matrix3D::Multiply(obj_tm, *end_tm, end_tm);
	return true;
}
