// cl: /Od

// The target entry at 0x00013260 zeroes the first dword at this and returns;
// it is the matched _M_initialize body with the same no-argument thiscall ABI.
#pragma comment(linker, "/alternatename:?m@Gen_0082ad50@@QAEXXZ=?_M_initialize@_STLP_mutex_base@_STL@@QAEXXZ")

struct Gen_0082ad50
{
	void m();
};

Gen_0082ad50 g_bfme0130b254;

class BfmeIf1VMK
{
public:
	void grokIf1();
};

void BfmeIf1VMK::grokIf1()
{
	int n1;
	if (1)
		g_bfme0130b254.m();
}
