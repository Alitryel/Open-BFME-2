#ifndef BFME_LIVING_WORLD_EYE_TOWER_VIEW_H
#define BFME_LIVING_WORLD_EYE_TOWER_VIEW_H

#include "../../../../Libraries/Include/Lib/Coord3D.h"

class U4Target0060C2C0;
class Rva003F936EHost;
struct EyeTowerPair {
    EyeTowerPair(float x, float y) : first(x), second(y) {}
    ~EyeTowerPair() {}
    float first;
    float second;
};

// Scoped receiver view for the matched transform, frame and state bodies.
// Retail proves distinct host fields at 0x18, 0x1C and 0x20. processFrame
// copies 0x5C/0x60 into the first two words of the transform's eye at 0x24.
// State bodies prove the vector at 0x3C and fields at 0x48 through 0x70.
// Original member names and the rest of the receiver remain unknown.
class LivingWorldEyeTower
{
private:
    void rva003F962F();
    void rva003F935A(U4Target0060C2C0 *target, void *payload);
    void processFrame();
    void rva003F936E(Rva003F936EHost *, float *);
    void *getPair();
    void processItems();
    void beginState();
    void updateState();
public:
    void rva003F9B5A();
private:
    char m_pad00[0x18];
    U4Target0060C2C0 *m_firstHost;
    Rva003F936EHost *m_frameFirstHost; // +0x1C
    U4Target0060C2C0 *m_secondHost;
    Coord3D m_eye; // +0x24
    Coord3D m_target; // +0x30
    EyeTowerPair *m_begin; // +0x3C
    EyeTowerPair *m_end;
    EyeTowerPair *m_capacity;
public:
    unsigned int m_state; // +0x48
    EyeTowerPair m_to; // +0x4C
    EyeTowerPair m_from; // +0x54
    EyeTowerPair m_current; // +0x5C
    float m_rate64;
    float m_progress68;
    float m_rate6C;
    float m_progress70;
};

#endif
