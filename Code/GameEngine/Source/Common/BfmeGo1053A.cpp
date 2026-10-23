// Open-BFME5 conversions.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/BfmeConv1053.cpp); trimmed to the single T2
// body the sweep places. The sibling bfmeGo1053E is not placed in game.dat,
// so only the A-block init moves here under its own TU name.

// Native CE33EC..CE3404 is a complete six-slot table. The following bytes
// start an independent string. Use its existing rowed owners, retaining their
// neutral names; the shared slot at 587F40 is already owned by fpos<int>::state.
extern "C" void __identifier("?bfmeDelUNA@BfmeThingUNA@@QAEPAXE@Z")();
extern "C" void __identifier("?state@?$fpos@H@_STL@@QAEXH@Z")();
extern "C" void __identifier("?rva007FA790@Rva007FA6C0@@QAEHI@Z")();
extern "C" void __identifier("?bfmeGoVFA@BfmeThingVFA@@QAEHPAUBfmeRecVFA@@@Z")();
extern "C" void __identifier("?openHost@Rva007FA6C0@@QAEHPAURva007FA6C0Arg@@E@Z")();
extern "C" void __identifier("?bfmeGoTMB@BfmeThingTMB@@QAEXXZ")();
typedef void (*Bfme1053Slot)();
extern "C" Bfme1053Slot const bfmeVft1053A[6] = {
	__identifier("?bfmeDelUNA@BfmeThingUNA@@QAEPAXE@Z"),
	__identifier("?state@?$fpos@H@_STL@@QAEXH@Z"),
	__identifier("?rva007FA790@Rva007FA6C0@@QAEHI@Z"),
	__identifier("?bfmeGoVFA@BfmeThingVFA@@QAEHPAUBfmeRecVFA@@@Z"),
	__identifier("?openHost@Rva007FA6C0@@QAEHPAURva007FA6C0Arg@@E@Z"),
	__identifier("?bfmeGoTMB@BfmeThingTMB@@QAEXXZ")
};
void *bfmeAlloc1053(int n);

class BfmeA1053
{
public:
	BfmeA1053 *bfmeGo1053A(void);

	const void *m_bfmeVfptr;
	int m_bfme04;
	void *m_bfmeBuf;
	int m_bfme0c;
	char m_bfme10;
};

BfmeA1053 *BfmeA1053::bfmeGo1053A(void)
{
	m_bfmeVfptr = bfmeVft1053A;
	m_bfmeBuf = bfmeAlloc1053(0x1000);

	int z = 0;

	m_bfme04 = z;
	m_bfme0c = z;
	m_bfme10 = (char)z;
	return this;
}
