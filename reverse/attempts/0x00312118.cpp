// ?rebuildH@SplineTableH@@QAEXXZ
// partial score=0.0 date=2026-10-17
// ?rebuildH@SplineTableH@@QAEXXZ
// partial score=0.4011094202991215 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /Oi
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
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
__forceinline SplinePointH interpolateH(const SplinePointH &a,const SplinePointH &b,const SplinePointH &c,const SplinePointH &d,float t) {
 float t2=t*t;
 float t3=(t2*t);
 { SplinePointH ta=a; SplinePointH tb=b; SplinePointH tc=c; SplinePointH td=d; aCopyHack: (void)0; }
 float ax=a.x; float ay=a.y; float az=a.z;
 float bx=b.x; float by=b.y; float bz=b.z;
 float cx=c.x; float cy=c.y; float cz=c.z;
 float dx=d.x; float dy=d.y; float dz=d.z;
 float x0=(bx*2.0f+(cx-ax)*t);
 float y0=(by*2.0f+(cy-ay)*t);
 float z0=(bz*2.0f+(cz-az)*t);
 float x1=(ax*2.0f-(bx*5.0f)+(cx*4.0f)-dx);
 float y1=(ay*2.0f-(by*5.0f)+(cy*4.0f)-dy);
 float z1=(az*2.0f-(bz*5.0f)+(cz*4.0f)-dz);
 float x2=((-ax+(bx*3.0f)-(cx*3.0f)+dx)*t);
 float y2=((-ay+(by*3.0f)-(cy*3.0f)+dy)*t);
 float z2=((-az+(bz*3.0f)-(cz*3.0f)+dz)*t);
 float x=(x0+((x1+x2)*t2));
 float y=(y0+((y1+y2)*t2));
 float z=(z0+((z1+z2)*t2));
 return SplinePointH(x*0.5f,y*0.5f,z*0.5f);
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
  SplinePointH ta; SplinePointH tb; SplinePointH tc; SplinePointH td;
  float spillA[64]; float spillB[64];
  *(volatile float*)&spillA[0]=0;
  *(volatile float*)&spillB[0]=0;
  _ReadWriteBarrier();
  _ReadWriteBarrier();
  _ReadWriteBarrier();
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
