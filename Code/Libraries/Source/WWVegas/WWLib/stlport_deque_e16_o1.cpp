// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// The element type here is a STAND-IN. What the image fixes is the element
// SIZE - it is the stride in every loop and the shift in every distance - and
// a byte-exact body says only that the real element is a POD of that size.
// BfmeE8, BfmeE12 and BfmeE16 name that size and claim nothing more. The
// bodies are byte-exact; the mangled names carry a placeholder where the real
// instantiation's type belongs, and should be repointed if that type is ever
// identified from a call site.
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
#include "../../../Include/Lib/BfmeE16.h"

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
template <> void _Deque_base<BfmeOpaqueOwnedRecord1408, allocator<BfmeOpaqueOwnedRecord1408> >::_M_initialize_map(size_t);
}

template void _STL::_Deque_iterator_base<BfmeE16>::_M_increment();
template void _STL::_Construct<BfmeE16, BfmeE16>(BfmeE16 *, const BfmeE16 &);
template BfmeE16 *_STL::allocator<BfmeE16>::allocate(unsigned int, const void *) const;
template _STL::_Deque_base<BfmeOpaqueOwnedRecord1408, _STL::allocator<BfmeOpaqueOwnedRecord1408> >::_Deque_base(
	const _STL::allocator<BfmeOpaqueOwnedRecord1408> &, unsigned int);
template _STL::deque<BfmeOpaqueOwnedRecord1408>::deque(const _STL::allocator<BfmeOpaqueOwnedRecord1408> &);
