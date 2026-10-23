// ?rva004E0625@Rva004E0625@@QBEHXZ @0x004E0625 13B + ?rva004E0632@Rva004E0632@@QBEHXZ @0x004E0632 13B
// Conditional dword getters: if dword at +0x20 == -1 return 0 else return dword at +0x40/+0x44.
// Evidence: retail bytes cmp [ecx+0x20],-1 / jne / xor eax,eax / ret / mov eax,[ecx+0x40|0x44] / ret;
// callers at 0x002B2D7D 0x002E1202 0x004FB972 0x0056AA3F (0625) and 0x002B64EE 0x002B6E30 0x0040C447 (0632);
// same check offset implies same underlying class; modelled as two honest-address classes.
// No // cl: line (defaults; neighbours Disp8ByteChaseGetters/Disp8PtrChaseDwordGetters also default).
class Rva004E0625
{
public:
	int rva004E0625() const;
	char m_pad0[0x20];
	int m_key;
	char m_pad1[0x40 - 0x20 - 4];
	int m_value;
};
int Rva004E0625::rva004E0625() const
{
	if (m_key == -1)
		return 0;
	return m_value;
}

class Rva004E0632
{
public:
	int rva004E0632() const;
	char m_pad0[0x20];
	int m_key;
	char m_pad1[0x44 - 0x20 - 4];
	int m_value;
};
int Rva004E0632::rva004E0632() const
{
	if (m_key == -1)
		return 0;
	return m_value;
}
