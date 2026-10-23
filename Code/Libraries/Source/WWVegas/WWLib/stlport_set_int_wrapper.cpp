// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ?rva000BCA55@Rva000BCA55@@QAEXH@Z retail 0x000BCA55 28B
// Set-insert discard wrapper: set<int> at +0x9c via rowed insert 0x000BC15D,
// pair return discarded via stack temp. No callers; leaf.
// Evidence: callee 0x000BC15D plus prev row 0x000BC834 in same page.
#include <set>

// vector<int> fill/insert otherwise instantiates the _Construct<int,int>
// COMDAT (one byte shape per TU flags); a file-static overload takes those
// calls instead so this TU emits no external copy.
#include <new>
namespace _STL {
static inline void _Construct(int *__p, const int &__val)
{ new (__p) int(__val); }
}

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

// Node factory and allocator paths of the set<int> insert, emitted inline
// (dllimport+forceinline) so this TU emits no losing COMDAT copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<int> *allocator<_Rb_tree_node<int> >::allocate(size_t n, const void *) const
{ return n != 0 ? reinterpret_cast<_Rb_tree_node<int> *>(__sgi_alloc::allocate(n * sizeof(_Rb_tree_node<int>))) : 0; }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<int> *_STLP_alloc_proxy<_Rb_tree_node<int> *, _Rb_tree_node<int>, allocator<_Rb_tree_node<int> > >::allocate(size_t n)
{ return __stl_alloc_rebind(static_cast<allocator<_Rb_tree_node<int> >&>(*this), (_Rb_tree_node<int> *)0).allocate(n, 0); }
template <> __declspec(dllimport) __forceinline
_Rb_tree_node<int> *_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_create_node(const int &__x)
{
  _Rb_tree_node<int> *__tmp = this->_M_header.allocate(1);
  _Construct(&__tmp->_M_value_field, __x);
  return __tmp;
}
}

namespace _STL {
template <> _Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::iterator
_Rb_tree<int, int, _Identity<int>, less<int>, allocator<int> >::_M_insert(_Rb_tree_node_base *, _Rb_tree_node_base *, const int &, _Rb_tree_node_base *);
}

struct Rva000BCA55
{
	void rva000BCA55(int x);

	char m_pad[0x9c];
	_STL::set<int> m_set;
};

void Rva000BCA55::rva000BCA55(int x)
{
	m_set.insert(x);
}
