// cl: /DNDEBUG /MD /GX
// Retail 362D6C (81B) and 362CF2 (51B), including exact EH cleanup.
// Snapshot restores BBB554; embedded material at30 is a complete14B object.
#include "../GameClient/BuffManager.h"

class Rva00419BA5 { public: void rva00419BA5(); };
// Existing rowed release helper at362C9F; its complete class is unrecovered.
class Rva0040AD80ReferenceState { public: void releaseReferences(); };
BuffInstance::~BuffInstance()
{
    if (m_glow) { m_glow->rva00419BA5(); m_glow=0; }
    m_thing=0;
}
GlowMaterial::~GlowMaterial()
{
    reinterpret_cast<Rva0040AD80ReferenceState *>(this)->releaseReferences();
}
void BuffInstance::LoadPostProcess() {}
