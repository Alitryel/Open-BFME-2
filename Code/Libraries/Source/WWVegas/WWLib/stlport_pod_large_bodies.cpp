// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 vector/deque members for large placeholder POD
// elements (132..900 bytes), each placed by a single masked whole-.text hit
// whose own bytes carry the element size (allocate multiplies by it,
// push_back/__uninitialized_fill_n step by it). BfmePodN stands for the real
// N-byte element; no retail caller is claimed and no container kind is
// asserted for the allocate rows.
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
struct BfmePod132 { int a[33]; };
struct BfmePod156 { int a[39]; };
struct BfmePod184 { int a[46]; };
struct BfmePod204 { int a[51]; };
struct BfmePod272 { int a[68]; };
struct BfmePod276 { int a[69]; };
struct BfmePod476 { int a[119]; };
struct BfmePod480 { int a[120]; };
struct BfmePod492 { int a[123]; };
struct BfmePod544 { int a[136]; };
// 696 = 0x2B8 is BuddyRequest (see BuddyRequestDequePushBackAux.cpp): the
// placed deque's _Construct callee is the matched _Construct<BuddyRequest>
// at 0x00550798, so these rows carry the real element type.
class BuddyRequest
{
	char m_bfmeBody[0x2B8];
};
struct BfmePod840 { int a[210]; };
struct BfmePod872 { int a[218]; };
struct BfmePod900 { int a[225]; };
// _Construct<BfmePod900> is the rowed non-trivial copy construct at 0x004CB8DE: declare it so this
// unit calls it rather than emitting its own trivial copy (as stlport_pod_vector_bodies.cpp does).
// Native 4CBB1A calls the same 4CBA0F growth helper as the owning-record
// instantiation. The copy loops call its 4CB8DE placement-copy helper too.
// Keep the size-only public rows, but call those providers by their row names.
struct BfmeRecordOwner900;
namespace _STL {
template <> __declspec(nothrow) void _Construct<BfmeRecordOwner900, BfmeRecordOwner900>(
    BfmeRecordOwner900 *, const BfmeRecordOwner900 &);
template <> class vector<BfmeRecordOwner900, allocator<BfmeRecordOwner900> > {
    friend class vector<BfmePod900, allocator<BfmePod900> >;
protected:
    void _M_insert_overflow(BfmeRecordOwner900 *, const BfmeRecordOwner900 &,
                           const __false_type &, unsigned int, bool);
};
template <> __declspec(dllimport) __forceinline __declspec(nothrow)
void _Construct<BfmePod900, BfmePod900>(BfmePod900 *p, const BfmePod900 &value) {
    _Construct(reinterpret_cast<BfmeRecordOwner900 *>(p),
               reinterpret_cast<const BfmeRecordOwner900 &>(value));
}
template <> __declspec(dllimport) __forceinline
void vector<BfmePod900>::_M_insert_overflow(BfmePod900 *pos, const BfmePod900 &value,
    const __false_type &tag, unsigned int count, bool at_end) {
    // This empty dispatch tag carries no state; the native helper ignores it.
    // Default initialization avoids materializing the caller's value-initialized tag.
    __false_type provider_tag;
    reinterpret_cast<vector<BfmeRecordOwner900> *>(this)->_M_insert_overflow(
        reinterpret_cast<BfmeRecordOwner900 *>(pos),
        reinterpret_cast<const BfmeRecordOwner900 &>(value), provider_tag, count, at_end);
}
}
// Only allocation is established for this 132-byte element.
template class _STL::allocator<BfmePod132>;
template class _STL::allocator<BfmePod156>;
template class _STL::allocator<BfmePod184>;
template class _STL::deque<BfmePod204, _STL::allocator<BfmePod204 > >;
template class _STL::deque<BfmePod272, _STL::allocator<BfmePod272 > >;
template class _STL::deque<BfmePod276, _STL::allocator<BfmePod276 > >;
template class _STL::allocator<BfmePod476>;
template class _STL::vector<BfmePod480, _STL::allocator<BfmePod480 > >;
template class _STL::vector<BfmePod492, _STL::allocator<BfmePod492 > >;
template class _STL::allocator<BfmePod544>;
template class _STL::vector<BuddyRequest, _STL::allocator<BuddyRequest > >;
template class _STL::vector<BfmePod840, _STL::allocator<BfmePod840 > >;
// Only allocation and trivial assignment are claimed for this size-only view.
template class _STL::allocator<BfmePod872>;
template BfmePod872* _STL::__copy<BfmePod872*, BfmePod872*, int>(
    BfmePod872*, BfmePod872*, BfmePod872*,
    const _STL::random_access_iterator_tag&, int*);
template class _STL::vector<BfmePod900, _STL::allocator<BfmePod900 > >;
template class _STL::deque<BfmePod492, _STL::allocator<BfmePod492 > >;
template class _STL::deque<BuddyRequest, _STL::allocator<BuddyRequest > >;
template class _STL::deque<BfmePod840, _STL::allocator<BfmePod840 > >;

template _STL::_Deque_iterator<BfmePod492, _STL::_Nonconst_traits<BfmePod492> > &
_STL::_Deque_iterator<BfmePod492, _STL::_Nonconst_traits<BfmePod492> >::operator++();
template _STL::_Deque_iterator<BfmePod840, _STL::_Nonconst_traits<BfmePod840> > &
_STL::_Deque_iterator<BfmePod840, _STL::_Nonconst_traits<BfmePod840> >::operator++();
template _STL::_Deque_iterator<BuddyRequest, _STL::_Nonconst_traits<BuddyRequest> > &
_STL::_Deque_iterator<BuddyRequest, _STL::_Nonconst_traits<BuddyRequest> >::operator++();
