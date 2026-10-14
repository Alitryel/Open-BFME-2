// ?rva002E734E@Rva002E7334@@QAEHPAURva002E734ECell@@0HH@Z
// partial score=0.85 date=2026-10-14
// Bank for 0x002E734E (58B), a method of the 0x002E7334 record (GapBodiesGE15.cpp).
// This spelling matches all but the tail: retail extracts the flag as
// shr eax,16 / movzx eax,al / and eax,1 from the one dword load it also used for
// the type test; cl folds the movzx away. Byte-bitfield views load bytes, and
// a local struct copy spills to the stack.
struct Rva002E734ECell { int m_pad00[3]; unsigned int m_flags; };
struct Rva002E7334
{
	int rva002E734E(Rva002E734ECell *from, Rva002E734ECell *to, int x, int y);
	int m_00, m_04, m_08;
};
int Rva002E7334::rva002E734E(Rva002E734ECell *from, Rva002E734ECell *to, int x, int y)
{
	if (x == m_04 && y == m_08)
		return 0;
	unsigned int flags = to->m_flags;
	unsigned int type = flags & 0xF;
	if (type == 0 || type == 1)
		return (unsigned char)(flags >> 16) & 1;
	return 1;
}
