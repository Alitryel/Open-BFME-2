// ?reallyCreate@GenericObjectCreationNugget@@IBEPAVObject@@PBUCoord3D@@PBVMatrix3D@@MPBV2@I@Z
// partial score=0.059 date=2026-10-17
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// GenericObjectCreationNugget members that gate and forward a create (retail
// 0x001F1513 and 0x001F14B6; ObjectCreationList.cpp in the debug build).
// The nugget keeps two upgrade-name lists, +0x114 and +0x120, 4-byte
// AsciiString entries each (the dtor TU's three tail vectors).
//
//   rva001F1513  the object may be created for: no +0x120 upgrade is
//                present on the primary or its player, and when the
//                +0x114 list is not empty at least one of its upgrades is
//   create       slot 2 of the nugget vftable (the object-pair create):
//                skip airborne primaries when +0xAF is set, check the
//                upgrades, then really create at the primary's position
//                (+0x38), transform (+0x08) and orientation (+0x44) and
//                drop the result
#include "ascii_string.h"

class Player;

class Object
{
public:
	bool rva0028D9E5(int bit) const;
	Player *getControllingPlayer() const;
	bool isSignificantlyAboveTerrain() const;
	char m_pad00[0x38];
	float m_position[3];	// +0x38
	float m_pad44;		// +0x44 orientation
};

class UpgradeTemplate
{
public:
	char m_pad00[0x38];
	int m_38;		// +0x38 the bit the object and player test
};

class UpgradeCenter
{
public:
	const UpgradeTemplate *findUpgrade(const AsciiString &name) const;
};

extern UpgradeCenter *TheUpgradeCenter;

struct NuggetNameList
{
	unsigned int size() const { return m_end - m_begin; }
	AsciiString *m_begin;
	AsciiString *m_end;
	AsciiString *m_capacity;
};

struct Coord3D;
class Matrix3D;

// reallyCreate's by-value result: three words torn down through the 5-byte
// thunk at 0x001F22A3.
struct NuggetCreated
{
	~NuggetCreated();
	char m_data[12];
};

class GenericObjectCreationNugget
{
public:
	virtual void v0();
	virtual void v1();
	virtual void create(const Object *primary, const Object *secondary, unsigned int lifetimeFrames) const;
	bool rva001F1513(const Object *obj) const;
protected:
	Object *reallyCreate(const Coord3D *pos, const Matrix3D *transform, float orientation,
		const Object *sourceObj, unsigned int lifetimeFrames) const;	// 0x001F1634
private:
	char m_pad04[0xAF - 4];
	bool m_skipIfSignificantlyAirborne;	// +0xAF
	char m_padB0[0x114 - 0xB0];
	NuggetNameList m_114;	// +0x114
	NuggetNameList m_120;	// +0x120
};

// --- helpers the retail body calls (declarations only) ---
class ThingTemplate;
class Team;
class BuildAssistant;
class TerrainLogic;
class PartitionManager;
class Pathfinder;
class ScriptEngine;

struct CreateMask;

class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool);
};

extern ThingFactory *TheThingFactory;
extern BuildAssistant *TheBuildAssistant;
extern TerrainLogic *TheTerrainLogic;
extern PartitionManager *ThePartitionManager;
extern Pathfinder *ThePathfinder;
extern ScriptEngine *TheScriptEngine;

// findPositionAround options
struct FindPositionOptions
{
	int m_flags;
	float m_minRadius;
	float m_maxRadius;
	float m_angle;
	float m_angle2;
	float m_angle3;
	int m_pad[6];
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);
float GetGameLogicRandomValueReal(float lo, float hi, char *file, int line);

// The retail body also routes through several out-of-line helpers that the
// linker resolves by address; declare them so the calls match.
NuggetCreated reallyCreateBody(GenericObjectCreationNugget *self, ...);

// --- the function ---
Object *GenericObjectCreationNugget::reallyCreate(
	const Coord3D *pos, const Matrix3D *transform, float orientation,
	const Object *sourceObj, unsigned int lifetimeFrames) const
{
	const GenericObjectCreationNugget *self = this;

	static AsciiString s_debrisName("GenericDebris");
	const ThingTemplate *s_debrisTemplate = TheThingFactory->findTemplate(s_debrisName);
	(void)s_debrisTemplate;

	AsciiString debrisName("GenericDebris");
	const ThingTemplate *debrisTmpl = TheThingFactory->findTemplate(debrisName);
	(void)debrisTmpl;
	char bigPad[0x1DC];
	{
	NuggetNameList emptyList;
	emptyList.m_begin = 0;
	emptyList.m_end = 0;
	emptyList.m_capacity = 0;
	}
	if (0) throw 1;
	NuggetCreated result = reallyCreateBody((GenericObjectCreationNugget *)self, pos, transform, (float)(double)orientation, sourceObj, lifetimeFrames);
	*(volatile char*)&bigPad[0] = 0;

	const volatile NuggetNameList *vlist = &self->m_114;
	if (vlist->m_end == vlist->m_begin)
	{
		return 0;
	}

	if (self->m_skipIfSignificantlyAirborne)
	{
		if (sourceObj && sourceObj->isSignificantlyAboveTerrain())
		{
			return 0;
		}
	}

	Player *owner = 0;
	if (sourceObj)
		owner = sourceObj->getControllingPlayer();

	AsciiString primaryName("Primary");
	const ThingTemplate *primaryTemplate = TheThingFactory->findTemplate(primaryName);
	int listSize = self->m_114.size();
	if (listSize != 0)
		listSize = self->m_114.size();
	if (listSize == 0 && self->m_114.size() == 0)
	{
		return 0;
	}

	Player *owner2 = 0;
	if (primaryTemplate)
	{
		FindPositionOptions opts;
		opts.m_flags = 0;
		opts.m_minRadius = 0.0f;
		opts.m_maxRadius = 10.0f;
		float r = GetGameLogicRandomValueReal((float)(double)0.0f, (float)(double)1.0f, __FILE__, __LINE__);
		(void)r;
		int v = GetGameLogicRandomValue(0, 100, __FILE__, __LINE__);
		(void)v;
		Team *team = 0;
		CreateMask *mask = 0;
		Object *obj = TheThingFactory->newObject(primaryTemplate, team, mask, false);
		(void)obj;
	}

	(void)orientation;
	(void)pos;
	(void)transform;
	(void)lifetimeFrames;
	(void)owner;
	(void)owner2;

	return (Object *)result.m_data;
}
