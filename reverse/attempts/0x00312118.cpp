// ?rebuildH@SplineTableH@@QAEXXZ
// partial score=0.4011094202991215 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Oi
// Partial reconstruction of native RVA00312118, 2860 bytes, WB00EADCE0.
// WB exposes an inline Catmull-Rom calculation, not an imported D3DX call.
// Target +2C/+30 vector holds 184-byte records; +38 total length, +54 last position.
// Algorithm follows WB and independently decoded retail; owner/method names unknown.
// Neighbor 00312EDA uses the same vector; no application class identity asserted.
#include <math.h>
#pragma intrinsic(sqrt)
struct SplinePointH {
 float x,y,z;
 SplinePointH() {}
 SplinePointH(float a,float b,float c):x(a),y(b),z(c){}
 __forceinline float length() const { return (float)sqrt(x*x+z*z+y*y); }
};
__forceinline SplinePointH operator+(const SplinePointH &a,const SplinePointH &b) {return SplinePointH(a.x+b.x,a.y+b.y,a.z+b.z);}
__forceinline SplinePointH operator-(const SplinePointH &a,const SplinePointH &b) {return SplinePointH(a.x-b.x,a.y-b.y,a.z-b.z);}
__forceinline SplinePointH operator-(const SplinePointH &a) {return SplinePointH(-a.x,-a.y,-a.z);}
__forceinline SplinePointH operator*(const SplinePointH &a,float k) {return SplinePointH(a.x*k,a.y*k,a.z*k);}
__forceinline SplinePointH interpolateH(const SplinePointH &a,SplinePointH b,SplinePointH c,SplinePointH d,float t) {
 const float t2=t*t, t3=t2*t;
 return (b*2.0f+(c-a)*t+(a*2.0f-b*5.0f+c*4.0f-d)*t2+(-a+b*3.0f-c*3.0f+d)*t3)*0.5f;
}
struct SplineSampleH {
 float length;
 float distances[10];
 SplinePointH samples[10];
 SplinePointH position;
 unsigned trailing[2];
};
class SplineTableH {
 char prefix[0x2c];
 SplineSampleH *begin,*end,*capacity;
 float total;
 char reserved[0x18];
 SplinePointH last;
public:
 void rebuildH();
};
void SplineTableH::rebuildH() {
 int count=(end-begin)-3;
 for(int i=0;i<count;++i) {
  begin[i].length=0;
  SplinePointH previous=interpolateH(begin[i].position,begin[i+1].position,begin[i+2].position,begin[i+3].position,0.0f);
  for(int j=0;j<10;++j) {
   float t=(j+1)*0.1f;
   SplinePointH point=interpolateH(begin[i].position,begin[i+1].position,begin[i+2].position,begin[i+3].position,t);
   float distance=(point-previous).length();
   begin[i].length+=distance;
   begin[i].distances[j]=distance;
   begin[i].samples[j]=point;
   previous=point;
  }
  total+=begin[i].length;
 }
 last=begin[end-begin-2].position;
}
