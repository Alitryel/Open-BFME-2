// cl: /DBFME_ASCII_DTOR_DECL /O1 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?parseConditionState@W3DScriptedModelDrawModuleData@@SAXPAVINI@@PAX1PBX@Z,
// retail 0x000C8914..0x000C8B83 (623 bytes, EH). WorldBuilder names it
// W3DScriptedModelDrawModuleData::parseConditionState; Zero Hour's
// W3DModelDrawModuleData::parseConditionState (W3DModelDraw.cpp) is the
// semantic donor, reduced in BFME 2 to its normal (0) and default (1)
// forms. Each form validates against the module data's 0xFC-byte state
// records (vector at +0x18) and default index (+0x4C) and throws Zero
// Hour's asset errors as INIException(3, ...); then the state's fields are
// read through the condition-state field table (retail 0x00BCAB20), its
// model list (+0x4C of the record) is required and dropped when it names
// "None", the condition bits (0x4C bytes, parsed by the rowed 0x000B937E
// and compared by 0x00045473) are copied in and the record is appended.
// The record's rowed constructor 0x000C47F4, assignment 0x000C27B0 and
// destructor 0x000C2980 carry address-derived names, so a stack view
// binds them. The table and record names are descriptive.
#include "ascii_string.h"
#include <string.h>
#include <vector>
// bfme link decl-only begin
namespace _STL { template <> AsciiString * vector<AsciiString, allocator<AsciiString> >::erase(AsciiString *, AsciiString *); }
// bfme link decl-only end
// Declaration-only: retail keeps one _STL::max<unsigned int> (17-byte jae
// shape); this TU's flags would emit a private copy.
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class INI
{
public:
	const char *getNextTokenOrNull(const char *seps);			// 0x0002DEED
	void initFromINI(void *what, const FieldParse *parseTable);	// 0x0002DE78
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C2B23_ParseModelName(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6E5A_ParseLowercasedString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3824_ParseTexturePair(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C3AB3Parse(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B9AFF_ParseShadowEvent(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2D93_ParseShadowReal(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2DBB_ParseShadowAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B2DE3_ParseShadowBool(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C2C5FParseBoneRecord(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6E9E_ParseTurretArtAngle(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000C2CA4ParseTurretPitch(INI *ini, void *instance, void *store, const void *userData);
	static void Rva000B6EBE_ParseTurretArtPitch(INI *ini, void *instance, void *store, const void *userData);
};

void ParseScriptedModelParticleSysBone(INI *ini, void *instance, void *store, const void *userData);
void rva000C4B61(INI *ini, void *instance, void *store, const void *userData);

class INIException
{
public:
	char *mFailureMessage;
	int mErrorCode;
	INIException(int code, const char *format, ...);			// 0x0002F681
	INIException(const INIException &);
	~INIException();
};

// Retail VA 0x00DB4E00 (.data): the shadow type names Shadow parses
// against, 16 names and the null terminator, read from retail.
extern const char *TheShadowNames[] =
{
	"SHADOW_DECAL",
	"SHADOW_VOLUME",
	"SHADOW_VOLUME_NEW",
	"SHADOW_DYNAMIC_PROJECTION",
	"SHADOW_DIRECTIONAL_PROJECTION",
	"SHADOW_ALPHA_DECAL",
	"SHADOW_ADDITIVE_DECAL",
	"SHADOW_VOLUME_NON_SELF_1",
	"SHADOW_VOLUME_NON_SELF_2",
	"SHADOW_VOLUME_NON_SELF_3",
	"SHADOW_ALPHA_DECAL_DYNAMIC",
	"SHADOW_ADDITIVE_DECAL_DYNAMIC",
	"SHADOW_MERGE_DECAL",
	"SHADOW_DECAL_TERRAIN_CLAIM",
	"SHADOW_VOLUME_OR_DECAL",
	"SHADOW_VOLUME_NEW_OR_DECAL",
	NULL
};

// The condition-state field table at retail VA 0x00BCAB20 (.rdata): 32
// fields and the zero sentinel; tokens, callbacks, user data and offsets are
// read from that retail table.
extern const FieldParse TheScriptedModelConditionStateFieldParse[] =
{
	{ "Model", &INI::Rva000C2B23_ParseModelName, 0, 0x0 },
	{ "Skeleton", &INI::Rva000B6E5A_ParseLowercasedString, 0, 0x58 },
	{ "ModelAnimationPrefix", &INI::parseAsciiString, 0, 0x70 },
	{ "Texture", &INI::Rva000C3824_ParseTexturePair, 0, 0x64 },
	{ "PortraitImageName", &INI::parseAsciiString, 0, 0x60 },
	{ "ButtonImageName", &INI::parseAsciiString, 0, 0x5C },
	{ "WeaponFireFXBone", &INI::Rva000C3AB3Parse, 0, 0x84 },
	{ "WeaponLaunchBone", &INI::Rva000C3AB3Parse, 0, 0xA8 },
	{ "WeaponRecoilBone", &INI::Rva000C3AB3Parse, 0, 0x90 },
	{ "WeaponMuzzleFlash", &INI::Rva000C3AB3Parse, 0, 0x9C },
	{ "ParticleSysBone", &ParseScriptedModelParticleSysBone, 0, 0x0 },
	{ "OverrideTooltip", &INI::parseAsciiString, 0, 0x74 },
	{ "FXEvent", &rva000C4B61, 0, 0x0 },
	{ "RetainSubObjects", &INI::parseBool, 0, 0xF4 },
	{ "Shadow", &INI::Rva000B9AFF_ParseShadowEvent, TheShadowNames, 0x0 },
	{ "ShadowSizeX", &INI::Rva000B2D93_ParseShadowReal, 0, 0xC },
	{ "ShadowSizeY", &INI::Rva000B2D93_ParseShadowReal, 0, 0x10 },
	{ "ShadowOffsetX", &INI::Rva000B2D93_ParseShadowReal, 0, 0x14 },
	{ "ShadowOffsetY", &INI::Rva000B2D93_ParseShadowReal, 0, 0x18 },
	{ "ShadowSunAngle", &INI::Rva000B2D93_ParseShadowReal, 0, 0x1C },
	{ "ShadowTexture", &INI::Rva000B2DBB_ParseShadowAsciiString, 0, 0x0 },
	{ "ShadowMaxHeight", &INI::Rva000B2D93_ParseShadowReal, 0, 0x20 },
	{ "ShadowOverrideLODVisibility", &INI::Rva000B2DE3_ParseShadowBool, 0, 0x24 },
	{ "ShadowOpacityStart", &INI::parseUnsignedInt, 0, 0xE0 },
	{ "ShadowOpacityFadeInTime", &INI::parseReal, 0, 0xE4 },
	{ "ShadowOpacityPeak", &INI::parseUnsignedInt, 0, 0xE8 },
	{ "ShadowOpacityFadeOutTime", &INI::parseReal, 0, 0xEC },
	{ "ShadowOpacityEnd", &INI::parseUnsignedInt, 0, 0xF0 },
	{ "Turret", &INI::Rva000C2C5FParseBoneRecord, 0, 0x0 },
	{ "TurretArtAngle", &INI::Rva000B6E9E_ParseTurretArtAngle, 0, 0x0 },
	{ "TurretPitch", &INI::Rva000C2CA4ParseTurretPitch, 0, 0x0 },
	{ "TurretArtPitch", &INI::Rva000B6EBE_ParseTurretArtPitch, 0, 0x0 },
	{ 0, 0, 0, 0 }
};

// The 0x4C-byte condition bit set.
class Rva000B937E { public: void rva000B937E(INI *ini, void *description); };
bool Rva00045473Equal(const void *a, const void *b);
struct ScriptedModelConditionFlags
{
	unsigned int m_bits[19];

	void parse(INI *ini) { ((Rva000B937E *)this)->rva000B937E(ini, 0); }
	bool any() const
	{
		for (unsigned int i = 0; i < 19; ++i)
			if (m_bits[i])
				return true;
		return false;
	}
};

// The 252-byte state record: the condition bits, then the model names.
struct BfmePod252
{
	unsigned char m_bytes[252];
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> void _Destroy<BfmePod252 *>(BfmePod252 *,BfmePod252 *); }
class Rva000C38F8 { public: Rva000C38F8(); };
class Rva000C27B0 { public: Rva000C27B0 &operator=(const Rva000C27B0 &that); };
class Rva000C2980 { public: ~Rva000C2980(); };
struct ScriptedModelConditionInfo
{
	__forceinline ScriptedModelConditionInfo() { ((Rva000C38F8 *)this)->Rva000C38F8::Rva000C38F8(); }
	__forceinline ~ScriptedModelConditionInfo() { ((Rva000C2980 *)this)->~Rva000C2980(); }
	ScriptedModelConditionInfo &operator=(const BfmePod252 &that)
	{
		*(Rva000C27B0 *)this = *(const Rva000C27B0 *)&that;
		return *this;
	}

	// The model names: a vector<AsciiString> the record's own constructor
	// and destructor manage.
	_STL::vector<AsciiString> &models() { return *(_STL::vector<AsciiString> *)m_models; }

	ScriptedModelConditionFlags m_flags;			// +0x00
	unsigned char m_models[sizeof(_STL::vector<AsciiString>)];	// +0x4C
	unsigned char m_tail[252 - 0x4c - sizeof(_STL::vector<AsciiString>)];
};

class W3DScriptedModelDrawModuleData
{
public:
	static void parseConditionState(INI *ini, void *instance, void *store, const void *userData);

	unsigned char m_pad00[0x18];
	_STL::vector<BfmePod252> m_conditionStates;		// +0x18
	unsigned char m_pad24[0x4c - 0x24];
	int m_defaultState;								// +0x4C
};

void W3DScriptedModelDrawModuleData::parseConditionState(INI *ini, void *instance, void *store, const void *userData)
{
	ScriptedModelConditionInfo info;
	ScriptedModelConditionFlags conditions;
	memset(&conditions, 0, sizeof(conditions));
	W3DScriptedModelDrawModuleData *self = (W3DScriptedModelDrawModuleData *)instance;
	switch ((unsigned int)userData)
	{
	case 0:
		if (self->m_defaultState >= 0)
			info = self->m_conditionStates[self->m_defaultState];
		conditions.parse(ini);
		if (self->m_defaultState < 0 && self->m_conditionStates.empty() && conditions.any())
			throw INIException(3, "*** ASSET ERROR: when not using DefaultConditionState, the first ConditionState must be for NONE (%s)", "");
		if (!conditions.any() && self->m_defaultState >= 0)
			throw INIException(3, "*** ASSET ERROR: you may not specify both a Default state and a Conditions=None state");
		for (_STL::vector<BfmePod252>::iterator it = self->m_conditionStates.begin(); it != self->m_conditionStates.end(); ++it)
		{
			if (Rva00045473Equal(&conditions, &*it))
				throw INIException(3, "*** ASSET ERROR: duplicate condition states are not currently allowed (%s)", "");
		}
		break;
	case 1:
		if (self->m_defaultState >= 0)
			throw INIException(3, "*** ASSET ERROR: you may have only one default state!");
		if (ini->getNextTokenOrNull(0))
			throw INIException(3, "*** ASSET ERROR: unknown keyword");
		if (!self->m_conditionStates.empty())
			throw INIException(3, "*** ASSET ERROR: when using DefaultConditionState, it must be the first state listed (%s)\n", "");
		self->m_defaultState = self->m_conditionStates.size();
		break;
	}
	ini->initFromINI(&info, TheScriptedModelConditionStateFieldParse);
	if (info.models().size() == 0)
		throw INIException(3, "*** ASSET ERROR: you must specify a model name");
	if (info.models()[0].isNone())
		info.models().erase(info.models().begin(), info.models().end());
	info.m_flags = conditions;
	self->m_conditionStates.push_back(*(const BfmePod252 *)&info);
}
