// cl: -EHsc /Os
// stlport
// STLport 4.5.3 slist<int>(const allocator_type &), retail 0x00071233
// (18B), unreferenced: hands the allocator to the rowed out-of-line
// _Slist_base<int> constructor (0x0006FA99) and returns this. The
// declaration-only specialisation keeps that call out of line, as in retail.
// The payload is int as in the rowed base (tgrid_008_Rva0006FA99.cpp).
#include <slist>

namespace _STL {
template <> _Slist_base<int, allocator<int> >::_Slist_base(const allocator<int> &);
}

template _STL::slist<int>::slist(const _STL::allocator<int> &);
