// cl: /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
// ??1GameState@@UAE@XZ @0x002DE58D 180B: GameState destructor (was ??1Rva002DE58D). Identity: vtable
// 0x00C0402C#0 (scalar deleting dtor at 0x002DF2DA calls it), member offsets shared
// with Rva002DEE9AOwner (E0C/E10/E14/E18 in Rva002DEE9AClear.cpp), save-info member
// 0xDE8 bytes at +0x24 (BfmeSubobject0022CE19 row at 0x002DD1E9), Snapshot base at +0xC
// (restores vtable 0x00BBB554), SubsystemInterface dtor row at 0x001B4E74.
// Callers: 0x002DF03C, ??_G at 0x002DF2DA, unwind at 0x007783D4.

struct CameraMarker;

namespace _STL
{
template <class _Tp>
class allocator
{
};

template <class _Tp, class _Alloc>
class _List_base
{
public:
	void clear();
	~_List_base();
private:
	void *_M_head;
};
}

class BfmeSubobject0022CE19
{
public:
	virtual ~BfmeSubobject0022CE19();
private:
	char m_pad[0xDE8 - 4];
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
private:
	char m_pad[0xC - 4];
};

// Native secondary-base vptr BBB554 and +0xC adjustment identify Snapshot.
#include "Common/Snapshot.h"

class Rva002DE311Owner
{
public:
	void rva002DE311();
};

class GameState : public SubsystemInterface, public Snapshot
{
public:
	virtual ~GameState();
private:
	_STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> > m_cameraLists[5];
	BfmeSubobject0022CE19 m_saveInfo;
	_STL::_List_base<int, _STL::allocator<int> > m_intListA;
	_STL::_List_base<int, _STL::allocator<int> > m_intListB;
};

// ??1GameState@@UAE@XZ
GameState::~GameState()
{
	_STL::_List_base<CameraMarker, _STL::allocator<CameraMarker> > *cameraLists = m_cameraLists;
	for (int i = 0; i < 5; ++i)
		cameraLists[i].clear();

	m_intListA.clear();
	m_intListB.clear();
	// Same GameState object: Rva002DEE9AOwner shares the E0C/E10/E14/E18 layout
	// (Rva002DEE9AClear.cpp); call its pinned clearer by its row name.
	((Rva002DE311Owner *)this)->rva002DE311();
}
