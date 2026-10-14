// ?RegisterCreateAHeroAtRva0021D517@@YAXPAVCreateAHeroData@@@Z
// partial score=0.99 date=2026-10-14
// ?RegisterCreateAHeroAtRva0021D517@@YAXPAVCreateAHeroData@@@Z
// partial score=0.99 date=2026-10-04
// ?RegisterCreateAHeroAtRva0021D517@@YAXPAVCreateAHeroData@@@Z
// cl: /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Retail 49B: search the CreateAHeroData pointer vector at VA DFE358 with the
// rowed STLport find 0x20E873 and append through the folded push_back rowed at
// 0x4DFCB0 only when the pointer is absent. All 48 bytes of code match; the
// sole difference is retail's one-byte nop at 0x21D546 before the ret, which no
// source shape or /O1../O2 flag combination reproduces (it is an alignment fill,
// like the loop-alignment nops banked elsewhere, and no matched ledger row ends
// in a genuine nop;ret).
#include <vector>
#include <algorithm>
class CreateAHeroData;
namespace _STL {
template<> void vector<CreateAHeroData*>::push_back(CreateAHeroData* const&);
template<> CreateAHeroData** vector<CreateAHeroData*>::erase(CreateAHeroData**);
template<> CreateAHeroData** find(CreateAHeroData**,CreateAHeroData**,CreateAHeroData* const&);
}
extern _STL::vector<CreateAHeroData*> g_CreateAHeroRegistry;
void RegisterCreateAHeroAtRva0021D517(CreateAHeroData* hero) {
    _STL::vector<CreateAHeroData*>::iterator finish = g_CreateAHeroRegistry.end();
    if (_STL::find(g_CreateAHeroRegistry.begin(),finish,hero)==finish)
        g_CreateAHeroRegistry.push_back(hero);
}
