// ?rva004B959C@InheritUpgradeCreate@@QAEXXZ
// ?rva004B959C@InheritUpgradeCreate@@QAEXXZ
// cl: /O1 /G7 /arch:SSE /EHsc /MD /DNDEBUG
#include "../../../Common/PartitionRangeQueryCallView.h"
#include "../../../Common/PartitionRangeQueryCallView.h"
// ?rva004B959C@InheritUpgradeCreate@@QAEXXZ @0x004B959C 269B
// InheritUpgradeCreate create work (the pinned body onBuildComplete 0x004B96A9 tail-calls, see
// InheritUpgradeCreateOnBuildComplete.cpp): every object within the module data's range (+0x08) of this module's
// object that belongs to the same controlling player and whose upgrade mask (+0x284) contains the module data's
// mask (+0x0C) is given each upgrade of that mask, through the upgrade center. The query's filter is the
// Rva002614EC player filter (what = the module data's +0x8C). Evidence: target bytes; pins for the query
// (ThePartitionManager 0x00625610), the hit handle (0x00045623 / 0x0004AA28), UpgradeCenter 0x0026EEA0 and
// Object 0x00293077; filter shape from RousingSpeechUpdateUpdate.cpp / Rva004051BC.cpp. Member roles are inferred.
class Player;
class Object;
class ModuleData;
#include "../../../../../Libraries/Include/Lib/Coord3D.h"

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *m_next;
};

class Rva002614ECFilter : public Rva000421C8
{
public:
	Rva002614ECFilter(const void *what, Player *player, bool match)
		: m_what(what), m_player(player), m_match(match) {}
	virtual bool allow(Object *obj);
	const void *m_what;
	Player *m_player;
	bool m_match;
};


extern PartitionManager *ThePartitionManager;

class UpgradeTemplate;
class UpgradeCenter
{
public:
	const UpgradeTemplate *rva0026EEA0(int index) const;
};
extern UpgradeCenter *TheUpgradeCenter;

class Rva002AA292
{
public:
	bool rva002AA292(const int *mask) const;
};

class Object
{
public:
	Player *getControllingPlayer() const;
	void rva00293077(const void *upgrade);
	char m_pad000[0x38];
	Coord3D m_pos;	// +0x38
	char m_pad044[0x284 - 0x44];
	int m_upgradeMask[32];	// +0x284
};

struct InheritUpgradeCreateData
{
	char m_pad00[0x08];
	float m_range;	// +0x08
	unsigned int m_mask[32];	// +0x0C
	char m_pad8C[0x4];
};

class InheritUpgradeCreate
{
public:
	virtual ~InheritUpgradeCreate();
	void rva004B959C();

private:
	const InheritUpgradeCreateData *m_moduleData;	// +0x04
	Object *m_object;	// +0x08
};

void InheritUpgradeCreate::rva004B959C()
{
	Object *self = m_object;
	if (self)
	{
		const InheritUpgradeCreateData *data = m_moduleData;
		if (data)
		{
			BfmeWideResult hits = ThePartitionManager->iterateObjectsInRange(&self->m_pos, data->m_range, 1, &Rva002614ECFilter(data->m_pad8C, self->getControllingPlayer(), true), 0);
			for (Object *other = hits.next(); other != 0; other = hits.next())
			{
				if (self->getControllingPlayer() != other->getControllingPlayer())
					continue;
				const int *otherMask = other->m_upgradeMask;
				const int *thisMask = (const int *)data->m_mask;
				if (!((Rva002AA292 *)otherMask)->rva002AA292(thisMask))
					continue;
				for (int i = 0; i < 1024; ++i)
				{
					if (data->m_mask[(unsigned int)i >> 5] & (1u << (i & 31)))
						self->rva00293077(TheUpgradeCenter->rva0026EEA0(i));
				}
			}
		}
	}
}
