// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv507.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoBPC@@YGXPAVBfmeThingBPC@@PAX@Z 0x0047DB95 (27B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
class BfmeThingBPC
{
public:
	void bfmeSetBPC(int what);
};

void __stdcall bfmeDoBPC(BfmeThingBPC *one, void *two);

void __stdcall bfmeGoBPC(BfmeThingBPC *one, void *two)
{
	bfmeDoBPC(one, two);
	one->bfmeSetBPC(3);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x00291C9B reads ?setDisabled@Object@@QAEXW4DisabledType@@@Z
#pragma comment(linker, "/alternatename:?bfmeSetBPC@BfmeThingBPC@@QAEXH@Z=?setDisabled@Object@@QAEXW4DisabledType@@@Z")
//   0x00478C2C reads ?onContaining@GarrisonContain@@UAEXPAVObject@@_N@Z
#pragma comment(linker, "/alternatename:?bfmeDoBPC@@YGXPAVBfmeThingBPC@@PAX@Z=?onContaining@GarrisonContain@@UAEXPAVObject@@_N@Z")
