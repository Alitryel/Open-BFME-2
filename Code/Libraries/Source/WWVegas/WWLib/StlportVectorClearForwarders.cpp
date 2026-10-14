// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 vector::clear() -- erase(begin(), end()) -- for four element
// stand-ins whose range erase is rowed elsewhere. Each retail body is 11
// bytes: push _M_finish, push _M_start, call erase on the same receiver, ret
// (twin skeleton of vector<BfmeFixedObject60>::clear 0x000BCFB8). The erase
// members are only declared so clear calls the rowed bodies out of line:
//   0x001FF218 -> erase 0x001FEFB9 (StlportObject476Erase.cpp)
//   0x002B8134 -> erase 0x000819EC (StlportVectorEraseRangeFamily.cpp)
//   0x00312CF2 -> erase 0x00312C44 (StlportVectorEraseRangeFamily.cpp)
//   0x003360EB -> erase 0x00335C62 (StlportVectorErase38Family.cpp)
// The element types are the ledger's existing stand-ins for those erases.
#include <vector>

struct BfmeObject476;
struct TreeHintRef00217D4C;
struct BfmeStringHeadRecord184;
struct BfmeOpaqueRecord156;
struct BfmeAssignRecord172;
struct Rva001EBEABElement;

namespace _STL {
template <> BfmeObject476 *vector<BfmeObject476>::erase(BfmeObject476 *, BfmeObject476 *);
template <> TreeHintRef00217D4C *vector<TreeHintRef00217D4C>::erase(TreeHintRef00217D4C *, TreeHintRef00217D4C *);
template <> BfmeStringHeadRecord184 *vector<BfmeStringHeadRecord184>::erase(BfmeStringHeadRecord184 *, BfmeStringHeadRecord184 *);
template <> BfmeOpaqueRecord156 *vector<BfmeOpaqueRecord156>::erase(BfmeOpaqueRecord156 *, BfmeOpaqueRecord156 *);
template <> BfmeAssignRecord172 *vector<BfmeAssignRecord172>::erase(BfmeAssignRecord172 *, BfmeAssignRecord172 *);
template <> void vector<Rva001EBEABElement>::_M_fill_insert(Rva001EBEABElement *, unsigned int, const Rva001EBEABElement &);
}

template void _STL::vector<BfmeObject476>::clear();
template void _STL::vector<TreeHintRef00217D4C>::clear();
template void _STL::vector<BfmeStringHeadRecord184>::clear();
template void _STL::vector<BfmeOpaqueRecord156>::clear();

// 0x001EC090 (11B) -> erase 0x001EBDFA (stlport_vector_bfmeassignrecord172_erase.cpp)
template void _STL::vector<BfmeAssignRecord172>::clear();

// 0x001EC09B (5B): directly after it, vector::insert(pos, n, value) as a
// bare tail jump to the rowed _M_fill_insert 0x001EBEAB of the 172-byte
// element vector (StlSweepW4Rva001EBEAB.cpp stand-in).
template void _STL::vector<Rva001EBEABElement>::insert(Rva001EBEABElement *, unsigned int, const Rva001EBEABElement &);
