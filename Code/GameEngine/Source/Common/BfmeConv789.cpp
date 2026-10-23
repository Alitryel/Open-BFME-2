struct BfmeCsDWA
//
// Bodies ported from Open-BFME-1's GameEngine/Source/Common/BfmeConv789.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus
// /O1). Compiled that way each body below places uniquely on unclaimed
// game.dat .text by masked whole-.text search, and ./build.sh reproduces it
// byte for byte: BfmeThingDWC::bfmeGoDWC 0x000387D0 (27B). Callee addresses
// are read off retail's call sites (reverse/symbols.csv). Only the placed
// bodies are carried; the donor's other definitions are omitted.
{
	unsigned char m_bfmeHead[0x18];
};

extern "C" __declspec(dllimport) void __stdcall EnterCriticalSection(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall InterlockedIncrement(BfmeCsDWA *cs);
extern "C" __declspec(dllimport) void __stdcall DeleteCriticalSection(BfmeCsDWA *cs);

struct BfmeThingDWB
{
	void bfmeGoDWB();
	void bfmeOneDWB();
	unsigned char m_bfmeHead[4];
	BfmeCsDWA m_bfmeCs;
};


extern BfmeCsDWA g_bfmeCsDWC;

struct BfmeThingDWC
{
	bool bfmeGoDWC();
	unsigned char m_bfmeHead[0x9df8];
	BfmeCsDWA m_bfmeCs;
};

bool BfmeThingDWC::bfmeGoDWC()
{
	InterlockedIncrement(&m_bfmeCs);
	EnterCriticalSection(&g_bfmeCsDWC);
	return false;
}

// The global(s) below are defined elsewhere under another name at the same
// address (the census owner of that DIR32 target); bind this unit's spelling.
#pragma comment(linker, "/alternatename:?g_bfmeCsDWC@@3UBfmeCsDWA@@A=?g_bfmeCsDWC@@3UDebugCriticalSection@@A")
