// cl: /O1 /GX- /MD /DNDEBUG
// Opaque dtor at 0x004E18A2 (vptr store plus conditional member-method
// tail-jump). The +8 slot holds a pointer to an opaque pool member whose
// release method lives at 0x50ED3 (pinned); a null member returns directly.
// /GX- suppresses handler-SEH around the opaque member call (retail is a
// frameless 18B leaf), cf. the Rva004907C0 member-call precedent.

class PoolMember
{
public:
	void Rva0050ED3();

private:
	unsigned char m_pad[16];
};

class Rva004E18A2
{
public:
	virtual ~Rva004E18A2();

private:
	unsigned char m_pad04[4];
	PoolMember *m_member08;
};

// ??1Rva004E18A2@@UAE@XZ
inline Rva004E18A2::~Rva004E18A2()
{
	if (m_member08 != 0)
		m_member08->Rva0050ED3();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva004E18A2InlineAnchor@@YAXPAVRva004E18A2@@@Z absent-from-retail
void _bfmeRva004E18A2InlineAnchor(Rva004E18A2 *p)
{
    p->Rva004E18A2::~Rva004E18A2();
}
#pragma inline_depth()
