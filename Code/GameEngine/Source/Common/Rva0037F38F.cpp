// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ?addRevivableUnit@UnitRevivalTracker@@QAEXABURva002E2D10Record@@PAVPlayer@@@Z @0x0037F38F 15B
// Evidence: unlock lane; forwards member +4 vector push_back 0x002E2D10;
// ret 8 with an unused second slot: the Player, as in WorldBuilder's
// signature; caller 0x001EC8C0 and the callers in PlayerNewMapBFME2.cpp and
// ScriptActions_livingWorldRegion.cpp pass one.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

class Player;

// The record is the rowed UnitRevivalEntry (copy ctor 0x002E134C); the
// address-derived name is only a view. Forward to the real body so _Construct
// binds the canonical symbol instead of an undefined address-named twin.
class UnitRevivalEntry { public: UnitRevivalEntry(const UnitRevivalEntry &); };
struct Rva002E2D10Record
{
    Rva002E2D10Record();
    __declspec(dllimport) __forceinline Rva002E2D10Record(const Rva002E2D10Record &that)
    {
        ((UnitRevivalEntry *)this)->UnitRevivalEntry::UnitRevivalEntry(*(const UnitRevivalEntry *)&that);
    }
    ~Rva002E2D10Record();
    Rva002E2D10Record &operator=(const Rva002E2D10Record &that);

private:
    char bytes[216];
};

class UnitRevivalTracker
{
    int m_unk00;
    _STL::vector<Rva002E2D10Record> m_vec04;

public:
    void addRevivableUnit(const Rva002E2D10Record &item, Player *player);
};

void UnitRevivalTracker::addRevivableUnit(const Rva002E2D10Record &item, Player *)
{
    m_vec04.push_back(item);
}
