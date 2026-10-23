// Disp8 byte-chase one-setters: eight-byte __thiscall members with one shape:
//
//     mov eax,[ecx+<DISP1>] / mov byte ptr [eax+<DISP2>],1 / ret
//
// A pointer is read at a fixed displacement from `this`, then a byte at a
// second displacement from that pointer is set to 1. Chase sibling of the
// direct Disp8ByteOneSetters family (MSVC 7.1 uses disp8 whenever the offset
// fits). Identity is not recovered: every name is derived from its address.
// No // cl: line (defaults match the frameless eight-byte shape).
// ?rva005C39AA@Rva005C39AA@@QAEXXZ @0x005C39AA 8B: ptr at +4, flag at +0x45 set to 1.
// Callers at 0x00567AD5 0x005680CD 0x005D24D5 0x005E0CE4 (jmp). Sibling shapes:
// direct +0x45 setter at 0x005C399E, ptr-chase dword getter +4/+0x1C at 0x005C39A3.
struct Rva005C39AAPointee
{
	char m_pad[0x45];
	unsigned char m_flag;
};
class Rva005C39AA
{
public:
	void rva005C39AA();
private:
	char m_lead[0x04];
	Rva005C39AAPointee *m_ptr;
};
void Rva005C39AA::rva005C39AA()
{
	m_ptr->m_flag = 1;
}
