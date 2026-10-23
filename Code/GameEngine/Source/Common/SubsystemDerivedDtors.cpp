// cl: /Ireference/shims/bfme2_ascii /O1 /MD /EHsc /DNDEBUG
//
// Opaque subsystem destructors ending in ~SubsystemInterface 0x001B4E74
// (pinned; 12-byte base: vptr plus the name string at +0x08). Each installs
// its own vtable, tears down its string members (0x00036410) in reverse
// order, then calls the base. Scalar deleting dtors are already rowed in
// OpaqueScalarDeletingDtors.cpp (0x000984B2, 0x0009864B, 0x00095242).
// Names are the existing address-derived pins; owners unrecovered.
//
// ??1Rva0098477@@UAE@XZ @0x00098477 59B: vtable 0x00BC8298, string +0x0C.
// ??1Rva00985E4@@UAE@XZ @0x000985E4 74B: vtable 0x00BC8318, strings +0x10, +0x0C.
// ??1Rva009519B@@UAE@XZ @0x0009519B 113B: vtable 0x00BC81A8, strings +0xAC,
//   +0x24, +0x14, +0x10, +0x0C.

#include "ascii_string.h"

#include "../../../Libraries/Source/subsystem/SubsystemInterface.h"

class Rva0098477 : public SubsystemInterface
{
public:
	virtual ~Rva0098477();

private:
	AsciiString m_0C;
};

inline Rva0098477::~Rva0098477()
{
}

class Rva00985E4 : public SubsystemInterface
{
public:
	virtual ~Rva00985E4();

private:
	AsciiString m_0C;
	AsciiString m_10;
};

inline Rva00985E4::~Rva00985E4()
{
}

class Rva009519B : public SubsystemInterface
{
public:
	virtual ~Rva009519B();

private:
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	int m_18[3];
	AsciiString m_24;
	int m_28[(0xAC - 0x28) / 4];
	AsciiString m_AC;
};

inline Rva009519B::~Rva009519B()
{
}

// ??1Rva0098477, ??1Rva00985E4, ??1Rva009519B are header inlines elsewhere:
// other units emit select-any copies, so strong definitions here were
// duplicate symbols in the linked build. This anchor only makes this unit
// emit its copies for the ledger rows; it is not retail code.
#pragma inline_depth(0)
// ?bfmeEmitSubsystemDerivedDtors@@YAXPAVRva0098477@@PAVRva00985E4@@PAVRva009519B@@@Z present-unmatched
void bfmeEmitSubsystemDerivedDtors(Rva0098477 *p1, Rva00985E4 *p2, Rva009519B *p3)
{
	p1->Rva0098477::~Rva0098477();
	p2->Rva00985E4::~Rva00985E4();
	p3->Rva009519B::~Rva009519B();
}
#pragma inline_depth()
