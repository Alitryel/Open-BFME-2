// cl: /O1 /G7 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??0BFMENetworkQueue@@QAE@XZ, retail 0x00558D41..0x00558D56 (21B).
//
// The network queue's out-of-line default constructor: an empty STLport
// deque of the network records, i.e. the rowed _Deque_base constructor
// 0x005532FF called with a default allocator and no initial elements (the
// same shape as the rowed queue constructor 0x0038D28E). The pin and its
// callers name the class; native_network_BFMENetwork_Ctor.cpp keeps its own
// inline field view for the copy BFMENetwork builds in place, so this
// definition lives in its own unit. The record type is opaque here.
#include <deque>
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

struct BfmeOpaqueOwnedRecord492
{
	BfmeOpaqueOwnedRecord492(const BfmeOpaqueOwnedRecord492 &that);
	~BfmeOpaqueOwnedRecord492();
	char m_body[0x1EC];	// 492 bytes, as PeerThread.cpp (rowed _Deque_base 0x5532FF) and StlportOwnedRecordDeque.cpp define it
};

class BFMENetworkQueue
{
public:
	BFMENetworkQueue();

private:
	_STL::deque<BfmeOpaqueOwnedRecord492> m_records;
};

BFMENetworkQueue::BFMENetworkQueue()
{
}
