// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /D_STLP_NO_EXCEPTIONS
// stlport
#include <vector>

// Retain the bfmealloc primary bodies inline without competing external copies.
namespace _STL {
template<> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* p, size_t n) const {
 _STLP_ASSERT( (p == 0) == (n == 0) )
 if(p != 0) ::free((void*)p);
}
template<> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int* p, size_t n) {
 __stl_alloc_rebind(static_cast<allocator<int>&>(*this),(int*)0).deallocate(p,n);
}
}


struct Rva0042464E
{
	char m_pad[0xC];
	~Rva0042464E();
};

struct LightSubPoint
{
	Rva0042464E m_vec1;
	_STL::vector<int> m_vec2;
	~LightSubPoint();
};

LightSubPoint::~LightSubPoint()
{
}

class LightPoint
{
public:
	_STL::vector<LightSubPoint> m_points;
	~LightPoint();
};

LightPoint::~LightPoint()
{
}

// ?anchorDeleteLightPoint@@YAXPAVLightPoint@@@Z present-unmatched
void anchorDeleteLightPoint(LightPoint *lightPoint)
{
	delete lightPoint;
}
