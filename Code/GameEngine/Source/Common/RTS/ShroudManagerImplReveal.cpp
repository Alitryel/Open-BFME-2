// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// stlport
//
// ShroudManagerImpl::DoShroudReveal (retail 0x0073CAF0) and UndoShroudReveal
// (retail 0x0073CCC0), split out of ShroudManagerImpl008FBA40.cpp with its flags.
// Their polygon rasters 0x0073BFE0 and 0x0073C450 live in Rva0073BFE0Raster.cpp and
// Rva0073C450Raster.cpp; while they were unrowed and the two callers sat in
// ShroudManagerImpl008FBA40.cpp, those unresolved names kept that whole unit
// from linking. Nothing else in that unit references them.
// Keep MSVC's float math overloads local; the matched operations inline.
#define inline static inline
#include <math.h>
#undef inline
#pragma intrinsic(sin,cos)

// The shroud manager, only the two members defined here.
class ShroudManagerImpl
{
private:
	void DoShroudReveal(int,int,void*,float,int);
	void UndoShroudReveal(int,int,void*,float,int);
};

class Gen_008F7CD0;
class Rva0073BAA0Base {
public:
 virtual char testFunc(int,int);
 char rva0073BAA0(int,int,int);
 Gen_008F7CD0 *grid;unsigned mask;
};
static __forceinline Rva0073BAA0Base revealUpdater(Gen_008F7CD0 *grid,unsigned mask)
{
 Rva0073BAA0Base result;
 result.grid=grid;result.mask=mask;
 return result;
}
char __cdecl Rva0073BF40Raster(int,int,int,Rva0073BAA0Base);
char __cdecl Rva0073BFE0Raster(int*,int*,int,Rva0073BAA0Base);
void ShroudManagerImpl::DoShroudReveal(int x,int y,void *opaque,float rotation,int mask)
{
 int *radii=(int*)opaque;
 if(!mask || radii[0]<0)return;
 mask&=0xfffff;
 if(radii[0]==radii[1] && radii[1]==radii[2]){
  Rva0073BF40Raster(x,y,radii[0],revealUpdater((Gen_008F7CD0*)this,mask));return;
 }
 float a=1.5705f-rotation;
 float c=(float)cos(a);
 float s=-(float)sin(a);
 float minusS=-s;
 float c2=c;
 int xs[16],ys[16];
 for(int i=0;i<16;++i){
  float angle=(i-4)*3.141f/8.f;
  xs[15-i]=(int)(x+(float)sin(angle)*c*radii[1]+(float)cos(angle)*minusS*radii[(i/4)&2]+0.5f);
  ys[15-i]=(int)(y+(float)sin(angle)*s*radii[1]+(float)cos(angle)*c2*radii[(i/4)&2]+0.5f);
 }
 Rva0073BFE0Raster(xs,ys,16,revealUpdater((Gen_008F7CD0*)this,mask));
}

char __cdecl Rva0073C3B0Raster(int,int,int,Rva0073BAA0Base);
char __cdecl Rva0073C450Raster(int*,int*,int,Rva0073BAA0Base);
void ShroudManagerImpl::UndoShroudReveal(int x,int y,void *opaque,float rotation,int mask)
{
 int *radii=(int*)opaque;
 if(!mask || radii[0]<0)return;
 mask&=0xfffff;
 if(radii[0]==radii[1] && radii[1]==radii[2]){
  Rva0073C3B0Raster(x,y,radii[0],revealUpdater((Gen_008F7CD0*)this,mask));return;
 }
 float a=1.5705f-rotation;
 float c=(float)cos(a);
 float s=-(float)sin(a);
 float minusS=-s;
 float c2=c;
 int xs[16],ys[16];
 for(int i=0;i<16;++i){
  float angle=(i-4)*3.141f/8.f;
  xs[15-i]=(int)(x+(float)sin(angle)*c*radii[1]+(float)cos(angle)*minusS*radii[(i/4)&2]+0.5f);
  ys[15-i]=(int)(y+(float)sin(angle)*s*radii[1]+(float)cos(angle)*c2*radii[(i/4)&2]+0.5f);
 }
 Rva0073C450Raster(xs,ys,16,revealUpdater((Gen_008F7CD0*)this,mask));
}
