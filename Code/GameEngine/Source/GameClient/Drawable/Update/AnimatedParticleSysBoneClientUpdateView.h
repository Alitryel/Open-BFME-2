#ifndef BFME2_ANIMATED_PARTICLE_SYS_BONE_CLIENT_UPDATE_VIEW_H
#define BFME2_ANIMATED_PARTICLE_SYS_BONE_CLIENT_UPDATE_VIEW_H

// Receiver shared by the matched clientUpdate and pool-key bodies. Retail
// clientUpdate reads the drawable at +8 and increments the word at +0xC.
// These declarations do not model the complete virtual interface or emit a
// vtable; the opaque constructor donor is not reconciled by this view.
class Drawable;

enum NameKeyType
{
    NK_UNKNOWN = 0
};

class AnimatedParticleSysBoneClientUpdate
{
public:
    virtual void clientUpdate();
    virtual NameKeyType getModuleNameKey() const;

private:
    void *moduleData;
    Drawable *drawable;
    unsigned life;
};

#endif
