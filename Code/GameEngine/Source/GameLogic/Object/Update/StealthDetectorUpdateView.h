#pragma once

// Partial receiver for the existing BFME 2 update, transfer and pool-key
// bodies. The measured data/object pointers are +4/+8, other interface +0xC
// and update interface +0x10. No constructor or vtable is defined here;
// the complete retail hierarchy and trailing UpdateModule fields are omitted.
class Object;
class Xfer;
struct StealthDetectorUpdateModuleData;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1, UPDATE_SLEEP_FOREVER = 0x3fffffff };
enum NameKeyType { NAMEKEY_INVALID = 0 };

class NameKeyGenerator
{
public:
    NameKeyType nameToKey(const char *name);
};
extern NameKeyGenerator *TheNameKeyGenerator;

class DetectorPrimary
{
public:
    virtual void primary();
    virtual void v01();
    virtual void v02();
    virtual void xfer(Xfer *xfer);
    const StealthDetectorUpdateModuleData *m_data;
    Object *m_object;
};
class DetectorOther { public: virtual void other(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class UpdateModule : public DetectorPrimary, public DetectorOther, public UpdateModuleInterface
{
public:
    virtual void xfer(Xfer *xfer);
};
class StealthDetectorUpdate : public UpdateModule
{
public:
    virtual UpdateSleepTime update();
    virtual NameKeyType getModuleNameKey() const;
    Object *getObject() const { return m_object; }
protected:
    virtual void xfer(Xfer *xfer);
};
