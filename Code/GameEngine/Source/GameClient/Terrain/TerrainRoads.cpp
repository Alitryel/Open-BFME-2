// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
/*
**	Command & Conquer Generals Zero Hour(tm)
**	Copyright 2025 Electronic Arts Inc.
**
**	This program is free software: you can redistribute it and/or modify
**	it under the terms of the GNU General Public License as published by
**	the Free Software Foundation, either version 3 of the License, or
**	(at your option) any later version.
**
**	This program is distributed in the hope that it will be useful,
**	but WITHOUT ANY WARRANTY; without even the implied warranty of
**	MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
**	GNU General Public License for more details.
**
**	You should have received a copy of the GNU General Public License
**	along with this program.  If not, see <http://www.gnu.org/licenses/>.
*/

// FILE: TerrainRoads.cpp /////////////////////////////////////////////////////////////////////////
// Author: Colin Day, December 2001
// Desc:   Terrain road descriptions
//
// Ported from Zero Hour's GameEngine/Source/GameClient/Terrain/TerrainRoads.cpp
// (GeneralsMD tree vendored under reference/open-bfme-1/inputs/reference).
// BFME 2 keeps the bridge transition tables but moves the friend_set*String
// accessors out of line, and the INI parsers throw an INIException carrying
// Zero Hour's DEBUG_CRASH text instead of INI_INVALID_DATA.
///////////////////////////////////////////////////////////////////////////////////////////////////

#include "ascii_string.h"

typedef bool Bool;
typedef int Int;
#define TRUE true
#define FALSE false

enum BodyDamageType
{
	BODY_PRISTINE,
	BODY_DAMAGED,
	BODY_REALLYDAMAGED,
	BODY_RUBBLE,

	BODYDAMAGETYPE_COUNT
};

// Zero Hour defines DEFINE_BODYDAMAGETYPE_NAMES before including its headers,
// so BodyModule.h gives this unit its own static copy of the names. Retail
// keeps one copy per defining unit: this one is at VA 0x00DBCF30, and
// GlobalData's is at 0x00DBA444.
static const char *TheBodyDamageTypeNames[] =
{
	"PRISTINE",
	"DAMAGED",
	"REALLYDAMAGED",
	"RUBBLE",

	0
};

enum { MAX_BRIDGE_BODY_FX = 3 };

class INI
{
public:
	const char *getNextSubToken(const char *expected);
	Int scanIndexList(const char *token, const char *const *nameList);
	Int scanInt(const char *token);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseRGBColor(INI *ini, void *instance, void *store, const void *userData);
};

typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

// BFME 2 parses the bridge sound tokens through the audio-token parser rowed
// in INIAudioTokenParsers.cpp, not ZH's INI::parseAsciiString.
void Rva00339900Parse(INI *ini, void *instance, void *store, const void *userData);

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *errorMessage, ...);
	INIException(const INIException &that);
	~INIException();
};

// BFME 2 keeps the bridge sound slots as 4-byte reference records assigned
// through the rowed operator= 0x00239099 (the audio-token parser fills them).
struct OpaqueRefElement4
{
	struct OpaqueRefCounted *referent;
	~OpaqueRefElement4();
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
};

// BFME 2 layout: the road allocation/INI paths establish name +4, bridge +8,
// ID +0xC, next +0x10, widths +0x14/+0x18 and texture +0x38. Other prefix
// fields remain opaque. Existing transition-table accessor offsets are retained.
class TerrainRoadType
{
public:
	TerrainRoadType();
	virtual ~TerrainRoadType();
	void friend_setName(AsciiString name);
	void friend_setTexture(AsciiString texture);
    void friend_setID(unsigned int id) { m_id = id; }
    void friend_setBridge(Bool bridge) { m_isBridge = bridge; }
    void friend_setNext(TerrainRoadType *next) { m_next = next; }
    void friend_setRoadWidth(float width) { m_roadWidth = width; }
    void friend_setRoadWidthInTexture(float width) { m_roadWidthInTexture = width; }
    void friend_setBridgeModelName(AsciiString name);
    void friend_setBridgeModelNameDamaged(AsciiString name);
    void friend_setBridgeModelNameReallyDamaged(AsciiString name);
    void friend_setBridgeModelNameBroken(AsciiString name);
    void friend_setTextureDamaged(AsciiString texture);
    void friend_setTextureReallyDamaged(AsciiString texture);
    void friend_setTextureBroken(AsciiString texture);
    void friend_setDamageToSoundString(BodyDamageType state, const OpaqueRefElement4 &sound);
    void friend_setRepairedToSoundString(BodyDamageType state, const OpaqueRefElement4 &sound);
    const AsciiString &getName() const { return m_name; }
    TerrainRoadType *friend_getNext() { return m_next; }
    const AsciiString &getTexture() const { return m_texture; }
    float getRoadWidth() const { return m_roadWidth; }
    float getRoadWidthInTexture() const { return m_roadWidthInTexture; }
	static void parseTransitionToOCL( INI *ini, void *instance, void *store, const void *userData );
	static void parseTransitionToFX( INI *ini, void *instance, void *store, const void *userData );

	static const FieldParse m_terrainRoadFieldParseTable[];		///< retail 0x00C039E8
	static const FieldParse m_terrainBridgeFieldParseTable[];	///< retail 0x00C03A28

	AsciiString getDamageToOCLString( BodyDamageType state, Int index );

	void friend_setDamageToOCLString( BodyDamageType state, Int index, AsciiString str );
	void friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString str );
	void friend_setRepairedToOCLString( BodyDamageType state, Int index, AsciiString str );
	void friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString str );

protected:
	AsciiString m_name;                         ///< 0x04
	Bool m_isBridge;                            ///< 0x08
	unsigned int m_id;                          ///< 0x0C
	TerrainRoadType *m_next;                     ///< 0x10
	float m_roadWidth;                           ///< 0x14
	float m_roadWidthInTexture;                  ///< 0x18
	float m_bridgeScale;                        ///< 0x1C
	AsciiString m_scaffoldObjectName;           ///< 0x20
	AsciiString m_scaffoldSupportObjectName;    ///< 0x24
	float m_radarColor[3];                      ///< 0x28
	AsciiString m_bridgeModelName;              ///< 0x34
	AsciiString m_texture;                      ///< 0x38
	AsciiString m_bridgeModelNameDamaged;       ///< 0x3C
	AsciiString m_textureDamaged;               ///< 0x40
	AsciiString m_bridgeModelNameReallyDamaged; ///< 0x44
	AsciiString m_textureReallyDamaged;         ///< 0x48
	AsciiString m_bridgeModelNameBroken;        ///< 0x4C
	AsciiString m_textureBroken;                ///< 0x50
	AsciiString m_towerObjectName[4];           ///< 0x54
	AsciiString m_damageToSoundString[ BODYDAMAGETYPE_COUNT ];								///< 0x64
	AsciiString m_damageToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];		///< 0x74
	AsciiString m_damageToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];		///< 0xA4
	AsciiString m_repairedToSoundString[ BODYDAMAGETYPE_COUNT ];							///< 0xD4
	AsciiString m_repairedToOCLString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];	///< 0xE4
	AsciiString m_repairedToFXString[ BODYDAMAGETYPE_COUNT ][ MAX_BRIDGE_BODY_FX ];	///< 0x114
	float m_transitionEffectsHeight;            ///< 0x144
	Int m_numFXPerType;                         ///< 0x148
};

// Zero Hour's TerrainRoads.cpp field tables, as retail holds them: the road
// table at 0x00C039E8 (read by INI::parseTerrainRoadDefinition) and the bridge
// table at 0x00C03A28 (INI::parseTerrainBridgeDefinition). Tokens, parsers and
// offsets are retail's; BFME 2 adds the transition height and FX count and
// moves the damaged/repaired sounds to the audio-token parser.
const FieldParse TerrainRoadType::m_terrainRoadFieldParseTable[] =
{
	{ "Texture",				&INI::parseAsciiString,	0, 0x38 },	// m_texture
	{ "RoadWidth",				&INI::parseReal,		0, 0x14 },	// m_roadWidth
	{ "RoadWidthInTexture",		&INI::parseReal,		0, 0x18 },	// m_roadWidthInTexture
	{ 0, 0, 0, 0 }
};

const FieldParse TerrainRoadType::m_terrainBridgeFieldParseTable[] =
{
	{ "BridgeScale",					&INI::parseReal,			0, 0x1C },
	{ "ScaffoldObjectName",				&INI::parseAsciiString,		0, 0x20 },
	{ "ScaffoldSupportObjectName",		&INI::parseAsciiString,		0, 0x24 },
	{ "RadarColor",						&INI::parseRGBColor,		0, 0x28 },
	{ "TransitionEffectsHeight",		&INI::parseReal,			0, 0x144 },	// m_transitionEffectsHeight
	{ "NumFXPerType",					&INI::parseInt,				0, 0x148 },	// m_numFXPerType
	{ "BridgeModelName",				&INI::parseAsciiString,		0, 0x34 },
	{ "Texture",						&INI::parseAsciiString,		0, 0x38 },	// m_texture
	{ "BridgeModelNameDamaged",			&INI::parseAsciiString,		0, 0x3C },
	{ "TextureDamaged",					&INI::parseAsciiString,		0, 0x40 },
	{ "BridgeModelNameReallyDamaged",	&INI::parseAsciiString,		0, 0x44 },
	{ "TextureReallyDamaged",			&INI::parseAsciiString,		0, 0x48 },
	{ "BridgeModelNameBroken",			&INI::parseAsciiString,		0, 0x4C },
	{ "TextureBroken",					&INI::parseAsciiString,		0, 0x50 },
	{ "TowerObjectNameFromLeft",		&INI::parseAsciiString,		0, 0x54 },
	{ "TowerObjectNameFromRight",		&INI::parseAsciiString,		0, 0x58 },
	{ "TowerObjectNameToLeft",			&INI::parseAsciiString,		0, 0x5C },
	{ "TowerObjectNameToRight",			&INI::parseAsciiString,		0, 0x60 },
	{ "DamagedToSound",					&Rva00339900Parse,			0, 0x68 },	// m_damageToSoundString[BODY_DAMAGED]
	{ "RepairedToSound",				&Rva00339900Parse,			0, 0xD8 },	// m_repairedToSoundString[BODY_DAMAGED]
	{ "TransitionToOCL",				&TerrainRoadType::parseTransitionToOCL,	0, 0 },
	{ "TransitionToFX",					&TerrainRoadType::parseTransitionToFX,	0, 0 },
	{ 0, 0, 0, 0 }
};

// Native newRoad/newBridge calls prove this by-value name setter at 0x002DAD19.
// ZH calls the same operation friend_setName. The complete 52-byte body has
// its own EH graph, so it replaces the old gen-alias claim rather than folding.
void TerrainRoadType::friend_setName(AsciiString name)
{
    AsciiString &slot = m_name;
    slot = name;
}

// Native calls at 0x002DB60D and 0x002DB6E5 set the texture at +0x38.
// Keep the existing 52-byte body while reconciling its real owner and home unit.
void TerrainRoadType::friend_setTexture(AsciiString texture)
{
    AsciiString &slot = m_texture;
    slot = texture;
}

// The seven by-value bridge name/texture setters follow at 0x002DAD81..
// 0x002DAEB9, 52 bytes each, in Zero Hour's declaration order; each stores the
// field the bridge parse table names at its offset, and newBridge 0x002DB64E
// calls them in that order with the default bridge's values.
void TerrainRoadType::friend_setBridgeModelName(AsciiString name)
{
    AsciiString &slot = m_bridgeModelName;
    slot = name;
}

void TerrainRoadType::friend_setBridgeModelNameDamaged(AsciiString name)
{
    AsciiString &slot = m_bridgeModelNameDamaged;
    slot = name;
}

void TerrainRoadType::friend_setBridgeModelNameReallyDamaged(AsciiString name)
{
    AsciiString &slot = m_bridgeModelNameReallyDamaged;
    slot = name;
}

void TerrainRoadType::friend_setBridgeModelNameBroken(AsciiString name)
{
    AsciiString &slot = m_bridgeModelNameBroken;
    slot = name;
}

void TerrainRoadType::friend_setTextureDamaged(AsciiString texture)
{
    AsciiString &slot = m_textureDamaged;
    slot = texture;
}

void TerrainRoadType::friend_setTextureReallyDamaged(AsciiString texture)
{
    AsciiString &slot = m_textureReallyDamaged;
    slot = texture;
}

void TerrainRoadType::friend_setTextureBroken(AsciiString texture)
{
    AsciiString &slot = m_textureBroken;
    slot = texture;
}

// Select-any like every other TU's copy (a strong definition would duplicate theirs at link time);
// the anchor keeps the noinline body emitted.
__declspec(noinline) inline AsciiString TerrainRoadType::getDamageToOCLString( BodyDamageType state, Int index )
{
	return m_damageToOCLString[ state ][ index ];
}

// ?bfmeAnchorTerrainRoadTypegetDamageToOCLString absent-from-retail
AsciiString bfmeAnchorTerrainRoadTypegetDamageToOCLString(TerrainRoadType *p, BodyDamageType state, Int index)
{
	return p->getDamageToOCLString(state, index);
}

void TerrainRoadType::friend_setDamageToOCLString( BodyDamageType state, Int index, AsciiString str )
{
	m_damageToOCLString[ state ][ index ] = str;
}

void TerrainRoadType::friend_setDamageToFXString( BodyDamageType state, Int index, AsciiString str )
{
	m_damageToFXString[ state ][ index ] = str;
}

void TerrainRoadType::friend_setRepairedToOCLString( BodyDamageType state, Int index, AsciiString str )
{
	m_repairedToOCLString[ state ][ index ] = str;
}

void TerrainRoadType::friend_setRepairedToFXString( BodyDamageType state, Int index, AsciiString str )
{
	m_repairedToFXString[ state ][ index ] = str;
}

// 0x002DB44F / 0x002DB463: Zero Hour's inline sound-string setters, out of
// line in BFME 2 over the 4-byte sound records at +0x64 and +0xD4 (newBridge
// 0x002DB7B8 / 0x002DB7C3).
void TerrainRoadType::friend_setDamageToSoundString( BodyDamageType state, const OpaqueRefElement4 &sound )
{
	((OpaqueRefElement4 *)m_damageToSoundString)[ state ] = sound;
}

void TerrainRoadType::friend_setRepairedToSoundString( BodyDamageType state, const OpaqueRefElement4 &sound )
{
	((OpaqueRefElement4 *)m_repairedToSoundString)[ state ] = sound;
}

// ------------------------------------------------------------------------------------------------
/** In the form of
	* Label = Transition:<Damage|Repair> ToState:<BODYTYPE> EffectNum:<INT> OCL:<OCL NAME> */
// ------------------------------------------------------------------------------------------------
/*static*/ void TerrainRoadType::parseTransitionToOCL( INI *ini,
																											 void *instance,
																											 void *store,
																											 const void *userData )
{
	const char *token;
	TerrainRoadType *theInstance = (TerrainRoadType *)instance;

	// which transition is this
	Bool damageTransition;
	token = ini->getNextSubToken( "Transition" );
	if( _strcmpi( token, "Damage" ) == 0 )
		damageTransition = TRUE;
	else if( _strcmpi( token, "Repair" ) == 0 )
		damageTransition = FALSE;
	else
	{

		throw INIException( 3, "Expected Damage/Repair transition keyword\n" );

	}  // end else

	// get body damage state
	token = ini->getNextSubToken( "ToState" );
	BodyDamageType state = (BodyDamageType)ini->scanIndexList( token, TheBodyDamageTypeNames );

	// get effect num
	token = ini->getNextSubToken( "EffectNum" );
	Int effectNum = ini->scanInt( token );

	// make effect num zero based
	--effectNum;

	// sanity check effect num
	if( effectNum < 0 || effectNum >= MAX_BRIDGE_BODY_FX )
	{

		throw INIException( 3, "Effect number max on bridge transitions is '%d'\n", MAX_BRIDGE_BODY_FX );

	}  // end if

	// read the string
	token = ini->getNextSubToken( "OCL" );
	if( damageTransition )
		theInstance->friend_setDamageToOCLString( state, effectNum, token );
	else
		theInstance->friend_setRepairedToOCLString( state, effectNum, token );

}  // end parseTransitionToOCL

// ------------------------------------------------------------------------------------------------
/** In the form of
	* Label = Transition:<Damage|Repair> ToState:<BODYTYPE> EffectNum:<INT> FX:<FXLIST NAME> */
// ------------------------------------------------------------------------------------------------
/*static*/ void TerrainRoadType::parseTransitionToFX( INI *ini,
																											void *instance,
																											void *store,
																											const void *userData )
{
	const char *token;
	TerrainRoadType *theInstance = (TerrainRoadType *)instance;

	// which transition is this
	Bool damageTransition;
	token = ini->getNextSubToken( "Transition" );
	if( _strcmpi( token, "Damage" ) == 0 )
		damageTransition = TRUE;
	else if( _strcmpi( token, "Repair" ) == 0 )
		damageTransition = FALSE;
	else
	{

		throw INIException( 3, "Expected Damage/Repair transition keyword\n" );

	}  // end else

	// get body damage state
	token = ini->getNextSubToken( "ToState" );
	BodyDamageType state = (BodyDamageType)ini->scanIndexList( token, TheBodyDamageTypeNames );

	// get effect num
	token = ini->getNextSubToken( "EffectNum" );
	Int effectNum = ini->scanInt( token );

	// make effect num zero based
	--effectNum;

	// sanity check effect num
	if( effectNum < 0 || effectNum >= MAX_BRIDGE_BODY_FX )
	{

		throw INIException( 3, "Effect number max on bridge transitions is '%d'\n", MAX_BRIDGE_BODY_FX );

	}  // end if

	// read the string
	token = ini->getNextSubToken( "FX" );
	if( damageTransition )
		theInstance->friend_setDamageToFXString( state, effectNum, token );
	else
		theInstance->friend_setRepairedToFXString( state, effectNum, token );

}  // end parseTransitionToFX

// TerrainRoadCollection: findRoad (0x002DB496), findBridge (0x002DB4DA) and
// findRoadOrBridge are the Zero Hour lookups. findRoadOrBridge is the donor
// body verbatim, placed by compiling the Open-BFME-1 donor at /O1.
// Native collection list slots are +0x0C/+0x10; the subsystem prefix remains opaque.
class TerrainRoadCollection
{
    char m_subsystemPrefix[0x0C];
    TerrainRoadType *m_roadList;
    TerrainRoadType *m_bridgeList;
    static unsigned int m_idCounter;
public:
    TerrainRoadType *newRoad(AsciiString name);
	TerrainRoadType *findRoad( AsciiString name );
	TerrainRoadType *findBridge( AsciiString name );
	TerrainRoadType *findRoadOrBridge( AsciiString name );
};

// Native 0x009FF088 is a zero-initialized 4-byte counter. The collection
// constructor resets it to one; newRoad and newBridge increment the same slot.
unsigned int TerrainRoadCollection::m_idCounter;

//-------------------------------------------------------------------------------------------------
/** Find road with matching name. Retail walks m_roadList (+0x0C) through the
	* next link at +0x10 inline and compares the name at +0x04 in place through
	* the nonthrowing AsciiString::compare (0x000069D6), so getName is a reference
	* here, not Zero Hour's by-value copy. */
//-------------------------------------------------------------------------------------------------
TerrainRoadType *TerrainRoadCollection::findRoad( AsciiString name )
{
	TerrainRoadType *road;

	for( road = m_roadList; road; road = road->friend_getNext() )
	{

		if( road->getName() == name )
			return road;

	}  // end for road

	// not found
	return 0;

}  // end findRoad

//-------------------------------------------------------------------------------------------------
/** Find bridge with matching name (list head +0x10) */
//-------------------------------------------------------------------------------------------------
TerrainRoadType *TerrainRoadCollection::findBridge( AsciiString name )
{
	TerrainRoadType *bridge;

	for( bridge = m_bridgeList; bridge; bridge = bridge->friend_getNext() )
	{

		if( bridge->getName() == name )
			return bridge;

	}  // end for bridge

	// not found
	return 0;

}  // end findBridge

//-------------------------------------------------------------------------------------------------
/** Search the roads first, then the bridges */
//-------------------------------------------------------------------------------------------------
TerrainRoadType *TerrainRoadCollection::findRoadOrBridge( AsciiString name )
{
	TerrainRoadType *road = findRoad( name );

	if( road )
		return road;
	else
		return findBridge( name );

}  // end findRoadOrBridge

// ZH newRoad at BFME1 ba7ddda7e8. Target differences: ordinary global new
// allocates 0x14C (not the donor's pool macro); texture access returns a
// reference. Native code proves all fields copied and the complete list update.
typedef char TerrainRoadTypeSizeCheck[sizeof(TerrainRoadType) == 0x14C ? 1 : -1];
TerrainRoadType *TerrainRoadCollection::newRoad(AsciiString name)
{
    TerrainRoadType *road = new TerrainRoadType;
    road->friend_setName(name);
    road->friend_setID(m_idCounter++);
    road->friend_setBridge(FALSE);
    TerrainRoadType *defaultRoad = findRoad(AsciiString("DefaultRoad"));
    if (defaultRoad) {
        road->friend_setTexture(defaultRoad->getTexture());
        road->friend_setRoadWidth(defaultRoad->getRoadWidth());
        road->friend_setRoadWidthInTexture(defaultRoad->getRoadWidthInTexture());
    }
    road->friend_setNext(m_roadList);
    m_roadList = road;
    return road;
}
