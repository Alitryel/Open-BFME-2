// cl: /MD /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// ??0Rva002D22CA@@QAE@XZ
// RVA 0x002D22AC size 30. Ctor calls SubsystemInterface ctor at 0x1B4E63
// via pin then stores derived vtable 0x00802A20 and zeroes 48B tail at +0x0C
// via 12-int loop lowered to rep stosd with lea before xor. Evidence: vtable
// store names Rva002D22CA per packet; base layout 12B from
// GameEngineDeletingBaseDtor.cpp; unblocks 0x4CA3A; neighbours in
// GameEngineDeletingBaseDerived.cpp share /O1 /MD; loop (not memset) keeps
// retail lea-xor order.

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
// The native header GameEngineDeletingBaseDerived.cpp (which defines ~Rva002D22CA)
// uses: flag +0x04, name +0x08 and its fourteen slots, so both TUs emit one table.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva002D22CA : public SubsystemInterface
{
public:
	Rva002D22CA();
	virtual ~Rva002D22CA();

private:
	char m_tail0C[48];
};

Rva002D22CA::Rva002D22CA() : SubsystemInterface()
{
	for (int i = 0; i < 12; i++)
		((int *)m_tail0C)[i] = 0;
}
