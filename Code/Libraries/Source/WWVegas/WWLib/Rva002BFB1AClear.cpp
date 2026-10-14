// cl: /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ?rva002BFB1A@Rva002BFB1A@@QAEXXZ, retail 0x002BFB1A (14B).
// Target evidence: erases [begin, end) of the 16-byte-element vector at +8
// through the rowed vector<BfmePod16>::erase(first, last) 0x002BF70F, its
// only callee -- STLport vector::clear() on a member (twin skeleton of the
// +4 AsciiString-vector clear 0x002CEC34). The owner and element type are
// not recovered (BfmePod16 stands for the 16-byte element, as in
// stlport_pod_vector_malloc_bodies.cpp, which compiles that erase); erase is
// only declared here so the call stays out of line as in retail.
#include <vector>

struct BfmePod16 { int a[4]; };

namespace _STL {
template <> vector<BfmePod16>::iterator vector<BfmePod16>::erase(vector<BfmePod16>::iterator, vector<BfmePod16>::iterator);
}

class Rva002BFB1A
{
public:
	void rva002BFB1A();
private:
	int m_00;
	int m_04;
	_STL::vector<BfmePod16> m_08;
};

void Rva002BFB1A::rva002BFB1A()
{
	m_08.clear();
}
