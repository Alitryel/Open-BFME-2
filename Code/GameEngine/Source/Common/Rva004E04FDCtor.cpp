// ??0Rva004E04FD@@QAE@XZ @0x004E04FD 22B
// Zeroing constructor: zeroes five dwords at +0x00..+0x10 plus byte at +0x14.
// Retail is mov eax,ecx / xor ecx,ecx / mov [eax],ecx x5 / mov [eax+0x14],cl /
// ret (22B). The leading mov eax,ecx is the ctor returning this; a void method
// would use xor eax,eax plus stores via ecx (20B). No vtable, no base.
// Evidence: unlock lane; callers at 0x00299276 0x0037DF79 0x0037E308 0x0037E3AD;
// unblocks 0x0037E289/201 0x0037E352/135 0x0037DF2C/97.
// No // cl: line (defaults match the mov-eax-plus-xor-ecx shape).
class Rva004E04FD
{
public:
	Rva004E04FD();
	int m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;
	unsigned char m_14;
};
Rva004E04FD::Rva004E04FD()
{
	m_00 = 0;
	m_04 = 0;
	m_08 = 0;
	m_0C = 0;
	m_10 = 0;
	m_14 = 0;
}
