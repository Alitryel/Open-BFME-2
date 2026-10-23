// ?rva005FD034@Rva005FD034@@QAEXH@Z retail 0x005FD034 19B
// Evidence: setter for member 0x34 with dirty flag 0x39; caller 0x005F44B0; neighbours Disp8 getters with defaults
struct Rva005FD034
{
	char m_pad0[0x34];
	int m_v34;
	char m_pad38[1];
	bool m_f39;
	void rva005FD034(int v);
};
void Rva005FD034::rva005FD034(int v)
{
	if (v != m_v34)
	{
		m_v34 = v;
		m_f39 = 0;
	}
}
