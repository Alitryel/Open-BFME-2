// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

// Fill constructor of vector<LightSubPoint> (retail 0x0042545A) and its
// uninitialized_fill_n wrapper (0x0042536A), moved unchanged from
// stlport_copy_camera_marker.cpp. The element is LightSubPoint (24 bytes):
// retail's LightPoint constructor 0x004257AD fills its member with this body
// and its unwind funclet 0x00787199 destroys it with the rowed
// vector<LightSubPoint> destructor 0x00425717; the base constructor 0x000B63B2
// and the fill loop 0x00424D8C stride 0x18. The base is compiled without
// exceptions and with the bfmealloc allocator (its 0x000B63B2 unit), so this
// unit declares it only.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

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

struct LightSubPoint
{
	~LightSubPoint();
	LightSubPoint &operator=(const LightSubPoint &src);

	int m_words[6];
};

// bfme link decl-only begin
namespace _STL { template <> _Vector_base<LightSubPoint, allocator<LightSubPoint> >::_Vector_base(size_t, const allocator<LightSubPoint> &); }
// bfme link decl-only end

template _STL::vector<LightSubPoint>::vector(unsigned int, const LightSubPoint &, const _STL::allocator<LightSubPoint> &);
