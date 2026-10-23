// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0BFMENetworkQueue1@@QAE@XZ @0x00558D56 21B: Default ctor wraps the 1408-byte record DequeBase at 0x0055334A with a temporary allocator and zero count.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <deque>
class PSPlayerAllStats {
public:
	PSPlayerAllStats &operator=(const PSPlayerAllStats &);
	~PSPlayerAllStats();
private:
	union {
		unsigned int alignmentWitness;
		unsigned char bytes[0x548];
	};
};

struct BfmeOwnedRecord1408Tail5 {
	unsigned int values[5];
};

struct BfmeOpaqueOwnedRecord1408 {
	unsigned int head[2];
	PSPlayerAllStats member;
	BfmeOwnedRecord1408Tail5 tail550;
	unsigned int value564;
	unsigned int value568;
	unsigned int value56C;
	unsigned int value570;
	unsigned int value574;
	unsigned int value578;
	unsigned char value57C;
	unsigned char value57D;
	BfmeOpaqueOwnedRecord1408();
	BfmeOpaqueOwnedRecord1408(const BfmeOpaqueOwnedRecord1408 &);
	BfmeOpaqueOwnedRecord1408 &operator=(const BfmeOpaqueOwnedRecord1408 &);
};

namespace _STL {
template <> _Deque_base<BfmeOpaqueOwnedRecord1408, allocator<BfmeOpaqueOwnedRecord1408> >::_Deque_base(
	const allocator<BfmeOpaqueOwnedRecord1408> &, unsigned int);
}

class BFMENetworkQueue1
{
	_STL::_Deque_base<BfmeOpaqueOwnedRecord1408, _STL::allocator<BfmeOpaqueOwnedRecord1408> > m_base;
public:
	BFMENetworkQueue1();
};
BFMENetworkQueue1::BFMENetworkQueue1() : m_base(_STL::allocator<BfmeOpaqueOwnedRecord1408>(), 0)
{
}
