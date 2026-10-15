// cl: /O1 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// CreateAHeroData pointer registry at VA 0x00DFE358 (target evidence: the
// verified CreateAHeroData copy 0x00409D4D registers its this pointer through
// 0x0021D517; both register 0x0021D517 and unregister 0x0021A624 search the
// vector with the rowed STLport find 0x0020E873).
//
// Both retail bodies keep a one-byte nop between the container call and the
// shared ret; the WorldBuilder debug twin of the register (WB 0xB7E820) has
// the same nop after its push_back, so it is a source-level statement carried
// by both builds (spelled here as the __asm nop WWMath's matrix3d.cpp uses).
#include <vector>
#include <algorithm>

class CreateAHeroData;

extern _STL::vector<CreateAHeroData *> g_CreateAHeroRegistry;

void RegisterCreateAHeroAtRva0021D517(CreateAHeroData *hero)
{
    if (_STL::find(g_CreateAHeroRegistry.begin(), g_CreateAHeroRegistry.end(), hero) == g_CreateAHeroRegistry.end()) {
        g_CreateAHeroRegistry.push_back(hero);
        __asm nop
    }
}
