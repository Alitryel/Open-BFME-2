// cl: /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// stlport
// ??0DelayedExperienceLevelGrantSystem@@QAE@XZ, retail 0x00420E0D, 82 bytes. MI ctor over
// GameEngineDeletingBase-size base plus Snapshot plus Coord3D list at +0x10
// plus bool at +0x14: baseConstruct then Snapshot base vtable then derived
// vtables then List_base then bool false with EH prolog. Evidence: dtor
// 0x00420E67 same class; callees rowed baseConstruct 0x001B4E63 plus
// List_base 0x00280A8D; layouts +0xC/+0x10/+0x14 match dtor.
#include <list>

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class BFME2NativeNetwork
{
public:
};

// The ctor calls 0x001B4E63 and the paired destructor calls 0x001B4E74;
// both place Snapshot after the twelve-byte subsystem base.
typedef bool Bool;
#include "subsystem_interface.h"

#include "../../../../../reference/shims/moduledata/Common/Snapshot.h"


class DelayedExperienceLevelGrantSystem : public SubsystemInterface, public Snapshot
{
public:
	DelayedExperienceLevelGrantSystem();
	virtual ~DelayedExperienceLevelGrantSystem();	// 0x00420E67, Rva00420E67Dtor.cpp
private:
	_STL::list<Coord3D> m_list10;
	bool m_14;
};

DelayedExperienceLevelGrantSystem::DelayedExperienceLevelGrantSystem()
: m_list10(), m_14(false)
{
}
