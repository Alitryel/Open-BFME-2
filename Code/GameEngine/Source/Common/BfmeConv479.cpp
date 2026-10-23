// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv479.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBLA@BfmeThingBLA@@QAEXPAX_N@Z 0x0028AA55 (24B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
void __stdcall bfmeDoBLA(int what);

class BfmeThingBLA
{
public:
	void bfmeGoBLA(void *what, bool flag);
	unsigned char m_bfmeHead[0x18];
	void *m_bfmeWhat;
};

void BfmeThingBLA::bfmeGoBLA(void *what, bool flag)
{
	m_bfmeWhat = what;
	if (flag)
		bfmeDoBLA(1);
}

// Retail 0x002C94F5, the address this body's call reads off its call site, is
// the ledger's ?cacheStatus@Weapon@@QBEXW4WeaponStatus@@@Z row. The donor's own
// name for that callee is kept (its __stdcall view is what the verified call
// bytes use) and bound to the rowed owner, so one address keeps one definition.
#pragma comment(linker, "/alternatename:?bfmeDoBLA@@YGXH@Z=?cacheStatus@Weapon@@QBEXW4WeaponStatus@@@Z")
