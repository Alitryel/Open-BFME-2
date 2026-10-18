// cl: /O1 /EHsc /MD /arch:SSE /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC
// stlport
// class-gate: allow Snapshot Snapshot subobject view at +0x0C with virtual DoXfer slot 1 reproduces byte-exact CaveSystem::DoXfer at 0x00427738
// CaveSystem.cpp -- CaveSystem members recovered from WorldBuilder leads
// (reverse/wb_name_leads.csv): WB's debug build names the function; retail
// supplies the bytes. Zero Hour's getTunnelTrackerForCaveIndex
// (GameLogic/System/CaveSystem.cpp) without its lazy creation: the tracker
// vector sits at +0x10.

#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> void vector<unsigned int, allocator<unsigned int> >::_M_set(unsigned int *, unsigned int *, unsigned int *); }
namespace _STL { template <> void * __malloc_alloc<0>::allocate(unsigned int); }
namespace _STL { template <> void __malloc_alloc<0>::deallocate(void *, unsigned int); }
namespace _STL { template <> void allocator<unsigned int>::deallocate(unsigned int *, unsigned int) const; }
// bfme link decl-only end
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

typedef int Int;
typedef unsigned int UnsignedInt;

class TunnelTracker
{
public:
	TunnelTracker();
	virtual ~TunnelTracker();
	char pad[0x28 - 4];
};

class Xfer
{
public:
	virtual void slot0();
	virtual void slot1();
	virtual bool isSaving() const;
	virtual void slot3();
	virtual void slot4();
	virtual void slot5();
	virtual void slot6();
	virtual void slot7();
	virtual void slot8();
	virtual void slot9();
	virtual void slot10();
	virtual void slot11();
	virtual void Snapshot(void *object);
	virtual void slot13();
	virtual void slot14();
	virtual void slot15();
	virtual void slot16();
	virtual void slot17();
	virtual void slot18();
	virtual void slot19();
	virtual void slot20();
	virtual void slot21();
	virtual void slot22();
	virtual void slot23();
	virtual void slot24();
	virtual void slot25();
	virtual void slot26();
	virtual void slot27();
	virtual void slot28();
	virtual void slot29();
	virtual void slot30();
	virtual void slot31();
	virtual void xferUnsignedShort(unsigned short *value);

	void Version1();
};

class XferException
{
public:
	XferException(int tag, const char *format, ...);
	XferException(const XferException &that);
	~XferException(void);

	char *text;
	int tagValue;
};

class SubsystemInterface
{
public:
	virtual ~SubsystemInterface();
	char pad[8];
};

class Snapshot
{
public:
	virtual void crc(Xfer *xfer) = 0;
	virtual void DoXfer(Xfer *xfer) = 0;
	virtual void loadPostProcess() = 0;
};

class CaveSystem : public SubsystemInterface, public Snapshot
{
public:
	virtual ~CaveSystem();
	TunnelTracker *getTunnelTrackerForCaveIndex(UnsignedInt index);
	void registerNewCave(Int theIndex);
	void unregisterCave(Int theIndex);
	virtual void crc(Xfer *xfer) {}
	virtual void DoXfer(Xfer *xfer);
	virtual void loadPostProcess() {}

private:
	_STL::vector<TunnelTracker *> m_tunnelTrackerVector;
};

// CaveSystem::getTunnelTrackerForCaveIndex, retail 0x004275B6.
TunnelTracker *CaveSystem::getTunnelTrackerForCaveIndex(UnsignedInt index)
{
	TunnelTracker *retVal = 0;
	if (index < m_tunnelTrackerVector.size())
		retVal = m_tunnelTrackerVector[index];
	return retVal;
}

// CaveSystem::registerNewCave, retail 0x004276B6 (130 bytes), Zero Hour's
// body: a new index grows the tracker vector with null slots (the folded
// pointer-vector push_back, reached as in DoXfer), and a new or empty slot
// gets a fresh TunnelTracker.
void CaveSystem::registerNewCave(Int theIndex)
{
	bool needToCreate = false;
	if (theIndex >= m_tunnelTrackerVector.size())
	{
		needToCreate = true;
		while (theIndex >= m_tunnelTrackerVector.size())
		{
			unsigned int empty = 0;
			reinterpret_cast<_STL::vector<unsigned int> *>(&m_tunnelTrackerVector)->push_back(empty);
		}
	}
	else
	{
		if (m_tunnelTrackerVector[theIndex] == 0)
			needToCreate = true;
	}
	if (needToCreate)
		m_tunnelTrackerVector[theIndex] = new TunnelTracker;
}

// CaveSystem::unregisterCave: empty in Zero Hour ("Doesn't need to do
// anything"); retail folds the 3-byte RET 4 into 0x0047A69C. CaveContain's
// onDie 0x00466724 and tryToSetCaveIndex 0x004667D1 call it with ECX =
// TheCaveSystem and the cave index, between getTunnelTrackerForCaveIndex and
// the tracker's destroyed-tunnel notification, in Zero Hour's order.
void CaveSystem::unregisterCave(Int theIndex)
{
}

// ?DoXfer@CaveSystem@@UAEXPAVXfer@@@Z
void CaveSystem::DoXfer(Xfer *xfer)
{
	xfer->Version1();
	unsigned short count = (unsigned short)m_tunnelTrackerVector.size();
	xfer->xferUnsignedShort(&count);
	TunnelTracker *tracker;
	if (xfer->isSaving())
	{
		for (_STL::vector<TunnelTracker *>::iterator it = m_tunnelTrackerVector.begin(); it != m_tunnelTrackerVector.end(); ++it)
		{
			tracker = *it;
			xfer->Snapshot(tracker);
		}
	}
	else
	{
		if (!m_tunnelTrackerVector.empty())
		{
			throw XferException(5, 0);
		}
		for (unsigned short i = 0; i < count; ++i)
		{
			tracker = new TunnelTracker;
			xfer->Snapshot(tracker);
			reinterpret_cast<_STL::vector<unsigned int> *>(&m_tunnelTrackerVector)->push_back(reinterpret_cast<unsigned int &>(tracker));
		}
	}
}
