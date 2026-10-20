// ?AllocateAndFillBuffers@RenderableStandingWaterArea@@QAEXXZ
// partial score=0.9394 date=2026-10-20
// 2026-10-20: clean bank, superseding the inherited r5 status below.
// Native extent 8304A..834CE remains1156; this partial emits1163.
// Native frame88 and the complete parent EH graph now EXACT. No volatile
// locals, barrier calls, padding objects or synthetic callee bodies.
// Genuine cache ctor153 and coordinate-add39 definitions are byte-exact.
// Remaining first-pass induction/zero web and argument scheduling are
// recorded in reverse/attempt_support/water-buffer-lifetimes-20261020/readme.md.
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
class Rva0030812E { public: void *getTextureName(int index); };
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
 StringBase<char> *s=(StringBase<char>*)m_area->getTextureName(index);
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
#include "../../Code/Libraries/Include/Lib/Coord2D.h"
#define fill bfmeLoaderHeaderFill
#include <stl/_algobase.h>
#undef fill
namespace _STL { void fill(char *, char *, const char &); }
namespace _STL { static inline const unsigned int &max(const unsigned int &a, const unsigned int &b) { return a < b ? b : a; } }
#include <vector>
#include "ascii_string.h"
namespace _STL { extern template char *__uninitialized_copy(char *, char *, char *, const __true_type &); }
namespace _STL { extern template char *fill_n<unsigned int>(char *, unsigned int, const char &); }
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *p, size_t n) { allocator<char>::deallocate(p,n); } }


namespace _STL {
template <> __declspec(dllimport) __forceinline
allocator<char> &__stl_alloc_rebind(allocator<char> &a, const char *) { return a; }
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
char *_STLP_alloc_proxy<char *,char,allocator<char> >::allocate(size_t n) {
    return __stl_alloc_rebind(static_cast<allocator<char> &>(*this), (char *)0).allocate(n,0);
}
}
namespace _STL {
template <> __declspec(dllimport) __forceinline
_Vector_base<char, allocator<char> >::~_Vector_base() {
    if (_M_start != 0)
        _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start);
}
}

// game.dat's STLport passes vector<char>::resize's fill by value (the rowed
// 0x000826E3 body; the call site pushes the byte itself), so this unit
// specializes vector<char> to that interface. The count constructor and
// resize are the rowed out-of-line bodies; swap is STLport's inline one.
// The members resize reaches keep STLport 4.5.3's bodies, so the compiler
// sees that the vector's address is not retained across the file calls.
namespace _STL
{
template <>
class vector<char, allocator<char> > : public _Vector_base<char, allocator<char> >
{
public:
	typedef allocator<char> allocator_type;
	typedef unsigned int size_type;

	explicit vector(const allocator_type &a = allocator_type()) : _Vector_base<char, allocator<char> >(a) {}
	explicit vector(size_type n);

	char *begin() { return this->_M_start; }
	char *end() { return this->_M_finish; }
	size_type size() const { return size_type(this->_M_finish - this->_M_start); }
	char *erase(char *first, char *last)
	{
		char *i = __copy_ptrs(last, this->_M_finish, first, __true_type());
		_Destroy(i, this->_M_finish);
		this->_M_finish = i;
		return first;
	}
protected:
	void _M_clear()
	{
		_Destroy(this->_M_start, this->_M_finish);
		this->_M_end_of_storage.deallocate(this->_M_start, this->_M_end_of_storage._M_data - this->_M_start);
	}
	void _M_set(char *s, char *f, char *e)
	{
		this->_M_start = s;
		this->_M_finish = f;
		this->_M_end_of_storage._M_data = e;
	}
	void _M_insert_overflow(char *position, const char &value, const __true_type &, unsigned int fill_len, bool at_end = false)
	{
    const unsigned int old_size = this->_M_finish - this->_M_start;
    char *new_start;
    const unsigned int new_len = old_size + (max)(old_size, fill_len);
    if (new_len != 0)
        new_start = this->_M_end_of_storage.allocate(new_len);
    else
        new_start = 0;
    char *new_finish = (char *)_STL::__copy_trivial(this->_M_start, position, new_start);
    new_finish = _STL::fill_n(new_finish, fill_len, value);
    if (!at_end)
        new_finish = (char *)_STL::__copy_trivial(position, this->_M_finish, new_finish);
    this->_M_clear();
    this->_M_set(new_start, new_finish, new_start + new_len);
}
public:
	void _M_fill_insert(char *position, size_type n, const char &x);

	char &operator[](size_type n) { return this->_M_start[n]; }
	void resize(size_type newSize, char x)
	{
		if (newSize < size())
			erase(begin() + newSize, end());
		else
			_M_fill_insert(end(), newSize - size(), x);
	}
	void swap(vector<char, allocator<char> > &x)
	{
		_STLP_STD::swap(this->_M_start, x._M_start);
		_STLP_STD::swap(this->_M_finish, x._M_finish);
		_STLP_STD::swap(this->_M_end_of_storage, x._M_end_of_storage);
	}
};

inline void vector<char, allocator<char> >::_M_fill_insert(char *position, size_type n, const char &x)
{
	if (n != 0) {
		if (size_type(this->_M_end_of_storage._M_data - this->_M_finish) >= n) {
			char xCopy = x;
			const size_type elemsAfter = this->_M_finish - position;
			char *oldFinish = this->_M_finish;
			if (elemsAfter > n) {
				(char *)__copy_trivial(this->_M_finish - n, this->_M_finish, this->_M_finish);
				this->_M_finish += n;
				__copy_backward_ptrs(position, oldFinish - n, oldFinish, __true_type());
				_STLP_STD::fill(position, position + n, xCopy);
			} else {
				uninitialized_fill_n(this->_M_finish, n - elemsAfter, xCopy);
				this->_M_finish += n - elemsAfter;
				(char *)__copy_trivial(position, oldFinish, this->_M_finish);
				this->_M_finish += elemsAfter;
				_STLP_STD::fill(position, oldFinish, xCopy);
			}
		} else
			_M_insert_overflow(position, x, __true_type(), n);
	}
}
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
#include "../../Code/Libraries/Include/Lib/Region2D.h"
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

struct BfmeWordVec : _STL::vector<unsigned short> {
 void resize(unsigned int,unsigned short);
};
Rva00082A53::Rva00082A53(int a1,int a2,int a3,float a4,int *a5,int a6)
 :self(a1),cells(),dimX(a2+1),dimY(a3+1),records()
{
 origin[0]=a5[0];origin[1]=a5[1];origin[2]=a5[2];spacing=a4;
 int n=dimX*dimY;
 ((BfmeWordVec*)&cells)->resize((unsigned int)n,(unsigned short)0xFFFF);
 ((_STL::vector<BfmePod44>*)&records)->reserve((unsigned int)a6);
}

MathCoord2D operator+(MathCoord2D left,const MathCoord2D &right){left.x+=right.x;left.y+=right.y;return left;}

void RenderableStandingWaterArea::AllocateAndFillBuffers() {
 reinterpret_cast<Rva00081F03*>(this)->rva00081F03();
 BFMEDX8DeviceLock guard;
 Region2D bounds=reinterpret_cast<PolygonTrigger*>(reinterpret_cast<char*>(m_area)+0x30)->rva0007E03A();
 int limit=60000;register float spacing=20.0f;
 if(TheGameLODManager && *reinterpret_cast<int*>(reinterpret_cast<char*>(TheGameLODManager)+0x1784)<=2){limit=30000;spacing=40.0f;}
 int nx,ny,total;
 do {
  nx=int(bounds.hi.x/spacing)-int(bounds.lo.x/spacing)+1;
  ny=int(bounds.hi.y/spacing)-int(bounds.lo.y/spacing)+1;
  total=nx*ny;
  if(total>limit)spacing*=2.0f;
 }while(total>limit);
 bounds.lo.x=(float)int(bounds.lo.x/spacing)*spacing;
 bounds.lo.y=(float)int(bounds.lo.y/spacing)*spacing;
 bounds.hi.x=float(int(bounds.hi.x/spacing))*spacing+spacing;
 bounds.hi.y=float(int(bounds.hi.y/spacing))*spacing+spacing;
 _STL::vector<char> flags;
 flags.resize(total,0);
 MathCoord2D half(spacing*.5f,spacing*.5f);
 MathCoord2D center=(*reinterpret_cast<MathCoord2D*>(&bounds))+half;
 int y;
 int count=0;

 for(y=0;y<ny;++y) {
  Coord2D pos;pos.y=y*spacing+center.y;
  for(int x=0;x<nx;++x){
   pos.x=x*spacing+center.x;
   
   Rva0030D111Shape *shape=m_area ? reinterpret_cast<Rva0030D111Shape*>(reinterpret_cast<char*>(m_area)+0x18+(*reinterpret_cast<int**>(reinterpret_cast<char*>(m_area)+0x18))[1]) : 0;
   bool in=Rva0030D111Contains(shape,&pos);
   int idx=y*nx+x;
   flags[idx]=in;
   count+=in;
  }
 }
 if(!count)return;
 {
  int indexCount=count*6;
  Rva00082A53 cache(reinterpret_cast<int>(this),nx,ny,spacing,BfmeOriginInts(Vector3(bounds.lo.x,bounds.lo.y,boundary[2])),2*count+nx+1);
  const ModuleData *ib=reinterpret_cast<const ModuleData*>(new DX8IndexBufferClass(indexCount,DX8IndexBufferClass::USAGE_DEFAULT));
  indexBuffers.push_back(ib);
  {
   IndexBufferClass::WriteLockClass lock(reinterpret_cast<IndexBufferClass*>(const_cast<ModuleData*>(indexBuffers.back())),0);
   unsigned short *out=lock.indices;
   for(y=0;y<ny;++y){

    for(int x=0;x<nx;++x){
     if(flags[y*nx+x]){
      out[0]=cache.rva00082E33(x,y);
      out[1]=cache.rva00082E33(x+1,y+1);
      out[2]=cache.rva00082E33(x,y+1);
      out[3]=cache.rva00082E33(x,y);
      out[4]=cache.rva00082E33(x+1,y);
      out[5]=cache.rva00082E33(x+1,y+1);
      out+=6;
     }

    }
   }
  }
  _STL::vector<BfmePod44> *records = reinterpret_cast<_STL::vector<BfmePod44>*>(&cache.records);
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
