// cl: /DNDEBUG /MD
//
// CreateModuleData::buildFieldParse procs: GrantUpgrade is a single-table
// leaf (11 bytes); ObjectCreationUpgrade registers its own table followed by
// the shared Upgrade table from Rva004CE29DGet at extraOffset 0x10 (34 bytes).
// ?buildFieldParse@GrantUpgradeCreateModuleData@@SAXAAVMultiIniFieldParse@@@Z,
// retail 0x004B8FF0, registers the table at 0x00C594A0 (UpgradeToGrant plus
// ExemptStatus plus GiveOnBuildComplete) with MultiIniFieldParse::add (rowed
// at 0x2BC6E). Provenance: the BFME1 GrantUpgradeCreate.cpp donor carries
// the UpgradeToGrant plus ExemptStatus table for GrantUpgradeCreateModuleData;
// the BFME2 table extends it with GiveOnBuildComplete. The owning factory
// (0x250B41) pushes this proc immediate.

class MultiIniFieldParse;

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseDurationUnsignedInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseCoord3D(INI *ini, void *instance, void *store, const void *userData);
	static void parseAngleReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseObjectCreationList(INI *ini, void *instance, void *store, const void *userData);
	static void Rva0044E6CD_ParseCustomAnimAndDuration(INI *ini, void *instance, void *store, const void *userData);
};

// The rowed ExemptStatus parser 0x003B1327 (opaque owner class).
class Rva003B1017
{
public:
	static void parseFromINI(INI *ini, void *instance, void *store, const void *userData);
};

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
	void add(const FieldParse *parse, unsigned int extraOffset);
};

int Rva004CE29DGet(void);

// The two own tables, from retail's bytes (data rows; descriptive names,
// the originals are unknown): GrantUpgrade's at 0x00C594A0 and
// ObjectCreationUpgrade's at 0x00C57708. Every parser is rowed.
extern const FieldParse GrantUpgradeCreateModuleDataFieldParse[4] =
{
	{ "UpgradeToGrant",			&INI::parseAsciiString,		0, 0x08 },
	{ "ExemptStatus",			&Rva003B1017::parseFromINI,	0, 0x0C },
	{ "GiveOnBuildComplete",	&INI::parseBool,			0, 0x1C },
	{ 0, 0, 0, 0 }
};

extern const FieldParse ObjectCreationUpgradeModuleDataFieldParse[12] =
{
	{ "UpgradeObject",			&INI::parseObjectCreationList,	0, 0x08 },
	{ "Delay",					&INI::parseDurationUnsignedInt,	0, 0x0C },
	{ "RemoveUpgrade",			&INI::parseAsciiString,			0, 0x120 },
	{ "GrantUpgrade",			&INI::parseAsciiString,			0, 0x124 },
	{ "ThingToSpawn",			&INI::parseAsciiString,			0, 0x128 },
	{ "Offset",					&INI::parseCoord3D,				0, 0x12C },
	{ "Angle",					&INI::parseAngleReal,			0, 0x138 },
	{ "DestroyWhenSold",		&INI::parseBool,				0, 0x13C },
	{ "DeathAnimAndDuration",	&INI::Rva0044E6CD_ParseCustomAnimAndDuration, 0, 0x140 },
	{ "FadeInTime",				&INI::parseUnsignedInt,			0, 0x14C },
	{ "UseBuildingProduction",	&INI::parseBool,				0, 0x150 },
	{ 0, 0, 0, 0 }
};

class GrantUpgradeCreateModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

void GrantUpgradeCreateModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(GrantUpgradeCreateModuleDataFieldParse, 0);
}

class ObjectCreationUpgradeModuleData
{
public:
	static void buildFieldParse(MultiIniFieldParse &parse);
};

// ?buildFieldParse@ObjectCreationUpgradeModuleData@@SAXAAVMultiIniFieldParse@@@Z
// Retail starts at 0x004B4084 and ends at its ret at 0x004B40A5, directly
// before the rowed ObjectCreationUpgrade constructor at 0x004B40A6. Its
// factory at 0x24FFAC pushes this proc VA.
void ObjectCreationUpgradeModuleData::buildFieldParse(MultiIniFieldParse &parse)
{
	parse.add(ObjectCreationUpgradeModuleDataFieldParse, 0);
	parse.add(reinterpret_cast<const FieldParse *>(Rva004CE29DGet()), 0x10);
}
