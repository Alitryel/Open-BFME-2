// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii
// stlport
//
// FireWeaponUpdate (BFME 2): update, its sleep-time helper, xfer and the
// entry builder.
//
// Target facts. The module data (ctor row 0x0048BC03, parse table 0xC4C210)
// holds the FireWeaponNugget list at +0x08 and the HeroModeTrigger,
// ChargingModeTrigger and AliveOnly flags at +0x0C/+0x0D/+0x0E. The module
// (ctor row 0x0048C0C5) keeps a single Weapon at +0x20, a list of per-nugget
// entries at +0x24 (0x18-byte records built by the helper 0x0048BDF8: weapon,
// next fire frame, one-shot flag, offset) and a ready flag at +0x28.
// update is reached through the UpdateModuleInterface at +0x10.
// Zero Hour's FireWeaponUpdate::update fires one weapon when isOkayToFire;
// BFME 2 adds the trigger checks and the nugget list, so the bodies here are
// read from retail, with names from the INI field table.

#include <list>

extern "C" double __cdecl sin(double);
extern "C" double __cdecl cos(double);

// __node_alloc<1,0>::allocate (STLport list/vector node path) otherwise emits a
// per-TU COMDAT that loses to another unit's copy in link order; this explicit
// dllimport+forceinline specialization keeps the body inline and emits none.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__node_alloc<true, 0>::allocate(size_t __n)
{ return (__n > (size_t)_MAX_BYTES) ? __stl_new(__n) : _M_allocate(__n); }
}
#include "ascii_string.h"
// class-gate: allow Coord3D update calls the out-of-line Coord3D::lengthSqr (rowed 0x00065A1A, WB 0x403FBC), absent from the canonical data-only header, and adds through the inline set/add; same three floats
#define CANONICAL_COORD3D_H
struct Coord3D
{
	float x;
	float y;
	float z;

	float lengthSqr() const;
	void set(const Coord3D *a) { x = a->x; y = a->y; z = a->z; }
	void set(float ax, float ay, float az) { x = ax; y = ay; z = az; }
	void add(const Coord3D *a) { x += a->x; y += a->y; z += a->z; }
};
#include "../../../../../../reference/shims/moduledata/Common/Snapshot.h"

// _List_iterator comparisons otherwise instantiate the base-class
// operator!= COMDAT (one byte shape per TU flags); exact-match free
// overloads take those calls instead so this TU emits no external copy.
namespace _STL {
template <class _IterTp, class _LeftTraits, class _RightTraits>
static inline bool operator!=(const _List_iterator<_IterTp, _LeftTraits> &a,
                              const _List_iterator<_IterTp, _RightTraits> &b)
{ return a._M_node != b._M_node; }
}

typedef bool Bool;
typedef int Int;
typedef unsigned int UnsignedInt;
typedef float Real;

// A reference maximum that compares with '>': retail keeps the entry's frame
// when it is strictly later, which STLport's max (a < b) spells the other way.
template <class T> inline const T &maxOf(const T &a, const T &b) { return a > b ? a : b; }
// LINK: static overload takes the UnsignedInt maxOf call below (identical
// inlined bytes) so this TU emits no loser ??$maxOf@I COMDAT.
static inline const UnsignedInt &maxOf(const UnsignedInt &a, const UnsignedInt &b) { return a > b ? a : b; }
namespace _STL {
// LINK: static overload takes the UnsignedInt min call below (identical
// inlined bytes to the template) so this TU emits no loser ??$min@I COMDAT.
// Mirrors stlport's `__b < __a ? __b : __a` spelling exactly.
static inline const UnsignedInt &min(const UnsignedInt &a, const UnsignedInt &b)
{ return b < a ? b : a; }
}

class Thing;
class ModuleData;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1,
	UPDATE_SLEEP_FOREVER = 0x3FFFFFFF
};

class AsciiString;
class UnicodeString;
class PooledString;
struct XferUnknown11;
class ICoord3D;
class Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;
class Snapshot;
class WeaponTemplate;

enum ObjectID
{
	INVALID_ID = 0
};

// WWMath Vector3 subset (WB 0x11D15EE.. names Vector3::Rotate_Z, vector3.h):
// sin then cos as statements, then the WW3D two-argument rotate, X first.
struct Vector3
{
	float x, y, z;
	Vector3(float a, float b, float c) : x(a), y(b), z(c) {}
	__forceinline void Rotate_Z(float angle)
	{
		float s = (float)sin((double)angle);
		float c = (float)cos((double)angle);
		Rotate_Z(s, c);
	}
	__forceinline void Rotate_Z(float s_angle, float c_angle)
	{
		float tmp_x = x;
		float tmp_y = y;
		x = c_angle * tmp_x - s_angle * tmp_y;
		y = s_angle * tmp_x + c_angle * tmp_y;
	}
};

class Object
{
public:
	ObjectID getID() const { return m_id; }
	const Coord3D *getPosition() const { return &m_pos; }
	Real getOrientation() const { return m_orientation; }
	// Condition words at +0x11C and +0x124 tested for the hero-mode and
	// charging triggers; bit names unknown.
	Bool testFlag11C4() const { return (m_flags11C >> 4) & 1; }
	Bool testFlag124_28() const { return (m_flags124 >> 28) & 1; }
	Bool isEffectivelyDead() const { return (m_flags438 & 1) != 0; }

private:
	char m_unknown00[0x38];
	Coord3D m_pos; // +0x38
	Real m_orientation; // +0x44
	char m_unknown48[0x74 - 0x48];
	ObjectID m_id; // +0x74
	char m_unknown78[0x11C - 0x78];
	UnsignedInt m_flags11C; // +0x11C
	char m_unknown120[0x124 - 0x120];
	UnsignedInt m_flags124; // +0x124
	char m_unknown128[0x438 - 0x128];
	unsigned char m_flags438; // +0x438
};

enum WeaponStatus
{
	READY_TO_FIRE = 0
};

// MSVC lists a virtual's overloads in reverse declaration order, so
// operator==(Version &) is slot 0x28 and operator==(bool &) slot 0x90.
class Xfer
{
public:
	class Version;

	virtual ~Xfer();

	virtual bool IsLoading() const;
	virtual bool IsStoring() const;
	virtual bool IsCRC() const;
	virtual bool IsLightCRC() const;

	virtual void v5() = 0;
	virtual void v6() = 0;
	virtual void v7() = 0;

	virtual void SkipBadBlock(Snapshot &snapshot, unsigned int size);
	virtual Xfer &XferRawBytes(void *data, unsigned int size);
	virtual Xfer &operator==(bool &value);
	virtual Xfer &operator==(char &value);
	virtual Xfer &operator==(unsigned char &value);
	virtual Xfer &operator==(short &value);
	virtual Xfer &operator==(unsigned short &value);
	virtual Xfer &operator==(int &value);
	virtual Xfer &operator==(unsigned int &value);
	virtual Xfer &operator==(__int64 &value);
	virtual Xfer &operator==(float &value);
	virtual Xfer &operator==(AsciiString &value);
	virtual Xfer &operator==(UnicodeString &value);
	virtual Xfer &operator==(PooledString &value);
	virtual Xfer &operator==(Coord3D &value);
	virtual Xfer &operator==(ICoord3D &value);
	virtual Xfer &operator==(Region3D &value);
	virtual Xfer &operator==(IRegion3D &value);
	virtual Xfer &operator==(Coord2D &value);
	virtual Xfer &operator==(ICoord2D &value);
	virtual Xfer &operator==(Region2D &value);
	virtual Xfer &operator==(IRegion2D &value);
	virtual Xfer &operator==(RealRange &value);
	virtual Xfer &operator==(RGBColor &value);
	virtual Xfer &operator==(RGBAColorReal &value);
	virtual Xfer &operator==(RGBAColorInt &value);
	virtual Xfer &operator==(Snapshot &value);
	virtual Xfer &operator==(XferUnknown11 &value) = 0;
	virtual Xfer &operator==(Version &value);
};

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};

class Weapon : public Snapshot
{
public:
	UnsignedInt getPossibleNextShotFrame() const { return m_whenWeCanFireAgain; }
	WeaponStatus getStatus() const;
	Object *forceFireWeapon(const Object *source, const Coord3D *pos);
	void loadAmmoNow(const Object *source);
	void setOwnerID(ObjectID id) { m_ownerID = id; }

private:
	const WeaponTemplate *m_template; // +0x04
	ObjectID m_ownerID; // +0x08
	char m_unknown0C[0x18 - 0x0C];
	UnsignedInt m_whenWeCanFireAgain; // +0x18
};

enum WeaponSlotType
{
	PRIMARY_WEAPON = 0
};

class WeaponStore
{
public:
	const WeaponTemplate *findWeaponTemplate(const AsciiString &name) const;
	Weapon *allocateNewWeapon(const WeaponTemplate *tmpl, WeaponSlotType slot) const;
};

extern WeaponStore *TheWeaponStore;

class GameLogic
{
public:
	UnsignedInt getFrame() const { return m_frame; }
private:
	char m_unknown00[0x40];
	UnsignedInt m_frame;
};

extern GameLogic *TheGameLogic;

// One FireWeaponNugget block of the module data (0x18 bytes, parsed by
// 0x0048BCBB through the field table 0xC4C0C0).
struct FireWeaponNugget
{
	AsciiString m_weaponName; // WeaponName
	UnsignedInt m_fireDelay; // +0x04 FireDelay
	Bool m_oneShot; // +0x08 OneShot
	Coord3D m_offset; // +0x0C Offset
};

class FireWeaponUpdateModuleData
{
public:
	char m_unknown00[0x08];
	_STL::list<FireWeaponNugget *> m_nuggets; // +0x08
	Bool m_heroModeTrigger; // +0x0C
	Bool m_chargingModeTrigger; // +0x0D
	Bool m_aliveOnly; // +0x0E
};

// Coord3D::zero for the canonical data-only Coord3D. Spelled as a call, the
// zero register is materialized after the frame store, as retail has it.
inline void zeroCoord(Coord3D &c) { c.x = 0.0f; c.y = 0.0f; c.z = 0.0f; }

// One FireWeaponNugget instance (0x18 bytes, built by 0x0048BDF8). Its name is
// unknown; the address-derived one reflects that retail folded this list's
// push_back into list<int>'s (0x0005548F).
struct Rva0048BDF8Entry
{
	Rva0048BDF8Entry() : m_weapon(NULL), m_nextFireFrame(0xFFFFFFFF), m_oneShot(false)
	{
		zeroCoord(m_offset);
	}

	Weapon *m_weapon;
	UnsignedInt m_nextFireFrame; // +0x04
	Bool m_oneShot; // +0x08
	Coord3D m_offset; // +0x0C
};

class BehaviorModuleBase
{
public:
	virtual void behaviorModuleBaseAnchor();
	const ModuleData *m_moduleData;
	Object *m_object;
};

class BehaviorModuleOther
{
public:
	virtual void behaviorModuleOtherAnchor();
};

class BehaviorModule : public BehaviorModuleBase, public BehaviorModuleOther
{
public:
	Object *getObject() const { return m_object; }
};

class UpdateModuleInterface
{
public:
	virtual UpdateSleepTime update();
};

class UpdateModule : public BehaviorModule, public UpdateModuleInterface
{
public:
	void xfer(Xfer *xfer);

protected:
	unsigned m_nextCallFrameAndPhase;
	int m_indexInLogic;
	int m_bfmeReserved;
};

class FireWeaponUpdate : public UpdateModule
{
public:
	virtual UpdateSleepTime update();
	void Rva0048BDF8Helper();

protected:
	virtual void xfer(Xfer *xfer);
	UpdateSleepTime rva0048BA3E();
	const FireWeaponUpdateModuleData *getFireWeaponUpdateModuleData() const
	{
		return (const FireWeaponUpdateModuleData *)m_moduleData;
	}

private:
	Weapon *m_weapon; // +0x20
	_STL::list<Rva0048BDF8Entry *> m_entries; // +0x24
	Bool m_entriesReady; // +0x28
};

// ?rva0048BA3E@FireWeaponUpdate@@IAE?AW4UpdateSleepTime@@XZ @0x0048BA3E 105B
// (Ghidra boundary; called at every exit of update 0x0048BEE8). Sleeps until the
// earliest frame any entry may fire again: the later of its weapon's next
// shot frame (Weapon +0x18) and its own next fire frame, minimised over the
// list; forever when the list is empty. Method name unknown.
UpdateSleepTime FireWeaponUpdate::rva0048BA3E()
{
	UnsignedInt next = 0xFFFFFFFF;
	for (_STL::list<Rva0048BDF8Entry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
	{
		Rva0048BDF8Entry *entry = *it;
		UnsignedInt frame = maxOf(entry->m_nextFireFrame, entry->m_weapon->getPossibleNextShotFrame());
		next = _STL::min(frame, next);
	}
	if (next == 0xFFFFFFFF)
		return UPDATE_SLEEP_FOREVER;
	UnsignedInt now = TheGameLogic->getFrame();
	if (next <= now)
		return UPDATE_SLEEP_NONE;
	return (UpdateSleepTime)(next - now);
}

// ?update@FireWeaponUpdate@@UAE?AW4UpdateSleepTime@@XZ @0x0048BEE8 432B
// (Ghidra boundary; slot of the +0x10 UpdateModuleInterface; OilSpillUpdate's
// update calls it first). Skips firing when a set trigger flag is not met
// (hero mode, charging) or the object is dead with AliveOnly; then fires the
// single weapon when ready, else every due entry whose weapon is ready, at
// the object position plus its offset rotated by the object's orientation
// (WB 0x11D1500..: Vector3 offset, Rotate_Z(angle), a Coord3D delta added to
// the position); one-shot entries never fire again.
UpdateSleepTime FireWeaponUpdate::update()
{
	const FireWeaponUpdateModuleData *data = getFireWeaponUpdateModuleData();
	if (data->m_heroModeTrigger && !getObject()->testFlag124_28())
		return rva0048BA3E();
	if (data->m_chargingModeTrigger && !getObject()->testFlag11C4())
		return rva0048BA3E();
	if (data->m_aliveOnly && getObject()->isEffectivelyDead())
		return rva0048BA3E();

	if (m_weapon)
	{
		if (m_weapon->getStatus() == READY_TO_FIRE)
			m_weapon->forceFireWeapon(getObject(), getObject()->getPosition());
	}
	else
	{
		UnsignedInt now = TheGameLogic->getFrame();
		for (_STL::list<Rva0048BDF8Entry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
		{
			Rva0048BDF8Entry *entry = *it;
			if (now > entry->m_nextFireFrame && entry->m_weapon->getStatus() == READY_TO_FIRE)
			{
				Object *me = getObject();
				Coord3D pos;
				pos.set(me->getPosition());
				if (entry->m_offset.lengthSqr() > 0.0f)
				{
					Real angle = me->getOrientation();
					Vector3 offset(entry->m_offset.x, entry->m_offset.y, 0.0f);
					offset.Rotate_Z(angle);
					Coord3D delta;
					delta.set(offset.x, offset.y, 0.0f);
					pos.add(&delta);
				}
				entry->m_weapon->forceFireWeapon(getObject(), &pos);
				if (entry->m_oneShot)
					entry->m_nextFireFrame = 0xFFFFFFFF;
			}
		}
	}
	return rva0048BA3E();
}

// ?xfer@FireWeaponUpdate@@MAEXPAVXfer@@@Z @0x0048BAA7 332B (Ghidra boundary;
// slot 3 of the primary vftable 0x00C4C198, called as the base by
// OilSpillUpdate::xfer). Version 2 before the rowed UpdateModule::xfer; the
// single weapon (allocated through TheWeaponStore on load) is skipped by a
// light CRC; version 2 adds the ready flag and, per entry, its one-shot flag,
// next fire frame, offset and weapon snapshot, in two identical loops for
// load and save.
void FireWeaponUpdate::xfer(Xfer *xfer)
{
	Xfer::Version version(1, 2);
	*xfer == version;
	UpdateModule::xfer(xfer);
	if (!xfer->IsLightCRC())
	{
		Bool hasWeapon = m_weapon != NULL;
		*xfer == hasWeapon;
		if (hasWeapon)
		{
			if (xfer->IsLoading())
				m_weapon = TheWeaponStore->allocateNewWeapon(NULL, PRIMARY_WEAPON);
			*xfer == *m_weapon;
		}
	}
	if (version.m_minimum >= 2)
	{
		*xfer == m_entriesReady;
		if (xfer->IsLoading())
		{
			for (_STL::list<Rva0048BDF8Entry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
			{
				Rva0048BDF8Entry *entry = *it;
				*xfer == entry->m_oneShot;
				*xfer == entry->m_nextFireFrame;
				*xfer == entry->m_offset;
				*xfer == *entry->m_weapon;
			}
		}
		else if (xfer->IsStoring())
		{
			for (_STL::list<Rva0048BDF8Entry *>::iterator it = m_entries.begin(); it != m_entries.end(); ++it)
			{
				Rva0048BDF8Entry *entry = *it;
				*xfer == entry->m_oneShot;
				*xfer == entry->m_nextFireFrame;
				*xfer == entry->m_offset;
				*xfer == *entry->m_weapon;
			}
		}
	}
}

// ?Rva0048BDF8Helper@FireWeaponUpdate@@QAEXXZ @0x0048BDF8 240B (Ghidra
// boundary; called once, from the ctor 0x0048C0C5). Builds one entry per
// FireWeaponNugget whose WeaponName resolves (rowed findWeaponTemplate
// 0x002CB8BF): one-shot flag and offset copied, first fire frame FireDelay
// frames from now, a primary weapon from TheWeaponStore owned by the object
// (ObjectID +0x74 into Weapon +0x08) with its ammo loaded (rowed loadAmmoNow
// 0x002CE1AC); then marks the entries ready. Method name unknown.
void FireWeaponUpdate::Rva0048BDF8Helper()
{
	const FireWeaponUpdateModuleData *data = getFireWeaponUpdateModuleData();
	UnsignedInt now = TheGameLogic ? TheGameLogic->getFrame() : 0;
	for (_STL::list<FireWeaponNugget *>::const_iterator it = data->m_nuggets.begin(); it != data->m_nuggets.end(); ++it)
	{
		const FireWeaponNugget *nugget = *it;
		const WeaponTemplate *tmpl = TheWeaponStore->findWeaponTemplate(nugget->m_weaponName);
		if (tmpl)
		{
			Rva0048BDF8Entry *entry = new Rva0048BDF8Entry;
			entry->m_oneShot = nugget->m_oneShot;
			entry->m_nextFireFrame = nugget->m_fireDelay + now;
			entry->m_offset = nugget->m_offset;
			entry->m_weapon = TheWeaponStore->allocateNewWeapon(tmpl, PRIMARY_WEAPON);
			entry->m_weapon->setOwnerID(getObject()->getID());
			entry->m_weapon->loadAmmoNow(getObject());
			m_entries.push_back(entry);
		}
	}
	m_entriesReady = true;
}
