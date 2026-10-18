// cl: /DNDEBUG /MD
//
// CastleBehaviorModuleData file-unit (parse first; the ctor remains pinned
// for a follow-up).
//
// ?buildFieldParse@CastleBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x0039ABC5, 33 bytes. Double-table parse proc (tables 0x00BF00A0
// and 0x00C1ABA0) through the rowed MultiIniFieldParse::add at 0x2BC6E.
// Row supersedes the parse pin.

class INI;
typedef void (*INIFieldParseProc)(INI *ini, void *instance, void *store, const void *userData);
struct FieldParse
{
	const char *token;
	INIFieldParseProc parse;
	const void *userData;
	int offset;
};

class MultiIniFieldParse
{
public:
	void add(const FieldParse *parseTable, unsigned int extraOffset);
};

class INI
{
public:
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseFXList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A4FC_ParseNameCountList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0039A565_ParseNameNameReal(INI *ini, void *instance, void *store, const void *userData);
};

void iniParseObjectFilter(INI *ini, void *instance, void *store, const void *userData);
void Rva001DEE74Parse(INI *ini, void *instance, void *store, const void *userData);

// The shared two-field table at VA 0x00BF00A0 (RepairHealthPercentPerSecond,
// BuildVariation), owned by GapBodiesGE17.cpp with the FoundationAIUpdate
// data factory that also registers it.
extern const FieldParse s_Rva002534B1FieldParse[];

class CastleBehaviorModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
	static void rva0039981E(INI *ini, void *instance, void *store, const void *userData);
};

// Retail VA 0x00C1ABA0 (RVA 0x0081ABA0, .rdata): 23 fields and the zero
// sentinel; tokens, callbacks and offsets are read from that retail table.
// The global name below is descriptive; its original spelling is unknown.
extern const FieldParse BfmeCastleBehaviorFields[] = {
	{ "CastleToUnpackForFaction", &CastleBehaviorModuleData::rva0039981E, 0, 0x68 },
	{ "FilterValidOwnedEntries", &iniParseObjectFilter, 0, 0x30 },
	{ "FilterCrew", &iniParseObjectFilter, 0, 0x34 },
	{ "FactionDecal", &INI::Rva0039A565_ParseNameNameReal, 0, 0x5C },
	{ "PreBuiltList", &INI::Rva0039A4FC_ParseNameCountList, 0, 0x50 },
	{ "PreBuiltPlyr", &INI::parseAsciiString, 0, 0x10 },
	{ "DecalName", &INI::parseAsciiString, 0, 0x14 },
	{ "DecalSize", &INI::parseReal, 0, 0x18 },
	{ "FadeTime", &INI::parseReal, 0, 0x1C },
	{ "UnpackDelayTime", &INI::parseReal, 0, 0x20 },
	{ "BuildTime", &INI::parseReal, 0, 0x24 },
	{ "ScanDistance", &INI::parseReal, 0, 0x28 },
	{ "MaxCastleRadius", &INI::parseReal, 0, 0x2C },
	{ "CrewPrepareTime", &INI::parseDurationUnsignedInt, 0, 0x38 },
	{ "InstantUnpack", &INI::parseBool, 0, 0x3C },
	{ "KeepDeathKillsEverything", &INI::parseBool, 0, 0x3D },
	{ "CrewReleaseFX", &INI::parseFXList, 0, 0x48 },
	{ "CrewPrepareFX", &INI::parseFXList, 0, 0x44 },
	{ "CrewPrepareInterval", &INI::parseDurationUnsignedInt, 0, 0x40 },
	{ "DisableStructureRotation", &INI::parseBool, 0, 0x74 },
	{ "EvaEnemyCastleSightedEvent", &Rva001DEE74Parse, 0, 0x4C },
	{ "Summoned", &INI::parseBool, 0, 0x3E },
	{ "TransferFoundationHealthToCastleUponUnpack", &INI::parseBool, 0, 0x75 },
	{ 0, 0, 0, 0 }
};

// ?buildFieldParse@CastleBehaviorModuleData@@SAXAAVMultiIniFieldParse@@@Z @0x0039ABC5
void CastleBehaviorModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(s_Rva002534B1FieldParse, 0);
	parse.add(BfmeCastleBehaviorFields, 0);
}
