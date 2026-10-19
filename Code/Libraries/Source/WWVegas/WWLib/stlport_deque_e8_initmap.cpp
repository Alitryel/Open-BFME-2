// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<BfmeE8>: _M_initialize_map 189B at
// 0x0073C8F0 plus the (alloc n) base ctor 76B at 0x0073CFE0 which calls it.
// Same placeholder-element convention as the sibling stlport_deque_e8_o1.cpp
// (BfmeE8 names only the element SIZE). Split into its own TU without /EHsc:
// retail carries no exception-handling frame for either function (the
// _STLP_TRY/_STLP_UNWIND rollback in vendor/stlport/stl/_deque.c compiles to
// nothing once _STLP_USE_EXCEPTIONS is off), while the sibling files need
// /EHsc for other members they host. /O2 inlines _M_create_nodes into
// _M_initialize_map (the /O1 probe outlines it as a call and lands 33B
// short); the node stride is 0x80 with shr-4 sizing (128/8 = 16 per node).
#include <deque>
struct BfmeE8 { int a, b; };

// The full explicit instantiation below also emits _M_push_back_aux_v for this
// {int,int} element, whose body is not retail's: retail's copy
// (stlport_deque_e8_pushback_aux.cpp, 0x0054B456) copies the second word
// through xmm0, so its element is {int,float}. With the o1 sibling no longer
// emitting its copy this TU's would be the first copy in link order and win.
// Declare it declaration-only so retail's copy in pushback_aux is kept.
namespace _STL {
template <> void deque<BfmeE8, allocator<BfmeE8> >::_M_push_back_aux_v(const BfmeE8 &);
}

template class _STL::deque<BfmeE8, _STL::allocator<BfmeE8 > >;
