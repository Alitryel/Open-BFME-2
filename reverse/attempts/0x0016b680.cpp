// ?get_deformed_vertices@MeshModelClass@@QAEXPAVVector3@@PBVHTreeClass@@@Z
// partial score=0.95 date=2026-10-20
// cl: /I. /Ireference/shims/meshgeom /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Compose with meshgeometry.cpp; target proof and provenance in re_attempts.log.
// Matrices use the HTreePivotTransform::Get_Matrix3D spelling (0x0014D28E); both are scaled row by row as in BFME1 0x00925860.
// Shape follows WorldBuilder MeshGeometryClass::get_deformed_vertices (0xA0E990): buffers read through Get_Array(),
// pivots through Get_Transform(), and the blend sums in the order of its Matrix3D helper (0xA0ECA0).
// The blend (WB 0xA0ECA0) and the single-bone loop (WB BoneTransform::TransformPositionArray, 0xA0EE10) are members with
// their loops inside, in WB's operand order with each output row in outer parentheses; the tree view is held in htree.
#include "reference/shims/bfme_vector3_full_link/vector3_full_link.h"
#include "reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "htree.h"
#include "quat.h"
struct BfmeSkinRow { float X,Y,Z,W; __forceinline float &operator[](int i) {return (&X)[i];} __forceinline const float &operator[](int i) const {return (&X)[i];} __forceinline BfmeSkinRow &operator*=(float k) {X*=k;Y*=k;Z*=k;W*=k;return *this;} };
struct BfmeSkinMatrix { BfmeSkinRow v[3]; __forceinline BfmeSkinRow &operator[](int i) {return v[i];} __forceinline const BfmeSkinRow &operator[](int i) const {return v[i];} void Blend(const Vector3 *in0,const BfmeSkinMatrix &tm1,const Vector3 *in1,Vector3 *out,int count) const; };
void Rva00129510Inc();
struct BfmeSkinTransform {
 __forceinline void Get_Matrix3D(BfmeSkinMatrix &m) const {
 float xx=Rotation.X*Rotation.X*2.0f;
 float xy=Rotation.X*Rotation.Y*2.0f;
 float xz=Rotation.X*Rotation.Z*2.0f;
 float xw=Rotation.X*Rotation.W*2.0f;
 float yy=Rotation.Y*Rotation.Y*2.0f;
 float yz=Rotation.Y*Rotation.Z*2.0f;
 float yw=Rotation.Y*Rotation.W*2.0f;
 float zz=Rotation.Z*Rotation.Z*2.0f;
 float zw=Rotation.Z*Rotation.W*2.0f;
 m[0][0]=1.0f-yy-zz;m[0][1]=xy-zw;m[0][2]=xz+yw;
 m[1][0]=xy+zw;m[1][1]=1.0f-zz-xx;m[1][2]=yz-xw;
 m[2][0]=xz-yw;m[2][1]=yz+xw;m[2][2]=1.0f-yy-xx;
 m[0][3]=Translation.X;m[1][3]=Translation.Y;m[2][3]=Translation.Z;
 }
 void TransformPositionArray(const Vector3 *v,Vector3 *out,int count) const;
 Quaternion Rotation;Vector3 Translation;
};
struct BfmeSkinPivot {char name[16];BfmeSkinPivot *parent;BfmeSkinTransform Base,Current;int index;bool visible;char tail[7];};
typedef char BfmeSkinPivotStride[sizeof(BfmeSkinPivot)==0x58?1:-1];
struct BfmeSkinTreeView {public:const BfmeSkinTransform &Get_Transform(int pivot) const {return pivots[pivot].Current;} char fields00[0x14];BfmeSkinPivot *pivots;};
template<class T> struct BfmeSkinBuffer {T *Get_Array() {return data;} char fields00[0xc];T *data;};
__forceinline void BfmeSkinTransform::TransformPositionArray(const Vector3 *v,Vector3 *out,int count) const {
 while(count--) {
   float x=Rotation.W*v->X+(Rotation.Y*v->Z-v->Y*Rotation.Z);
   float y=Rotation.W*v->Y-(Rotation.X*v->Z-v->X*Rotation.Z);
   float z=Rotation.W*v->Z+(Rotation.X*v->Y-v->X*Rotation.Y);
   float w=-(Rotation.X*v->X+Rotation.Y*v->Y+Rotation.Z*v->Z);
   out->X=(x*Rotation.W-w*Rotation.X+(z*Rotation.Y-y*Rotation.Z)+Translation.X);
   out->Y=(y*Rotation.W-w*Rotation.Y-(z*Rotation.X-x*Rotation.Z)+Translation.Y);
   out->Z=(z*Rotation.W-w*Rotation.Z+(y*Rotation.X-x*Rotation.Y)+Translation.Z);
  v++;out++;
 }
}
__forceinline void BfmeSkinMatrix::Blend(const Vector3 *in0,const BfmeSkinMatrix &tm1,const Vector3 *in1,Vector3 *out,int count) const {
 while(count--) {
  out->X=(v[0].X*in0->X+v[0].Y*in0->Y+v[0].Z*in0->Z+v[0].W+tm1.v[0].X*in1->X+tm1.v[0].Y*in1->Y+tm1.v[0].Z*in1->Z+tm1.v[0].W);
  out->Y=(v[1].X*in0->X+v[1].Y*in0->Y+v[1].Z*in0->Z+v[1].W+tm1.v[1].X*in1->X+tm1.v[1].Y*in1->Y+tm1.v[1].Z*in1->Z+tm1.v[1].W);
  out->Z=(v[2].X*in0->X+v[2].Y*in0->Y+v[2].Z*in0->Z+v[2].W+tm1.v[2].X*in1->X+tm1.v[2].Y*in1->Y+tm1.v[2].Z*in1->Z+tm1.v[2].W);
  in0++;in1++;out++;
 }
}
class MeshModelClass {
public:
 void get_deformed_vertices(Vector3 *,const HTreeClass *);
 void get_deformed_vertices(Vector3 *,Vector3 *,const HTreeClass *);
 int Get_Vertex_Count() const {return vertexCount;}
private:
 char fields00[0x28];int vertexCount;int fields2C;
 BfmeSkinBuffer<Vector3> *vertices[2],*normals[2];
 char fields40[0x10];BfmeSkinBuffer<unsigned short> *bones,*runs;
};
void MeshModelClass::get_deformed_vertices(Vector3 *dst,const HTreeClass *tree) {
 if(runs==0||bones==0||tree==0)return;
 const BfmeSkinTreeView *htree=(const BfmeSkinTreeView*)tree;
 int streams=1;
 if(vertices[1])streams=2;
 int i;
 Vector3 *source[2];
 for(i=0;i<streams;++i) {if(vertices[i])source[i]=vertices[i]->Get_Array();else source[i]=0;}
 unsigned short *run=runs->Get_Array();
 unsigned short *bone=bones->Get_Array();
 Rva00129510Inc();
 int total=Get_Vertex_Count();
 int remaining=total;
 while(remaining>0) {
  unsigned int count=run[1];run+=2;
  remaining-=count;
  unsigned int first=bone[0],second=bone[total];
  if(streams==2 && second) {
   float firstWeight=bone[total*2]*0.01f;
   float secondWeight=bone[total*3]*0.01f;
   BfmeSkinMatrix a,b;
   htree->Get_Transform(first).Get_Matrix3D(a);
   htree->Get_Transform(second).Get_Matrix3D(b);
   for(int r=0;r<3;++r) {a[r]*=firstWeight;b[r]*=secondWeight;}
   a.Blend(source[0],b,source[1],dst,count);
  } else {
   const BfmeSkinTransform &t=htree->Get_Transform(first);
   t.TransformPositionArray(source[0],dst,count);
  }
  bone+=count;
  for(i=0;i<streams;++i)source[i]+=count;
  dst+=count;
 }
}
