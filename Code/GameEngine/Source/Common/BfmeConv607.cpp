class BfmeThingCIC
{
public:
	void bfmeGoCIC(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

int Rva007ECE60(char *a, int b, const char *one, const char *two);

void BfmeThingCIC::bfmeGoCIC(void *one, void *two)
{
	if (Rva007ECE60((char *)m_bfmeA, (int)m_bfmeB, (const char *)one, (const char *)two) < 0)
		m_bfmeErr = -100;
}

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeWrite@BfmeSetupRecord@@QAEXPBDH@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:?bfmeSetVJA@BfmeMsgVJA@@QAEXPBDPAX@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVJI@BfmeMsgVJI@@QAEXPBD0@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVJC@BfmeMsgVJC@@QAEXPBDPAX@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVIR@BfmeMsgVIR@@QAEXPBDPAX@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVJF@BfmeMsgVJF@@QAEXPBDPAX@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVJH@BfmeMsgVJH@@QAEXPBD0@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
#pragma comment(linker, "/alternatename:?bfmeSetVJJ@BfmeMsgVJJ@@QAEXPBD0@Z=?bfmeGoCIC@BfmeThingCIC@@QAEXPAX0@Z")
