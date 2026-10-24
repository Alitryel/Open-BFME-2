#pragma once
// Retail UpgradeCenter table 0x007FABB8 and fields used by its constructor and destructor.
typedef bool Bool;
// The native reload overrides give names to the shared header's provisional slots.
#define vslot04 attemptReload
#define vslot05 attemptRefresh
#include "../subsystem_bfme2/subsystem_interface.h"
#undef vslot04
#undef vslot05

class UpgradeTemplate;
enum ObjectID { INVALID_ID = 0 };

class UpgradeCenter : public SubsystemInterface
{
public:
    UpgradeCenter();
    virtual ~UpgradeCenter();
    virtual void init();
    virtual bool attemptReload(int);
    virtual bool attemptRefresh();
    virtual void reset();
    virtual void update() {}
protected:
    UpgradeTemplate *m_upgradeList;
    int m_nextTemplateMaskBit;
    bool m_buttonImagesCached;
    _STL::vector<ObjectID> m_extra;
};
