// cl: /DNDEBUG /MD /GX
// stlport
//
// ??0FireWeaponUpdate@@QAE@PAVThing@@PBVModuleData@@@Z retail 0x0048C0C5
// 112 bytes. Behavior-side ctor completing the FireWeaponUpdate file-unit
// (behavior instance factory rowed at 0x24CF1E news 0x2C with this 2-arg
// ctor as its caller; FireWeaponUpdate poolkey rowed at 0x48BDB3; ModuleData
// proc 0x48C0B4 is the opaque Hero-side base link).
//
// Shape: EH prolog plus UpdateModule base call 0x253390, then the compiler
// installs the three tables (+0/+0xC/+0x10) ahead of the member inits (the
// RMW-and of m_20 hoists to the front), the runtime watch list resolves
// through the rowed _List_base int spelling, and the setWakeFrame tail
// passes frame literal 1. Member names are behavior-state inferred from the
// zero-init layout; no donor names them. The single-caller 0x48BDF8 helper
// rides as an opaque Rva pin (do-not-name note).



#include <list>

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::_List_base(const allocator<int> &);
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> void _List_base<int, allocator<int> >::clear();
}

// Declaration-only: retail keeps one copy of this STLport member (rowed elsewhere); this unit calls it
// rather than emitting its own.
namespace _STL {
template <> _List_base<int, allocator<int> >::~_List_base();
}

// list<int> destruction otherwise instantiates per-TU deallocate
// COMDATs (one byte shape per TU flags); explicit dllimport+forceinline
// specializations take those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<int> >::deallocate(_List_node<int>* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<int> *, _List_node<int>, allocator<_List_node<int> > >::deallocate(_List_node<int> *__p, size_t __n) {
  allocator<_List_node<int> >().deallocate(__p, __n);
}
}

class Thing;
class ModuleData;
class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

template <int NUMBITS> class BitFlags;

// Zero Hour's UpdateModule shape, with the interface views CreateCrateDie.cpp
// and FireWeaponUpdate.cpp declare: ObjectModule at +0, BehaviorModuleInterface
// at +0xC (retail's folded table) and UpdateModuleInterface at +0x10, whose
// table 0x00C4C18C is the rowed update 0x0048BEE8 then UpdateModule's rowed
// getDisabledTypesToProcess 0x00253376 and 0x0044DF8D. The compiler installs
// all three after the pinned UpdateModule ctor.
class ObjectModule
{
public:
	virtual void objectModuleAnchor();
protected:
	const ModuleData *m_moduleData;		// +4
	Object *m_object;					// +8
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceAnchor();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
	virtual BitFlags<11> getDisabledTypesToProcess() const = 0;
	virtual void rva0044DF8D(UpdateSleepTime frame) = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
public:
	UpdateModule(Thing *thing, const ModuleData *moduleData);
	virtual ~UpdateModule();
	virtual BitFlags<11> getDisabledTypesToProcess() const;
	virtual void rva0044DF8D(UpdateSleepTime frame);
protected:
	void setWakeFrame(Object *object, UpdateSleepTime frame);
	unsigned int m_nextCallFrameAndPhase;	// +0x14
	int m_indexInLogic;					// +0x18
	int m_reserved1C;					// +0x1C
};
class FireWeaponUpdate : public UpdateModule
{
public:
	FireWeaponUpdate(Thing *thing, const ModuleData *moduleData);
	virtual ~FireWeaponUpdate();
	virtual UpdateSleepTime update();
	void Rva0048BDF8Helper(void);
private:
	int m_weaponState;					// +0x20
	_STL::list<int> m_trackedIds;		// +0x24, runtime watch list
	unsigned char m_weaponsReady;		// +0x28
};

// ??0FireWeaponUpdate@@QAE@PAVThing@@PBVModuleData@@@Z @0x0048C0C5
FireWeaponUpdate::FireWeaponUpdate(Thing *thing, const ModuleData *moduleData)
	: UpdateModule(thing, moduleData)
	, m_weaponState(0)
	, m_weaponsReady(0)
{
	Rva0048BDF8Helper();
	Object **objSlot = &m_object;
	setWakeFrame(*objSlot, UPDATE_SLEEP_NONE);
}
