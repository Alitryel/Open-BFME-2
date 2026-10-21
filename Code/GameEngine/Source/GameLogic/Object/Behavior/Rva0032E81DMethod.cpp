// cl: /GX- /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva0032E81D@Rva0032E81D@@QAEPAV1@PAX0@Z, retail 0x0032E81D, 29 bytes.
// Two-arg setter copying int from *a and vector from *b via rowed nested
// vector copyctor, returning this. Evidence: callees rowed; caller at
// 0x0032E925; prev/next STLport TUs.
#include <vector>
// Suppress this TU's non-retail copy of ??$__destroy_aux@PAV?$vector@UBfmeE8@@V?$allocator@UBfmeE8@@@_STL@@@_STL@@@_STL@@YAXPAV?$v:
// the kept copy serves the link. Plain declaration-only form (no __imp_).
struct BfmeE8;
namespace _STL { template <> void __destroy_aux<vector<BfmeE8,allocator<BfmeE8> > *>(vector<BfmeE8,allocator<BfmeE8> > *,vector<BfmeE8,allocator<BfmeE8> > *,__false_type const &); }

struct BfmeE8 { int a[2]; };
typedef _STL::vector<_STL::vector<BfmeE8> > VecVec;

class Rva0032E81D
{
public:
	Rva0032E81D(void *a, void *b);
	Rva0032E81D(const Rva0032E81D &other);
private:
	int m_val00;
	VecVec m_vec04;
};

Rva0032E81D::Rva0032E81D(void *a, void *b) : m_val00(*(int *)a), m_vec04(*(VecVec *)b)
{
}

Rva0032E81D::Rva0032E81D(const Rva0032E81D &other) : m_val00(other.m_val00), m_vec04(other.m_vec04)
{
}
