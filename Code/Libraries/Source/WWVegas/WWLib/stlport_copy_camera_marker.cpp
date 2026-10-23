// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport

// Eight-byte CameraMarker copy/erase helpers. The fill constructor and its
// worker remain in stlport_camera_marker_fill_deferred.cpp pending the
// independently observed 24-byte allocation/layout reconciliation.
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

struct CameraMarker
{
	~CameraMarker();
	CameraMarker &operator=(const CameraMarker &src);

	CameraMarker *m_next;
	void *m_name;
};

template CameraMarker *_STL::__copy<CameraMarker *, CameraMarker *, int>(CameraMarker *, CameraMarker *, CameraMarker *, const _STL::random_access_iterator_tag &, int *);
template CameraMarker *_STL::vector<CameraMarker>::erase(CameraMarker *);
