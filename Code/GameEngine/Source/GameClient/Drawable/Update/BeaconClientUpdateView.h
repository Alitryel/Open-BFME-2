#pragma once

// Accessed receiver prefix shared by the update and cached-name-key bodies.
// These units emit no receiver constructor or vtable; the full inherited
// virtual interface remains unreconstructed.
class Drawable;
struct BeaconClientUpdateModuleData;

enum ParticleSystemID
{
    INVALID_PARTICLE_SYSTEM_ID = 0
};

enum NameKeyType
{
    NK_UNKNOWN = 0
};

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};

extern NameKeyGenerator *TheNameKeyGenerator;

class BeaconClientUpdate
{
public:
    virtual void clientUpdate();
    virtual NameKeyType getModuleNameKey() const;
    void hideBeacon();
    const BeaconClientUpdateModuleData *data;
    Drawable *draw;
    ParticleSystemID id;
    unsigned lastRadarPulse;
};
