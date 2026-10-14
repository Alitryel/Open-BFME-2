// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// _Deque_base map setup for deque<BfmeE32>: _M_initialize_map 191B at
// 0x0073C9D0 plus the (alloc n) base ctor 76B at 0x0073CF90 which calls it.
// Same placeholder-element convention as the sibling stlport_deque_e8_o1.cpp
// (BfmeE32 names only the element SIZE: rep-movs x8 bodies elsewhere fix the
// 32B stride, and shr-2 map sizing here fixes 128/32 = 4 per node). Same
// noexc split-TU rationale as stlport_deque_e8_initmap.cpp: retail carries
// no exception-handling frame, and /O2 inlines _M_create_nodes.
//
// Retail's map reallocator (0x0073D5E0, ICF-folded with deque<int>'s) expands
// the vendored inline __copy_trivial and __copy_trivial_backward into imported
// memmove calls. bfmealloc declares both out of line, as this unit's other
// bodies need, so the member is specialized below with those expansions.
// string.h is read first with the CRT's import linkage, so memmove is the
// import retail calls; the other units' direct CRT calls keep /D_CRTIMP=.
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <string.h>
#undef _CRTIMP
#define _CRTIMP
#include <deque>
struct BfmeE32 { int a[8]; };

namespace _STL {
inline void *bfmeCopyTrivial(const void *__first, const void *__last, void *__result)
{
  return (__last == __first) ? __result :
    ((char *)memmove(__result, __first, ((const char *)__last - (const char *)__first))) +
    ((const char *)__last - (const char *)__first);
}
inline void *bfmeCopyTrivialBackward(const void *__first, const void *__last, void *__result)
{
  const ptrdiff_t _Num = (const char *)__last - (const char *)__first;
  return (_Num > 0) ? memmove((char *)__result - _Num, __first, _Num) : __result;
}

template <> __declspec(noinline) inline
void deque<BfmeE32, allocator<BfmeE32> >::_M_reallocate_map(size_type __nodes_to_add,
                                                             bool __add_at_front)
{
  size_type __old_num_nodes = this->_M_finish._M_node - this->_M_start._M_node + 1;
  size_type __new_num_nodes = __old_num_nodes + __nodes_to_add;

  _Map_pointer __new_nstart;
  if (this->_M_map_size._M_data > 2 * __new_num_nodes) {
    __new_nstart = this->_M_map._M_data + (this->_M_map_size._M_data - __new_num_nodes) / 2
                     + (__add_at_front ? __nodes_to_add : 0);
    if (__new_nstart < this->_M_start._M_node)
      bfmeCopyTrivial(this->_M_start._M_node, this->_M_finish._M_node + 1, __new_nstart);
    else
      bfmeCopyTrivialBackward(this->_M_start._M_node, this->_M_finish._M_node + 1,
                              __new_nstart + __old_num_nodes);
  }
  else {
    size_type __new_map_size =
      this->_M_map_size._M_data + (max)((size_t)this->_M_map_size._M_data, __nodes_to_add) + 2;

    _Map_pointer __new_map = this->_M_map.allocate(__new_map_size);
    __new_nstart = __new_map + (__new_map_size - __new_num_nodes) / 2
                         + (__add_at_front ? __nodes_to_add : 0);
    bfmeCopyTrivial(this->_M_start._M_node, this->_M_finish._M_node + 1, __new_nstart);
    this->_M_map.deallocate(this->_M_map._M_data, this->_M_map_size._M_data);

    this->_M_map._M_data = __new_map;
    this->_M_map_size._M_data = __new_map_size;
  }

  this->_M_start._M_set_node(__new_nstart);
  this->_M_finish._M_set_node(__new_nstart + __old_num_nodes - 1);
}
}

template class _STL::deque<BfmeE32, _STL::allocator<BfmeE32 > >;
