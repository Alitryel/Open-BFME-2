// cl: /arch:SSE /O1 /ICode/GameEngine/Source/Common /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc  /D_CRTIMP=
// Split from HordeSiegeEngineContain.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Target evidence: HordeSiegeEngineContain ctor 0x0047D247 installs primary
// vtable 0x00C474A0; slot 8 at 0x00C474C0 points to 0x0047CB4D. That slot in
// the OpenContain and TransportContain primary tables points to 0x00464120.
// The target calls that base body, walks the list at +0x128, clears dword
// +0x274 for each stored object pointer, calls rowed GameLogic::destroyObject,
// and tail-calls the rowed int-list clear at 0x0023DAA5.
//
// Identity: BFME1 OpenContain declares primary slot 8 as onDelete(void), and
// the target vtable slot and base call support HordeSiegeEngineContain::onDelete.
// The list<int> and +0x128 offset are target constructor evidence; its values
// are object pointers stored as ints. Object+0x274 remains unnamed.
#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}
// stlport

class Object;
class Thing;
class ModuleData;

#include "GameLogicObjectLookupView.h"
enum ObjectStatusTypes;
class Object
{
public:
	bool testStatus(ObjectStatusTypes) const;
	unsigned char unknown00[0x274];
	Object *m_containedBy274;
};

extern GameLogic *TheGameLogic;

class OpenContain
{
public:
	virtual void onDelete();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
	unsigned char m_padding0C[0x100 - 0x0C];
};

class TransportContain : public OpenContain
{
private:
	unsigned char m_padding100[0x11C - 0x100];
};

#include "../../../../../Include/GameLogic/ContainmentListView.h"

class HordeTransportContain : public TransportContain
{
public:
	void rva00463A4D(ContainmentList riders, int arg);	// 0x00463A4D
	void rva00477513();					// 0x00477513

private:
	unsigned char m_padding11C[0x128 - 0x11C];
};

class HordeSiegeEngineContain : public HordeTransportContain
{
public:
	virtual void onDelete();
	virtual void LoadPostProcess();
	void rva0047D33A();

private:
	_STL::list<int> m_riderObjects;
	unsigned char m_pad12C[0x134 - 0x12C];
	unsigned char m_riderMap134[0x140 - 0x134];
	_STL::list<int> m_restoreIDs140;
};


// Retail 0x0047CE0C..0x0047CEBB uses the +0x20 containment interface.
// WB 0x011AF7D0 establishes the loop, removal slot and random-force behavior;
// its class file and line 824 string agree with this unit. The slot's name
// and ignored argument remain unknown. Retail supplies the offsets below.
struct Rva0047CE0CVector
{
	float x, y, z;
	Rva0047CE0CVector(float first, float second, float third) : x(first), y(second), z(third) {}
	Rva0047CE0CVector(const Rva0047CE0CVector &other) : x(other.x), y(other.y), z(other.z) {}
};

class Rva003909FAObj
{
public:
	void consume(void *vector, int first, int second);
};

struct Rva0047CE0COwner
{
	unsigned char m_pad00[8];
	float m_directionX;
	unsigned char m_pad0C[0x18 - 0x0C];
	float m_directionY;
	unsigned char m_pad1C[0x25C - 0x1C];
	Rva003909FAObj *m_physics;
};

int GetGameLogicRandomValue(int low, int high, char *file, int line);

template <int N> class Rva0047CE0CSlots : public Rva0047CE0CSlots<N - 1>
{
public:
	virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0047CE0CSlots<0> {};

class Rva0047CE0CInterface : public Rva0047CE0CSlots<41>
{
public:
	virtual void removeRider(Object *object, bool flag) = 0;
	void removeAndApplyForce(int unused);
private:
	unsigned char m_pad04[0x108 - 4];
	_STL::list<int> m_riders;
};

void Rva0047CE0CInterface::removeAndApplyForce(int)
{
	_STL::list<int>::iterator first = m_riders.begin();
	while (first != m_riders.end()) {
		Object *rider = (Object *)*first;
		if (rider != 0) {
			removeRider(rider, false);
			Rva0047CE0COwner *owner = *(Rva0047CE0COwner **)((char *)this - 0x18);
			Rva003909FAObj *physics = owner->m_physics;
			if (physics != 0) {
				Rva0047CE0CVector direction(owner->m_directionX, owner->m_directionY, 1.0f);
				float magnitude = (float)GetGameLogicRandomValue(3, 8,
					"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Contain\\HordeContain\\HordeSiegeEngineContain.cpp", 824);
				direction.x *= magnitude;
				direction.y *= magnitude;
				direction.z *= magnitude;
				Rva0047CE0CVector force = direction;
				physics->consume(&force, 0, 0);
			}
		}
		first = m_riders.begin();
	}
}

class XferException
{
public:
    XferException(int tag, const char *format, ...);
    XferException(const XferException &);
    ~XferException();
    char *text;
    int tag;
};
class Rva00479D68 { public: void rva00479D68(); };
template <int N> class Rva0047D19CSlots : public Rva0047D19CSlots<N - 1>
{
public:
    virtual void gap(char (*)[N]) = 0;
};
template <> class Rva0047D19CSlots<0> {};
class Rva0047D19CInterface : public Rva0047D19CSlots<24>
{
public:
    virtual void slot24(Object *, int, int) = 0;
};


// Retail 0x0047D33A..0x0047D36A (48B), HordeSiegeEngineContain vtable entry
// 112 (0x008474E8). WB 0x011AE860 shows the same three calls: the rider list
// is copied by value through the containment-list copier 0x0036ADF9 into the
// 0x00463A4D worker together with the address at +0x134, then 0x00477513
// runs on the container. Method names are address-derived.
void HordeSiegeEngineContain::rva0047D33A()
{
	rva00463A4D(*reinterpret_cast<ContainmentList *>(&m_riderObjects), (int)m_riderMap134);
	rva00477513();
}
