// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??$assign@U?$_List_iterator@PAVGameWindow@@U?$_Const_traits@PAVGameWindow@@@_STL@@@_STL@@@?$list@PAVGameWindow@@V?$allocator@PAVGameWindow@@@_STL@@@_STL@@QAEXU?$_List_iterator@PAVGameWindow@@U?$_Const_traits@PAVGameWindow@@@_STL@@@1@0@Z, retail 0x004243BE, 22 bytes.
// _STL::list<GameWindow*>::assign over const_iterator range: forwards first
// last plus __false_type tag to rowed honest dispatch 0x00423D92.
// Evidence: STLport _list.h assign shape plus rowed honest rva00423D92 plus
// stash 0x004243BE score 0.95 plus callers none plus prev next same flags.
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
template void GWList::assign<GWList::const_iterator>(GWList::const_iterator, GWList::const_iterator);
