// cl: /O1
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv667.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ?bfmeGoDAB@@YAXXZ 0x007B7ACD (20B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).

// Retail's atexit cleanup destroys WaterSettings, an array of six WaterSetting
// objects of element size 0x7C (defined by WaterSettingsArray.cpp).
class WaterSetting;
extern WaterSetting WaterSettings[];

// C++ cannot name a destructor's address, so the rowed WaterSetting destructor
// (WaterSettingCtor.cpp) is declared by its symbol.
extern "C" void __identifier("??1WaterSetting@@UAE@XZ")(void *what);

void __stdcall bfmeRegisterDAB(void *obj, unsigned int size, unsigned int count, void (*dtor)(void *));

void bfmeGoDAB()
{
	bfmeRegisterDAB(WaterSettings, 0x7c, 6, __identifier("??1WaterSetting@@UAE@XZ"));
}
