// ?addObject@ElvenWoodSpecialPower@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.9762 date=2026-10-18
// ?addObject@ElvenWoodSpecialPower@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.9929563492063492 date=2026-10-15
extern "C" void _ReadWriteBarrier();
#pragma intrinsic(_ReadWriteBarrier)
// ?addObject@ElvenWoodSpecialPower@@QAEPAVObject@@PBUCoord3D@@PBVAsciiString@@@Z
// partial score=0.9 date=2026-10-15
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include "ascii_string.h"
#include "matrix3d.h"

class Thing;
class ModuleData;
class Object;
class Team;
struct Coord3D;

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/BehaviorModule.h
class BehaviorModule
{
public:
	virtual void behaviorModuleAnchor();

protected:
	const ModuleData *m_moduleData;
	Object *m_object;
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModuleInterface
{
public:
	virtual void specialPowerModuleInterfaceAnchor();
};

class ModuleInterface
{
public:
	virtual void moduleInterfaceAnchor();
};

// upstream layout: reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameLogic/Module/SpecialPowerModule.h
class SpecialPowerModule : public BehaviorModule,
	public SpecialPowerModuleInterface,
	public ModuleInterface
{
public:
	SpecialPowerModule( Thing *thing, const ModuleData *moduleData );

protected:
	virtual ~SpecialPowerModule();
};

class ElvenWoodSpecialPower : public SpecialPowerModule
{
public:
	ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData );
	Object *addObject(const Coord3D *position, const AsciiString *name);

protected:
	virtual ~ElvenWoodSpecialPower();
};

ElvenWoodSpecialPower::ElvenWoodSpecialPower( Thing *thing, const ModuleData *moduleData )
	: SpecialPowerModule( thing, moduleData )
{
}

// ??1ElvenWoodSpecialPower@@MAE@XZ present-unmatched
ElvenWoodSpecialPower::~ElvenWoodSpecialPower()
{
}

// Placeholder virtuals in this unit's vftables: in retail, every vftable that holds
// each one has the same function in that slot (vftable addresses from matched vptr
// stores). Bind them to the rows at those functions.
#pragma comment(linker, "/alternatename:?specialPowerModuleInterfaceAnchor@SpecialPowerModuleInterface@@UAEXXZ=?ControlBarInput@@YA?AW4WindowMsgHandledType@@PAVGameWindow@@III@Z")

// KINDOF bit set of a thing template (218 bits in dwords at template+0x108).
class Rva004C397FKindOfMask
{
public:
	__forceinline unsigned int test(int bit) const { return m_words[bit >> 5] & (1u << (bit & 31)); }
private:
	unsigned int m_words[7];
};
class ThingTemplate
{
public:
	__forceinline unsigned int isKindOf(int bit) const { return m_kindOf.test(bit); }
	float getScale() const { return m_scale; }
private:
	unsigned char m_pad000[0x108];
	Rva004C397FKindOfMask m_kindOf; // +0x108
	unsigned char m_pad124[0x4E0 - 0x124];
	float m_scale;                  // +0x4E0
};
class TerrainLogic
{
public:
	void addTree(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva00280176(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
	void rva0027D3D9(const ThingTemplate *, const Coord3D *, const Matrix3D *, float);
};
extern TerrainLogic *TheTerrainLogic;
struct CreateMask
{
	unsigned int m_words[4];
};
class Thing
{
public:
	void setPosition(const Coord3D *);
};
class Object : public Thing
{
public:
	void setTeam(Team *);
	Team *getTeam() const { return m_team; }
private:
	char m_pad[0x304];
	Team *m_team; // +0x304
};
class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, bool flag);
};
extern ThingFactory *TheThingFactory;
#include <string.h>

Object *ElvenWoodSpecialPower::addObject(const Coord3D *position, const AsciiString *name)
{
	const ThingTemplate *tmpl = TheThingFactory->findTemplate(*name);
	if (tmpl)
	{
		if (tmpl->isKindOf(100) || tmpl->isKindOf(94) || tmpl->isKindOf(95))
		{
Matrix3D matrix;
*(volatile float *)&matrix[0][0] = 1.0f;
*(volatile float *)&matrix[1][1] = 1.0f;
matrix[0][1] = 0.0f;
*(volatile float *)&matrix[2][2] = 1.0f;
matrix[0][2] = 0.0f;
matrix[0][3] = 0.0f;
matrix[1][0] = 0.0f;
matrix[1][2] = 0.0f;
matrix[1][3] = 0.0f;
matrix[2][0] = 0.0f;
matrix[2][1] = 0.0f;
matrix[2][3] = 0.0f;

float scale=tmpl->getScale();
unsigned kind=*(const volatile unsigned *)((const char*)tmpl+0x110); if(kind&0x40000000) TheTerrainLogic->addTree(tmpl,position,&matrix,scale); else if(kind&0x80000000) TheTerrainLogic->rva00280176(tmpl,position,&matrix,scale); else TheTerrainLogic->rva0027D3D9(tmpl,position,&matrix,scale);
		}
		else
		{
			CreateMask mask;
			memset(&mask, 0, sizeof(mask));
			Object *object = TheThingFactory->newObject(tmpl, 0, &mask, false);
			if (object)
			{
				object->setTeam(m_object->getTeam());
				object->setPosition(position);
				return object;
			}
		}
	}
	return 0;
}
