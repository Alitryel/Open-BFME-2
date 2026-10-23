// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// stlport
// ??0Rva0022CA95@@QAE@XZ @0x0022CA95 47B
// Derived ctor: baseConstruct via inlined base then vtable 0x00BE5348 then
// two BfmeE16 Vector_base at +0xC and +0x18. Same family as rowed
// ??0Rva0022CA74 at 0x0022CA74 (33B, one vector) in Rva0022CA74Ctor.cpp.
// Evidence: leaf packet calls rowed baseConstruct 0x001B4E63 and rowed
// Vector_base 0x00211E58 twice; vtable store 0x00BE5348 at [esi];
// caller at 0x0022F49B.
#include <vector>

#include "../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }

class BFME2NativeNetwork
{
public:
};

// Calls the rowed subsystem constructor; the paired destructor proves
// the same twelve-byte base at +0 before the vector storage at +0x0C.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0022CA95 : public SubsystemInterface
{
public:
	Rva0022CA95();
protected:
	virtual ~Rva0022CA95();
private:
	_STL::vector<BfmeE16> m_vec0;
	_STL::vector<BfmeE16> m_vec1;
};

Rva0022CA95::Rva0022CA95()
: m_vec0(), m_vec1()
{
}
