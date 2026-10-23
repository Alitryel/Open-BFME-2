// cl: /Ireference/shims/bfme2_ascii /MD /EHsc /D_CRTIMP= /Ireference/shims/bfmelist /Ireference/shims/bfmealloc
// stlport
#define _STLP_USE_STATIC_LIB 1
#include <list>
#include <vector>
#include "W3DFloorElement.h"
// Use the same direct node comparison as the canonical list<int> provider;
// keep its unused iterator-base wrapper out of this object's definitions.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}
// Cursor-slot render helper: release (0x000E473F, 93B) plus reinit
// (0x000E479C, 234B). Both take the DX8 device mutex around their work.
// The reinit drops any live vertex/index buffers through the release body,
// allocates a 32-byte BfmeDynamicNativeVB (0x152, 0x3A9C, 1, 0) and a 24-byte
// DX8IndexBufferClass (0x7534, USAGE_DYNAMIC), zeroes two words, refills the
// embedded texture slot, and when the slot holds a surface, fetches its
// level-0 reset surface and draws one 0x7F7FFF pixel at (0, 0) before
// raising the +0x22 ready flag.
//
// Target facts (read-only retail decode this seat): both bodies open with
// mov eax,imm32 plus call __EH_prolog (0x00629188), save this in esi behind
// BFME_DX8_Thread_Lock (0x0011F520), and close with BFME_DX8_Thread_Assert
// (0x00120F50). The release repeats the REF_PTR_RELEASE shape (test, dec
// [ecx+4], jne, call [eax] slot 0, and-zero) for +0x04 and +0x08, then
// BfmeResetTextureRef::clear (0x0004D75B) on +0x14. The reinit calls the
// release when +0x04 or +0x08 is live, runs operator new (0x0002FDA0) for
// 0x20/0x18 bytes with the standard new-expression EH states 1/2, calls the
// 6-arg slot refill (0x00131DFC) on +0x14, checks the slot head, fetches
// CursorTextureSlot::Get_Surface_Level (0x00132D70) into an ebp-0x10 holder,
// calls SurfaceClass::DrawPixel (0x00116C30) on it with (0, 0, 0x7F7FFF),
// destroys the holder via W3DRadarResetSurface::~ (0x00176CB0), and sets
// [esi+0x22]. Class and member names are address-derived; the slot view
// (reset-ref base, cursor-slot middle, refill tail) is inferred from the
// three co-located calls sharing one unadjusted this, not from a header.

void __cdecl BFME_DX8_Thread_Lock();
bool __cdecl BFME_DX8_Thread_Assert();
void *__cdecl operator new(unsigned);
void __cdecl operator delete(void *) throw();

class BFMEDX8DeviceLock
{
public:
	BFMEDX8DeviceLock() { BFME_DX8_Thread_Lock(); }
	~BFMEDX8DeviceLock() { BFME_DX8_Thread_Assert(); }
};

struct BfmeResetResource
{
	void Release_Ref();
};

struct BfmeResetTextureRef
{
	BfmeResetResource *pointer;
	void clear();
};

struct SurfaceClass
{
	void DrawPixel(unsigned int x, unsigned int y, unsigned int color);
};

class W3DRadarResetSurface : public SurfaceClass
{
public:
	void *m_surface;
	~W3DRadarResetSurface();
};

struct CursorTextureSlot : public BfmeResetTextureRef
{
	W3DRadarResetSurface Get_Surface_Level();
};

struct Rva00131DFC : public CursorTextureSlot
{
	void rva00131DFC(void *a, void *b, void *c, void *d, int e, int f);
};

class BfmeDynamicVBRefCount
{
public:
	virtual void DeleteThis();
	virtual ~BfmeDynamicVBRefCount();
	int references;
	void Release_Ref() { if (--references == 0) DeleteThis(); }
};

class BfmeDynamicVBBase : public BfmeDynamicVBRefCount
{
public:
	virtual ~BfmeDynamicVBBase();
	unsigned type;
	unsigned short vertexCount;
	int engineReferences;
	void *format;
	bool usesDeclaration;
};

class BfmeDynamicNativeVB : public BfmeDynamicVBBase
{
public:
	void *buffer;
	BfmeDynamicNativeVB(unsigned a, unsigned short b, unsigned c, unsigned d);
};

class DX8IndexBufferClass
{
public:
	enum UsageType
	{
		USAGE_DEFAULT = 0,
		USAGE_DYNAMIC = 1
	};
	virtual void DeleteThis();
	virtual ~DX8IndexBufferClass();
	int m_references;
	char m_pad08[0x18 - 8];
	void Release_Ref() { if (--m_references == 0) DeleteThis(); }
	DX8IndexBufferClass(unsigned index_count, UsageType usage);
};

// The Xfer virtual declaration follows the already verified E5725 provider.
// Only Version is stored here; the geometry types are reference parameters.
class Xfer;
class AsciiString;
class UnicodeString;
class PooledString;
class Snapshot;
struct XferUnknown11;
struct Coord3DBase;
struct ICoord3D;
struct Region3D;
struct IRegion3D;
struct Coord2D;
struct ICoord2D;
struct Region2D;
struct IRegion2D;
struct RealRange;
struct RGBColor;
struct RGBAColorReal;
struct RGBAColorInt;
#include "../../../../GameEngine/Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class Rva000E5725 { public: void rva000E5725(Xfer *xfer); };

class Drawable;
class GameClient;
extern GameClient *TheGameClient;
class FloorClientSlots {
public:
    virtual void slot00();
    virtual void slot04();
    virtual void slot08();
    virtual void slot0C();
    virtual void slot10();
    virtual void slot14();
    virtual void slot18();
    virtual void slot1C();
    virtual void slot20();
    virtual void slot24();
    virtual void slot28();
    virtual void slot2C();
    virtual void slot30();
    virtual void slot34();
    virtual void slot38();
    virtual void slot3C();
    virtual Drawable *findDrawable(int id);
};
class Rva000E5EC1;
class Rva000E5F60 { public: Rva000E5EC1 *rva000E5F60(int, AsciiString); };
class Rva000E440D { public: bool rva000E440D(); };
class Rva000E459F { public: void rva000E46DA(Drawable *, const AsciiString &, const AsciiString &, bool, bool); bool rva000E459F(); };


// drawFloors (0x000E5AAD) render-side views. The rendering-method handle is
// the WW3D reference pointer (inline add/release through slot 0); the floor
// texture handle at +0x14 is copied into each draw call by the rowed
// AssetReference copy constructor 0x000424BB.
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
// The texture handle wraps an AssetReference whose out-of-line copy
// constructor is 0x000424BB; its inline copy gives retail's argument-copy
// order (argument home stored before ECX takes the slot).
class AssetReference
{
public:
	AssetReference(const AssetReference &that);
	void *m_object;
};
template <>
class RefCountPtr<TextureClass>
{
public:
	// Keep the verified inline argument copy without emitting a competing owner.
	__declspec(dllimport) __forceinline RefCountPtr(const RefCountPtr &rhs) : m_asset(rhs.m_asset) {}

private:
	AssetReference m_asset;
};

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
	virtual bool Begin(int *passCount, int flags);	// slot 2
	virtual void Begin_Pass(int pass);	// slot 3
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
	static bool ShaderDirty;
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

class VertexBufferClass;
class IndexBufferClass;
class DX8Wrapper
{
public:
	static void Set_Index_Buffer(const IndexBufferClass *ib, unsigned short index_base_offset);
	static void Set_Vertex_Buffer(const VertexBufferClass *vb, unsigned stream);
	static void Set_Light_Environment(LightEnvironmentClass *light_env);
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
// the floors draw untextured.
struct BfmeTerrainRenderState { char m_pad[0x14]; int m_mode; };
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

class Rva000E48BC { public: int rva000E49B8(int); };
class Rva000E58BE { public: void rva000E58BE(); };
class Rva000E44BE { public: void rva000E44BE(FXShader::RenderingMethod *, RefCountPtr<TextureClass>); };
class PlayerList;
extern PlayerList *ThePlayerList;
class PartitionManager;
extern PartitionManager *TheShroudManager;
struct FloorPlayerView { char pad[0x54]; int index; };
// The floor element's shroud status (+0x94), set through its inline
// accessor as the retail register choice in both shroud branches shows.
struct FloorShroudView
{
	char m_pad[0x94];
	int m_shroudStatus;
	int getShroudStatus() const { return m_shroudStatus; }
	void setShroudStatus(int status) { m_shroudStatus = status; }
};
struct FloorPlayerListView { char pad[0x10]; FloorPlayerView *local; };

class W3DFloorBuffer
{
public:
	void rva000E473F();
	void allocateFloorBuffers();
	void rva000E598B();
	void DoXfer(Xfer *xfer);
	Gen_uw_000e5033 *addFloor(int id, AsciiString *name, AsciiString *second, bool front, bool flag);
	void drawFloors(RenderInfoClass &rinfo, RefCountPtr<FXShader::RenderingMethod> method);

private:
	char m_pad00[4];
	BfmeDynamicNativeVB *m_vb;
	DX8IndexBufferClass *m_ib;
	int m_0C;
	int m_10;
	CursorTextureSlot m_slot;
	_STL::list<Gen_uw_000e5033 *> m_floors;
	int m_numFloors;
	bool m_ready20, m_flag21, m_ready22;
};

// ?rva000E473F@W3DFloorBuffer@@QAEXXZ @0x000E473F 93B
void W3DFloorBuffer::rva000E473F()
{
	BFMEDX8DeviceLock guard;
	if (m_vb != 0)
	{
		m_vb->Release_Ref();
		m_vb = 0;
	}
	if (m_ib != 0)
	{
		m_ib->Release_Ref();
		m_ib = 0;
	}
	m_slot.clear();
}

// ?allocateFloorBuffers@W3DFloorBuffer@@QAEXXZ @0x000E479C 234B
void W3DFloorBuffer::allocateFloorBuffers()
{
	BFMEDX8DeviceLock guard;
	if (m_vb != 0 || m_ib != 0)
		rva000E473F();
	m_vb = new BfmeDynamicNativeVB(0x152, 0x3A9C, 1, 0);
	m_ib = new DX8IndexBufferClass(0x7534, DX8IndexBufferClass::USAGE_DYNAMIC);
	m_0C = 0;
	m_10 = 0;
	static_cast<Rva00131DFC *>(&m_slot)->rva00131DFC((void *)1, (void *)1, (void *)0x15, (void *)1, 1, 0);
	if (m_slot.pointer != 0)
	{
		m_slot.Get_Surface_Level().DrawPixel(0, 0, 8355839); // 0x7F7FFF: DrawPixel color, not an image address
	}
	m_ready22 = true;
}

// Native E598B..E59D3 and WB 8841B0 prove the pointer list at +18,
// element cleanup before delete, and the final +10/+1C resets. Adapted from
// Open-BFME-1 6c1e0b51 W3DFloorBuffer_rva006F9050.cpp's reset semantics.
// The emitted pointer-list clear is proved against the complete 39-byte
// retail list<int> owner, including its free call, by the normal byte gate.
void W3DFloorBuffer::rva000E598B()
{
    for (_STL::list<Gen_uw_000e5033 *>::iterator it = m_floors.begin(); it._M_node != m_floors.end()._M_node; ++it) {
        reinterpret_cast<Rva000E4567 *>(*it)->rva000E4567();
        delete *it;
    }
    m_floors.clear();
    m_10 = 0;
    m_numFloors = 0;
}

// WB8844D0 identifies addFloor; native E6005..E6135 proves the entire
// 304-byte body, the five stack arguments, 0xA0 allocation and list order.
// Element constructor/destructor and both list folds are independently verified.
Gen_uw_000e5033 *W3DFloorBuffer::addFloor(int id, AsciiString *name, AsciiString *second, bool front, bool flag)
{
    Drawable *drawable = TheGameClient ? reinterpret_cast<FloorClientSlots *>(TheGameClient)->findDrawable(id) : 0;
    if (m_numFloors >= 450 || !drawable || !m_ready20) return 0;
    // The lookup (0x000E5F60) takes the name as AsciiString by value.
    Gen_uw_000e5033 *floor = reinterpret_cast<Gen_uw_000e5033 *>(
        reinterpret_cast<Rva000E5F60 *>(this)->rva000E5F60(id, *name));
    if (floor) {
        if (!reinterpret_cast<Rva000E440D *>(floor)->rva000E440D()) return 0;
        reinterpret_cast<Rva000E459F *>(floor)->rva000E46DA(drawable,*name,*second,front,flag);
        return floor;
    }
    floor = new Gen_uw_000e5033;
    reinterpret_cast<Rva000E459F *>(floor)->rva000E46DA(drawable,*name,*second,front,flag);
    if (floor->load()) {
        if (front) m_floors.push_front(floor); else m_floors.push_back(floor);
        m_numFloors = m_floors.size();
        m_ready22 = true;
        return floor;
    }
    delete floor;
    return 0;
}

// WB8854D0 names DoXfer; native E6186..E6350 is the complete 458-byte
// RET4 body. Version 3, loading/store branches, element construction and
// cleanup, all transferred scalar/matrix fields and list traversal agree.
// The stack element and its unwind action use the shared verified layout.
void W3DFloorBuffer::DoXfer(Xfer *xfer)
{
    if (xfer->IsLightCRC()) return;
    Xfer::Version version(3,3);
    *xfer == version;
    int count = m_floors.size();
    *xfer == count;
    if (xfer->IsLoading()) {
        rva000E598B();
        for (int index=0; index<count; ++index) {
            Gen_uw_000e5033 current;
            reinterpret_cast<Rva000E5725 *>(&current)->rva000E5725(xfer);
            Gen_uw_000e5033 *floor = addFloor(current.m_id4c, &current.m_name8c, &current.m_name90, current.m_flag82, current.m_flag81);
            if (floor) {
                floor->m_matrix50.rows[0].x = current.m_matrix50.rows[0].x;
                floor->m_matrix50.rows[0].y = current.m_matrix50.rows[0].y;
                floor->m_matrix50.rows[0].z = current.m_matrix50.rows[0].z;
                floor->m_matrix50.rows[0].w = current.m_matrix50.rows[0].w;
                floor->m_matrix50.rows[1].x = current.m_matrix50.rows[1].x;
                floor->m_matrix50.rows[1].y = current.m_matrix50.rows[1].y;
                floor->m_matrix50.rows[1].z = current.m_matrix50.rows[1].z;
                floor->m_matrix50.rows[1].w = current.m_matrix50.rows[1].w;
                floor->m_matrix50.rows[2].x = current.m_matrix50.rows[2].x;
                floor->m_matrix50.rows[2].y = current.m_matrix50.rows[2].y;
                floor->m_matrix50.rows[2].z = current.m_matrix50.rows[2].z;
                floor->m_matrix50.rows[2].w = current.m_matrix50.rows[2].w;
                floor->m_active80 = current.m_active80;
                floor->m_flag81 = current.m_flag81;
                floor->m_flag82 = current.m_flag82;
                floor->m_opacity84 = current.m_opacity84;
                floor->m_speed88 = current.m_speed88;
                floor->m_94 = current.m_94;
                floor->m_state98 = current.m_state98;
                floor->m_flag9c = current.m_flag9c;
                floor->m_flag9d = current.m_flag9d;
            }
        }
    } else {
        for (_STL::list<Gen_uw_000e5033 *>::iterator it=m_floors.begin(); it._M_node != m_floors.end()._M_node; ++it)
            reinterpret_cast<Rva000E5725 *>(*it)->rva000E5725(xfer);
    }
}

// WB8848E0 names drawFloors; native E5AAD..E5EBF is the complete 1044-byte
// RET8 body. It first drops floors whose element reports done (E440D),
// refreshes each floor's shroud state for the local player (E49B8) and the
// dirty flag, rebuilds the buffers (E58BE) when dirty, then draws every
// visible floor either untextured (terrain render mode 1) or through each
// pass of the rendering-method stack, as the matched W3DRoadBuffer path does.
// Removal/shroud loop shape carried from Open-BFME-1 a7c38d3b
// FloorBuffer006F9380Draw.cpp (donor semantics); offsets, callees and the
// render path are target facts from the native body and WB.
void W3DFloorBuffer::drawFloors(RenderInfoClass &rinfo, RefCountPtr<FXShader::RenderingMethod> method)
{
	int player;
	if (ThePlayerList)
		player = reinterpret_cast<FloorPlayerListView *>(ThePlayerList)->local->index;
	else
		player = 0;
	_STL::list<Gen_uw_000e5033 *>::iterator it = m_floors.begin();
	for (; it != m_floors.end(); ++it) {
		while (it != m_floors.end() && reinterpret_cast<Rva000E440D *>(*it)->rva000E440D()) {
			_STL::list<Gen_uw_000e5033 *>::iterator next = it;
			++next;
			reinterpret_cast<Rva000E4567 *>(*it)->rva000E4567();
			delete *it;
			m_floors.erase(it);
			m_numFloors = m_floors.size();
			it = next;
		}
		if (it == m_floors.end())
			break;
		if (reinterpret_cast<Rva000E459F *>(*it)->rva000E459F())
			m_ready22 = true;
		if (ThePlayerList && TheShroudManager) {
			int old = reinterpret_cast<FloorShroudView *>(*it)->getShroudStatus();
			int current = reinterpret_cast<Rva000E48BC *>(*it)->rva000E49B8(player);
			if (current != old) {
				reinterpret_cast<FloorShroudView *>(*it)->setShroudStatus(current);
				Gen_uw_000e5033 *floor = *it;
				if (floor->m_state98 == 0) {
					if (current == 1) { floor->m_state98 = 1; m_ready22 = true; }
				} else if (floor->m_state98 == 1) {
					if (current == 0) { floor->m_state98 = 2; m_ready22 = true; }
				} else if (floor->m_state98 == 2) {
					if (current == 1) { floor->m_state98 = 1; m_ready22 = true; }
				}
			}
		} else {
			reinterpret_cast<FloorShroudView *>(*it)->setShroudStatus(1);
			(*it)->m_state98 = 1;
			m_ready22 = true;
		}
	}
	if (m_ready22) {
		reinterpret_cast<Rva000E58BE *>(this)->rva000E58BE();
		m_ready22 = false;
	}
	m_flag21 = false;
	if (!m_10)
		return;
	DX8Wrapper::Set_Index_Buffer(reinterpret_cast<IndexBufferClass *>(m_ib), 0);
	DX8Wrapper::Set_Vertex_Buffer(reinterpret_cast<VertexBufferClass *>(m_vb), 0);
	DX8Wrapper::Set_Light_Environment(rinfo.light_environment);
	if (TheTerrainRenderObject && reinterpret_cast<BfmeTerrainRenderView *>(TheTerrainRenderObject)->getRenderState()->m_mode == 1) {
		BFME2Set_Texture(0, BFME2TextureRef(0));
		DX8Wrapper::Set_Shader(ShaderClass::_PresetOpaque2DShader);
		for (_STL::list<Gen_uw_000e5033 *>::iterator drawIt = m_floors.begin(); drawIt != m_floors.end(); ++drawIt)
			if ((*drawIt)->m_active80 && (*drawIt)->m_state98 != 0 && !reinterpret_cast<Rva000E440D *>(*drawIt)->rva000E440D())
				reinterpret_cast<Rva000E44BE *>(*drawIt)->rva000E44BE(0, reinterpret_cast<const RefCountPtr<TextureClass> &>(m_slot));
	} else {
		g_00DEBC60->setRenderingMode(3);
		rinfo.Push_Rendering_Method(method);
		Rva001688FFShift((Rva001688FFElement **)rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
		RefCountPtr<FXShader::RenderingMethod> current = rinfo.Get_Rendering_Method_Stack()[0];
		int passes;
		if (!current->Begin(&passes, 0xffff))
			return;
		passes = 1;
		for (int pass = 0; pass < passes; ++pass) {
			current->Begin_Pass(pass);
			// Retail reloads the list head from this+0x18 on every test here
			// instead of keeping the list address in a register.
			for (_STL::list<Gen_uw_000e5033 *>::iterator drawIt = m_floors.begin(); drawIt._M_node != m_floors._M_node._M_data; ++drawIt)
				if ((*drawIt)->m_active80 && (*drawIt)->m_state98 != 0 && !reinterpret_cast<Rva000E440D *>(*drawIt)->rva000E440D())
					reinterpret_cast<Rva000E44BE *>(*drawIt)->rva000E44BE(current.Peek(), reinterpret_cast<const RefCountPtr<TextureClass> &>(m_slot));
			current->End_Pass();
		}
		current->End();
		Rva00168952Clear((Rva001688FFElement **)rinfo.Get_Rendering_Method_Stack().begin(), rinfo.Get_Rendering_Method_Stack().size());
		rinfo.Pop_Rendering_Method();
	}
	g_00DEBC60->clearTextures();
	DX8Wrapper::Set_Light_Environment(0);
	DX8Wrapper::Set_Vertex_Shader(0);
	DX8Wrapper::Set_Pixel_Shader(0);
}
