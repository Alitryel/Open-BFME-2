// cl: /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// stlport
// ??0Rva0022CA74@@QAE@XZ @0x0022CA74 33B
// Derived ctor: baseConstruct via inlined base then vtable 0xBE2704 then
// BfmeE16 Vector_base at +0xC. Same 33B shape as rowed ??0Rva00421242 at
// 0x00421242 (push ecx push esi mov esi ecx call baseConstruct lea eax
// [esp+7] push eax lea ecx [esi+0xC] mov [esi] vtable call Vector_base).
// Evidence: leaf packet calls rowed baseConstruct 0x001B4E63 and rowed
// Vector_base 0x00211E58; vtable store 0xBE2704; caller at 0x0022EA0A.
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

class Rva0022CA74 : public SubsystemInterface
{
public:
	Rva0022CA74();
protected:
	virtual ~Rva0022CA74();
private:
	_STL::vector<BfmeE16> m_vec;
};

Rva0022CA74::Rva0022CA74()
: m_vec()
{
}
