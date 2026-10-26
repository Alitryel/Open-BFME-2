// cl: /O1 /Ireference/shims/moduledata /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// AudioManager's constructor (retail 0x0005107D, 32 bytes): the base
// constructor and the three vptr stores that follow it:
//
//     push esi / mov esi,ecx / call <REL32>
//     mov dword ptr [esi+0xC],<SNAPSHOT-VFTABLE>
//     mov dword ptr [esi],<OWN-VFTABLE-FOR-FIRST>
//     mov dword ptr [esi+0xC],<OWN-VFTABLE-FOR-SECOND>
//     mov eax,esi / pop esi / ret
//
// The called constructor is retail 0x001B4E63, the rowed SubsystemInterface
// constructor, and the slot at +0xC is the Snapshot base. This is the view
// MilesAudioManager.cpp already uses for MilesAudioManager's base: the
// abstract Rva005109D (SubsystemInterface + Snapshot, destructor rowed at
// 0x0005109D), with AudioManager derived from it. Declaring the same view
// here makes both units emit the same implicit AudioManager destructor.
// Retail stores no Rva005109D vptrs in the constructor, so the abstract base
// is novtable, as in Rva005109DDtor.cpp.
typedef bool Bool;
#include "subsystem_interface.h"
#include "Common/Snapshot.h"

class __declspec(novtable) Rva005109D : public SubsystemInterface, public Snapshot {
public:
    __forceinline Rva005109D() {}
    virtual ~Rva005109D();
};
class AudioManager : public Rva005109D {
public:
    AudioManager();
};

// @??0AudioManager@@QAE@XZ 0x0005107D
AudioManager::AudioManager()
{
}
