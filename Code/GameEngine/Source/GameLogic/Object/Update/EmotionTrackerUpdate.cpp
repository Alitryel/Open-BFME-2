// cl: /I. /O1 /arch:SSE /G7 /MD /EHsc
// stlport
// EmotionTrackerUpdate nugget selection, native 0x004B13D8..0x004B15AE.
// WB 0x01232340 corroborates the class, flow and accessed fields, but does
// not establish this method's original name. Address-derived name retained.
// Layouts below expose only fields used by this selector; offsets are native.
#define _STLP_USE_STATIC_LIB
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/Libraries/Include/Lib/Coord3D.h"
#include <vector>

// The lookup bodies are visible so the compiler knows they only read the map
// and keeps the closest ID and the active nugget across the lookups.
struct EmotionLookupNode { EmotionLookupNode *next; ObjectID key; Object *object; };
struct EmotionLookupBuckets {
 EmotionLookupNode **begin,**end,**capacity;
 unsigned int size() const { return end-begin; }
 EmotionLookupNode *const &operator[](unsigned int i) const { return begin[i]; }
};
struct EmotionLookupMap { unsigned char hashEqual[4]; EmotionLookupBuckets buckets; };
inline ObjectIdNode *ObjectIdMap::find(const ObjectID &id) {
 EmotionLookupMap *map=(EmotionLookupMap*)this;
 unsigned int bucket=(unsigned int)id % map->buckets.size();
 EmotionLookupNode *node;
 for(node=map->buckets[bucket];node && node->key!=id;node=node->next) {}
 return (ObjectIdNode*)node;
}

inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectIdNode *node = m_map.find(id);
	if (node == 0)
		return 0;
	return node->object;
}

enum UpdateSleepTime { UPDATE_SLEEP_NONE=1, UPDATE_SLEEP_FOREVER=0x3fffffff };
class Player { public: char pad[0x54]; int index; };
class ThingTemplate { public: char pad[0x10b]; unsigned char flags10b; };
class ExperienceTracker { public: char pad[0x24]; int level; };
class Object {
public:
    Player *getControllingPlayer() const;
    int rva0028B511() const;
    char pad0[4]; ThingTemplate *m_template;
    char pad8[0x38-8]; Coord3D pos;
    char pad44[0x94-0x44]; unsigned int status94;
    char pad98[0x264-0x98]; ExperienceTracker *m_tracker;
};
struct EmotionUpdateData { char pad[0x2c]; unsigned char flag2c; char pad2d[3]; int level30; };
struct EmotionEntry { char pad[4]; int kind; char pad8[4]; int duration; };
struct Rva004DD018Arg;
class EmotionNugget {
public:
    bool CanBeActivatedFor(int,int,Rva004DD018Arg *);
    char pad[4]; EmotionEntry *entry;
};
class EmotionModuleBase {
public:
    virtual ~EmotionModuleBase();
    Object *getObject() const { return m_object; }
    EmotionUpdateData *m_data;
    Object *m_object;
};
class EmotionBehaviorInterface { public: virtual void behaviorSlot0(); };
class EmotionUpdateInterface { public: virtual UpdateSleepTime update()=0; };
class EmotionTrackerUpdate : public EmotionModuleBase, public EmotionBehaviorInterface, public EmotionUpdateInterface {
public:
    virtual UpdateSleepTime update();
    EmotionNugget *rva004B13D8();
    char pad14[0x24-0x14];
    bool flags[12];
    unsigned int expiry[12];
    ObjectID targetID[12];
    std::vector<EmotionNugget *> nuggets;
    EmotionNugget *active;
    int countdown;
    char pada4[0xb0-0xa4];
    int forcedKind,forcedFrames;
};
class PlayerList { public: int getPlayersWithRelationship(int,unsigned int,bool); };
struct BfmePointFD;
class Rva00739830 { public: int rva00739830(const BfmePointFD *,int,unsigned int) const; };
class PartitionManager;
extern GameLogic *TheGameLogic;
extern PlayerList *ThePlayerList;
extern PartitionManager *TheShroudManager;

EmotionNugget *EmotionTrackerUpdate::rva004B13D8()
{
	int level, slotA, slotB;
	EmotionNugget **cursor;

	slotA = 0;
	slotB = 0;
	Player *player = m_object ? m_object->getControllingPlayer() : 0;
	if (player != 0)
	{
		int index = player->index;
		int rel3 = ThePlayerList->getPlayersWithRelationship(index, 3, false);
		int index4 = player->index;
		int rel4 = ThePlayerList->getPlayersWithRelationship(index4, 4, false);
		Object *host = m_object;
		slotA = ((Rva00739830 *)TheShroudManager)->rva00739830((const BfmePointFD *)&host->pos, 1, (unsigned int)rel4);
		host = m_object;
		slotB = ((Rva00739830 *)TheShroudManager)->rva00739830((const BfmePointFD *)&host->pos, 1, (unsigned int)rel3);
	}

	level = 0;
	ExperienceTracker *tracker = m_object->m_tracker;
	if (tracker)
		level = tracker->level;

	for (cursor = nuggets.begin(); cursor != nuggets.end(); ++cursor)
	{
		EmotionNugget *entry = *cursor;
		if (!entry)
			continue;

		if (entry == active)
		{
			EmotionEntry *inner = entry->entry;
			if (inner->duration != 0)
			{
				int index = inner->kind;
				Object *found = TheGameLogic->findObjectByID((ObjectID)targetID[index]);
				if (entry->CanBeActivatedFor(slotA, slotB, (Rva004DD018Arg *)found))
					return entry;
			}
		}

		int flag = forcedFrames;
		int kind = entry->entry->kind;
		if (flag)
		{
			if (kind != forcedKind)
			{
				continue;
			}
		}
		else if (flags[kind] == 0)
		{
			continue;
		}

		EmotionUpdateData *data = m_data;
		if (!flag)
		{
			if (data->flag2c == (unsigned char)flag && level >= data->level30)
			{
				if (kind == 4)
					continue;
				if (kind == 5)
					continue;
				if (kind == 6)
					continue;
			}
		}

		if (kind == 6)
		{
			Object *other = TheGameLogic->findObjectByID((ObjectID)targetID[6]);
			if (other)
			{
				unsigned char bit = (unsigned char)(other->status94 >> 6);
				if ((other->m_template->flags10b & 2) == 0 && (bit & 1) == 0)
				{

					if (getObject()->rva0028B511() != other->rva0028B511())
						continue;
				}
			}
		}

		kind = entry->entry->kind;
		Object *found = TheGameLogic->findObjectByID((ObjectID)targetID[kind]);
		if (entry->CanBeActivatedFor(slotA, slotB, (Rva004DD018Arg *)found))
			return entry;
	}

	if (forcedFrames)
	{
		forcedFrames = 0;
		return rva004B13D8();
	}
	return 0;
}
