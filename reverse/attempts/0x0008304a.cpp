// ?AllocateAndFillBuffers@RenderableStandingWaterArea@@QAEXXZ
// partial score=0.84 date=2026-10-17
// cl: /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// stlport
// claudeb3 r5: Vector3 temp origin via BfmeOriginInts (retail movss stores) and one continuous grid pointer (*grid++=in): inner fill loop now matches retail (pointer in edi, x in memory). Remaining: retail keeps a per-row grid pointer IV in memory (+=nx, set after ny>0 guard); half/center/lock slots not packed (frame 0x9c vs retail 0x90); zero-register choice in vector copy (edi vs ebx).
// RenderableStandingWaterArea::createTexture: native 0x0007EDBC..0x0007EEB0,
// 244 bytes, RET4. WB 0x0073EFF0 identifies the method and W3DWater.cpp.
// Native calls and member accesses prove area+40, texture slots+50, and
// the 60/62/61 fallback order for slot zero. The matched river-water
// createTexture at 7EEBE supplies the loader's counted return lifetime.
// StringBase<char>'s canonical header owns isEmpty; the native string
// prefix read proves its shared-buffer data starts eight bytes later.
#include <vector>
#include "string_base.h"
class ModuleData;
class Rva0030812E { public: void *rva0030812E(int index); };
enum WW3DFormat { WW3D_FORMAT_UNKNOWN = 0 };
class W3DRadarFormatCaps { public: bool supportTextureFormat(WW3DFormat format); };
class DX8Caps;
class TextureClass;
class ZTextureClass;
struct IDirect3DSurface8;
class DX8Wrapper {
 friend class RenderableStandingWaterArea;
public:
 static void Set_Render_Target_With_Z(TextureClass *texture, ZTextureClass *ztexture);
 static void Set_Render_Target(IDirect3DSurface8 *renderTarget, bool useDefaultDepthBuffer);
protected:
 static DX8Caps *CurrentCaps;
};
class TextureBaseClass
{
public:
	void Release_Ref();
};

class TextureClass : public TextureBaseClass
{
	int m_pad[2];
};

template <class T>
class RefCountPtr
{
public:
	const RefCountPtr &operator=(const RefCountPtr &other);
	~RefCountPtr() { if (m_ptr) m_ptr->Release_Ref(); }
	T *m_ptr;
};

class BFME2ParticleTextureHandle : public RefCountPtr<TextureClass>
{
};

class TextureAsset
{
public:
	static BFME2ParticleTextureHandle Get(const char *filename, int a, int b);
};


class RenderableStandingWaterArea {
public:
 void createTexture(int index);
 void AllocateAndFillBuffers();
private:
 char m_pad00[0x14];float *boundary;char m_pad18[0x28];
 Rva0030812E *m_area;
 char m_unknown44[0x0c];
 BFME2ParticleTextureHandle m_textures[4];
 char m_pad60[0x10];
 _STL::vector<const ModuleData*> vertexBuffers,vertexCounts,indexBuffers,indexCounts;
};
void RenderableStandingWaterArea::createTexture(int index) {
 StringBase<char> *s=(StringBase<char>*)m_area->rva0030812E(index);
 if (!s->isEmpty()) {
  if (index == 0) {
   int format=0;
   if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3c)) format=0x3c;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3e)) format=0x3e;
   else if (reinterpret_cast<W3DRadarFormatCaps *>(DX8Wrapper::CurrentCaps)->supportTextureFormat((WW3DFormat)0x3d)) format=0x3d;
   const char *data=*(const char *const *)s;
   m_textures[0] = TextureAsset::Get(data ? data+8 : "",1,format);
  } else {
   const char *data=*(const char *const *)s;
   m_textures[index] = TextureAsset::Get(data ? data+8 : "",0,0);
  }
 }
}

// Native 00082140..000822F7,439B; WB742CF0 WaterRenderObjClass destructor.
// Reference BFME1 575ba2b04 WaterRenderObjVirtualDestructor.cpp provides
// resource teardown semantics; target owns three area-list observers and
// different member offsets. Retain the existing opaque owner spelling.
#include "Common/Snapshot.h"
#include <string.h>
#include <vector>
#include "ascii_string.h"
void __cdecl operator delete(void*) throw();
class RefCountClass { public: virtual void Delete_This(); virtual ~RefCountClass(); int refs; };
class MultiListObjectClass { public: virtual ~MultiListObjectClass(); void *node; };
class RenderObjClass : public RefCountClass,public MultiListObjectClass {
public: RenderObjClass(); virtual ~RenderObjClass();
private: char unmodelled[0xC4-0x10];
};
template<int N> class WaterAreaObserver {public: virtual ~WaterAreaObserver(){} };
class CreateAHeroData;
class Rva002B7250 {public: void rva002B7250(CreateAHeroData*);};
struct WaterTextureHandle { TextureBaseClass *ptr; WaterTextureHandle():ptr(0){} ~WaterTextureHandle(){if(ptr)ptr->Release_Ref();} };
struct WaterCountedRef {
 RefCountClass *ptr;
 WaterCountedRef():ptr(0){}
 WaterCountedRef(RefCountClass *p):ptr(p){}
 __forceinline ~WaterCountedRef(){ RefCountClass *p=ptr; if(p && --p->refs==0)p->Delete_This(); }
};
struct TreeHintRef00217D4C { ~TreeHintRef00217D4C(); };
// The unit's vectors use STLport's own empty construction; their destructor
// is the existing out-of-line instantiation.
namespace _STL { template<> vector<TreeHintRef00217D4C>::~vector(); }
class WaterTracksRenderSystem {public: ~WaterTracksRenderSystem();};
class Rva0007E12F {public: void rva0007E12F();};
void BFME_DX8_Thread_Lock();
void BFME_DX8_Thread_Assert();
// Native destructor EH cleanup 75F6F6 uses the existing device-lock
// destructor 42F8C, paired with lock 11F520 and release 120F50.
struct BFMEDX8DeviceLock {
 BFMEDX8DeviceLock(){BFME_DX8_Thread_Lock();}
 ~BFMEDX8DeviceLock(){BFME_DX8_Thread_Assert();}
};
class WaterSetting;
extern WaterSetting WaterSettings[];
struct WaterSettingClearView {
 void *vtable;
 AsciiString sky,water;
 char rest[0x7C-0xC];
};
class WaterTransparencySetting;
// The native slot is the scalar-deleting destructor ABI, flags=0 and
// returned allocation pointer, followed by the separate game deallocator.
class WaterTransparencyDeleteView {public: virtual void *destroy(unsigned flags);};
template<class T> class OVERRIDE {public: T *ptr;};
extern OVERRIDE<WaterTransparencySetting> TheWaterTransparency;
class WaterRenderObjClass {
public:
 struct Setting {Setting():skyTexture(0),waterTexture(0){} ~Setting(); TextureBaseClass *skyTexture,*waterTexture; char data[0x28];};
};
class CameraClass : public RenderObjClass {
public: CameraClass();
private: char unmodelled[0x3FC-0xC4];
};
class Rva0082140 : public Snapshot,public RenderObjClass,
 public WaterAreaObserver<0>,public WaterAreaObserver<1>,public WaterAreaObserver<2> {
public: Rva0082140(); virtual ~Rva0082140();
 void rva0007F87C(void *scene, CameraClass *camera);
private:
 int fieldD4;
 unsigned fieldD8;
 float fieldDC,fieldE0,fieldE4,fieldE8;
 int fieldEC;
 bool fieldF0;
 int fieldF4;
 WaterTextureHandle textureF8;
 WaterCountedRef refFC;
 WaterTracksRenderSystem *tracks100;
 Rva002B7250 *standing104;
 _STL::vector<TreeHintRef00217D4C> standing108;
 Rva002B7250 *rivers114;
 _STL::vector<TreeHintRef00217D4C> rivers118;
 Rva002B7250 *waves124;
 WaterCountedRef ref128;
 float field12C,field130;
 bool field134,field135;
 WaterRenderObjClass::Setting settings138[6];
 int field258;
 bool field25C;
 int field260;
};
// Native 00082329..000824C3,410B, the WaterRenderObjClass constructor: it
// stores the vtables this unit's destructor restores and builds the members
// the destructor's unwind map tears down, in the same order (EH states 5..A).
Rva0082140::Rva0082140()
 : fieldD4(0),fieldD8(0x10441B),fieldDC(0),fieldE0(0),fieldE4(0),fieldE8(0),
   fieldEC(0),fieldF0(false),fieldF4(0),
   refFC(new CameraClass),tracks100(0),standing104(0),rivers114(0),waves124(0),
   field12C(0),field130(0),field134(false),field135(false),
   field258(2),field25C(false),field260(0)
{
 memset(settings138,0,sizeof(settings138));
}
Rva0082140::~Rva0082140() {
 if(standing104) {
  standing104->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<0>*>(this)));standing104=0;
  rivers114->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<1>*>(this)));rivers114=0;
  waves124->rva002B7250(reinterpret_cast<CreateAHeroData*>(static_cast<WaterAreaObserver<2>*>(this)));waves124=0;
 }
 BFMEDX8DeviceLock guard;
 for(int i=0;i<6;++i) {
  reinterpret_cast<WaterSettingClearView*>(WaterSettings)[i].sky.clear();
  reinterpret_cast<WaterSettingClearView*>(WaterSettings)[i].water.clear();
 }
 WaterTransparencyDeleteView *transparency=reinterpret_cast<WaterTransparencyDeleteView*>(TheWaterTransparency.ptr);
 ::operator delete(transparency ? transparency->destroy(0) : 0);
 TheWaterTransparency.ptr=0;
 reinterpret_cast<Rva0007E12F*>(this)->rva0007E12F();
 if(tracks100)delete tracks100;
}

// Native 0x0007F87C..0x0007F92A, 174B, RET8: the reflection pass. After the
// mirror camera setup 0x0007F0FB, a live mirror camera (+0xFC) renders the
// scene into the reflection texture (+0xF8): the render target is set with
// an empty z texture holder, the frame begins cleared to black (WW3D::Begin_Render
// 0x00118170) and, when it begins, the scene is drawn through 0x00118660
// and the frame ended; the camera projection override byte is cleared and
// the default render target restored. WB 0x007492F0 (unnamed) has the same
// call chain. The method name stays address-derived.
class Vector3 {public: Vector3(float x,float y,float z):X(x),Y(y),Z(z){} float X,Y,Z;};
class WW3D {
public:
 static bool Begin_Render(bool clear, bool clearZ, const Vector3 &color, float alpha);
 static bool End_Render(bool flip);
};
bool Rva00118660Call(void *scene, void *camera);
extern bool bfmeCameraProjectionOverride;
class Rva0007F0FBOwner {public: void rva0007F0FB(CameraClass *camera, bool flag);};
void Rva0082140::rva0007F87C(void *scene, CameraClass *camera) {
 reinterpret_cast<Rva0007F0FBOwner*>(this)->rva0007F0FB(camera,false);
 if(refFC.ptr) {
  {
   WaterTextureHandle zbuffer;
   DX8Wrapper::Set_Render_Target_With_Z((TextureClass*)&textureF8,(ZTextureClass*)&zbuffer);
  }
  if(WW3D::Begin_Render(true,true,Vector3(0.0f,0.0f,0.0f),0.0f)) {
   Rva00118660Call(scene,refFC.ptr);
   WW3D::End_Render(false);
  }
  bfmeCameraProjectionOverride=false;
  DX8Wrapper::Set_Render_Target(0,false);
 }
}

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include <vector>
#include <string.h>
#include "../../../../../Libraries/Include/Lib/Coord2D.h"
namespace _STL {
 template<> class vector<char,allocator<char> > {
  public: char *start,*finish,*end;
  void resize(unsigned int,char);
 };
}
struct BfmeE12 { float x,y,z; };
struct BfmeE16 { float x,y,z,w; };
struct BfmePod44 {int a[11];};
void Rva00030830FreeAllocation(void *);
namespace _STL {
 template<> inline void allocator<BfmeE12>::deallocate(BfmeE12 *p,size_type) const {if(p) Rva00030830FreeAllocation(p);}
 template<> inline void allocator<BfmeE16>::deallocate(BfmeE16 *p,size_type) const {if(p) Rva00030830FreeAllocation(p);}
}
class Rva00082A53 {
 int self;
 _STL::vector<BfmeE12> cells;
 int dimX,dimY;
 public:
 _STL::vector<BfmeE16> records;
 int origin[3]; float spacing;
 Rva00082A53(int,int,int,float,int*,int);
 ~Rva00082A53();
 unsigned short rva00082E33(int,int);
};
class ModuleData;
class Rva00081F03 {public:void rva00081F03();};
class Rva0030D111Shape {public:virtual int count();};
bool Rva0030D111Contains(Rva0030D111Shape*,const Coord2D*);
struct Region2D {Region2D(){} Region2D(const Region2D&r){x0=r.x0;y0=r.y0;x1=r.x1;y1=r.y1;} ~Region2D(){} float x0,y0,x1,y1;};
class PolygonTrigger { public:Region2D rva0007E03A();};
class GameLODManager;
extern GameLODManager *TheGameLODManager;
void BFME_DX8_Thread_Lock();

class IndexBufferClass {public:
 class WriteLockClass {
  IndexBufferClass *buffer; public: unsigned short *indices; private: BFMEDX8DeviceLock lock;
  public:WriteLockClass(IndexBufferClass*,int);~WriteLockClass();
 };
};
class DX8IndexBufferClass {
 public:enum UsageType{USAGE_DEFAULT=0};
 char record[24];
 DX8IndexBufferClass(unsigned,UsageType);
};
class VertexBufferClass {public:
 class WriteLockClass {
  VertexBufferClass *buffer;public: void *vertices;private:BFMEDX8DeviceLock lock;
  public:WriteLockClass(VertexBufferClass*,int);~WriteLockClass();
 };
};
class BfmeDynamicNativeVB {
 public:char record[32];
 BfmeDynamicNativeVB(unsigned,unsigned short,unsigned,unsigned);
};
class MathCoord2D {
public:
 MathCoord2D(){} MathCoord2D(float a,float b):x(a),y(b){}
 MathCoord2D(const MathCoord2D &p):x(p.x),y(p.y){} ~MathCoord2D(){}
 float x,y;
};
MathCoord2D operator+(MathCoord2D,const MathCoord2D&);
inline int *BfmeOriginInts(const Vector3 &v){return (int*)&v;}
void RenderableStandingWaterArea::AllocateAndFillBuffers() {
 reinterpret_cast<Rva00081F03*>(this)->rva00081F03();
 BFMEDX8DeviceLock guard;
 Region2D bounds=reinterpret_cast<PolygonTrigger*>(reinterpret_cast<char*>(m_area)+0x30)->rva0007E03A();
 int limit=60000;register float spacing=20.0f;
 if(TheGameLODManager && *reinterpret_cast<int*>(reinterpret_cast<char*>(TheGameLODManager)+0x1784)<=2){limit=30000;spacing=40.0f;}
 int nx,ny,total;
 do {
  nx=int(bounds.x1/spacing)-int(bounds.x0/spacing)+1;
  ny=int(bounds.y1/spacing)-int(bounds.y0/spacing)+1;
  total=nx*ny;
  if(total>limit)spacing*=2.0f;
 }while(total>limit);
 bounds.x0=(float)int(bounds.x0/spacing)*spacing;
 bounds.y0=(float)int(bounds.y0/spacing)*spacing;
 bounds.x1=float(int(bounds.x1/spacing))*spacing+spacing;
 bounds.y1=float(int(bounds.y1/spacing))*spacing+spacing;
 _STL::_Vector_base<BfmeE12,_STL::allocator<BfmeE12> > flags((_STL::allocator<BfmeE12>()));
 reinterpret_cast<_STL::vector<char>*>(&flags)->resize(total,0);
 MathCoord2D half(spacing*.5f,spacing*.5f);
 MathCoord2D center=(*reinterpret_cast<MathCoord2D*>(&bounds))+half;
 int count=0;
 char *grid=*reinterpret_cast<char**>(&flags);
 for(int y=0;y<ny;++y) {
  Coord2D pos;pos.y=y*spacing+center.y;
  for(int x=0;x<nx;++x){
   pos.x=x*spacing+center.x;
   
   Rva0030D111Shape *shape=m_area ? reinterpret_cast<Rva0030D111Shape*>(reinterpret_cast<char*>(m_area)+0x18+(*reinterpret_cast<int**>(reinterpret_cast<char*>(m_area)+0x18))[1]) : 0;
   bool in=Rva0030D111Contains(shape,&pos);
   *grid++=in;
   count+=in;
  }
 }
 if(!count)return;
 {
  int indexCount=count*6;
  Rva00082A53 cache(reinterpret_cast<int>(this),nx,ny,spacing,BfmeOriginInts(Vector3(bounds.x0,bounds.y0,boundary[2])),2*count+nx+1);
  const ModuleData *ib=reinterpret_cast<const ModuleData*>(new DX8IndexBufferClass(indexCount,DX8IndexBufferClass::USAGE_DEFAULT));
  indexBuffers.push_back(ib);
  {
   IndexBufferClass::WriteLockClass lock(reinterpret_cast<IndexBufferClass*>(const_cast<ModuleData*>(indexBuffers.back())),0);
   unsigned short *out=lock.indices;
   for(int y=0;y<ny;++y){
    char * volatile slot = *reinterpret_cast<char**>(&flags)+y*nx;
    for(int x=0;x<nx;++x){
     if(*slot){
      out[0]=cache.rva00082E33(x,y);
      out[1]=cache.rva00082E33(x+1,y+1);
      out[2]=cache.rva00082E33(x,y+1);
      out[3]=cache.rva00082E33(x,y);
      out[4]=cache.rva00082E33(x+1,y);
      out[5]=cache.rva00082E33(x+1,y+1);
      out+=6;
     }
     ++slot;
    }
   }
  }
  _STL::vector<BfmePod44> * volatile records = reinterpret_cast<_STL::vector<BfmePod44>*>(&cache.records);
  const ModuleData *vb=reinterpret_cast<const ModuleData*>(new BfmeDynamicNativeVB(0x252,records->size(),0,0));
  vertexBuffers.push_back(vb);
  {
   VertexBufferClass::WriteLockClass lock(reinterpret_cast<VertexBufferClass*>(const_cast<ModuleData*>(vertexBuffers.back())),0);
   memcpy(lock.vertices,records->begin(),records->size()*44);
  }
  int vc=records->size();vertexCounts.push_back(*reinterpret_cast<const ModuleData**>(&vc));
  indexCounts.push_back(*reinterpret_cast<const ModuleData**>(&indexCount));
 }
}
