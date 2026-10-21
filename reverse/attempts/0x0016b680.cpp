// ?get_deformed_vertices@MeshModelClass@@QAEXPAVVector3@@PBVHTreeClass@@@Z
// partial score=0.98513 date=2026-10-21
// cl: /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug
// Compose with meshgeometry.cpp; target proof and provenance in re_attempts.log.
// Matrices use the HTreePivotTransform::Get_Matrix3D spelling (0x0014D28E); both are scaled row by row as in BFME1 0x00925860.
// Shape follows WorldBuilder MeshGeometryClass::get_deformed_vertices (0xA0E990): buffers read through Get_Array(),
// pivots through Get_Transform(), and the blend sums in the order of its Matrix3D helper (0xA0ECA0).
// The blend (WB 0xA0ECA0) and the single-bone loop (WB BoneTransform::TransformPositionArray, 0xA0EE10) are members with
// their loops inside, in WB's operand order; the tree view is held in htree.
// This version compiles against the real WWMath vector3.h, vector4.h, matrix3d.h and quat.h; SkinMatrix3D stands in for
// BFME 2's Matrix3D blend member. The locals are WB 0xA0E990's set plus the run-record pointer run, which replaces htree.
#include "vector3.h"
#include "vector4.h"
#include "matrix3d.h"
#include "quat.h"
void Rva00129510Inc();
class BoneTransform {
public:
 __forceinline void Get_Matrix3D(Matrix3D &m) const {
  float xx=Rotation.X*Rotation.X*2.0f;
  float xy=Rotation.X*Rotation.Y*2.0f;
  float xz=Rotation.X*Rotation.Z*2.0f;
  float xw=Rotation.X*Rotation.W*2.0f;
  float yy=Rotation.Y*Rotation.Y*2.0f;
  float yz=Rotation.Y*Rotation.Z*2.0f;
  float yw=Rotation.Y*Rotation.W*2.0f;
  float zz=Rotation.Z*Rotation.Z*2.0f;
  float zw=Rotation.Z*Rotation.W*2.0f;
  m[0][0]=(1.0f-yy-zz);m[0][1]=xy-zw;m[0][2]=xz+yw;
  m[1][0]=xy+zw;m[1][1]=(1.0f-zz-xx);m[1][2]=yz-xw;
  m[2][0]=xz-yw;m[2][1]=yz+xw;m[2][2]=(1.0f-yy-xx);
  m[0][3]=Translation.X;m[1][3]=Translation.Y;m[2][3]=Translation.Z;
 }
 void TransformPositionArray(const Vector3 *v,Vector3 *out,int count) const;
 Quaternion Rotation;
 Vector3 Translation;
};
struct PivotClass {char Name[16];PivotClass *Parent;BoneTransform BaseTransform;BoneTransform Transform;int Index;bool IsVisible;char tail[7];};
class HTreeClass {
public:
 const BoneTransform &Get_Transform(int pivot) const {return Pivot[pivot].Transform;}
private:
 char Name[16];int NumPivots;PivotClass *Pivot;
};
template<class T> class ShareBufferClass {public:T *Get_Array() {return Array;} private:char fields00[0xc];T *Array;};
__forceinline void BoneTransform::TransformPositionArray(const Vector3 *v,Vector3 *out,int count) const {
 while(count--) {
  float x=(Rotation.W*v->X+(Rotation.Y*v->Z-v->Y*Rotation.Z));
  float y=Rotation.W*v->Y-(Rotation.X*v->Z-v->X*Rotation.Z);
  float z=Rotation.W*v->Z+(Rotation.X*v->Y-v->X*Rotation.Y);
  float w=-((Rotation.X*v->X)+Rotation.Y*v->Y+(Rotation.Z*v->Z));
  out->X=(x*Rotation.W-w*Rotation.X+(z*Rotation.Y-y*Rotation.Z)+Translation.X);
  out->Y=(y*Rotation.W-w*Rotation.Y-(z*Rotation.X-x*Rotation.Z)+Translation.Y);
  out->Z=z*Rotation.W-w*Rotation.Z+(y*Rotation.X-x*Rotation.Y)+Translation.Z;
  v++;out++;
 }
}
class SkinMatrix3D : public Matrix3D {
public:
 void Blend(const Vector3 *in0,const SkinMatrix3D &tm1,const Vector3 *in1,Vector3 *out,int count) const;
};
__forceinline void SkinMatrix3D::Blend(const Vector3 *in0,const SkinMatrix3D &tm1,const Vector3 *in1,Vector3 *out,int count) const {
 while(count--) {
  out->X=Row[0].X*in0->X+Row[0].Y*in0->Y+Row[0].Z*in0->Z+Row[0].W+tm1.Row[0].X*in1->X+tm1.Row[0].Y*in1->Y+tm1.Row[0].Z*in1->Z+tm1.Row[0].W;
  out->Y=Row[1].X*in0->X+Row[1].Y*in0->Y+Row[1].Z*in0->Z+Row[1].W+tm1.Row[1].X*in1->X+tm1.Row[1].Y*in1->Y+tm1.Row[1].Z*in1->Z+tm1.Row[1].W;
  out->Z=Row[2].X*in0->X+Row[2].Y*in0->Y+Row[2].Z*in0->Z+Row[2].W+tm1.Row[2].X*in1->X+tm1.Row[2].Y*in1->Y+tm1.Row[2].Z*in1->Z+tm1.Row[2].W;
  in0++;in1++;out++;
 }
}
class MeshModelClass {
public:
 void get_deformed_vertices(Vector3 *,const HTreeClass *);
 void get_deformed_vertices(Vector3 *,Vector3 *,const HTreeClass *);
 int Get_Vertex_Count() const {return VertexCount;}
private:
 char fields00[0x28];int VertexCount;int fields2C;
 ShareBufferClass<Vector3> *Vertex[2],*VertexNorm[2];
 char fields40[0x10];ShareBufferClass<unsigned short> *VertexBoneLink,*VertexRuns;
};
// Destination pointers MUST point to arrays large enough to hold all vertices
void MeshModelClass::get_deformed_vertices(Vector3 *dst_vert,const HTreeClass *htree) {
 if(VertexRuns==0||VertexBoneLink==0||htree==0)return;
 int streams=1;
 if(Vertex[1])streams=2;
 int i;
 Vector3 *src[2];
 for(i=0;i<streams;++i) {if(Vertex[i])src[i]=Vertex[i]->Get_Array();else src[i]=0;}
 unsigned short *runs=VertexRuns->Get_Array();
 unsigned short *bonelinks=VertexBoneLink->Get_Array();
 Rva00129510Inc();
 int vi=Get_Vertex_Count();
 int remaining=vi;
 while(remaining>0) {
  unsigned short *run=runs;
  int cnt=run[1];runs+=2;
  remaining-=cnt;
  int bone0=bonelinks[0];
  int bone1=bonelinks[vi];
  if(streams==2 && bone1) {
   float w0=bonelinks[vi*2]/100.0f;
   float w1=(bonelinks[vi*3]/100.0f);
   SkinMatrix3D tm0;
   htree->Get_Transform(bone0).Get_Matrix3D(tm0);
   SkinMatrix3D tm1;
   htree->Get_Transform(bone1).Get_Matrix3D(tm1);
   for(int j=0;j<3;j++) {tm0[j]*=w0;tm1[j]*=w1;}
   tm0.Blend(src[0],tm1,src[1],dst_vert,cnt);
  } else {
   const BoneTransform &tm=htree->Get_Transform(bone0);
   tm.TransformPositionArray(src[0],dst_vert,cnt);
  }
  bonelinks+=cnt;
  for(int k=0;k<streams;++k)src[k]+=cnt;
  dst_vert+=cnt;
 }
}
