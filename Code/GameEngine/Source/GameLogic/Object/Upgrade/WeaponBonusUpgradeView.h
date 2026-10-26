#ifndef WEAPON_BONUS_UPGRADE_VIEW_H
#define WEAPON_BONUS_UPGRADE_VIEW_H

// Partial receiver for the pool key and constructor. The constructor measures
// the primary pointer and secondary stores at +0x0C, +0x10 and +0x18.
// No complete vtable order or semantics for the intervening storage is claimed.
// novtable leaves the existing explicit retail pointer stores in the constructor;
// these declarations do not emit replacement vtables.
enum NameKeyType { NK_UNKNOWN = 0 };
class Thing;
class ModuleData;

class __declspec(novtable) UpgradeModule
{
public:
    UpgradeModule(Thing *thing, const ModuleData *moduleData);
    virtual ~UpgradeModule();
protected:
    unsigned char m_storage04[8];
    const void *m_p0C;
    const void *m_p10;
    unsigned char m_pad14[4];
};

class __declspec(novtable) WeaponBonusUpgrade : public UpgradeModule
{
public:
    WeaponBonusUpgrade(Thing *thing, const ModuleData *moduleData);
    virtual NameKeyType getModuleNameKey() const;
private:
    const void *m_p18;
};
#endif
