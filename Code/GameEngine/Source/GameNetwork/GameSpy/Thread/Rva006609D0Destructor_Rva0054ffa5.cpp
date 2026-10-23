// ??1Rva006609D0@@UAE@XZ, retail 0x0054FFA5, 156 bytes. Dedicated TU ported
// from the Open-BFME-1 donor
// game/GameEngine/Source/GameNetwork/GameSpy/Thread/Rva006609D0Destructor.cpp
// (reference/open-bfme-1). The donor body does not place at BFME 1's flags;
// compiled /Os it is byte-identical to retail once relocations are masked
// (unique hit on unclaimed .text). Only the placed body is defined here; the
// donor's other definitions are omitted.
//
// Open-BFME7: the destructor at 0x006609D0 (BFME 1 retail 197 B) of a
// 0xB4-byte network results object: after a clearing member call (retail
// 0x0054FC14) the members unwind in reverse -- the owning holder of a mutex
// lock at +0xB0 (its inline destructor is the eighth EH state) -- a
// GameResultsCounter at +0xA8, a red-black tree at +0x74, two deques at +0x44
// and +0x1C and three GameResultsCounters at +0x14, +0x0C and +0x04 -- and the
// base vtable is restored.  Member types are opaque address-derived shells
// sized from the offsets with out-of-line destructors.
//
// 6 callee pins read off retail's REL32 displacements, over only four distinct
// target addresses because retail folds them:
//  0x0054FC14 clearing member call (matched ?rva0054FC14);
//  0x0009990D lock-holder destructor (matched ?clear@Rva0009990D);
//  0x00613A20 counter destructor, reached from +0x04 +0x0C +0x14 and +0xA8
//      (matched ??1MutexClass);
//  0x0038A48B tree destructor (matched STLport string-pair Rb_tree dtor);
//  0x0054FF17 deque destructor, reached from both +0x1C and +0x44, body
//      unrowed.
// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork/GameSpy/Thread

class GameResultsCounter
{
public:
	~GameResultsCounter();

private:
	char m_body[ 8 ];
};

class MutexClass
{
public:
	class LockClass
	{
	public:
		~LockClass();

	private:
		char m_body[ 4 ];
	};
};

struct Rva00660470Deque
{
	~Rva00660470Deque();
	char m_body[ 0x28 ];
};

struct Rva00660610Deque
{
	~Rva00660610Deque();
	char m_body[ 0x28 ];
};

struct Rva0064C290Tree
{
	~Rva0064C290Tree();
	char m_body[ 0x0C ];
};

struct Rva006609D0LockHolder
{
	~Rva006609D0LockHolder()
	{
		// The shared retail clear body at 0x0009990D clears the owner before
		// destroying the previous lock; omitting this store emits a wrong copy.
		MutexClass::LockClass *old = m_lock;
		m_lock = 0;
		if( old )
			delete old;
	}

	MutexClass::LockClass *m_lock;
};

class Rva006609D0Base
{
public:
	virtual ~Rva006609D0Base() {}
};

class Rva0055011A : public Rva006609D0Base
{
public:
	virtual ~Rva0055011A();

private:
	void bfmeClearVHX( void );

	GameResultsCounter m_counter04;
	GameResultsCounter m_counter0C;
	GameResultsCounter m_counter14;
	Rva00660470Deque m_deque1C;
	Rva00660610Deque m_deque44;
	char m_unreconstructed6C[ 8 ];
	Rva0064C290Tree m_tree74;
	char m_unreconstructed80[ 0xA8 - 0x80 ];
	GameResultsCounter m_counterA8;
	Rva006609D0LockHolder m_lockB0;
};

// ??1Rva0055011A@@UAE@XZ
Rva0055011A::~Rva0055011A()
{
	bfmeClearVHX();
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x0054FF17 reads ??1?$deque@UBfmePod16@@V?$allocator@UBfmePod16@@@_STL@@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00660470Deque@@QAE@XZ=??1?$deque@UBfmePod16@@V?$allocator@UBfmePod16@@@_STL@@@_STL@@QAE@XZ")
//   0x0054FF17 reads ??1?$deque@UBfmePod16@@V?$allocator@UBfmePod16@@@_STL@@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva00660610Deque@@QAE@XZ=??1?$deque@UBfmePod16@@V?$allocator@UBfmePod16@@@_STL@@@_STL@@QAE@XZ")
//   0x0038A48B reads ??1?$_Rb_tree@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@U?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@@_STL@@QAE@XZ
#pragma comment(linker, "/alternatename:??1Rva0064C290Tree@@QAE@XZ=??1?$_Rb_tree@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@2@U?$_Select1st@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@U?$less@V?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@2@V?$allocator@U?$pair@$$CBV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@H@_STL@@@2@@_STL@@QAE@XZ")
//   0x00613A20 reads ??1MutexClass@@QAE@XZ
#pragma comment(linker, "/alternatename:??1GameResultsCounter@@QAE@XZ=??1MutexClass@@QAE@XZ")
//   0x0054FC14 reads ?rva0054FC14@Rva0054FC14@@QAEXXZ
#pragma comment(linker, "/alternatename:?bfmeClearVHX@Rva0055011A@@AAEXXZ=?rva0054FC14@Rva0054FC14@@QAEXXZ")
