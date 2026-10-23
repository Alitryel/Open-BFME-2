// BfmeThingDXB::bfmeGoDXB, retail 0x00628D20 (22B).
// Ported from Open-BFME-1 Code/GameEngine/Source/Common/BfmeConv793.cpp
// (BFME1 0x009F69D3). Only the placed go is defined here; the donor's
// DXC/DXD/DXE/DXF helpers stay out, so the unmatched-definition gate passes.
// Retail inits the CS struct through the dllimport slot, then tail-jumps to
// the pinned sub call.

struct BfmeCsDXB
{
	unsigned char m_bfmeHead[0x18];
};

class BfmeSubDXB
{
public:
	void bfmeCallDXB();
};

// Retail's import slot 0xBBA158 is kernel32!DeleteCriticalSection, not a game
// helper: the donor's bfmeInitDXB alias is renamed to the real import. The
// 0x18-byte CS struct is a CRITICAL_SECTION; this go is its teardown path.
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(void *cs);

struct BfmeThingDXB
{
	void bfmeGoDXB();
	unsigned char m_bfmeHead[0x18];
	BfmeCsDXB m_bfmeCs;
	BfmeSubDXB m_bfmeSub;
};

// ?bfmeGoDXB@BfmeThingDXB@@QAEXXZ, retail 0x00628D20 (22B).
void BfmeThingDXB::bfmeGoDXB()
{
	DeleteCriticalSection(&m_bfmeCs);
	m_bfmeSub.bfmeCallDXB();
}

// The donor's bfmeQueryDXE import slot is oleaut32!VariantClear in game.dat;
// the failure helper resolves through the ledger pin at 0x00654B20.
extern "C" __declspec(dllimport) int __stdcall VariantClear(void *what);
// The 16-byte x86 VARIANTARG passed to VariantClear: VT_ERROR (0x000A) with
// error value 0x80020004, matching retail .data at VA 0x00DD7F18.
unsigned char g_bfmeArgDXE[16] = {
	0x0A, 0, 0, 0, 0, 0, 0, 0,
	0x04, 0, 0x02, 0x80, 0, 0, 0, 0,
};
void __stdcall bfmeFailDXE(int code);

// ?bfmeGoDXE@@YAXXZ, retail 0x007B9B40 (22B).
void bfmeGoDXE()
{
	int r = VariantClear(g_bfmeArgDXE);
	if (r < 0)
		bfmeFailDXE(r);
}

// Retail's call sites in this unit's matched rows land on bodies rowed under
// other spellings at the same addresses (same ABI). Bind the spellings used here.
#pragma comment(linker, "/alternatename:?bfmeFailDXE@@YGXH@Z=?_com_issue_error@@YGXJ@Z")
