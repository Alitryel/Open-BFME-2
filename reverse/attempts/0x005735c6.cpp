// ?findBestTarget@AITargetHeuristicEnemyStructure@@QAEXPAVAITarget@@PAVPlayer@@1@Z
// partial score=0.995 date=2026-10-20
// ?findBestTarget@AITargetHeuristicEnemyStructure@@QAEXPAVAITarget@@PAVPlayer@@1@Z
// retail 0x005735C6, 440 bytes, RET12. WB 0x01504010 names it (AITargetHeuristicEnemyStructure.cpp).
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP= /ICode/GameEngine/Source/Common /ICode/Libraries/Include
// stlport
#include "GameLogicObjectLookupView.h"
#include "Lib/Coord3D.h"
#include <map>
#include <vector>

// The vote map's operator[] is the rowed out-of-line provider 0x0028932C; this unit
// does not instantiate it (declaration-only, as retail's /O1 caller sees it).
namespace _STL { template <> int &map<ObjectID, int>::operator[](const ObjectID &); }

class Player;
class Rva002A8F24 { public: void *rva002A8F24(Player *); char pad[0x884]; float fallbackWeight; };
extern Rva002A8F24 *TheSkirmishAIManager;
extern GameLogic *TheGameLogic;
class Rva005C4AD1LeaField { public: void *get() const; };
typedef _STL::vector<ObjectID> IdRange;
struct Record { Rva005C4AD1LeaField *units; void *reserved; Rva005C4AD1LeaField *structures; };
class Object { public: char pad[0x38]; Coord3D pos; char pad44[0x74 - 0x44]; ObjectID id; };
struct Thing;
class AITarget { public: void setTarget(Object *, float); };
class AITargetHeuristicEnemyStructure
{
public:
	int isValidTarget(Thing *, void *);
	void findBestTarget(AITarget *, Player *, Player *);
};

void AITargetHeuristicEnemyStructure::findBestTarget(AITarget *target, Player *attacker, Player *defender)
{
	Record *myStats = (Record *)TheSkirmishAIManager->rva002A8F24(attacker);
	IdRange *units = (IdRange *)myStats->units->get();
	Record *enemyStats = (Record *)TheSkirmishAIManager->rva002A8F24(defender);
	IdRange *structures = (IdRange *)enemyStats->structures->get();
	_STL::map<ObjectID, int> votes;
	for (ObjectID *it = units->begin(); it != units->end(); ++it) {
		Object *unit = TheGameLogic->findObjectByID(*it);
		if (!unit)
			continue;
		ObjectID best = INVALID_OBJECT_ID;
		float bestDistance = -1.0f;
		for (ObjectID *s = structures->begin(); s != structures->end(); ++s) {
			Object *obj = TheGameLogic->findObjectByID(*s);
			if (obj && (unsigned char)isValidTarget((Thing *)obj, attacker)) {
				float dx = obj->pos.x - unit->pos.x;
				float dy = obj->pos.y - unit->pos.y;
				float distance = dx * dx + dy * dy;
				if (bestDistance < 0.0f || distance < bestDistance) {
					bestDistance = distance;
					best = obj->id;
				}
			}
		}
		if (best) {
			_STL::map<ObjectID, int>::iterator i = votes.find(best);
			if (i != votes.end())
				++i->second;
			else
				votes[best] = 1;
		}
	}
	if (!votes.empty()) {
		ObjectID building = INVALID_OBJECT_ID;
		int maximum = 0;
		for (_STL::map<ObjectID, int>::iterator i = votes.begin(); i != votes.end(); ++i) {
			if (i->second > maximum) {
				building = i->first;
				maximum = i->second;
			}
		}
		target->setTarget(TheGameLogic->findObjectByID(building), TheSkirmishAIManager->fallbackWeight);
	}
}
