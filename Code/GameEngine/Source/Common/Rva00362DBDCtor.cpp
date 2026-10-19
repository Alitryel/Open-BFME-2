#include "../GameClient/BuffManager.h"
class ModuleData;
// cl: /DNDEBUG /MD /GX
// BuffManager constructor 362DBD: native Snapshot table C17088 and nine
// complete BuffInstance elements at08, then GameClient registration.


class Rva00239FE4 {
public:
    void rva00239FE4(const ModuleData *p);
};
class ClientFrameSubsystem;
class ClientFrameSubsystem; extern class GameClient *TheGameClient;

BuffManager::BuffManager(int v) : m_drawable((void *)v)
{
    ((Rva00239FE4 *)((ClientFrameSubsystem *)TheGameClient))->rva00239FE4((const ModuleData *)this);
}
