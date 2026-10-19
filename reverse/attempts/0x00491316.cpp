// ?update@DamageFieldUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.99 date=2026-10-19
// cl: /O1 /G7 /arch:SSE /EHsc /DNDEBUG /MD /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /ICode/Libraries/Include/Lib /ICode/GameEngine/Source/Common
// stlport
// ?update@DamageFieldUpdate@@UAE?AW4UpdateSleepTime@@XZ
// Retail 0x00491316..0x0049157D (615 bytes). WB twin va 0x011DF5A0 (1503 B,
// callgraph 3; callees findUpgrade, Object 0x290D2B, getControllingPlayer,
// 3x PartitionFilter::And, iterateObjectsInRange, rowed 0x4911AE, list remove,
// FireWeaponUpdate 0x48BA3E confirm identity). Structure follows WB literally:
// data/object gate, upgrade gate, filter temporaries chained with And, two
// local std::list<ObjectID> (in range, gone), a while loop over the query
// remembering new victims in m_victims (+0x2C) with a found flag, a for loop
// collecting victims no longer in range, a for loop removing them.
// Real STLport 4.5.3 list<ObjectID> (not the old views) is what restores
// retail's frame (0x58), loop-2 register assignment and loop-3 hoisted
// sentinel with jmp-to-test; /EHsc removes the dtor EH-state writes.
// Code shape is byte-identical; only these STLport callees lack pins:
//   ??0?$_List_base<ObjectID> -> 0x0029FB3B, ??1?$_List_base<ObjectID> -> 0x00268902,
//   list<ObjectID>::insert -> 0x002A1316, list<ObjectID>::remove -> 0x002ABFC3,
//   list<ObjectID>::push_back -> 0x002A1B6F (already pinned at 0x0005548F).
#include "ascii_string.h"

typedef float Real;
typedef int Int;

enum UpdateSleepTime { UPDATE_SLEEP_NONE = 1 };
enum ObjectID { INVALID_ID = 0 };

#include "Coord3D.h"

class Player;
class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Object
{
public:
	Player *getControllingPlayer() const;
	bool rva00290D2B(const UpgradeTemplate *upgrade) const;	// has the upgrade
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	unsigned char m_pad00[0x38];
	Coord3D m_pos;			// +0x38
	unsigned char m_pad44[0x74 - 0x44];
	ObjectID m_id;			// +0x74
};

// Partition filters: vptr, +0x04 chain link, then each filter's members.
class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};
class Rva00BCECF0Filter : public Rva000421C8
{
public:
	Rva00BCECF0Filter(const void *spec, Player *player, bool flag) : m_spec(spec), m_player(player), m_flag(flag) {}
	virtual bool allow(Object *obj);
	const void *m_spec;
	Player *m_player;
	bool m_flag;
};
class Rva00BF91BCFilter : public Rva000421C8
{
public:
	Rva00BF91BCFilter(Object *obj) : m_obj(obj) {}
	virtual bool allow(Object *obj);
	Object *m_obj;
};
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual bool allow(Object *obj);
};
class Rva00BFBC90Filter : public Rva000421C8
{
public:
	Rva00BFBC90Filter(Object *obj, Int mode, bool flag) : m_obj(obj), m_mode(mode), m_flag(flag) {}
	virtual bool allow(Object *obj);
	Object *m_obj;
	Int m_mode;
	bool m_flag;
};

#include "PartitionRangeQueryCallView.h"
extern PartitionManager *ThePartitionManager;

#include <list>
#include <algorithm>
typedef std::list<ObjectID> ObjectIDList;
struct DamageFieldUpdateModuleData
{
	unsigned char m_pad00[0x10];
	Int m_radius;			// +0x10
	unsigned char m_filterSpec[4];	// +0x14
	AsciiString m_requiredUpgrade;	// +0x18
};

class ObjectModule
{
public:
	virtual ~ObjectModule();
protected:
	const DamageFieldUpdateModuleData *m_moduleData;	// +0x04
	Object *m_object;					// +0x08
};
class BehaviorModuleInterface { public: virtual void behaviorSlot(); };
class UpdateModuleInterface { public: virtual UpdateSleepTime update() = 0; };
class UpdateModule : public ObjectModule, public BehaviorModuleInterface, public UpdateModuleInterface
{
protected:
	int m_14, m_18, m_1c;
};
class FireWeaponUpdate : public UpdateModule
{
protected:
	UpdateSleepTime rva0048BA3E();
	void *m_20, *m_24, *m_28;
};
class DamageFieldUpdate : public FireWeaponUpdate
{
public:
	virtual UpdateSleepTime update();
	void rva004911AE(Object *other);
private:
	ObjectIDList m_victims;	// +0x2C
};

UpdateSleepTime DamageFieldUpdate::update()
{
	const DamageFieldUpdateModuleData *data = m_moduleData;
	Object *me = m_object;
	if (data && me)
	{
		if (data->m_requiredUpgrade != AsciiString::TheEmptyString)
		{
			const UpgradeTemplate *upgrade = TheUpgradeCenter->findUpgrade(data->m_requiredUpgrade);
			if (upgrade && !me->rva00290D2B(upgrade))
				return UPDATE_SLEEP_NONE;
		}

		BfmeWideResult iter = ThePartitionManager->iterateObjectsInRange(me->getPosition(), (Real)data->m_radius, 0,
			Rva00BFBC90Filter(me, 1, false).link(Rva0026119DFilter().link(Rva00BF91BCFilter(me).link(&Rva00BCECF0Filter(data->m_filterSpec, me->getControllingPlayer(), true)))), 0);

		ObjectIDList inRange;
		ObjectIDList gone;
		Object *other = 0;
		while ((other = iter.next()) != 0)
		{
			inRange.push_back(other->getID());
			bool found = false;
			if (std::find(m_victims.begin(), m_victims.end(), other->getID()) != m_victims.end())
				found = true;
			if (!found)
			{
				rva004911AE(other);
				m_victims.push_back(other->getID());
			}
		}

		ObjectIDList::iterator it;
		for (it = m_victims.begin(); it != m_victims.end(); ++it)
		{
			ObjectID id = *it;
			bool found = false;
			if (std::find(inRange.begin(), inRange.end(), id) != inRange.end())
				found = true;
			if (!found)
				gone.push_back(id);
		}

		ObjectIDList::iterator git;
		for (git = gone.begin(); git != gone.end(); ++git)
		{
			ObjectID id = *git;
			m_victims.remove(id);
		}
	}
	return FireWeaponUpdate::rva0048BA3E();
}
