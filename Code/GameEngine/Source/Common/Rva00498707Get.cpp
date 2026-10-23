// ?rva00498707@Rva00498707@@QAEHXZ @0x00498707 15B
// Leaf getter with global compare. Evidence: gap between DispDwordFieldGetters
// and ModuleNameGetters; single caller 0x004998D9; global g_00DCB4CC.
extern int g_00DCB4CC;

class Rva00498707
{
	char m_pad0[0xC];
	int m_0C;
	char m_pad1[0x34];
	int m_44;
public:
	int rva00498707();
};

int Rva00498707::rva00498707()
{
	int v = m_44;
	if (v == g_00DCB4CC)
		v = m_0C;
	return v;
}
