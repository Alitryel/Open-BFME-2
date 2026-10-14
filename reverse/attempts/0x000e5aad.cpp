// ?drawFloors@W3DFloorBuffer@@QAEXAAVRenderInfoClass@@V?$RefCountPtr@VRenderingMethod@FXShader@@@@@Z
// partial score=0.9224452692140581 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /I. /Ireference/shims/bfmealloc /Ireference/shims/bfmelist /D_CRTIMP=
// stlport
// Partial W3DFloorBuffer::drawFloors, target RVA000E5AAD size1044; WB008848E0.
// BFME1 a7c38d3b2597121f178ab5190b3062478823257d FloorBuffer006F9380Draw.cpp
// supplies list-maintenance/shroud guide; target rendering path follows the
// independently matched BFME2 W3DRoadBufferDrawRoads.cpp and WB, not BFME1 flags.
// Target layout: buffers+4/+8, vertexCount+10, fallback+14, list+18, count+1C,
// dirty+22. Canonical W3DFloorElement.h supplies byte-proven element storage.
// Compiles1045 vs1044; EDI owner / EBX list instead of EBX owner / EDI list,
// extra owner home at EBP-1C and frame14 vs10. List erase requires whole-body
// fold proof at438539 before pin admission. No bytes or synthetic ABI wrappers.
#include "Code/GameEngineDevice/Source/W3DDevice/GameClient/W3DFloorElement.h"
#include <list>
#include <vector>

typedef int Int;
typedef bool Bool;
typedef float Real;

class TextureClass
{
public:
	void Release_Ref();	// 0x0061ED10
};

template <class T>
class RefCountPtr
{
public:
	RefCountPtr(const RefCountPtr &rhs) : Referent(rhs.Referent)
	{
		if (Referent)
			Referent->Add_Ref();
	}
	~RefCountPtr(void)
	{
		if (Referent)
			Referent->Release_Ref();
	}
	T *Peek(void) const { return Referent; }
	T *operator->(void) const { return Referent; }

private:
	T *Referent;
};
// The texture handle's copy constructor is the out-of-line 0x000424BB.
template <> RefCountPtr<TextureClass>::RefCountPtr(const RefCountPtr<TextureClass> &rhs);

class RefCountClass
{
public:
	virtual void Delete_This(void);
	void Add_Ref(void) { NumRefs++; }
	void Release_Ref(void) { NumRefs--; if (NumRefs == 0) Delete_This(); }

protected:
	int NumRefs;
};

namespace FXShader {
class RenderingMethod : public RefCountClass
{
public:
	virtual void slot1();
	virtual bool Begin(Int *passCount, Int flags);	// slot 2
	virtual void Begin_Pass(Int pass);	// slot 3
	virtual void slot4();
	virtual void End_Pass(void);	// slot 5
	virtual void End(void);	// slot 6
};
}

typedef _STL::vector<RefCountPtr<FXShader::RenderingMethod>, _STL::allocator<RefCountPtr<FXShader::RenderingMethod> > > RenderingMethodStackType;

class LightEnvironmentClass;

class RenderInfoClass
{
public:
	void Push_Rendering_Method(RefCountPtr<FXShader::RenderingMethod> method);
	void Pop_Rendering_Method(void);
	const RenderingMethodStackType &Get_Rendering_Method_Stack(void) const;

	char _bfme_unk_00[0x28];
	LightEnvironmentClass *light_environment;	// +0x28
};

// Callees taking the rendering-method stack as (first element, count) around
// the passes; their identities are not established.
// Rendering-method stack walkers (element array, count): rows Rva001688FFShift
// 0x001688FF and Rva00168952Clear 0x00168952 (RenderingMethodLinkArray.cpp).
class Rva001688FFElement;
void Rva001688FFShift(Rva001688FFElement **items, int count);
void Rva00168952Clear(Rva001688FFElement **items, int count);

class StringClass
{
public:
	StringClass(int initial_len = 0, bool hint_temporary = false);
	__forceinline ~StringClass() { Free_String(); }
private:
	void Free_String();
	char *m_Buffer;
};

class ShaderClass
{
	friend class DX8Wrapper;
public:
	static ShaderClass _PresetOpaque2DShader;
	unsigned int ShaderBits;
protected:
	static bool ShaderDirty;	// ?ShaderDirty@ShaderClass@@1_NA (ShaderClassApply.cpp)
};



struct BFME2TextureResource;
struct BFME2TextureRef
{
	BFME2TextureRef(BFME2TextureResource *texture) : Ptr(texture) {}
	~BFME2TextureRef()
	{
		if (Ptr)
			((TextureBaseClass *)Ptr)->Release_Ref();
	}
	BFME2TextureResource *Ptr;
};
void BFME2Set_Texture(unsigned stage, const BFME2TextureRef &texture);

#define PAD_STDCALL10(p) \
	virtual void __stdcall p##0() = 0; virtual void __stdcall p##1() = 0; virtual void __stdcall p##2() = 0; \
	virtual void __stdcall p##3() = 0; virtual void __stdcall p##4() = 0; virtual void __stdcall p##5() = 0; \
	virtual void __stdcall p##6() = 0; virtual void __stdcall p##7() = 0; virtual void __stdcall p##8() = 0; \
	virtual void __stdcall p##9() = 0;

struct IDirect3DDevice8
{
	PAD_STDCALL10(d0) PAD_STDCALL10(d1) PAD_STDCALL10(d2) PAD_STDCALL10(d3) PAD_STDCALL10(d4)
	PAD_STDCALL10(d5) PAD_STDCALL10(d6) PAD_STDCALL10(d7) PAD_STDCALL10(d8)
	virtual void __stdcall d90() = 0; virtual void __stdcall d91() = 0;
	virtual long __stdcall SetVertexShader(void *shader) = 0;	// slot 92
	PAD_STDCALL10(e0)
	virtual void __stdcall f103() = 0; virtual void __stdcall f104() = 0;
	virtual void __stdcall f105() = 0; virtual void __stdcall f106() = 0;
	virtual long __stdcall SetPixelShader(void *shader) = 0;	// slot 107
};

extern unsigned number_of_DX8_calls;

struct RenderStateStruct
{
	ShaderClass shader;
};

class VertexBufferClass; class IndexBufferClass;
class DX8Wrapper
{
public:
 static void Set_Index_Buffer(const IndexBufferClass *,unsigned short);
 static void Set_Vertex_Buffer(const VertexBufferClass *,unsigned);
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
	static void Draw_Triangles(unsigned start_index, unsigned polygon_count, unsigned min_vertex_index, unsigned vertex_count);
	static IDirect3DDevice8 *_Get_D3D_Device8() { return D3DDevice; }

	static __forceinline void Set_Shader(const ShaderClass &shader)
	{
		if (!ShaderClass::ShaderDirty && shader.ShaderBits == render_state.shader.ShaderBits)
			return;
		render_state.shader.ShaderBits = shader.ShaderBits;
		render_state_changed |= 0x8000;
		StringClass str;
	}
	static __forceinline void Set_Vertex_Shader(void *shader)
	{
		_Get_D3D_Device8()->SetVertexShader(shader);
		number_of_DX8_calls++;
	}
	static __forceinline void Set_Pixel_Shader(void *shader)
	{
		_Get_D3D_Device8()->SetPixelShader(shader);
		number_of_DX8_calls++;
	}

protected:
	static IDirect3DDevice8 *D3DDevice;
	static unsigned int render_state_changed;
	static RenderStateStruct render_state;
};

// g_00DEBC60, the road/terrain shader interface (Rva000E19A3Dtor.cpp).
class Rva000E19A3Interface
{
public:
	virtual void setRenderingMode(int mode) = 0;
	virtual void setBaseTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void setNormalTexture(RefCountPtr<TextureClass> texture) = 0;
	virtual void clearTextures() = 0;
};
extern Rva000E19A3Interface *g_00DEBC60;

// TheTerrainRenderObject's slot 18 returns a state whose +0x14 mode 1 makes
// the roads draw untextured.
struct BfmeTerrainRenderState { char m_pad[0x14]; Int m_mode; };
class BaseHeightMapRenderObjClass;
extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
class BfmeTerrainRenderView
{
public:
	virtual void s0(); virtual void s1(); virtual void s2(); virtual void s3();
	virtual void s4(); virtual void s5(); virtual void s6(); virtual void s7();
	virtual void s8(); virtual void s9(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17();
	virtual BfmeTerrainRenderState *getRenderState();	// slot 18
};

class Rva000E440D { public: bool rva000E440D(); };
class Rva000E459F { public: bool rva000E459F(); };
class Rva000E48BC { public: int rva000E49B8(int); };
class Rva000E58BE { public: void rva000E58BE(); };
class Rva000E44BE { public: void rva000E44BE(FXShader::RenderingMethod*,RefCountPtr<TextureClass>); };
class PlayerList;
extern PlayerList *ThePlayerList;
class PartitionManager;
extern PartitionManager *TheShroudManager;
struct FloorPlayerH { char pad[0x54]; int index; };
struct FloorPlayerListH { char pad[0x10]; FloorPlayerH *local; };
class W3DFloorBuffer {
public:
 void drawFloors(RenderInfoClass &,RefCountPtr<FXShader::RenderingMethod>);
private:
 unsigned field00;
 VertexBufferClass *vertices;
 IndexBufferClass *indices;
 unsigned field0c;
 int vertexCount;
 RefCountPtr<TextureClass>fallback;
 _STL::list<Gen_uw_000e5033*>elements;
 unsigned count;
 bool flag20,flag21,dirty;
};
void W3DFloorBuffer::drawFloors(RenderInfoClass &rinfo,RefCountPtr<FXShader::RenderingMethod>method) {
 int player;
 FloorPlayerListH *root=(FloorPlayerListH*)ThePlayerList;
 FloorPlayerH *inner;
 int selected;
 if(root){inner=root->local;selected=inner->index;player=selected;}else player=0;
 _STL::list<Gen_uw_000e5033*>::iterator it=elements.begin();
 for(;it!=elements.end();++it) {
  while(it!=elements.end() && ((Rva000E440D*)*it)->rva000E440D()) {
   _STL::list<Gen_uw_000e5033*>::iterator next=it; ++next;
   ((Rva000E4567*)*it)->rva000E4567();
   delete *it;
   elements.erase(it);
   count=elements.size();
   it=next;
  }
  if(it==elements.end())break;
  if(((Rva000E459F*)*it)->rva000E459F())dirty=true;
  if(ThePlayerList && TheShroudManager) {
   int old=(*it)->m_94;
   int current=((Rva000E48BC*)*it)->rva000E49B8(player);
   if(current!=old) {
    (*it)->m_94=current;
    Gen_uw_000e5033 *e=*it;
    if(e->m_state98==0) {
     if(current==1){e->m_state98=1;dirty=true;}
    }else if(e->m_state98==1) {
     if(current==0){e->m_state98=2;dirty=true;}
    }else if(e->m_state98==2) {
     if(current==1){e->m_state98=1;dirty=true;}
    }
   }
  }else {
   (*it)->m_94=1;(*it)->m_state98=1;dirty=true;
  }
 }
 if(dirty){((Rva000E58BE*)this)->rva000E58BE();dirty=false;}
 flag21=false;
 if(!vertexCount)return;
 DX8Wrapper::Set_Index_Buffer(indices,0);
 DX8Wrapper::Set_Vertex_Buffer(vertices,0);
 DX8Wrapper::Set_Light_Environment(rinfo.light_environment);
 bool untextured=TheTerrainRenderObject && ((BfmeTerrainRenderView*)TheTerrainRenderObject)->getRenderState()->m_mode==1;
 if(untextured) {
  BFME2Set_Texture(0,BFME2TextureRef(0));
  DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaque2DShader);
  for(_STL::list<Gen_uw_000e5033*>::iterator drawIt=elements.begin();drawIt!=elements.end();++drawIt)
   if((*drawIt)->m_active80 && (*drawIt)->m_state98!=0 && !((Rva000E440D*)*drawIt)->rva000E440D())
    ((Rva000E44BE*)*drawIt)->rva000E44BE(0,fallback);
 }else {
  g_00DEBC60->setRenderingMode(3);
  rinfo.Push_Rendering_Method(method);
  Rva001688FFShift((Rva001688FFElement**)rinfo.Get_Rendering_Method_Stack().begin(),rinfo.Get_Rendering_Method_Stack().size());
  RefCountPtr<FXShader::RenderingMethod> current=rinfo.Get_Rendering_Method_Stack()[0];
  int passes;
  if(!current->Begin(&passes,0xffff))return;
  passes=1;
  for(int pass=0;pass<passes;++pass) {
   current->Begin_Pass(pass);
   for(_STL::list<Gen_uw_000e5033*>::iterator drawIt=elements.begin();drawIt!=elements.end();++drawIt)
    if((*drawIt)->m_active80 && (*drawIt)->m_state98!=0 && !((Rva000E440D*)*drawIt)->rva000E440D())
     ((Rva000E44BE*)*drawIt)->rva000E44BE(current.Peek(),fallback);
   current->End_Pass();
  }
  current->End();
  Rva00168952Clear((Rva001688FFElement**)rinfo.Get_Rendering_Method_Stack().begin(),rinfo.Get_Rendering_Method_Stack().size());
  rinfo.Pop_Rendering_Method();
 }
 g_00DEBC60->clearTextures();
 DX8Wrapper::Set_Light_Environment(0);
 DX8Wrapper::Set_Vertex_Shader(0);
 DX8Wrapper::Set_Pixel_Shader(0);
}
