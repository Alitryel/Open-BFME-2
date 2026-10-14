// ?rva0056AB35@Rva0056ACC5@@QAEXH@Z
// partial score=0.97 date=2026-10-15
// ?rva0056AB35@Rva0056ACC5@@QAEXH@Z
// partial score=0.93 date=2026-10-01
// cl: /MD /O1 /arch:SSE /G7 /Oa
// ?rva0056AB35@Rva0056ACC5@@QAEXH@Z @0x0056AB35 83B vslot slot 2 of 0x0086D0FC (class of ??1Rva0056ACC5@@UAE@XZ).
// Evidence: vtable slot 2; callee 0x0029B187 rowed; TheInGameUI 0x009FEDF0; floats g_00C6D010/14/18.
struct Rva004E57E6Pair {
	float m_0;
	float m_4;
};

class Rva0029B187 {
public:
	void rva0029B187(Rva004E57E6Pair *p, float f);
};

class InGameUI;
extern class InGameUI *TheInGameUI;

extern float g_00C6D018;
extern float g_00C6D014;
extern float g_00C6D010;

struct Rva0056AB35Helper {
	char m_pad[0x20];
	unsigned char m_20;
};

class Rva0056ACC5 {
	char m_pad[0x10];
public:
	Rva0056AB35Helper *m_10;
	int m_14;
	unsigned char m_18;
	void rva0056AB35(int arg);
};

// ?rva0056AB35@Rva0056ACC5@@QAEXH@Z present-unmatched
void Rva0056ACC5::rva0056AB35(int arg)
{
	if (m_14 != arg)
		return;
	m_10->m_20 = 0;
	{
	Rva004E57E6Pair tmp = { g_00C6D014, g_00C6D010 };
	((Rva0029B187 *)TheInGameUI)->rva0029B187(&tmp, g_00C6D018);
	}
	m_18 = 1;
}
