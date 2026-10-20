// ?get_deformed_vertices@MeshModelClass@@QAEXPAVVector3@@PBVHTreeClass@@@Z
// partial score=0.92 date=2026-10-20
// cl: /I. /Ireference/shims/meshgeom /Ireference/shims/bfmerendobj /arch:SSE /G7 /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
// Compose with meshgeometry.cpp; target proof and provenance in re_attempts.log.
// Matrices use the HTreePivotTransform::Get_Matrix3D spelling (0x0014D28E); both are scaled row by row as in BFME1 0x00925860.
// Shape follows WorldBuilder MeshGeometryClass::get_deformed_vertices (0xA0E990): buffers read through Get_Array(),
// pivots through Get_Transform(), and the blend sums in the order of its Matrix3D helper (0xA0ECA0).
#include "reference/shims/bfme_vector3_full_link/vector3_full_link.h"
#include "reference/shims/bfme_matrix3d_sse_link/vector4.h"
#include "reference/shims/bfme_matrix3d_full_link/matrix3d_full_link.h"
#include "htree.h"
#include "quat.h"
struct BfmeSkinMatrix { float v[3][4]; __forceinline float *operator[](int i) {return v[i];} __forceinline const float *operator[](int i) const {return v[i];} };
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
 Quaternion Rotation;Vector3 Translation;
};
struct BfmeSkinPivot {char name[16];BfmeSkinPivot *parent;BfmeSkinTransform Base,Current;int index;bool visible;char tail[7];};
typedef char BfmeSkinPivotStride[sizeof(BfmeSkinPivot)==0x58?1:-1];
struct BfmeSkinTreeView {public:const BfmeSkinTransform &Get_Transform(int pivot) const {return pivots[pivot].Current;} char fields00[0x14];BfmeSkinPivot *pivots;};
template<class T> struct BfmeSkinBuffer {T *Get_Array() {return data;} char fields00[0xc];T *data;};
static __forceinline void skinTransform(const BfmeSkinTransform &t,const Vector3 &v,Vector3 &out) {
 const Quaternion &q=t.Rotation;
 float x=(v.Z*q.Y-v.Y*q.Z)+v.X*q.W;
 float y=q.W*v.Y-(q.X*v.Z-v.X*q.Z);
 float z=(v.Y*q.X-v.X*q.Y)+v.Z*q.W;
 float w=-(q.X*v.X+q.Y*v.Y+q.Z*v.Z);
 out.X=(q.Y*z-y*q.Z)+(x*q.W-w*q.X)+t.Translation.X;
 out.Y=(y*q.W-w*q.Y)-(q.X*z-x*q.Z)+t.Translation.Y;
 out.Z=(y*q.X-x*q.Y)+(z*q.W-w*q.Z)+t.Translation.Z;
}
static __forceinline void skinBlend(const BfmeSkinMatrix &a,const Vector3 &v,const BfmeSkinMatrix &b,const Vector3 &w,Vector3 &out) {
 out.X=a[0][0]*v.X+a[0][1]*v.Y+a[0][2]*v.Z+a[0][3]+b[0][0]*w.X+b[0][1]*w.Y+b[0][2]*w.Z+b[0][3];
 out.Y=a[1][0]*v.X+a[1][1]*v.Y+a[1][2]*v.Z+a[1][3]+b[1][0]*w.X+b[1][1]*w.Y+b[1][2]*w.Z+b[1][3];
 out.Z=a[2][0]*v.X+a[2][1]*v.Y+a[2][2]*v.Z+a[2][3]+b[2][0]*w.X+b[2][1]*w.Y+b[2][2]*w.Z+b[2][3];
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
 int streams=1;
 if(vertices[1])streams=2;
 Vector3 *source[2];
 for(int k=0;k<streams;++k) {if(vertices[k])source[k]=vertices[k]->Get_Array();else source[k]=0;}
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
   ((const BfmeSkinTreeView*)tree)->Get_Transform(first).Get_Matrix3D(a);
   ((const BfmeSkinTreeView*)tree)->Get_Transform(second).Get_Matrix3D(b);
   for(int r=0;r<3;++r) {a[r][0]*=firstWeight;a[r][1]*=firstWeight;a[r][2]*=firstWeight;a[r][3]*=firstWeight;b[r][0]*=secondWeight;b[r][1]*=secondWeight;b[r][2]*=secondWeight;b[r][3]*=secondWeight;}
   Vector3 *v=source[0],*w=source[1],*out=dst;
   int n=count;
   while(n--) {skinBlend(a,*v++,b,*w++,*out++);}
  } else {
   const BfmeSkinTransform &t=((const BfmeSkinTreeView*)tree)->Get_Transform(first);
   Vector3 *v=source[0],*out=dst;
   int n=count;
   while(n--) {skinTransform(t,*v++,*out++);}
  }
  bone+=count;
  for(int k=0;k<streams;++k)source[k]+=count;
  dst+=count;
 }
}
