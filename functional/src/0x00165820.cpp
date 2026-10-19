// ?Combo_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimComboClass@@@Z
// partial score=0.436 date=2026-10-17
// ?Combo_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimComboClass@@@Z
// partial score=0.595 date=2026-10-14
// ?Combo_Update@HTreeClass@@QAEXABVMatrix3D@@PAVHAnimComboClass@@@Z
// cl: /O2 /G7 /arch:SSE /DNDEBUG /MD /EHsc
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// BFME1 htree.cpp at a7c38d3b2597121f178ab5190b3062478823257d; native 0x165820..0x166105.
// BFME2 quaternion transform and Nlerp; PivotMap secondary RefCount base at +0x18 verified in native.
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


class HAnimClass {
public:
 virtual void Delete_This();virtual void slot1();virtual void slot2();virtual void slot3();virtual void slot4();virtual void slot5();virtual void slot6();virtual void slot7();
 virtual void Get_Translation(Vector3 &,int,float);virtual bool Get_Orientation(Quaternion &,int,float);
 virtual void slot10();virtual bool Get_Visibility(int,float);virtual float Get_Fade(int,float);virtual int Get_Num_Pivots();
 int NumRefs;
 void Release_Ref(){if(--NumRefs==0)Delete_This();}
};
class RefCountClass {
public:
 virtual void Delete_This();int NumRefs;
 void Release_Ref(){if(--NumRefs==0)Delete_This();}
};
class PivotMapVector {
public:
 virtual void slot0();float *Values;char rest[0x10];
};
class PivotMapClass:public PivotMapVector,public RefCountClass {
public:float &operator[](int i){return Values[i];}
};
class HAnimComboClass {
public:
 char pad[0x10];int NumAnims;
 int Get_Num_Anims()const{return NumAnims;}
 HAnimClass *Get_Motion(int);HAnimClass *Peek_Motion(int);float Get_Frame(int);float Get_Weight(int);PivotMapClass *Get_Pivot_Weight_Map(int);
};
void BFME2_Nlerp(Quaternion &,const Quaternion &,const Quaternion &,float);
class HTreeClass {
public:
 void Combo_Update(const Matrix3D &,HAnimComboClass *);
 int Capture_Update(int);
 char Name[16];int NumPivots;PivotClass *Pivot;float ScaleFactor;
 struct CapturedBone{int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
 CapturedBone *CapturedBegin,*CapturedEnd,*CapturedCapacity;
};
void HTreeClass::Combo_Update(const Matrix3D &root,HAnimComboClass *anim) {
 PivotTransform &initial=Pivot[0].Transform;
 initial.Rotation=Build_Quaternion(root);
 initial.Translation.X=root.Row[0][3];initial.Translation.Y=root.Row[1][3];initial.Translation.Z=root.Row[2][3];
 Pivot[0].IsVisible=true;Pivot[0].m_bfme54=1.0f;
 int num_anim_pivots=100000;
 for(int anim_num=0;anim_num<(anim->Get_Num_Anims());++anim_num)
  num_anim_pivots=num_anim_pivots<anim->Peek_Motion(anim_num)->Get_Num_Pivots()?num_anim_pivots:anim->Peek_Motion(anim_num)->Get_Num_Pivots();
 _ReadWriteBarrier(); _ReadWriteBarrier();
 if(num_anim_pivots==100000)num_anim_pivots=0;
 int captured;
 if(CapturedBegin==CapturedEnd)captured=-1;
 else captured=CapturedBegin->Index;
 int piv_idx=1;
 for(;piv_idx<NumPivots;++piv_idx) {
  PivotClass *pivot=&Pivot[piv_idx];
  const PivotTransform &parent=pivot->Parent->Transform;
  PivotTransform &xform=pivot->Transform;
  Vector3 base_trans=pivot->BaseTransform.Translation;
  *(volatile float*)&base_trans.X; *(volatile float*)&base_trans.Y; *(volatile float*)&base_trans.Z;
  Vector3 _rv = Rotate_Vector(base_trans,parent.Rotation);
  xform.Translation=parent.Translation+_rv;
  _ReadWriteBarrier();
  xform.Rotation=parent.Rotation*pivot->BaseTransform.Rotation;
  if(piv_idx<num_anim_pivots) {
   Vector3 trans(0,0,0);Quaternion q0,q1;float weight_total=0;int wcount=0;
   for(int anim_num=0;anim_num<anim->Get_Num_Anims();++anim_num) {
    HAnimClass *motion=anim->Get_Motion(anim_num);
    if(motion) {
     float frame_num=anim->Get_Frame(anim_num);
     PivotMapClass *pivot_map=anim->Get_Pivot_Weight_Map(anim_num);
     float weight=anim->Get_Weight(anim_num);
     if(pivot_map){weight*=(*pivot_map)[piv_idx];pivot_map->Release_Ref();}
     if(weight!=0.0) {
      ++wcount;Vector3 temp_trans;motion->Get_Translation(temp_trans,piv_idx,frame_num);
      float scale=(float)(double)(weight*ScaleFactor);
      trans.X+=(scale*temp_trans.X);trans.Y+=(scale*temp_trans.Y);trans.Z+=(scale*temp_trans.Z);
      weight_total+=weight;
      if(!motion->Get_Orientation(q1,piv_idx,frame_num))q1=Quaternion(0,0,0,1);
      if(wcount==1)q0=q1;else BFME2_Nlerp(q0,q0,q1,weight/weight_total);
     }
     motion->Release_Ref();
    }
   }
   if(weight_total!=0.0f) {
    pivot->Transform.Translation=Rotate_Vector(trans,pivot->Transform.Rotation)+pivot->Transform.Translation;
    Quaternion old=pivot->Transform.Rotation;
    pivot->Transform.Rotation.X=(old.Y*q0.Z-q0.Y*old.Z)+q0.W*old.X+old.W*q0.X;
    pivot->Transform.Rotation.Y=q0.W*old.Y+old.W*q0.Y-(old.X*q0.Z-q0.X*old.Z);
    pivot->Transform.Rotation.Z=(q0.Y*old.X-old.Y*q0.X)+q0.W*old.Z+old.W*q0.Z;
    _ReadWriteBarrier();
    pivot->Transform.Rotation.W=q0.W*old.W-((q0.Z*old.Z+q0.Y*old.Y)+old.X*q0.X);
   }
   pivot->IsVisible=false;pivot->m_bfme54=0;float fade_count=0;
   for(anim_num=0;anim_num<anim->Get_Num_Anims()&&!pivot->IsVisible;++anim_num) {
    HAnimClass *motion=anim->Get_Motion(anim_num);
    if(motion) {
     float frame_num=anim->Get_Frame(anim_num);
     pivot->IsVisible|=motion->Get_Visibility(piv_idx,frame_num);
     pivot->m_bfme54+=motion->Get_Fade(piv_idx,frame_num);
     fade_count+=1.0f;motion->Release_Ref();
    }
   }
   if(fade_count>0.0f)pivot->m_bfme54/=fade_count;
  }
  if(piv_idx==captured)captured=Capture_Update(captured);
 }
}
