// cl: /MD /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// TunnelTracker contain-list bodies, ported from Zero Hour's
// GameEngine/Source/Common/RTS/TunnelTracker.cpp (GeneralsMD tree vendored
// under reference/open-bfme-1/inputs/reference).
//  - getContainMax, retail 0x004F5385 (12 bytes): TheGlobalData's
//    m_maxTunnelCapacity (+0xA98 in BFME 2). TunnelContain reaches it through
//    tail jumps at 0x0046652F and 0x0047DE0D.
//  - addToContainList, retail 0x004F56E5 (23 bytes): TunnelContain reaches it
//    through tail jumps at 0x00466481 and 0x0047DC83. The append is the
//    out-of-line four-byte list push_back 0x0005548F.
//  - healObject, retail 0x004F53C3 (115 bytes): the callback whose address
//    healObjects (the rowed 0x004F558C) hands to iterateContained. The
//    DamageInfo is the 0x7C BFME 2 layout with its pinned constructor
//    0x00263895 (damage type 7 HEALING at +0x10, death type 1 NONE at +0x1C,
//    amount at +0x20); body module Object +0x254 (getMaxHealth slot 6,
//    attemptHealing slot 1); contained-by frame Object +0x27C.
// BFME 2 layout (target evidence, matching TunnelTracker::xfer): tunnel ids
// +0x08, contain list +0x10, contain list size +0x18, tunnel count +0x1C.
#include <list>

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

class Object;

#include "../GameLogicObjectLookupView.h"

class DamageInfoInput
{
public:
	char m_pad00[0x10];
	Int m_damageType; // +0x10
	char m_pad14[0x1C - 0x14];
	Int m_deathType; // +0x1C
	Real m_amount; // +0x20
};

// Retail builds it through the rowed initializer Rva00263895Member
// (Rva00263895Init.cpp); the inline forwarder binds the call there.
class Rva00263895Member
{
public:
	Rva00263895Member();	// 0x00263895
};
class DamageInfo
{
public:
	__declspec(dllimport) __forceinline DamageInfo() { ((Rva00263895Member *)this)->Rva00263895Member::Rva00263895Member(); }
	DamageInfoInput in;
	char m_pad24[0x7C - 0x24];
};

enum
{
	DAMAGE_HEALING = 7,
	DEATH_NONE = 1
};

class BodyModuleInterface
{
public:
	virtual void slot00();
	virtual void attemptHealing(DamageInfo *damageInfo);
	virtual void slot02();
	virtual void slot03();
	virtual void slot04();
	virtual void slot05();
	virtual Real getMaxHealth() const;
};

#include "TunnelTrackerNemesisView.h"

extern GameLogic *TheGameLogic;

class GlobalData
{
public:
	char m_pad00[0xA98];
	Int m_maxTunnelCapacity; // +0xA98
};
extern GlobalData *TheWritableGlobalData; // 0x00DFE758
#define TheGlobalData TheWritableGlobalData

// The contain list's append is the STLport four-byte list push_back body
// 0x0005548F (ICF-shared with list<int>), not the separate list<Object*>
// instance 0x001EC03C, so the list is modelled as its own class here; the
// append binds to the rowed list<int> body (stlport_list_int_o1.cpp).
namespace _STL { template <> void list<int, allocator<int> >::push_back(const int &value); }
class TunnelContainedItemsList
{
public:
	__declspec(dllimport) __forceinline void push_back(Object *const &obj) { ((_STL::list<int> *)this)->push_back((const int &)obj); }
private:
	void *m_node;
};
typedef TunnelContainedItemsList ContainedItemsList;

// ------------------------------------------------------------------------
Int TunnelTracker::getContainMax() const
{
	return TheGlobalData->m_maxTunnelCapacity;
}

// ------------------------------------------------------------------------
void TunnelTracker::addToContainList( Object *obj )
{
	reinterpret_cast<TunnelContainedItemsList *>(&m_containHead)->push_back(obj);
	++m_containListSize;
}

// ------------------------------------------------------------------------
	// heal one object within the tunnel network system
void TunnelTracker::healObject( Object *obj, void *frames)
{

	//get the number of frames to heal
	Real *framesForFullHeal = (Real*)frames;

	// setup the healing damageInfo structure with all but the amount
	DamageInfo healInfo;
	healInfo.in.m_damageType = DAMAGE_HEALING;
	healInfo.in.m_deathType = DEATH_NONE;

	// get body module of the thing to heal
	BodyModuleInterface *body = obj->getBodyModule();

	// if we've been in here long enough ... set our health to max
	if( TheGameLogic->getFrame() - obj->m_containedByFrame >= *framesForFullHeal )
	{

		// set the amount to max just to be sure we're at the top
		healInfo.in.m_amount = body->getMaxHealth();

		// set max health
		body->attemptHealing( &healInfo );

	}  // end if
	else
	{
		healInfo.in.m_amount = body->getMaxHealth() / *framesForFullHeal;

		// do the healing
		body->attemptHealing( &healInfo );

	}  // end else
}

