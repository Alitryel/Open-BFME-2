// stlport
// cl: /D_OPERATOR_NEW_DEFINED_ /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_NO_EXCEPTIONS=1 /D_STLP_USE_MALLOC /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /ICode/Libraries/Include
//
// The W3D particle system manager of BFME 2's FXParticleSystem
// (vftable 0x007C4C20, class Rva0004CA4C). Owner proven by the sibling slot 36
// (0x0004CF9A, banked), whose smudge path names this file in its
// GetGameClientRandomValueReal literal; WorldBuilder twin 0x007FB050 names the
// handle TrackingPtr<FXParticleSystem::ParticleSystem> (RvaSmartPtr12 here).
//
// ?rva0004D47D@Rva0004CA4C@@QAEXAAVRenderInfoClass@@@Z, retail
// 0x0004D47D..0x0004D636 (441 bytes), slot 37: the pass over particle
// systems of type 6 (+0x0C), the ones slot 36 skips. Target facts: on-screen
// count +0x5C and the draw modules' count +0x54 reset, the terrain's maximum
// visible box from the camera frustum, sort lists 1 queued into the +0xAC
// vector pair while WW3D's static sort lists are on, the rest drawn through
// draw-module slot 4, then both sort-list vectors drawn back to front with
// the second sorting flag 0x00DB5F7D cleared, and SortingRendererClass::Flush.
// The zeroed reference local at [ebp-0x1C] (EH state 0, never released) is
// the twin's ref-counted local released at the end; its type is not
// established.
#include "Lib/Coord3D.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

class RenderInfoClass;
class FrustumClass;
class ParticleSystem;

class AABoxClass
{
public:
	Coord3D Center;
	Coord3D Extent;
};

class CameraClass
{
public:
	const FrustumClass &Get_Frustum() const
	{
		Update_Frustum();
		return *reinterpret_cast<const FrustumClass *>(m_pad + 0x100);
	}

protected:
	void Update_Frustum() const;			// 0x001340B0

private:
	unsigned char m_pad[0x100];
};

class RenderInfoClass
{
public:
	CameraClass &Camera;
};

class BaseHeightMapRenderObjClass
{
public:
	Bool getMaximumVisibleBox(const FrustumClass &frustum, AABoxClass *box, Bool ignoreMaxHeight);	// 0x0006B1FA
};

class RvaSmartPtr12
{
public:
	void attach();					// 0x0004CB9A
	RvaSmartPtr12(const RvaSmartPtr12 &that);	// 0x0004CC19
	~RvaSmartPtr12() { if (m_ptr) rva0004CBC0(); }
	void rva0004CBC0();				// 0x0004CBC0
	ParticleSystem *get() const { return m_ptr; }
	ParticleSystem *operator->() const { return m_ptr; }

private:
	ParticleSystem *m_ptr;
	int m_pad04;
	int m_pad08;
};

#include <vector>
#include <list>
template<> void _STL::vector<RvaSmartPtr12>::push_back(const RvaSmartPtr12 &);
template<> RvaSmartPtr12 *_STL::vector<RvaSmartPtr12>::erase(RvaSmartPtr12 *, RvaSmartPtr12 *);

class ParticleDrawModule
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual Int doParticles(RenderInfoClass &rinfo, void *box, Int *count);	// slot 4 (+0x10)
};

class ParticleSystem
{
public:
	unsigned char m_pad00[0x0C];
	Int m_0C;					// +0x0C
	unsigned char m_pad10[0x24 - 0x10];
	UnsignedInt m_sortList;				// +0x24
	unsigned char m_pad28[0x1C4 - 0x28];
	ParticleDrawModule *m_drawModule;		// +0x1C4
};

class ParticleSystemManager
{
public:
	unsigned char m_pad00[0x4C];
	_STL::list<RvaSmartPtr12> m_allParticleSystems;	// +0x4C
};

class SortingRendererClass
{
public:
	static void Flush();				// 0x0012F190
};

class WW3D
{
	static bool AreStaticSortListsEnabled;
	friend class Rva0004CA4C;
};

extern BaseHeightMapRenderObjClass *TheTerrainRenderObject;
extern ParticleSystemManager *TheParticleSystemManager;
extern unsigned char g_Va00DB5F7D;

class TextureBaseClass { public: void Release_Ref(); };
struct Rva0004D47DAssetRef
{
	TextureBaseClass *m_ptr;
	Rva0004D47DAssetRef() : m_ptr(0) {}
	~Rva0004D47DAssetRef() { if (m_ptr) m_ptr->Release_Ref(); }
};

class Rva0004CA4C
{
public:
	void rva0004D47D(RenderInfoClass &rinfo);

private:
	void *m_vtbl;
	unsigned char m_pad04[0x54 - 0x04];
	Int m_54;					// +0x54
	unsigned char m_pad58[0x5C - 0x58];
	Int m_onScreenParticleCount;			// +0x5C
	unsigned char m_pad60[0xAC - 0x60];
	_STL::vector<RvaSmartPtr12> m_sortLists[2];	// +0xAC
};

void Rva0004CA4C::rva0004D47D(RenderInfoClass &rinfo)
{
	m_onScreenParticleCount = 0;
	AABoxClass bbox;
	TheTerrainRenderObject->getMaximumVisibleBox(rinfo.Camera.Get_Frustum(), &bbox, true);
	m_54 = 0;

	Rva0004D47DAssetRef assetRef;

	_STL::list<RvaSmartPtr12> &particleSysList = TheParticleSystemManager->m_allParticleSystems;
	for (_STL::list<RvaSmartPtr12>::iterator it = particleSysList.begin(); it != particleSysList.end(); ++it)
	{
		RvaSmartPtr12 sys(*it);
		if (!sys.get())
			continue;
		if (sys->m_0C != 6)
			continue;
		if (WW3D::AreStaticSortListsEnabled && sys->m_sortList > 0 && sys->m_sortList < 2)
		{
			m_sortLists[sys->m_sortList].push_back(sys);
			continue;
		}
		if (sys->m_drawModule)
		{
			m_onScreenParticleCount += sys->m_drawModule->doParticles(rinfo, &bbox, &m_54);
			continue;
		}
	}

	if (WW3D::AreStaticSortListsEnabled)
	{
		unsigned char saved = g_Va00DB5F7D;
		if (saved)
			g_Va00DB5F7D = 0;
		for (Int k = 1; k >= 0; k--)
		{
			_STL::vector<RvaSmartPtr12> &list = m_sortLists[k];
			for (Int j = list.size() - 1; j >= 0; j--)
			{
				RvaSmartPtr12 sys(list[j]);
				ParticleSystem *raw = sys.get();
				if (!raw)
					continue;
				ParticleDrawModule *drawModule = raw->m_drawModule;
				if (drawModule)
					m_onScreenParticleCount += drawModule->doParticles(rinfo, &bbox, &m_54);
			}
			list.clear();
		}
		if (saved)
			g_Va00DB5F7D = 1;
	}

	SortingRendererClass::Flush();
}
