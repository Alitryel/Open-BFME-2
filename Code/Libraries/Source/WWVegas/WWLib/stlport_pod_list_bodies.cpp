// cl: /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Pristine STLport 4.5.3 list members for fixed-size POD elements; same
// evidence and naming rule as stlport_pod_vector_bodies.cpp.
//
// BfmePodN (BfmeShortPodN: 2-byte aligned) is a placeholder for the real
// N-byte element type at each site.
// Where retail's copy construct for that element is non-trivial (it calls a
// copy constructor), _Construct<BfmePodN> is pinned in symbols.csv at the
// address the byte-true call site proves; that body is not compiled from here.
// _M_create_node fixes only the node allocation size (rounded by the node
// allocator), so its N is exact only up to that rounding: BfmeShortPod22/26
// place equally as 24/28-byte int elements under /GX.
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _List_iterator<T, LeftTraits>& a,
                              const _List_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}
struct BfmePod12 { int a[3]; };

struct BfmePod20 { int a[5]; };
struct BfmePod24 { int a[6]; };
inline bool operator==(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] == y.a[0]; }
// Retail erase(iterator) relinks the node onto the freelist pool head inline
// (pool at VA 0x00DA60E8, head at +0x08; retail 0x002ABB20).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool;
namespace _STL {
template <> list<BfmePod12>::iterator list<BfmePod12>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool.m_head;
	g_freelistPool.m_head = __position._M_node;
	return iterator((_List_node<BfmePod12> *)__next_node);
}
}
inline bool operator<(const BfmePod12 &x, const BfmePod12 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod20 &x, const BfmePod20 &y) { return x.a[0] < y.a[0]; }
inline bool operator==(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod24 &x, const BfmePod24 &y) { return x.a[0] < y.a[0]; }
struct BfmePod8 { int a[2]; };
inline bool operator==(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod8 &x, const BfmePod8 &y) { return x.a[0] < y.a[0]; }
struct BfmePod28 { int a[7]; };
inline bool operator==(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod28 &x, const BfmePod28 &y) { return x.a[0] < y.a[0]; }
struct BfmePod32 { int a[8]; };
inline bool operator==(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod32 &x, const BfmePod32 &y) { return x.a[0] < y.a[0]; }
// push_back calls retail's 37-byte insert (0x000BC180) out of line; bind it there.
namespace _STL { template <> list<BfmePod32>::iterator list<BfmePod32>::insert(iterator, const BfmePod32 &); }
struct BfmePod60 { int a[15]; };
inline bool operator==(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod60 &x, const BfmePod60 &y) { return x.a[0] < y.a[0]; }
struct BfmePod72 { int a[18]; };
inline bool operator==(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod72 &x, const BfmePod72 &y) { return x.a[0] < y.a[0]; }
struct BfmePod124 { int a[31]; };
inline bool operator==(const BfmePod124 &x, const BfmePod124 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod124 &x, const BfmePod124 &y) { return x.a[0] < y.a[0]; }
struct BfmePod196 { int a[49]; };
inline bool operator==(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod196 &x, const BfmePod196 &y) { return x.a[0] < y.a[0]; }
namespace _STL { template<> void _Construct<BfmePod196, BfmePod196>(BfmePod196 *, const BfmePod196 &) throw(); }
// Keep the native 37-byte insert provider from its dedicated unit.
namespace _STL { template <> list<BfmePod196>::iterator list<BfmePod196>::insert(iterator, const BfmePod196 &); }
// Experience payload cleanup is virtual: retail list clear 0x002887EA.
// Keep the proven 0x108-byte node payload and existing provider spelling.
struct BfmePod264 { BfmePod264(const BfmePod264 &); virtual ~BfmePod264(); int a[65]; };
// bfme link decl-only BfmePod264
namespace _STL { template <> void _Construct<BfmePod264, BfmePod264>(BfmePod264 *, BfmePod264 const &); }
inline bool operator==(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmePod264 &x, const BfmePod264 &y) { return x.a[0] < y.a[0]; }
struct BfmeShortPod22 { short a[11]; };
inline bool operator==(const BfmeShortPod22 &x, const BfmeShortPod22 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmeShortPod22 &x, const BfmeShortPod22 &y) { return x.a[0] < y.a[0]; }
struct BfmeShortPod26 { short a[13]; };
inline bool operator==(const BfmeShortPod26 &x, const BfmeShortPod26 &y) { return x.a[0] == y.a[0]; }
inline bool operator<(const BfmeShortPod26 &x, const BfmeShortPod26 &y) { return x.a[0] < y.a[0]; }
template class _STL::list<BfmePod12, _STL::allocator<BfmePod12 > >;
template class _STL::list<BfmePod20, _STL::allocator<BfmePod20 > >;
template class _STL::list<BfmePod24, _STL::allocator<BfmePod24 > >;
template class _STL::list<BfmePod8, _STL::allocator<BfmePod8 > >;
template class _STL::list<BfmePod28, _STL::allocator<BfmePod28 > >;
template class _STL::list<BfmePod32, _STL::allocator<BfmePod32 > >;
template class _STL::list<BfmePod60, _STL::allocator<BfmePod60 > >;
template class _STL::list<BfmePod72, _STL::allocator<BfmePod72 > >;
template class _STL::list<BfmePod124, _STL::allocator<BfmePod124 > >;
template class _STL::list<BfmePod196, _STL::allocator<BfmePod196 > >;
// Emit the recovered experience-list operations and their cleanup only.
// Blanket instantiation also emitted unsupported comparisons and POD copies.
template _STL::list<BfmePod264>::list(const _STL::list<BfmePod264> &);
template void _STL::list<BfmePod264>::push_back(const BfmePod264 &);
template _STL::_List_base<BfmePod264, _STL::allocator<BfmePod264> >::~_List_base();
template class _STL::list<BfmeShortPod22, _STL::allocator<BfmeShortPod22 > >;
template class _STL::list<BfmeShortPod26, _STL::allocator<BfmeShortPod26 > >;


