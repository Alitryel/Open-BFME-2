// cl: /DNDEBUG /MD
// Object::isCurWeaponLocked, called by Weapon::isAmmoReady (retail
// 0x002CC3FF). ZH Object.h: m_weaponSet.isCurWeaponLocked(), i.e.
// m_curWeaponLockedStatus != NOT_LOCKED; the WeaponSet sits at +0x330 and its
// lock status at +0x24 (WeaponSetSetWeaponLock.cpp). BFME 1's
// Object::isCurWeaponLocked (0x001BE370) is the same 17-byte body at its own
// WeaponSet offset. The +0x24 getter stays an opaque pin for this caller: its
// four-byte body is also used by NetWrapperCommandMsg::getDataOffset, which
// does not make the Object-side subobject a network command.
typedef bool Bool;

// Host of the +0x24 fetch at retail 0x00091A56. One ledger body is retained
// under the target-supported network identity; this alias preserves the
// independently observed Object-side call without claiming a shared owner.
class Rva00091A56DwordField
{
public:
    int get() const;
};

class Object
{
public:
    Bool isCurWeaponLocked() const;
};

// ?isCurWeaponLocked@Object@@QBE_NXZ @0x0028AF65 (17B)
Bool Object::isCurWeaponLocked() const
{
    const Rva00091A56DwordField *slot =
        (const Rva00091A56DwordField *)((const char *)this + 0x330);
    return (Bool)slot->get();
}
