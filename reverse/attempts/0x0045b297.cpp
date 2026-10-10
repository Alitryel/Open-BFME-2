// ?update@AimWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.9 date=2026-10-10
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX
//
// ?update@AimWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ, retail 0x0045B297,
// 516 bytes. Interface-adjusted receiver: the matched ctor 0x0045B226
// installs the UpdateModuleInterface table 0x00C418C0 at module+0x10 and that
// table's slot 0 is this body, so the scheduler enters with ECX = module+0x10.
// The Object pointer is [this-8], the module data is [this-0xC] and the aiming
// byte is [this+0x10] (== module+0x20, the byte the ctor clears).
//
// Structural class views follow existing sibling recoveries; the candidate
// uses canonical Coord3D and existing callee providers. No new pin is proposed.
// These partial class views reproduce the observed receiver layout; they do
// not establish full vtables. Provider/COMDAT integration remains unverified.
// UpdateModule is 0x20 bytes, so AimWeaponBehavior::m_aiming lands on
// module+0x20 == interface+0x10.
//
// Native trace and tested differences are summarized in the committed support
// record; original ignored worker evidence contains errors noted there.
// Donor (semantic guide only, never a BFME 2 identity or byte proof):
// Open-BFME-1 fcbee55c91,
// game/GameEngine/Source/GameLogic/Object/Behavior/AimWeaponBehaviorUpdate.cpp.
// Target offsets, bits and call ABI come from BFME 2 retail and existing
// providers. Original names and complete class/vtable identities are uncertain.
// Corrected evidence: reverse/attempt_support/0x0045b297/README.md.

#include <math.h>

#include "../../Code/Libraries/Include/Lib/Coord3D.h"

typedef int Int;
typedef bool Bool;
typedef unsigned int UnsignedInt;
typedef float Real;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3fffffff
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

// The five model conditions this body manipulates. Native facts only: the
// five-bit mask constructor is handed 0xB5 0xB6 0xB4 0xB3 0xB2, and the pitch
// path tests/ors word 5 of the 0x4C-byte condition array (word 5 starts at
// Object+0x120) with 0x40000 / 0x80000 / 0x100000, which are word-5 bits
// 18 / 19 / 20. The names are unknown, so the numeric spellings stand.
enum AimConditionIndex
{
	AIM_CONDITION_178 = 0xB2, // word 5 bit 18
	AIM_CONDITION_179 = 0xB3, // word 5 bit 19
	AIM_CONDITION_180 = 0xB4, // word 5 bit 20
	AIM_CONDITION_181 = 0xB5, // word 5 bit 21
	AIM_CONDITION_182 = 0xB6  // word 5 bit 22
};

// Word-5 masks for the three conditions the pitch path chooses between. These
// are masks, not bit indices: native carries the selected mask in EAX through
// the single join at 0x0045B3C5 and does one `test [esi+0x120], eax` /
// `or [esi+0x120], eax` pair there.
// Selected constant masks reconstruct the native common join; this does not
// identify the original API or rule out an optimized constant-index helper.
enum AimConditionMask
{
	AIM_MASK_178 = 0x40000u,
	AIM_MASK_179 = 0x80000u,
	AIM_MASK_180 = 0x100000u
};

class Drawable
{
public:
	void rva00274176(bool immediate); // rowed 0x00274176
};

// Thing::getDrawable, rowed at 0x005508E2 (7 bytes, ICF-folded with the
// BuildListInfo getter). Returns the pointer at Thing+0x84.
class Thing
{
public:
	Drawable *getDrawable() const;
};

// AIUpdateInterface's primary table. Only slot 111 is called; the 111-slot
// ladder is the landed ObjectRva0028ACA0.cpp spelling and exists solely so
// `call dword ptr [eax+0x1BC]` lands.
template <int N>
class BfmeVirtualSlots : public BfmeVirtualSlots<N - 1>
{
public:
	virtual void unused(char (*)[N]) = 0;
};
template <>
class BfmeVirtualSlots<0>
{
};

class AIUpdateInterface : public BfmeVirtualSlots<111>
{
public:
	virtual bool rva00262D8F() const; // slot 111 (+0x1BC), rowed 0x00262D8F
};

// The 0x4C-byte (19-word) condition array. The accessors take a word mask
// because that is the only shape that folds to retail's test/or on one word.
class ModelConditionFlags
{
public:
	UnsignedInt testMask(UnsignedInt mask) const { return m_words[5] & mask; }
	void setMask(UnsignedInt mask) { m_words[5] |= mask; }

private:
	UnsignedInt m_words[19];
};

// The rowed one-bit mask constructor 0x0028F59A and the rowed five-bit mask
// constructor 0x000B6253. Both are 0x4C-byte value types with no destructor,
// so the stack temporaries need no cleanup - as in retail.
class Rva0028F59A
{
public:
	Rva0028F59A(Int a, Int bit);
	unsigned int m_bits[19];
};

class Rva000B6253
{
public:
	Rva000B6253 *rva000B6253(Int a, unsigned int b0, unsigned int b1, unsigned int b2,
		unsigned int b3, unsigned int b4);
	unsigned int m_bits[19];
};

class Object;
class AimWeaponBehavior;

class WeaponTemplate
{
public:
	unsigned char m_pad000[0x156];
	unsigned char m_flag156; // +0x156, one-byte weapon-template flag
};

class Weapon
{
public:
	const WeaponTemplate *getTemplate() const { return m_template; }
	bool rva002C9586(); // rowed 0x002C9586

private:
	unsigned char m_pad00[4];
	const WeaponTemplate *m_template; // +0x04
};

class Object : public Thing
{
	friend class AimWeaponBehavior;

public:
	const Weapon *getCurrentWeapon(WeaponSlotType *slot) const; // real owner 0x0028AEBD
	void rva0028AE6D();                              // rowed 0x0028AE6D
	// rowed 0x0028CFB2: clears the first mask's conditions, sets the second's
	void rva0028CFB2(const int *clearMask, const int *setMask);
	// rowed 0x001E42F2: clears one mask, then notifies
	void rva001E42F2(const int *mask);

	__forceinline void setModelConditionMask(UnsignedInt mask)
	{
		if (m_modelConditionFlags.testMask(mask) == 0)
		{
			m_modelConditionFlags.setMask(mask);
			rva0028AE6D();
		}
	}

private:
	unsigned char m_pad000[0x38];
	Coord3D m_position; // +0x38
	unsigned char m_pad044[0x84 - 0x44];
	Drawable *m_drawable; // +0x84
	unsigned char m_pad088[0x10C - 0x88];
	ModelConditionFlags m_modelConditionFlags; // +0x10C (0x4C bytes)
	unsigned char m_pad158[0x258 - 0x158];
	AIUpdateInterface *m_ai; // +0x258
	unsigned char m_pad25C[0x38C - 0x25C];
	Coord3D m_lastTargetPos; // +0x38C
};

// Field names and offsets from the matched AimWeaponBehaviorModuleData ctor
// 0x0045B1DD and its parse table 0x00C41948.
class AimWeaponBehaviorModuleData
{
public:
	unsigned char m_pad000[8];
	Real m_aimLowThreshold;  // +0x08 (pool default -0.05)
	Real m_aimHighThreshold; // +0x0C (pool default +0.05)
	Real m_aimNearDistance;  // +0x10 (pool default 0)
	Real m_aimFarDistance;   // +0x14 (pool default FLT_MAX)
};

class ModuleData;

class ObjectModule
{
public:
	virtual ~ObjectModule();

protected:
	const ModuleData *getModuleData() const { return m_moduleData; }
	Object *getObject() const { return m_object; }

private:
	const ModuleData *m_moduleData; // +0x04
	Object *m_object;               // +0x08
};

class BehaviorModuleInterface
{
public:
	virtual void behaviorModuleInterfaceSlot();
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update() = 0;
};

class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
private:
	UnsignedInt m_nextCallFrameAndPhase; // +0x14
	Int m_indexInLogic;                  // +0x18
	Int m_reserved;                      // +0x1C
};

class AimWeaponBehavior : public UpdateModule
{
public:
	virtual UpdateSleepTime update();

private:
	Bool m_aiming; // module+0x20 == interface+0x10
};

// ?update@AimWeaponBehavior@@UAE?AW4UpdateSleepTime@@XZ @0x0045B297
UpdateSleepTime AimWeaponBehavior::update()
{
	Object *object = getObject();
	AIUpdateInterface *ai = object->m_ai;
	Drawable *drawable = object->getDrawable();
	// Zero suppresses the optional OUT-slot write; the getter selects the current weapon.
	Weapon *weapon = const_cast<Weapon *>(object->getCurrentWeapon(0));

	if (ai != 0 && drawable != 0 && weapon != 0)
	{
		Bool conditionsChanged = false;
		Bool aiming = ai->rva00262D8F();
		aiming |= weapon->rva002C9586();

		if (weapon->getTemplate()->m_flag156 != 0 && aiming)
		{
			const Coord3D *target = &object->m_lastTargetPos;
			Coord3D aimPos;
			aimPos.x = target->x;
			aimPos.y = target->y;
			aimPos.z = target->z;
			aimPos.x -= object->m_position.x;
			aimPos.y -= object->m_position.y;
			aimPos.z -= object->m_position.z;

			// Retail multiplies and adds the float operands in x87, then stores
			// the sum as an eight-byte argument to the sqrt import.
			Real horizontal = (Real)sqrt((double)(aimPos.y * aimPos.y + aimPos.x * aimPos.x));
			Real ten = 10.0f;
			Real *chosen = (10.0f > horizontal) ? &ten : &horizontal;
			Real denominator = *chosen;

			const AimWeaponBehaviorModuleData *data =
				(const AimWeaponBehaviorModuleData *)getModuleData();
			Real pitch = aimPos.z / denominator;

			UnsignedInt conditionMask;
			if (pitch > data->m_aimHighThreshold)
				conditionMask = AIM_MASK_178;
			else if (pitch < data->m_aimLowThreshold)
				conditionMask = AIM_MASK_180;
			else
				conditionMask = AIM_MASK_179;

			m_aiming = true;
			object->setModelConditionMask(conditionMask);

			if (denominator < data->m_aimNearDistance)
			{
				m_aiming = true;
				object->rva0028CFB2((const int *)&Rva0028F59A(0, AIM_CONDITION_182),
					(const int *)&Rva0028F59A(0, AIM_CONDITION_181));
			}
			else if (denominator > data->m_aimFarDistance)
			{
				m_aiming = true;
				object->rva0028CFB2((const int *)&Rva0028F59A(0, AIM_CONDITION_181),
					(const int *)&Rva0028F59A(0, AIM_CONDITION_182));
			}
			conditionsChanged = true;
		}

		if (m_aiming && !aiming)
		{
			Rva000B6253 clearMask;
			m_aiming = false;
			object->rva001E42F2((const int *)clearMask.rva000B6253(0, AIM_CONDITION_181,
				AIM_CONDITION_182, AIM_CONDITION_180, AIM_CONDITION_179,
				AIM_CONDITION_178));
			conditionsChanged = true;
		}

		if (conditionsChanged)
			drawable->rva00274176(false);

		return UPDATE_SLEEP_NONE;
	}

	return UPDATE_SLEEP_FOREVER;
}
