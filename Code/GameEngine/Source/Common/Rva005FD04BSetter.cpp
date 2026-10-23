// ?rva005FD04B@Rva005FD04B@@QAEXE@Z retail 0x005FD04B 19B
// Evidence: setter for member 0x38 with dirty flag 0x3a; getter 0x005FD047 same disp; caller 0x005F4488; neighbours Disp8 getters with defaults
struct Rva005FD04B
{
	char m_pad0[0x38];
	unsigned char m_v38;
	char m_pad39;
	unsigned char m_f3a;
	void rva005FD04B(unsigned char v);
};
void Rva005FD04B::rva005FD04B(unsigned char v)
{
	if (v != m_v38)
	{
		m_v38 = v;
		m_f3a = 0;
	}
}
