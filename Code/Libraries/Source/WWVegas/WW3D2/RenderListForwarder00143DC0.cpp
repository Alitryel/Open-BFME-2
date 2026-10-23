// cl: /Ireference/shims/bfmepool /DNDEBUG /MD /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/game/Libraries/Source/Compression /Ireference/shims/sweep
// BFME1 a7c38d3b multilist.h forwarding semantics; native whole 5B
// thunk at 00143DC0 directly targets the owned GenericMultiListClass member.
// The original derived/template owner is unproven; this view retains the
// real base ABI and makes only an address-qualified forwarding claim.
#include "multilist.h"
class Rva00143DC0ListView : public GenericMultiListClass {
public: bool forward(MultiListObjectClass *object, bool onlyOnce);
};
bool Rva00143DC0ListView::forward(MultiListObjectClass *object, bool onlyOnce) {
 return Internal_Add_Tail(object, onlyOnce);
}
