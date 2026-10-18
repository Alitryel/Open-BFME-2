// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
//
// ??0Rva0016E400@@QAE@XZ @ 0x0016E400 (72B). Default ctor for non-virtual wrapper with hash_map<int int> at +0.
// Evidence: push 0x64 matches hash_map() default 100 in vendor/stlport/stl/_hash_map.h; callee is _M_initialize_buckets for hashtable<pair<const int int> hash<int>> rowed at 0x00622410 in stlport_hash_map_int.cpp; zeros at +4 +8 +0xC +0x10 are buckets vector plus num_elements; no vtable store; caller is unclaimed 0x0016E450 which becomes ready.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end
// Suppress this TU's non-retail vector<void*> operator[] copy (family2-LK3 row 25):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void *&_STL::vector<void*>::operator[](size_t);
}
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

class Rva0016E400
{
public:
    Rva0016E400();
private:
    _STL::hash_map<int, int> m_map;
};

Rva0016E400::Rva0016E400() : m_map() {}

// ??0Rva00624D60@@QAE@XZ, retail 0x00624D60, 72 bytes: the same constructor (a
// default hash_map<int, int> member) for another class; only the EH handler
// record differs from ??0Rva0016E400's bytes. Identity unknown.
class Rva00624D60
{
public:
    Rva00624D60();
private:
    _STL::hash_map<int, int> m_map;
};
Rva00624D60::Rva00624D60() : m_map() {}
