// TU-scoped LifetimeUpdateModuleData prefix, shared by its constructor and
// update. Native stores and accesses establish the fields at +0x08..+0x14.
// The existing explicit vtable store stays in the constructor; this is an
// accessed prefix, not a canonical class or a recovered original header.
#ifndef BFME_LIFETIME_UPDATE_MODULE_DATA_VIEW_H
#define BFME_LIFETIME_UPDATE_MODULE_DATA_VIEW_H

class LifetimeUpdateModuleData
{
public:
    LifetimeUpdateModuleData();

private:
    const char *m_vtable;
    int m_unmodelled_04;

public:
    unsigned int m_minFrames; // +0x08
    unsigned int m_maxFrames; // +0x0C
    bool m_startDisabled; // +0x10
    bool m_creditKiller; // +0x11
    int m_deathType; // +0x14
};

#endif
