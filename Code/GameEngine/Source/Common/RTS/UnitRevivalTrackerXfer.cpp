// cl: /Ireference/shims/moduledata /O1 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// UnitRevivalTracker::xfer, retail 0x0037F39E (290 bytes):
// ?xfer@UnitRevivalTracker@@MAEXPAVXfer@@@Z
// Identity (target): WorldBuilder's debug UnitRevivalTracker.cpp
// UnitRevivalTracker::DoXfer calls, in retail's order, the entry transfer
// (0x0037E473), the entry vector's range erase, UnitRevivalEntry's
// constructor (0x0037E352), push_back, the entry destructor and
// PlayerList::getNthPlayer; retail's only reference is a vtable slot
// (0x00818DF0).
// Body (target): Version(1, 1); the entry count (vector at +0x04, 0xD8-byte
// entries) as an unsigned int; on save each entry then the owner's player
// index (+0x10, -1 for none); on load the vector is emptied and refilled
// one transferred entry at a time, then the owner is looked up by index.
// The vector members are the folded STLport bodies already rowed for this
// element (push_back 0x002E2D10, range erase 0x002E2690).
#include "Common/Snapshot.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
// Suppress this TU's non-retail copy of ?_M_insert_overflow@?$vector@VUnitRevivalEntry@@V?$allocator@VUnitRevivalEntry@@@_STL@@@_S:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class UnitRevivalEntry;
// Range erase already has a complete retail provider; keep this unit from
// instantiating its private element-assignment dependency.
namespace _STL { template <> __declspec(dllimport) __forceinline UnitRevivalEntry *vector<UnitRevivalEntry, allocator<UnitRevivalEntry> >::erase(UnitRevivalEntry *, UnitRevivalEntry *); }
namespace _STL { template <> void vector<UnitRevivalEntry,allocator<UnitRevivalEntry> >::_M_insert_overflow(UnitRevivalEntry *,UnitRevivalEntry const &,__false_type const &,unsigned int,bool); }
// Suppress this TU's non-retail copy of ??$_Construct@VUnitRevivalEntry@@V1@@_STL@@YAXPAVUnitRevivalEntry@@ABV1@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
class UnitRevivalEntry;
namespace _STL { template <> void _Construct<UnitRevivalEntry,UnitRevivalEntry>(UnitRevivalEntry *,UnitRevivalEntry const &); }
// Use the push_back copy emitted by UnitRevivalTrackerRva0037F2C0Finish.cpp.
namespace _STL { template <> void vector<UnitRevivalEntry,allocator<UnitRevivalEntry> >::push_back(UnitRevivalEntry const &); }

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;

#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};



class Player
{
public:
	int getPlayerIndex() const { return m_playerIndex; }

private:
	unsigned char m_pad00[0x54];
	int m_playerIndex; // +0x54
};

class PlayerList
{
public:
	Player *getNthPlayer(int index);
};

extern PlayerList *ThePlayerList;

class UnitRevivalEntry
{
public:
	UnitRevivalEntry();
	UnitRevivalEntry(const UnitRevivalEntry &that);
	~UnitRevivalEntry();
	UnitRevivalEntry &operator=(const UnitRevivalEntry &that);
	void rva0037E473(Xfer *xfer);

private:
	char m_bytes[0xD8];
};

// The native 0x37F435 call uses the existing D8-stride erase owner at
// 0x2E2690. Both views describe that same vector ABI; preserve the owner name.
struct Rva002E2690Element;
namespace _STL {
template <> Rva002E2690Element *vector<Rva002E2690Element, allocator<Rva002E2690Element> >::erase(Rva002E2690Element *, Rva002E2690Element *);
template <> __declspec(dllimport) __forceinline
UnitRevivalEntry *vector<UnitRevivalEntry, allocator<UnitRevivalEntry> >::erase(UnitRevivalEntry *first, UnitRevivalEntry *last)
{
    return reinterpret_cast<UnitRevivalEntry *>(
        reinterpret_cast<vector<Rva002E2690Element> *>(this)->erase(
            reinterpret_cast<Rva002E2690Element *>(first),
            reinterpret_cast<Rva002E2690Element *>(last)));
}
}

typedef _STL::vector<UnitRevivalEntry> UnitRevivalEntryVector;

class UnitRevivalTracker : public Snapshot
{
protected:
	virtual void crc(Xfer *xfer);
	virtual void xfer(Xfer *xfer);
	virtual void loadPostProcess();

private:
	UnitRevivalEntryVector m_entries; // +0x04
	Player *m_player; // +0x10
};

void UnitRevivalTracker::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 1);
	*xfer == version;

	unsigned int count = m_entries.size();
	*xfer == count;

	if (xfer->IsStoring())
	{
		for (UnitRevivalEntryVector::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
			it->rva0037E473(xfer);
		int playerIndex;
		if (m_player)
			playerIndex = m_player->getPlayerIndex();
		else
			playerIndex = -1;
		*xfer == playerIndex;
	}
	else
	{
		m_entries.clear();
		for (unsigned int i = 0; i < count; ++i)
		{
			UnitRevivalEntry entry;
			entry.rva0037E473(xfer);
			m_entries.push_back(entry);
		}
		int playerIndex;
		*xfer == playerIndex;
		if (playerIndex != -1)
			m_player = ThePlayerList->getNthPlayer(playerIndex);
		else
			m_player = 0;
	}
}
