// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// ??$__copy@PAV?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@PAV12@H@_STL@@YAPAV?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@0@PAV10@00ABUrandom_access_iterator_tag@0@PAH@Z @0x004703B1 47B
// STLport __copy for list<GameWindow*> (4-byte list objects): range-loop
// calling rowed list operator= 0x0046F0C2. Called by copy 0x00474125.
// Evidence: callees rowed; callers 0x00474138; prev/next STL flags.
#include <algorithm>
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


class GameWindow;
// Retail erase(iterator) relinks the node onto the freelist pool head inline
// (pool at VA 0x00DB8FEC, head at +0x08; retail 0x0029DFC5).
class FreelistPool { public: void *pop(); int m_00; void *m_04; void *m_head; };
extern FreelistPool g_freelistPool00DB8FEC;
namespace _STL {
template <> list<GameWindow *>::iterator list<GameWindow *>::erase(iterator __position)
{
	_List_node_base *__prev_node = __position._M_node->_M_prev;
	_List_node_base *__next_node = __position._M_node->_M_next;
	__prev_node->_M_next = __next_node;
	__next_node->_M_prev = __prev_node;
	*(void **)__position._M_node = g_freelistPool00DB8FEC.m_head;
	g_freelistPool00DB8FEC.m_head = __position._M_node;
	return iterator((_List_node<GameWindow *> *)__next_node);
}
}
typedef _STL::list<GameWindow *, _STL::allocator<GameWindow *> > GWList;
template GWList *_STL::copy<GWList *, GWList *>(GWList *, GWList *, GWList *);
