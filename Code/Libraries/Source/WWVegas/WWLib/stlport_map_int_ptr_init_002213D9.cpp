// cl: /EHsc /D_STLP_NO_EXCEPTIONS /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?Rva002213D9Get@@YAPAV?$map@HPAXU?$less@H@_STL@@V?$allocator@U?$pair@$$CBHPAX@_STL@@@2@@_STL@@XZ, retail 0x002213D9 69B.
// Function-local static initializer for map<int,void*>: guard test/or,
// map ctor at 0x0033C432, atexit registration. Byte-exact via MSVC static
// init with /EHsc; callees resolve through rows.
#include <map>

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}

// The map's constructor, destructor and node allocator otherwise emit this
// unit's own copies, which are not retail's bodies; the calls link to the kept
// retail definitions.
namespace _STL {
template <> _Rb_tree_base<pair<const int, void *>, allocator<pair<const int, void *> > >::_Rb_tree_base(const allocator<pair<const int, void *> > &);
template <> _Rb_tree<int, pair<const int, void *>, _Select1st<pair<const int, void *> >, less<int>, allocator<pair<const int, void *> > >::~_Rb_tree();
}

_STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > *Rva002213D9Get()
{
    static _STL::map<int, void *, _STL::less<int>, _STL::allocator<_STL::pair<const int, void *> > > s_map;
    return &s_map;
}
