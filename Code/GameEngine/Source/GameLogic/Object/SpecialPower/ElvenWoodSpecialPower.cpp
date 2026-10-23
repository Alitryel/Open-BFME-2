// stlport
// cl: /O1 /D_STLP_USE_STATIC_LIB /Ob2 /d2inlS100 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme_matrix3d_bool_link /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib
#include <new>
#define _OPERATOR_NEW_DEFINED_
#include "ascii_string.h"
#include <bitset>
// Reuse the verified bool-constructor link view: inline the header body while
// retaining retail's existing out-of-line owner at 0x0004C91A.
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
    std::bitset<218> bits;
public:
    __forceinline bool test(int bit) const { return bits.test(bit); }
};
typedef char ElvenKindMaskSize[(sizeof(Rva004C397FKindOfMask)==28)?1:-1];
class ThingTemplate
{
public:
	// Local view adapter; this does not define the original isKindOf overload.
	__forceinline unsigned int testKindInView(int bit) const { return m_kindOf.test(bit); }
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
enum ObjectID; class ThingFactory
{
public:
	const ThingTemplate *findTemplate(const AsciiString &name);
	Object *newObject(const ThingTemplate *tmpl, Team *team, const CreateMask *mask, ObjectID flag);
};
extern ThingFactory *TheThingFactory;
#include <string.h>

// Native 0x004C397F..0x004C3A9F, RET8; WB125EB20 supplies the named
// matrix/scale/kind dispatch. The template+0x108 bit accesses, scale+0x4E0,
// owner+8 and team+0x304 are independently read from retail. The 218-bit
// wrapper is a reference layout guide, not a claim of the whole template ABI.
// /d2inlS100 lets the real STLport test inline at these constant valid indices;
// with the ordinary budget it stays out of line. Together with Matrix3D(true)
// this reproduces all 288 bytes without volatile reads/stores or barriers.
Object *ElvenWoodSpecialPower::addObject(const Coord3D *position, const AsciiString *name)
{
	const ThingTemplate *thingTemplate = TheThingFactory->findTemplate(*name);
	if (thingTemplate)
	{
		if (thingTemplate->testKindInView(100) || thingTemplate->testKindInView(94) || thingTemplate->testKindInView(95))
		{
            Matrix3D matrix(true);
            float scale = thingTemplate->getScale();
            if (thingTemplate->testKindInView(94))
                TheTerrainLogic->addTree(thingTemplate, position, &matrix, scale);
            else if (thingTemplate->testKindInView(95))
                TheTerrainLogic->rva00280176(thingTemplate, position, &matrix, scale);
            else
                TheTerrainLogic->rva0027D3D9(thingTemplate, position, &matrix, scale);
		}
		else
		{
			CreateMask mask;
			memset(&mask, 0, sizeof(mask));
			Object *object = TheThingFactory->newObject(thingTemplate, 0, &mask, (ObjectID)0);
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
