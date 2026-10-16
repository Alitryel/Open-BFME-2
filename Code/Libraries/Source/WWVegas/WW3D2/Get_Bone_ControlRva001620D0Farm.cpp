// ?Get_Bone_Control@HTreeClass@@QBEXHAAVMatrix3D@@@Z
// ?Get_Bone_Control@HTreeClass@@QBEXHAAVMatrix3D@@@Z
template<class T> inline volatile T &__vref(T &x){return *(volatile T *)&x;}
// cl: /O2 /arch:SSE /EHsc /MD /DNDEBUG
class Quaternion { public: float X,Y,Z,W; Quaternion &operator=(const Quaternion &q){X=q.X;Y=q.Y;Z=q.Z;W=q.W;return *this;} };
class Vector3 { public: float X,Y,Z; Vector3(const Vector3 &v):X(v.X),Y(v.Y),Z(v.Z){} Vector3 &operator=(const Vector3 &v){X=v.X;Y=v.Y;Z=v.Z;return *this;} Vector3(float x,float y,float z):X(x),Y(y),Z(z){} };
class Matrix3D { public: float M[3][4]; void Get_Translation(Vector3 *v) const {v->X=M[0][3];v->Y=M[1][3];v->Z=M[2][3];} };
// The same accessor under a unit-local name, so this /O2 unit emits no external
// Matrix3D::Get_Translation copy differing from retail's x87 body (0x0009314A).
struct HTreeTranslationView : Matrix3D { void Get_Translation(Vector3 *v) const {v->X=M[0][3];v->Y=M[1][3];v->Z=M[2][3];} };
Quaternion Build_Quaternion(const Matrix3D &);
class PivotClass;
class HTreeClass {
 struct CapturedBone {int Index;Quaternion Rotation;Vector3 Translation;bool WorldSpaceTranslation;};
 char Name[16];int NumPivots;PivotClass *Pivot;float ScaleFactor;
 CapturedBone *Begin,*End,*Capacity;
public: void Control_Bone(int,const Matrix3D &,bool); void Get_Bone_Control(int,Matrix3D &) const;
};
// HTreeClass::Control_Bone (0x00162060) is rowed in htree_control.cpp.

void HTreeClass::Get_Bone_Control(int index,Matrix3D &out) const
{
 CapturedBone *bone=Begin;
 while(bone!=End && bone->Index<index) ++bone;
 if(bone==End || bone->Index!=index) {
  out.M[0][0]=1.0f;out.M[0][1]=0.0f;out.M[0][2]=0.0f;out.M[0][3]=0.0f;
  out.M[1][0]=0.0f;out.M[1][1]=1.0f;out.M[1][2]=0.0f;out.M[1][3]=0.0f;
  out.M[2][0]=0.0f;out.M[2][1]=0.0f;out.M[2][2]=1.0f;out.M[2][3]=0.0f;
  return;
 }
 {
  const Quaternion &q=bone->Rotation;
  float xx=q.X*q.X*2.0f;
  float xy=__vref(q.X)*q.Y*2.0f;
  float xz=q.X*q.Z*2.0f;
  float xw=q.X*q.W*2.0f;
  float yy=q.Y*q.Y*2.0f;
  float yz=q.Y*q.Z*2.0f;
  float yw=q.Y*q.W*2.0f;
  float zz=q.Z*q.Z*2.0f;
  float zw=q.Z*q.W*2.0f;
  out.M[0][0]=1.0f-yy-zz; out.M[0][1]=xy-zw; out.M[0][2]=yw+xz;
  out.M[1][0]=zw+xy; out.M[1][1]=1.0f-zz-xx; out.M[1][2]=yz-xw;
  out.M[2][0]=xz-yw; out.M[2][1]=yz+xw; out.M[2][2]=1.0f-yy-xx;
  out.M[0][3]=bone->Translation.X;out.M[1][3]=bone->Translation.Y;out.M[2][3]=bone->Translation.Z;
 }
}
