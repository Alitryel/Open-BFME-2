// Cold-slice B8-imm32 const-int returners (twin-free TU).
//
// Same 6-byte shape as ConstIntGetters7.cpp (mov eax,<IMM32> / ret) for
// bodies in regions siblings have not touched. Each is an unclaimed leaf, so
// the opaque address-derived name witnesses only the address and the returned
// constant. Kept in a fresh TU to avoid contending with hot getter files.
// No // cl: line (defaults match the frameless 6-byte shape).

// ?rva00181230@Rva00181230@@QBEHXZ @ 0x00181230 (21B): 1 when the byte flag at
// +4 and the dword at +8 are both clear, else 0 (the 6B "returns 1" getter
// once rowed at 0x0018123c was this body's true arm). No call, jump or data
// reference in retail; address-derived owner.
class Rva00181230
{
public:
	int rva00181230() const;
private:
	int m_00;
	bool m_04;
	int m_08;
};

int Rva00181230::rva00181230() const
{
	if (m_04 || m_08)
		return 0;
	return 1;
}
