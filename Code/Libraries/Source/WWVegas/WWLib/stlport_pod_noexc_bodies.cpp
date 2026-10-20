// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector/deque members for placeholder POD elements
// in the _STLP_NO_EXCEPTIONS configuration (no try/catch around the
// reallocation paths), each placed by a single masked whole-.text hit whose
// own bytes carry the element size. BfmePodN stands for the real N-byte
// element; a non-trivial copy construct is pinned by call-site address, not
// compiled here. No retail caller is claimed.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>
#include <deque>
// Suppress this TU's non-retail copy of ??0?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAE@ABV01@@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> vector<BfmePod44, allocator<BfmePod44> >::vector(const vector<BfmePod44, allocator<BfmePod44> > &); }
// Suppress this TU's non-retail copy of ?resize@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXI@Z:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::resize(size_t); }
// Suppress this TU's non-retail copy of ?erase@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEPAUBfmePod44@@PAU3@0:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> BfmePod44 *vector<BfmePod44, allocator<BfmePod44> >::erase(BfmePod44 *, BfmePod44 *); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod52@@V?$allocator@UBfmePod52@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod52;
namespace _STL { template <> void vector<BfmePod52, allocator<BfmePod52> >::_M_fill_insert(BfmePod52 *, size_t, const BfmePod52 &); }
// Suppress this TU's non-retail copy of ?_M_fill_insert@?$vector@UBfmePod44@@V?$allocator@UBfmePod44@@@_STL@@@_STL@@QAEXPAUBfmePod:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmePod44;
namespace _STL { template <> void vector<BfmePod44, allocator<BfmePod44> >::_M_fill_insert(BfmePod44 *, size_t, const BfmePod44 &); }
struct BfmePod8 { int a[2]; };
struct BfmePod16 { int a[4]; };
struct BfmePod20 { int a[5]; };
struct BfmePod28 { int a[7]; };
// bfme link decl-only BfmePod28
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *, BfmePod28 *); }
namespace _STL { template <> BfmePod28 * vector<BfmePod28, allocator<BfmePod28> >::erase(BfmePod28 *); }
struct BfmePod32 { int a[8]; };
// bfme link decl-only BfmePod32
namespace _STL { template <> vector<BfmePod32, allocator<BfmePod32> >::~vector(); }
struct BfmePod40 { int a[10]; };
// bfme link decl-only BfmePod40
namespace _STL { template <> vector<BfmePod40, allocator<BfmePod40> >::~vector(); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *); }
namespace _STL { template <> BfmePod40 *vector<BfmePod40, allocator<BfmePod40> >::erase(BfmePod40 *, BfmePod40 *); }
struct BfmePod44 { int a[11]; };
struct BfmePod52 { int a[13]; };
struct BfmePod68 { int a[17]; };
struct BfmePod76 { int a[19]; };
struct BfmePod492 { int a[123]; };
struct BfmePod840 { int a[210]; };
struct BfmePod24 { int a[6]; };
// 696 = 0x2B8 is BuddyRequest, as in stlport_pod_large_bodies.cpp.
class BuddyRequest
{
	char m_bfmeBody[0x2B8];
};
namespace _STL { template <> BfmePod52 *vector<BfmePod52, allocator<BfmePod52> >::erase(BfmePod52 *, BfmePod52 *); }
template class _STL::vector<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::vector<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::vector<BfmePod40, _STL::allocator<BfmePod40 > >;
template class _STL::vector<BfmePod44, _STL::allocator<BfmePod44 > >;
template class _STL::vector<BfmePod52, _STL::allocator<BfmePod52 > >;
template class _STL::vector<BfmePod68, _STL::allocator<BfmePod68 > >;
template class _STL::vector<BfmePod76, _STL::allocator<BfmePod76 > >;
template class _STL::deque<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::deque<BfmePod16, _STL::allocator<BfmePod16 > >;
template class _STL::deque<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::deque<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::deque<BfmePod492, _STL::allocator<BfmePod492 > >;
template class _STL::deque<BuddyRequest, _STL::allocator<BuddyRequest > >;
template class _STL::deque<BfmePod840, _STL::allocator<BfmePod840 > >;
template _STL::_Bit_iterator &_STL::_Bit_iterator::operator++();
