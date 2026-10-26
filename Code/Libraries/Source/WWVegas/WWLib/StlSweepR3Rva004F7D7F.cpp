// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /G7 /EHsc- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

struct Rva004F7D7FRecord { ~Rva004F7D7FRecord(); char bytes[1]; };

// Retail's destructor calls the rowed 24-byte range-destroy forwarder at 0x005F97BC,
// ??$_Destroy@PAUTreeHintRef00217D4C@@@_STL@@YAXPAUTreeHintRef00217D4C@@0@Z
// (StlportVectorEraseRangeFamily.cpp). Spell STLport's ~vector body against that
// owner instead of emitting a competing _Destroy<Rva004F7D7FRecord *> copy.
struct TreeHintRef00217D4C;
namespace _STL {
template <> void _Destroy<TreeHintRef00217D4C *>(TreeHintRef00217D4C *, TreeHintRef00217D4C *);
template <> vector<Rva004F7D7FRecord>::~vector()
{ _Destroy(reinterpret_cast<TreeHintRef00217D4C *>(this->_M_start), reinterpret_cast<TreeHintRef00217D4C *>(this->_M_finish)); }
}

template _STL::vector<Rva004F7D7FRecord>::~vector();
