// cl: /O1 /DNDEBUG /MD /arch:SSE
//
// ?triggerAbilityEffect@WeaponFireSpecialAbilityUpdate@@UAEXXZ, retail
// 0x00492A72, 377 bytes: slot 17 of WeaponFireSpecialAbilityUpdate's primary
// vtable 0x00C4E090 (ctors 0x0049257C, 0x00492736), the override of the
// SpecialAbilityUpdate slot-17 base 0x0045108D (triggerAbilityEffect), as in
// ScaleWallSpecialAbilityUpdateSlot17.cpp. BFME 1 names the same slot
// WeaponFireSpecialAbilityUpdate::triggerAbilityEffect; the WB twin 0x011E40A0
// gives the statement shape. Cools the Object's +0x240 FiringTracker
// (0x004DEC88), then, unless the Object's template has bit 5 of +0x115 and
// the module data's +0xC4 flag, looks up the target (+0x40), redirecting
// through the target's +0x250 interface (0x0028C197, its slot 68) when the
// target's template has the same bit; with a ready Weapon (+0x88) it stamps
// the Object's ID into the Weapon's +0x08 and fires at the target
// (0x002CE6C5) or, with no target, forces a shot at +0x44 (the Object's own
// position when that is zero or the data's +0xD8 flag is set), reports it
// to the tracker (0x004DEECB) and hands the Object (0x002900E0) the frame
// plus the data's +0xD4. Then the base, and 1.0f to slot 15 of the module
// 0x0044E633 finds.
//
// The zero position is a Coord3D(0, 0, 0) temporary inside the && of the
// use-target test: retail's Coord3D has an empty user destructor, so cl
// keeps a construction flag for it, and its zero store at entry
// (`and [ebp-8], 0`) survives in the slot the module data later spills to.
typedef bool Bool;
typedef float Real;
#define COORD3D_VIEW_DTOR
#include "../../../../../Libraries/Include/Lib/Coord3DCtorView.h"
#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

struct Rva00492A72Template
{
	unsigned char m_pad000[0x115];
	unsigned char m_115; // +0x115
};

class Weapon;
class WeaponFireSpecialAbilityUpdate;

class FiringTracker
{
	friend class WeaponFireSpecialAbilityUpdate;
	void coolDown(Bool flag);
public:
	void shotFired(const Weapon *weapon, ObjectID victim, const Coord3D *pos, Bool flag);
};

class Rva00492A72Redirect
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16(); virtual void s17(); virtual void s18(); virtual void s19();
	virtual void s20(); virtual void s21(); virtual void s22(); virtual void s23();
	virtual void s24(); virtual void s25(); virtual void s26(); virtual void s27();
	virtual void s28(); virtual void s29(); virtual void s30(); virtual void s31();
	virtual void s32(); virtual void s33(); virtual void s34(); virtual void s35();
	virtual void s36(); virtual void s37(); virtual void s38(); virtual void s39();
	virtual void s40(); virtual void s41(); virtual void s42(); virtual void s43();
	virtual void s44(); virtual void s45(); virtual void s46(); virtual void s47();
	virtual void s48(); virtual void s49(); virtual void s50(); virtual void s51();
	virtual void s52(); virtual void s53(); virtual void s54(); virtual void s55();
	virtual void s56(); virtual void s57(); virtual void s58(); virtual void s59();
	virtual void s60(); virtual void s61(); virtual void s62(); virtual void s63();
	virtual void s64(); virtual void s65(); virtual void s66(); virtual void s67();
	virtual Object *s68();
};

class Object
{
public:
	void *rva0028C197() const;
	void rva002900E0(int frame);
	ObjectID getID() const { return m_74; }
	unsigned char m_pad000[0x04];
	const Rva00492A72Template *m_template; // +0x04
	unsigned char m_pad008[0x38 - 0x08];
	Coord3D m_38; // +0x38
	unsigned char m_pad044[0x74 - 0x44];
	ObjectID m_74; // +0x74
	unsigned char m_pad078[0x240 - 0x78];
	FiringTracker *m_240; // +0x240
};

class Weapon
{
public:
	WeaponStatus getStatus() const;
	Bool rva002CE6C5(const Object *source, int victimID, const Object *victim, int *shots);
	Object *forceFireWeapon(const Object *source, const Coord3D *pos);
	unsigned char m_pad00[0x08];
	ObjectID m_08; // +0x08
};

struct WeaponFireSpecialAbilityUpdateModuleData
{
	unsigned char m_pad00[0xC4];
	Bool m_C4; // +0xC4
	unsigned char m_padC5[0xD4 - 0xC5];
	int m_busyForDuration; // +0xD4
	Bool m_needLivingTargets; // +0xD8
};

class SpecialPowerModuleInterface
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14();
	virtual void rva15(Real value);
};

class Rva0044E633
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05(); virtual void s06(); virtual void s07();
	virtual void s08(); virtual void s09(); virtual void s10(); virtual void s11();
	virtual void s12(); virtual void s13(); virtual void s14(); virtual void s15();
	virtual void s16();
	void *rva0044E633();
};

class SpecialAbilityUpdate : public Rva0044E633
{
public:
	virtual void triggerAbilityEffect();
protected:
	const WeaponFireSpecialAbilityUpdateModuleData *m_moduleData; // +0x04
	Object *m_object; // +0x08
	unsigned char m_pad0C[0x40 - 0x0C];
	ObjectID m_targetID; // +0x40
	Coord3D m_targetPos; // +0x44
	unsigned char m_pad50[0x88 - 0x50];
};

class WeaponFireSpecialAbilityUpdate : public SpecialAbilityUpdate
{
public:
	virtual void triggerAbilityEffect();
private:
	Weapon *m_88; // +0x88
};

void WeaponFireSpecialAbilityUpdate::triggerAbilityEffect()
{
	const WeaponFireSpecialAbilityUpdateModuleData *data = m_moduleData;
	Object *obj = m_object;
	if (obj->m_240)
		obj->m_240->coolDown(true);
	if (!(obj->m_template->m_115 & 0x20) || !data->m_C4)
	{
		Object *target = TheGameLogic->findObjectByID(m_targetID);
		ObjectID targetID = target ? target->getID() : INVALID_OBJECT_ID;
		if (target && (target->m_template->m_115 & 0x20))
		{
			Rva00492A72Redirect *redirect = (Rva00492A72Redirect *)target->rva0028C197();
			if (redirect)
			{
				Object *other = redirect->s68();
				if (other)
				{
					target = other;
					targetID = other->getID();
				}
			}
		}
		if (m_88 && m_88->getStatus() == READY_TO_FIRE)
		{
			m_88->m_08 = obj->getID();
			if (target)
			{
				m_88->rva002CE6C5(obj, targetID, target, 0);
				if (obj->m_240)
					obj->m_240->shotFired(m_88, targetID, 0, true);
			}
			else
			{
				Bool useTargetPos = !(m_targetPos == Coord3D(0.0f, 0.0f, 0.0f)) && !data->m_needLivingTargets;
				const Coord3D *pos = useTargetPos ? &m_targetPos : &obj->m_38;
				m_88->forceFireWeapon(obj, pos);
				if (obj->m_240)
					obj->m_240->shotFired(m_88, INVALID_OBJECT_ID, pos, true);
			}
			obj->rva002900E0(TheGameLogic->getFrame() + m_moduleData->m_busyForDuration);
		}
	}
	SpecialAbilityUpdate::triggerAbilityEffect();
	SpecialPowerModuleInterface *spm = (SpecialPowerModuleInterface *)rva0044E633();
	if (spm)
		spm->rva15(1.0f);
}
