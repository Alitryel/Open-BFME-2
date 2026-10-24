// cl: /MD /DNDEBUG /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// ??0Rva0026E7EA@@QAE@XZ, retail 0x0026E7C8, 28 bytes.
//
// Frameless thiscall ctor abutting the AIUpdate parseLocomotorSet body
// (caller: the AIUpdateInterface ctor's +0x224 member). Stores 0xBFA3A4 at
// +0, the class vtable (slot 0 is the deleting dtor 0x26E81A over the rowed
// dtor ??1Rva0026E7EA 0x26E7EA, slot 3 the xfer 0x332975; spelled here as a
// data anchor until that vtable is defined) and builds the +4 member
// as an empty 16B-element vector through the rowed BfmeE16 _Vector_base
// 0x211E58 with the 1-byte stack allocator temp idiom. Class identity
// unproven; Rva vehicle asserts no false name.

#include <vector>

#include "../../../../../Libraries/Include/Lib/BfmeE16.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<BfmeE16,_STL::allocator<BfmeE16> >::~_Vector_base(); }
namespace _STL { template <> vector<BfmeE16,_STL::allocator<BfmeE16> >::~vector(); }
// bfme link decl-only end
// bfme link decl-only BfmeE16
namespace _STL { template <> vector<BfmeE16, allocator<BfmeE16> >::~vector(); }
// Suppress this TU's non-retail BfmeE16 proxy deallocate copy (family2-LK3 row 34):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<BfmeE16*, BfmeE16, allocator<BfmeE16> >::deallocate(BfmeE16*, size_t);
}

class Rva0026E7EA
{
public:
	Rva0026E7EA();

private:
	void *m_unk0;
	_STL::vector<BfmeE16> m_vec;
};

extern unsigned char Rva0026E7C8DataAnchor;
// Rva0026E7C8DataAnchor: matched references place it at VA 0xbfa3a4 (retail .rdata value 26).
unsigned char Rva0026E7C8DataAnchor = 26;

// ??0Rva0026E7EA@@QAE@XZ @0x0026E7C8
Rva0026E7EA::Rva0026E7EA() :
	m_unk0(&Rva0026E7C8DataAnchor)
{
}
