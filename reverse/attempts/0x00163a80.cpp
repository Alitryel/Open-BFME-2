// ?Anim_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHRawAnimClass@@M@Z
// partial score=0.41389 date=2026-10-14
// ?Anim_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHRawAnimClass@@M@Z
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// BFME1 htree.cpp and motchan.h at a7c38d3b2597121f178ab5190b3062478823257d; native 0x163A80..0x1645A2.
// Target changes: quaternion/translation transforms, fade channel type 15 identity, captured-index vector.
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
	float x = (v.Z*q.Y - q.Z*v.Y) + q.W*v.X;
	float y = q.W*v.Y - (v.Z*q.X - q.Z*v.X);
	float z = (q.X*v.Y - v.X*q.Y) + v.Z*q.W;
	float w = -((v.X*q.X + v.Z*q.Z) + v.Y*q.Y);

	return Vector3
	(
		(z*q.Y - q.Z*y) + (q.W*x - q.X*w),
		(q.W*y - w*q.Y) - (q.X*z - q.Z*x),
		(q.X*y - x*q.Y) + (q.W*z - q.Z*w)
	);
}


inline Quaternion operator * (const Quaternion &a, const Quaternion &b)
{
	return Quaternion
	(
		(a.Y*b.Z - b.Y*a.Z) + b.W*a.X + a.W*b.X,
		a.W*b.Y + b.W*a.Y - (a.X*b.Z - b.X*a.Z),
		(a.X*b.Y - b.X*a.Y) + b.W*a.Z + a.W*b.Z,
		a.W*b.W - ((a.Z*b.Z + a.X*b.X) + a.Y*b.Y)
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


class MotionChannelClass {
public:
 unsigned PivotIdx,Type; int VectorLen;float ValueOffset,ValueScale;float *Data;int FirstFrame,LastFrame;
 void Get_Vector(int frame,float *out) const {
  if(frame<FirstFrame || frame>LastFrame) {
   if(Type==15)out[0]=1.0f;
   else if(Type==6){out[0]=out[1]=out[2]=0.0f;out[3]=1.0f;}
   else out[0]=0.0f;
  } else {
   int vframe=frame-FirstFrame;
   for(int i=0;i<VectorLen;++i)out[i]=Data[vframe*VectorLen+i];
  }
 }
 void Get_Vector_As_Quat(int frame,Quaternion &q) const {
  if(frame<FirstFrame || frame>LastFrame)q=Quaternion(0,0,0,1);
  else {const float *d=&Data[(frame-FirstFrame)*VectorLen];q=Quaternion(d[0],d[1],d[2],d[3]);}
 }
};
class BitChannelClass {
public:
 unsigned PivotIdx,Type;int DefaultVal,FirstFrame,LastFrame;unsigned char *Bits;
 int Get_Bit(int frame) const {
  if(frame<FirstFrame || frame>LastFrame)return DefaultVal;
  int bit=frame-FirstFrame;unsigned char mask=(unsigned char)(1<<(bit%8));
  return (Bits[bit/8]&mask)!=0;
 }
};
struct NodeMotionStruct { MotionChannelClass *X,*Y,*Z,*XR,*YR,*ZR,*Q,*Fade;BitChannelClass *Vis;};
class HRawAnimClass {
public:
 virtual void slot0();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();
 virtual int Get_Num_Frames();virtual void slot6();virtual void slot7();virtual void slot8();virtual void slot9();virtual void slot10();virtual void slot11();virtual void slot12();virtual int Get_Num_Pivots();
 char pad[0x4c];NodeMotionStruct *Nodes;
};
class HTreeClass {
public:
 void Anim_Update(const Matrix3D &,HRawAnimClass *,float);
 int Capture_Update(int);
 char Name[16];int NumPivots;PivotClass *Pivot;float ScaleFactor;
 struct CapturedBone{int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
 CapturedBone *CapturedBegin,*CapturedEnd,*CapturedCapacity;
};
void HTreeClass::Anim_Update(const Matrix3D &root,HRawAnimClass *motion,float frame) {
 PivotTransform &initial=Pivot[0].Transform;
 initial.Rotation=Build_Quaternion(root);
 initial.Translation.X=root.Row[0][3];initial.Translation.Y=root.Row[1][3];initial.Translation.Z=root.Row[2][3];
 Pivot[0].IsVisible=true;Pivot[0].m_bfme54=1.0f;
 int iframe=(int)frame;
 if(iframe>=motion->Get_Num_Frames())iframe=0;
 NodeMotionStruct *node=motion->Nodes+1;
 PivotClass *pivot=&Pivot[1];
 PivotClass *endpivot=pivot+(NumPivots-1);
 PivotClass *lastAnimPivot=&Pivot[motion->Get_Num_Pivots()];
 int captured=CapturedBegin==CapturedEnd?-1:CapturedBegin->Index;
 for(;pivot<endpivot;++pivot,++node) {
  const PivotTransform &parent=pivot->Parent->Transform;
  pivot->Transform.Translation=parent.Translation+Rotate_Vector(pivot->BaseTransform.Translation,parent.Rotation);
  pivot->Transform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;
  if(pivot<lastAnimPivot) {
   Vector3 trans(0,0,0);
   if(node->X)node->X->Get_Vector(iframe,&trans.X);
   if(node->Y)node->Y->Get_Vector(iframe,&trans.Y);
   if(node->Z)node->Z->Get_Vector(iframe,&trans.Z);
   if(ScaleFactor!=1.0f){trans.X*=ScaleFactor;trans.Y*=ScaleFactor;trans.Z*=ScaleFactor;}
   if(node->Q) {
    Quaternion q;node->Q->Get_Vector_As_Quat(iframe,q);
    pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
    Quaternion old=pivot->Transform.Rotation;
    pivot->Transform.Rotation.X=(old.Y*q.Z-q.Y*old.Z)+q.W*old.X+old.W*q.X;
    pivot->Transform.Rotation.Y=q.W*old.Y+old.W*q.Y-(old.X*q.Z-q.X*old.Z);
    pivot->Transform.Rotation.Z=(q.Y*old.X-old.Y*q.X)+q.W*old.Z+old.W*q.Z;
    pivot->Transform.Rotation.W=q.W*old.W-((q.Z*old.Z+q.Y*old.Y)+old.X*q.X);
   } else {
    pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
   }
   if(node->Fade){float fade=1;node->Fade->Get_Vector(iframe,&fade);pivot->m_bfme54=fade;}else pivot->m_bfme54=1;
   pivot->IsVisible=node->Vis?node->Vis->Get_Bit(iframe)==1:true;
  }
  if(pivot->Index==captured)captured=Capture_Update(captured);
 }
}
