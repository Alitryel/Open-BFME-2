// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// 0x0002BA98 (8B), unreferenced in retail: the element count of a vector of
// twelve-byte elements held at +4, a tail jump (add ecx,4) into the rowed
// out-of-line vector<BfmeE12>::size (0x005D5847). BfmeE12 is the size
// stand-in of stlport_vector_e12_o1.cpp; the declaration-only specialisation
// keeps the call out of line, as retail does. Owner address-derived.
#include <vector>

struct BfmeE12 { float x, y, z; };
namespace _STL { template<> vector<BfmeE12>::size_type vector<BfmeE12>::size() const; }

class Rva0002BA98
{
public:
	unsigned int rva0002BA98() const;
private:
	int m_00;
	_STL::vector<BfmeE12> m_04;
};

unsigned int Rva0002BA98::rva0002BA98() const
{
	return m_04.size();
}
