// cl: /ICode/GameEngine/Source/Common /GX- /O1 /G7 /arch:SSE
// BFME1 9cbfb551fe ExperienceTracker.cpp setExperienceAndLevel supplies the
// sink-forwarding semantics. Native BFME2 0039B3D1..0039B433 RET8 uses float
// experience and the existing level-handle update providers.
#include "GameLogicObjectLookupView.h"
extern GameLogic *TheGameLogic;
class ExperienceTracker { public: int rva0039AC23(bool); };
class BfmeThingEFC {
public:
    void rva0039B1F9(void);
    void bfmeUpdate(int);
    char pad[0x0C]; int level;
};
struct ExperienceParentView { char pad[0x5E7]; bool trainable; };
// The ExperienceTracker receiver under its call-view name; ExperienceTracker.cpp
// reads the level at +0x0C through the same view (rva0039B28F).
class Rva003BD306Target {
public:
    char pad0[4]; ExperienceParentView *parent;
    char pad08[4]; int m_level; float experience;
    char pad14[0x2C-0x14]; BfmeThingEFC *handle;
    char pad30[8]; ObjectID sink; bool enable;
    void rva0039B3D1(float value,bool feedback);
};
struct ObjectExperienceView { char pad[0x264]; Rva003BD306Target *tracker; };
void Rva003BD306Target::rva0039B3D1(float value,bool feedback)
{
    if (sink!=INVALID_OBJECT_ID) {
        Object *object=TheGameLogic->findObjectByID(sink);
        if (object) {
            reinterpret_cast<ObjectExperienceView *>(object)->tracker->rva0039B3D1(value,feedback);
            return;
        }
    }
    if (!parent->trainable) return;
    experience=value;
    int level=reinterpret_cast<ExperienceTracker *>(this)->rva0039AC23(enable);
    if (feedback && level && level!=handle->level) handle->bfmeUpdate(level);
}
