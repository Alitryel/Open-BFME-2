// cl: /GX /DNDEBUG /MD
//
// ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z,
// retail 0x0024E237, 84 bytes. Dedicated TU: the factory news 0xA8, runs the
// declared-only ctor (pinned at 0x49780A, donor-backed BattlePlanUpdate body
// banked as a 0.88 partial against MSVC7.1 scheduling walls), then feeds the
// new data plus the class parse proc (present-unmatched at 0x49861A, pushed
// immediate, no pin) to INI::initFromINIMultiProc (rowed at 0x2DEB5) when ini
// is non-null. Operator new and __EH_prolog resolve via their rows. The
// TU-local class keeps only size and virtuality (vptr plus 0xA4 pad). Recipe:
// BoredUpdateModuleDataFriendNew.cpp. Class identity is the BFME1
// BattlePlanUpdate donor (BattlePlanUpdate.cpp ctor plus 30-field table at
// 0x00C4FF58) in the BattlePlanUpdate file-unit. The same-named proc row at
// 0x4CBBB4 covers a single SoundUpgrade field and is left for fleet consensus.
class ModuleData;
class INI;
class MultiIniFieldParse;

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseSpecialPowerTemplate(INI *ini, void *instance, void *store, const void *userData);
	void initFromINIMultiProc(void *what, void (__cdecl *proc)(MultiIniFieldParse &));
};

class BattlePlanUpdateModuleData
{
public:
	BattlePlanUpdateModuleData();
	virtual ~BattlePlanUpdateModuleData();
	static void buildFieldParse(MultiIniFieldParse &parse);
	static ModuleData *friend_newModuleData(INI *ini);

private:
	unsigned char m_pad[0xA8 - 4];
};

// ?friend_newModuleData@BattlePlanUpdateModuleData@@SAPAVModuleData@@PAVINI@@@Z
ModuleData *BattlePlanUpdateModuleData::friend_newModuleData(INI *ini)
{
	BattlePlanUpdateModuleData *data = new BattlePlanUpdateModuleData;
	if (ini)
		ini->initFromINIMultiProc(data, BattlePlanUpdateModuleData::buildFieldParse);
	return reinterpret_cast<ModuleData *>(data);
}

struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};
extern const FieldParse g_battlePlanUpdateFieldParseTable[];

void Rva002567EAParse(INI *ini, void *instance, void *store, const void *userData);
void Rva00339900Parse(INI *ini, void *instance, void *store, const void *userData);

// Zero Hour's BodyModule.h TheMaxHealthChangeTypeNames, a per-unit static
// list with no terminator (retail's copy here: .data 0x00DCB3FC, three names
// followed directly by the next list).
static const char *TheMaxHealthChangeTypeNames[] =
{
	"SAME_CURRENTHEALTH", "PRESERVE_RATIO", "ADD_CURRENT_HEALTH_TOO"
};

// The BattlePlanUpdate module data field table (.rdata 0x00C4FF58, 28
// entries read from retail); no unit defined it, so its only user does.
extern const FieldParse g_battlePlanUpdateFieldParseTable[] =
{
	{ "SpecialPowerTemplate", INI::parseSpecialPowerTemplate, 0, 0x8 },
	{ "BombardmentPlanAnimationTime", INI::parseDurationUnsignedInt, 0, 0xC },
	{ "HoldTheLinePlanAnimationTime", INI::parseDurationUnsignedInt, 0, 0x10 },
	{ "SearchAndDestroyPlanAnimationTime", INI::parseDurationUnsignedInt, 0, 0x14 },
	{ "TransitionIdleTime", INI::parseDurationUnsignedInt, 0, 0x18 },
	{ "BombardmentPlanUnpackSoundName", Rva00339900Parse, 0, 0x1C },
	{ "BombardmentPlanPackSoundName", Rva00339900Parse, 0, 0x20 },
	{ "BombardmentMessageLabel", INI::parseAsciiString, 0, 0x24 },
	{ "BombardmentAnnouncementName", Rva00339900Parse, 0, 0x28 },
	{ "SearchAndDestroyPlanUnpackSoundName", Rva00339900Parse, 0, 0x2C },
	{ "SearchAndDestroyPlanIdleLoopSoundName", Rva00339900Parse, 0, 0x30 },
	{ "SearchAndDestroyPlanPackSoundName", Rva00339900Parse, 0, 0x34 },
	{ "SearchAndDestroyMessageLabel", INI::parseAsciiString, 0, 0x38 },
	{ "SearchAndDestroyAnnouncementName", Rva00339900Parse, 0, 0x3C },
	{ "HoldTheLinePlanUnpackSoundName", Rva00339900Parse, 0, 0x40 },
	{ "HoldTheLinePlanPackSoundName", Rva00339900Parse, 0, 0x44 },
	{ "HoldTheLineMessageLabel", INI::parseAsciiString, 0, 0x48 },
	{ "HoldTheLineAnnouncementName", Rva00339900Parse, 0, 0x4C },
	{ "ValidMemberKindOf", Rva002567EAParse, 0, 0x54 },
	{ "InvalidMemberKindOf", Rva002567EAParse, 0, 0x70 },
	{ "BattlePlanChangeParalyzeTime", INI::parseDurationUnsignedInt, 0, 0x50 },
	{ "HoldTheLinePlanArmorDamageScalar", INI::parseReal, 0, 0x8C },
	{ "SearchAndDestroyPlanSightRangeScalar", INI::parseReal, 0, 0x90 },
	{ "StrategyCenterSearchAndDestroySightRangeScalar", INI::parseReal, 0, 0x94 },
	{ "StrategyCenterSearchAndDestroyDetectsStealth", INI::parseBool, 0, 0x98 },
	{ "StrategyCenterHoldTheLineMaxHealthScalar", INI::parseReal, 0, 0x9C },
	{ "StrategyCenterHoldTheLineMaxHealthChangeType", INI::parseIndexList, TheMaxHealthChangeTypeNames, 0xA0 },
	{ "VisionObjectName", INI::parseAsciiString, 0, 0xA4 },
	{ 0, 0, 0, 0 }
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *f, unsigned int extraOffset);
};

// ?buildFieldParse@BattlePlanUpdateModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0049861A (17B)
void __declspec(noinline) BattlePlanUpdateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(g_battlePlanUpdateFieldParseTable, 0);
}

