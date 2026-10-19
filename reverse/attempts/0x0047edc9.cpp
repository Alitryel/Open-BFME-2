// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.96 date=2026-10-19
// b1 2026-10-19 (WB 0x011B2240 literal pass, claude-opus-5.5): returning threshold is 5.0f (WB fcomp 5.0f,
// retail [0xbc4eb8] 5.0f; the bank's 10.0f was masked by the reloc), emitter radius test is WB's
// (Real)(m_maxWanderRadius * m_maxWanderRadius) with no `int radius` local (fixes the radius load order),
// delta.sub()/destination.scale() members as WB calls them (COORD3D_VIEW_INLINE, byte-neutral), no
// function-scope `position` pointer (WB re-reads obj->getPosition(), byte-neutral). Frame still 0xA4.
// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial score=0.96 date=2026-10-16
// ?update@AnimalAIUpdate@@UAE?AW4UpdateSleepTime@@XZ
// partial r3 W9-O1 2026-10-16 (nn 32, 20 hunks): home Code/GameEngine/Source/GameLogic/Object/Update/AIUpdate/AnimalAIUpdate.cpp
// (new TU; propose region flags). Every callee resolves to its rowed/pinned name (canonical
// PartitionRangeQueryCallView.h, GameLogicObjectLookupView.h, XYDistanceCallView.h,
// Lib/Coord3DCtorView.h; theLogicRandomLogFile instead of g_00DFEFF0).
// Levers vs the r2 bank (nn 190): (1) visible distSq body (inline noinline, below) lets cl keep the
// log-file global in ESI across the call and puts stateID/radius on retail's -0x28 spill (nn 90 -> 32);
// (2) both partition queries take full-expression filter temporaries (WB 0x011B2240 builds kind,
// alive, relationship in that order and destroys them right after the call); (3) plain-global log
// tests; (4) data->m_updateTimer > 0 guard (retail test/jbe), no volatile data; (5) named float dist.
// Residue is only frame packing: retail 0x8C, ours 0xA4. Retail: dest(emitter) -0x24 alone,
// stateID -0x28, {returning delta, no-emitter delta, no-emitter dest} -0x34, rel temp -0x3C,
// masks -0x58, kind -0x7C, accept -0x98. Ours: emitter dest + returning delta -0x24, no-emitter
// dest -0x34, rel -0x48, no-emitter delta -0x54 (below rel), masks -0x70 ... (disp32 leas).
// Tried (all worse or no slot change): delta temp helpers, sibling {} block for the no-emitter
// delta, function-scope reused delta, member-wise delta assignment, named filters in blocks,
// if(!emitter) branch swap, function-scope emitter destination. Observed: the returning delta
// joins whichever destination is declared first; the relationship temp is placed below the
// last-declared destination (in every variant, either branch order). Visible Coord3D
// GetLengthEstimate2D/GetLengthEstimate bodies (inline noinline, retail rows 0x37D1/0x3ACE)
// let the no-emitter delta share by lifetime (frame 0x98, nn 63): they regroup the 12-byte
// slots ({emitter dest, no-emitter delta}, {no-emitter dest, returning delta}) but keep stateID
// below them; declaring the emitter destination at its block level gives retail's 3-member
// group plus rel at -0x3C overlapping it, mirrored (emitter dest in the group), at the cost of
// broad register changes. Visible isReachableLayer (0x47ED3D, same retail TU) and {} around the
// emitter query change nothing.
// cl: /I. /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
#define COORD3D_VIEW_INLINE
#include "Code/Libraries/Include/Lib/Coord3DCtorView.h"
#include "Code/GameEngine/Source/Common/GameLogicObjectLookupView.h"
#include "Code/GameEngine/Source/Common/PartitionRangeQueryCallView.h"
#include "Code/GameEngine/Source/Common/RTS/XYDistanceCallView.h"
#include "ascii_string.h"

// BFME-only AnimalAIUpdate::update, retail 0x0047EDC9..0x0047F92D (2916 B).
// No Zero Hour twin. The update interface is the +0x10 secondary of the
// object installed by the constructor (0x0047ECA8, vtable VA 0x010C5590
// slot 0). WorldBuilder 0x011B2240 (AnimalAIUpdate.cpp lines 154..245)
// gives the CritterDesync messages, the call order and the full-expression
// filter temporaries of both partition queries.
// Target-reconciled fields: scaring object +0x3D8, original position +0x3DC,
// processed +0x3E8, returning +0x3E9 (update interface relative); module
// data at -0x0C, object at -0x08, state machine at +0x20 (current state +4,
// its ID +4). Module data: flee range +0x64, flee distance +0x68, wander
// percentage +0x6C, max wander distance +0x70, max wander radius +0x74,
// update timer +0x78. Object: template +4 (name +0x64), position +0x38,
// ID +0x74, flee distance +0x1AC.
// Donor semantic guide: BFME1 revision 9cbfb551 attempt 0x002B32A0.

class Object;

enum UpdateSleepTime
{
	UPDATE_SLEEP_NONE = 1
};

enum CommandSourceType
{
	CMD_FROM_PLAYER = 0,
	CMD_FROM_SCRIPT = 1,
	CMD_FROM_AI = 2
};

class ThingTemplate
{
public:
	const AsciiString &getName() const { return m_name; }
private:
	char m_pad[0x64];
	AsciiString m_name;
};

class Thing
{
public:
	const ThingTemplate *getTemplate() const { return m_template; }
	const Coord3D *getUnitDirectionVector2D() const;	// 0x0030A25F
private:
	void *m_vtbl;
	const ThingTemplate *m_template;
};

class Object : public Thing
{
public:
	const Coord3D *getPosition() const { return &m_pos; }
	ObjectID getID() const { return m_id; }
	char m_pad08[0x38 - 0x08];
	Coord3D m_pos;
	char m_pad44[0x74 - 0x44];
	ObjectID m_id;
	char m_pad78[0x1ac - 0x78];
	float m_fleeDistance;
};

class AICommandInterface
{
public:
	void aiIdle(CommandSourceType cmdSource);	// 0x001E8A38
	void aiMoveToPosition(const Coord3D *pos, CommandSourceType cmdSource);	// 0x0026C26D
};

// Command 0x2E with the object (0x0047ED64).
class Rva0047ED64
{
public:
	void rva0047ED64(void *obj, CommandSourceType src);
};

template <int N> class AnimalAIUpdateSlots : public AnimalAIUpdateSlots<N - 1>
{
public:
	virtual void slot(char (*)[N]);
};
template <> class AnimalAIUpdateSlots<0>
{
};

// chooseLocomotorSet is AIUpdateInterface vslot 142 (+0x238, 0x00268B20).
class AIUpdateInterface : public AnimalAIUpdateSlots<142>
{
public:
	virtual bool chooseLocomotorSet(int wst);
	virtual UpdateSleepTime update();	// 0x0026E267, called on the +0x10 interface
	int rva00260DED() const;	// 0x00260DED, current state ID
};

class AnimalAIUpdateDestinationLayer
{
public:
	unsigned char isReachableLayer(const Coord3D *position) const;	// 0x0047ED3D
};

class AnimalAIUpdate
{
public:
	virtual UpdateSleepTime update();
};

struct AnimalAIUpdateModuleDataView
{
	unsigned char m_beforeFleeRange[0x64];
	int m_fleeRange;
	int m_fleeDistance;
	int m_wanderPercentage;
	int m_maxWanderDistance;
	int m_maxWanderRadius;
	unsigned int m_updateTimer;
};

struct AnimalStateView { void *m_vtbl; int m_id; };
struct AnimalStateMachineView { void *m_vtbl; AnimalStateView *m_currentState; };


extern GameLogic *TheGameLogic;
extern PartitionManager *ThePartitionManager;
extern bool g_bfmeCritterDesyncLog;
extern "C" void *theLogicRandomLogFile;
extern "C" int __cdecl fprintf(void *stream, const char *format, ...);
int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float Sin(float radians);
float Cos(float radians);

template<int N> class BitFlags { public: unsigned int bits[7]; };
extern BitFlags<116> KINDOFMASK_NONE;
class BfmeFixedStorage0004543D { char bytes[28]; public: BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &) throw(); };
class Rva00045411BitSet { char bytes[28]; public: Rva00045411BitSet(int unused, int bit); };
struct Rva0006EE7A { unsigned m_bits[7]; Rva0006EE7A(int unused, int b1, int b2, int b3, int b4); };

class Rva000421C8
{
public:
	Rva000421C8() : m_next(0) {}
	virtual ~Rva000421C8() {}
	virtual bool allow(Object *obj) = 0;
	virtual int getPlayerMask();
	Rva000421C8 *link(Rva000421C8 *next);	// 0x00625790
	Rva000421C8 *m_next;
};

// Alive filter: vftable 0x00BFAD10, allow 0x0026119D.
class Rva0026119DFilter : public Rva000421C8
{
public:
	virtual ~Rva0026119DFilter() {}
	virtual bool allow(Object *obj);
};

// Relationship filter: vftable 0x00BFBC90, allow 0x00260EB1.
class Rva00260EB1Filter : public Rva000421C8
{
public:
	Rva00260EB1Filter(const Object *obj, int flags, bool match)
		: m_obj(obj), m_flags(flags), m_match(match) {}
	virtual ~Rva00260EB1Filter() {}
	virtual bool allow(Object *obj);
	virtual int getPlayerMask();
	const Object *m_obj;
	int m_flags;
	bool m_match;
};

// Any-kind filter (ctor 0x003959FA).
class Rva003959FA : public Rva000421C8
{
	BfmeFixedStorage0004543D mask;
public:
	Rva003959FA(const BfmeFixedStorage0004543D &mask);
	virtual ~Rva003959FA() {}
	virtual bool allow(Object *obj);
};

// Accept by kind (ctor 0x0004584D).
class Rva0004584D : public Rva000421C8
{
public:
	Rva0004584D(const BfmeFixedStorage0004543D &a, const BfmeFixedStorage0004543D &b) throw();
	virtual ~Rva0004584D() {}
	virtual bool allow(Object *obj);
	BfmeFixedStorage0004543D m_08;
	BfmeFixedStorage0004543D m_24;
};

class Rva000CBA20Point
{
public:
	float x;
	float y;
};

inline __declspec(noinline) float Rva000CBA20::distSq(const Rva000CBA20Point *p) throw()
{
	float dx = m_x - p->x;
	float dy = m_y - p->y;
	return dx * dx + dy * dy;
}

static const char *const kAnimalSource =
	"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\AIUpdate\\AnimalAIUpdate.cpp";

static __forceinline const AnimalAIUpdateModuleDataView *animalData(AnimalAIUpdate *self)
{
	return *(AnimalAIUpdateModuleDataView **)((char *)self - 0x0c);
}

static __forceinline Object *animalObject(AnimalAIUpdate *self)
{
	return *(Object **)((char *)self - 8);
}

static __forceinline const Coord3D *animalPosition(Object *object)
{
	return object->getPosition();
}

static __forceinline ObjectID animalID(Object *object)
{
	return object->getID();
}

static __forceinline const char *animalDebugName(Object*object){return ((const StringBase<char> *)&object->getTemplate()->getName())->str();}
static __forceinline AICommandInterface*animalCommands(AnimalAIUpdate*self){return (AICommandInterface*)((char*)self+0x10);}
static __forceinline AIUpdateInterface *animalPrimary(AnimalAIUpdate *self){return (AIUpdateInterface *)((char *)self - 0x10);}
static __forceinline Coord3D *originalPosition(AnimalAIUpdate *self)
{
	return (Coord3D *)((char *)self + 0x3dc);
}

static __forceinline ObjectID &scaringObjectID(AnimalAIUpdate *self)
{
	return *(ObjectID *)((char *)self + 0x3d8);
}

static __forceinline unsigned char &processedOne(AnimalAIUpdate *self)
{
	return *(unsigned char *)((char *)self + 0x3e8);
}

static __forceinline unsigned char &returning(AnimalAIUpdate *self)
{
	return *(unsigned char *)((char *)self + 0x3e9);
}

static __forceinline void animalLog(const char *text)
{
	if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
		fprintf(theLogicRandomLogFile, text);
}

UpdateSleepTime AnimalAIUpdate::update()
{
	AnimalAIUpdate *self = this;
	void *log;
	const AnimalAIUpdateModuleDataView *data = animalData(self);
	Object *animal = animalObject(self);
	AnimalStateMachineView *machine = *(AnimalStateMachineView **)((char *)self + 0x20);
	AnimalStateView *state = machine->m_currentState;
	int stateID = state ? state->m_id : 999999;

	((AIUpdateInterface *)self)->AIUpdateInterface::update();

	if (!processedOne(self))
	{
		*originalPosition(self) = *animalPosition(animal);
		if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile,
				"CritterDesync:  m_processedOne false - setting m_originalPos to %g,%g,%g",
				originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		processedOne(self) = 1;
	}

	if (!((AnimalAIUpdateDestinationLayer*)((char*)self-0x10))->isReachableLayer(animalPosition(animal)))
	{
		if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile,
				"CritterDesync:  animal %s is in a bad area, return to origin %g,%g,%g.",
				animalDebugName(animal), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);
		animalCommands(self)->aiIdle(CMD_FROM_AI);
		animalCommands(self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
		animalPrimary(self)->chooseLocomotorSet(0);
		returning(self) = 1;
		return UPDATE_SLEEP_NONE;
	}

	if (returning(self))
	{
		if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile,
				"CritterDesync:  m_returning is true - animal %s is checking if we are near origin %g,%g,%g to stop.",
				animalDebugName(animal), originalPosition(self)->x, originalPosition(self)->y,
				originalPosition(self)->z);

		Coord3D delta = *originalPosition(self);
		delta.sub(animalPosition(animal));
		if(delta.GetLengthEstimate2D() < 5.0f)
		{
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s is finished returning to origin.",
					animalDebugName(animal));
			returning(self) = 0;
		}
		else
		{
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s is NOT finished returning to origin.",
					animalDebugName(animal));
			return UPDATE_SLEEP_NONE;
		}
	}

	if (data->m_updateTimer > 0 && TheGameLogic->getFrame() % data->m_updateTimer == 0)
	{
		if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
			fprintf(theLogicRandomLogFile,
				"CritterDesync:  animal %s is doing periodic search for enemies.",
				animalDebugName(animal));
		Object *enemy = ThePartitionManager->getClosestObject(animalPosition(animal),
			(float)data->m_fleeRange, 0, Rva00260EB1Filter(animal, 3, false).link(&Rva0026119DFilter())->link(&Rva003959FA(*(const BfmeFixedStorage0004543D *)&Rva0006EE7A(0, 8, 9, 10, 11))));
		if (enemy)
		{
			ObjectID enemyID = animalID(enemy);
			bool same = enemyID == scaringObjectID(self) &&
				(animalPrimary(self)->rva00260DED() == 20 || animalPrimary(self)->rva00260DED() == 19);
            if(same)
			{
				if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile,
						"CritterDesync:  animal %s(%d) sees SAME enemy %s(%d) to be scared of.",
						animalDebugName(animal), animalID(animal), animalDebugName(enemy), enemyID);
				}
            else {
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s(%d) found NEW enemy %s(%d) to be scared of RUNAWAYPANIC.",
					animalDebugName(animal), animalID(animal), animalDebugName(enemy), enemyID);
			animal->m_fleeDistance = (float)data->m_fleeDistance;
			((Rva0047ED64 *)animalCommands(self))->rva0047ED64(TheGameLogic->findObjectByID(animalID(enemy)), CMD_FROM_SCRIPT);
			scaringObjectID(self) = animalID(enemy);
            }
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s(%d) blah-1",
					animalDebugName(animal), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}

	}

		if (stateID != 0)
		{
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s(%d) is not idle, sleep.",
					animalDebugName(animal), animalID(animal));
			return UPDATE_SLEEP_NONE;
		}
		scaringObjectID(self) = INVALID_OBJECT_ID;
		if (GetGameLogicRandomValue(0, 100, (char *)kAnimalSource, 0x9a)
			< data->m_wanderPercentage)
		{
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s(%d) dice roll suceeded for wanderpercentage",
					animalDebugName(animal), animalID(animal));
			Object *emitter = ThePartitionManager->getClosestObject(animalPosition(animal),
				(float)data->m_fleeRange, 1, &Rva0004584D(*(const BfmeFixedStorage0004543D *)&Rva00045411BitSet(0, 0x92), *(const BfmeFixedStorage0004543D *)&KINDOFMASK_NONE));
			animalPrimary(self)->chooseLocomotorSet(0);
			if (emitter)
			{
				if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile,
						"CritterDesync:  animal %s(%d) EMITTER CASE",
						animalDebugName(animal), animalID(animal));
				if (((Rva000CBA20 *)animal)->distSq((const Rva000CBA20Point *)animalPosition(emitter)) > (float)(data->m_maxWanderRadius * data->m_maxWanderRadius))
				{
					if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
						fprintf(theLogicRandomLogFile,
							"CritterDesync:  animal %s(%d) moving to emitter at %g,%g,%g",
							animalDebugName(animal), animalID(animal),
							animalPosition(emitter)->x, animalPosition(emitter)->y,
							animalPosition(emitter)->z);
					animalCommands(self)->aiMoveToPosition(animalPosition(emitter), CMD_FROM_AI);
				}
				else
				{
					if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
						fprintf(theLogicRandomLogFile,
							"CritterDesync:  animal %s(%d) wander to random location",
							animalDebugName(animal), animalID(animal));
					animal->getUnitDirectionVector2D();
					Coord3D destination = *animal->getUnitDirectionVector2D();
					float angle = (float)GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xbc);
					destination.x += Cos(angle);destination.y += Sin(angle);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xbf);
					destination.scale(distance);
					destination.x += animalPosition(animal)->x;destination.y += animalPosition(animal)->y;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
							fprintf(theLogicRandomLogFile,
								"CritterDesync:  animal %s(%d) wandering to dest %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
						animalCommands(self)->aiMoveToPosition(&destination, CMD_FROM_AI);
					}
					else
					{
						if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
							fprintf(theLogicRandomLogFile,
								"CritterDesync:  animal %s(%d) CANNOT wander to dest %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
			else
			{
				if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
					fprintf(theLogicRandomLogFile,
						"CritterDesync:  animal %s(%d) NO EMITTER CASE",
						animalDebugName(animal), animalID(animal));
				Coord3D delta = *originalPosition(self);
		delta.sub(animalPosition(animal));
				float dist = delta.GetLengthEstimate();
				if (dist > (float)data->m_maxWanderRadius)
				{
					if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
						fprintf(theLogicRandomLogFile,
							"CritterDesync:  animal %s(%d) returning to m_originalPos %g,%g,%g",
							animalDebugName(animal), animalID(animal),
							originalPosition(self)->x, originalPosition(self)->y,
							originalPosition(self)->z);
					animalCommands(self)->aiMoveToPosition(originalPosition(self), CMD_FROM_AI);
				}
				else
				{
					if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
						fprintf(theLogicRandomLogFile,
							"CritterDesync:  animal %s(%d) wandering to random spot",
							animalDebugName(animal), animalID(animal));
					animal->getUnitDirectionVector2D();
					Coord3D destination = *animal->getUnitDirectionVector2D();
					float angle = (float)GetGameLogicRandomValue(-15, 15, (char *)kAnimalSource, 0xf2);
					destination.x += Cos(angle);destination.y += Sin(angle);
					float distance = (float)GetGameLogicRandomValue(0,
						data->m_maxWanderDistance, (char *)kAnimalSource, 0xf5);
					destination.scale(distance);
					destination.x += animalPosition(animal)->x;destination.y += animalPosition(animal)->y;
					if (((AnimalAIUpdateDestinationLayer *)((char *)self - 0x10))->isReachableLayer(&destination))
					{
						if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
							fprintf(theLogicRandomLogFile,
								"CritterDesync:  animal %s(%d) wandering to %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
						animalCommands(self)->aiMoveToPosition(&destination, CMD_FROM_AI);
					}
					else
					{
						if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
							fprintf(theLogicRandomLogFile,
								"CritterDesync:  animal %s(%d) CANNOT wander to %g,%g,%g",
								animalDebugName(animal), animalID(animal),
								destination.x, destination.y, destination.z);
					}
				}
			}
		}
		else
		{
			if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
				fprintf(theLogicRandomLogFile,
					"CritterDesync:  animal %s(%d) dice roll failed.",
					animalDebugName(animal), animalID(animal));
		}

	if (g_bfmeCritterDesyncLog && theLogicRandomLogFile)
		fprintf(theLogicRandomLogFile,
			"CritterDesync:  animal %s(%d) finished update.", animalDebugName(animal), animalID(animal));

	return UPDATE_SLEEP_NONE;
}
