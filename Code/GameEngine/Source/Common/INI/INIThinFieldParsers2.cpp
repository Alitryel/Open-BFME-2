// cl: /DNDEBUG /MD
//
// Thin FieldParse procs (original names unproven; address names). Each is
// referenced from a retail FieldParse table entry named below.
//
// initFromINI forwarders (sub-block parsed into a fixed table):
//   0x00219440 19B ViewInfo (0x00DBA0B8)            store            table 0x00DB9D48
//   0x0041F316 23B AIEconomyAssigment (0x00C3B658)   instance + 0x24  table 0x00C3B050
//   0x0041F32D 23B AIWallNodeAssignment (0x00C3B668) instance + 0x28  table 0x00C3B050
//   0x0033A7A2 25B ThreatBreakdown (0x00DBF708)      instance + 0x520 table 0x00C1045C
//   0x0033DBC9 28B UnitSpecificFX (0x00DBF268)       store, cleared first through the
//                                                     rowed tree clear 0x002D02FD; table 0x00C10C0C
// Flag-set self-parse through the pinned 0x000B937E (ini, 0):
//   0x000B9468 16B on the store (DependencySharedModelFlags and three
//                  Required/Excluded model-condition rows)
//   0x00288739 23B on instance + 0x58 when instance is set (ModelConditionState 0x00BFBB40)
// 0x00438176 58B InvisibilityNugget (0x00C52468 / 0x00C5C468): the store is
//   filled from a local MultiIniFieldParse (rowed ctor 0x0002BAA0, add
//   0x0002BC6E) holding table 0x00C3D3A8, through the pinned initFromINIMulti.
// 0x004FCB23 62B Teams (0x00C635D0 and three more): the rowed
//   Rva004E8EFF_ParseDisabledSlots int list, then every entry made zero-based.

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

class MultiIniFieldParse
{
public:
	MultiIniFieldParse();
	void add(const FieldParse *parseTable, unsigned int extraOffset);
private:
	unsigned char m_unreconstructed_00[0x84];
};

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	void initFromINIMulti(void *what, const MultiIniFieldParse &parseTableList);
	static void Rva004E8EFF_ParseDisabledSlots(INI *ini, void *instance, void *store, const void *userData);
};

extern "C" {
void __identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x009B9D48: 23 entries and the null terminator; every parser is a rowed code owner.
extern const FieldParse g_00DB9D48[24] = {
	{ "CloseUpPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x30 },
	{ "CloseUpZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x34 },
	{ "CloseUpFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x38 },
	{ "CloseUpDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x3C },
	{ "CloseUpShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x40 },
	{ "PortraitPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x48 },
	{ "PortraitZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4C },
	{ "PortraitFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x50 },
	{ "PortraitDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x54 },
	{ "PortraitShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x58 },
	{ "NearPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x0 },
	{ "NearZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x4 },
	{ "NearFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x8 },
	{ "NearDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xC },
	{ "NearShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x10 },
	{ "FarPitch", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x18 },
	{ "FarZoom", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "FarFloor", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ "FarDist", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x24 },
	{ "FarShift", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x28 },
	{ "NormalCam", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x60 },
	{ "CameraAngle", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x64 },
	{ "MapLocation", (FieldParseProc)&__identifier("?parseInt@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x68 },
	{ 0, 0, 0, 0 }
};
extern const FieldParse g_00C3B050[];
extern const FieldParse g_00C1045C[];
extern const FieldParse g_00C10C0C[];
extern const FieldParse g_00C3D3A8[];


// Retail's packed pointer-list region at VA DC8C3C. The three table views
// begin at element 0 (InvisibilityType), 2 (ForbiddenConditions), and 12
// (Options). Keep the physical suffix through its first null; these names
// describe retail data, not inferred enum bounds.
const char *INIInvisibilityNameLists[] = {
    "STEALTH", "CAMOUFLAGE", "AWAY_FROM_TREES", "MOVING",
    "FIRING_PRIMARY", "FIRING_SECONDARY", "FIRING_TERTIARY",
    "FIRING_QUATERNARY", "FIRING_QUINARY", "FIRING_ANY",
    "TAKING_DAMAGE", "USING_ABILITY", "ALLOW_NEAR_TREES",
    "DETECTED_BY_FRIENDLIES", "DISCONTINUE_WHEN_REVEALED",
    "UNTOGGLE_HIDDEN_WHEN_LEAVING_STEALTH", "NONE", "HOLD", "KILL", "SPAWN", 0
};

extern "C" {
void __identifier("?Rva004E8E57_ParseAIKindOf@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseArbitraryFXIntoMap@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z")();
void __identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z")();
void __identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z")();
}

// These two retail tables occupy exactly one 16-byte entry: the next
// bytes are string/float data, not an invented null entry.
extern const FieldParse g_00C1045C[] = {
    { "AIKindOf", (FieldParseProc)&__identifier("?Rva004E8E57_ParseAIKindOf@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 }
};
extern const FieldParse g_00C3B050[] = {
    { "TemplateName", (FieldParseProc)&__identifier("?parseAsciiString@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0 }
};
// Null-token default callback followed by the retail null terminator.
extern const FieldParse g_00C10C0C[] = {
    { 0, (FieldParseProc)&__identifier("?parseArbitraryFXIntoMap@@YAXPAVINI@@PAX1PBX@Z"), 0, 0 },
    { 0, 0, 0, 0 }
};
extern const FieldParse g_00C3D3A8[] = {
    { "ForbiddenConditions", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), INIInvisibilityNameLists + 2, 0 },
    { "ForbiddenWeaponConditions", (FieldParseProc)&__identifier("?Rva002C8C06Parse@@YAXPAVINI@@PAX1PBX@Z"), 0, 4 },
    { "DetectionRange", (FieldParseProc)&__identifier("?parseReal@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x14 },
    { "InvisibilityType", (FieldParseProc)&__identifier("?parseIndexList@INI@@SAXPAV1@PAX1PBX@Z"), INIInvisibilityNameLists, 0x18 },
    { "IgnoreTreeCheckUpgrades", (FieldParseProc)&__identifier("?Rva0026F28BParse@@YAXPAVINI@@PAXPAI@Z"), 0, 0x1C },
    { "Options", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), INIInvisibilityNameLists + 12, 0x9C },
    { "BecomeStealthedFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA0 },
    { "ExitStealthFX", (FieldParseProc)&__identifier("?parseFXList@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0xA4 },
    { "HintDetectableConditions", (FieldParseProc)&__identifier("?parseFromINI@Rva003B1017@@SAXPAVINI@@PAX1PBX@Z"), 0, 0xA8 },
    { 0, 0, 0, 0 }
};

class Rva002D02FD
{
public:
	void rva002D02FD();
};

class Rva000B937E
{
public:
	void rva000B937E(INI *ini, void *extra);
};

struct Rva004FCB23IntList
{
	int *m_start;
	int *m_finish;
	int *m_endOfStorage;
	unsigned int size() const { return (unsigned int)(m_finish - m_start); }
	int &operator[](unsigned int n) { return m_start[n]; }
};

// ?Rva00219440Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00219440Parse(INI *ini, void *, void *store, const void *)
{
	ini->initFromINI(store, g_00DB9D48);
}

// ?Rva0041F316Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0041F316Parse(INI *ini, void *instance, void *, const void *)
{
	ini->initFromINI((char *)instance + 0x24, g_00C3B050);
}

// ?Rva0041F32DParse@@YAXPAVINI@@PAX1PBX@Z
void Rva0041F32DParse(INI *ini, void *instance, void *, const void *)
{
	ini->initFromINI((char *)instance + 0x28, g_00C3B050);
}

// ?Rva0033A7A2Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0033A7A2Parse(INI *ini, void *instance, void *, const void *)
{
	ini->initFromINI((char *)instance + 0x520, g_00C1045C);
}

// ?Rva0033DBC9Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva0033DBC9Parse(INI *ini, void *, void *store, const void *)
{
	((Rva002D02FD *)store)->rva002D02FD();
	ini->initFromINI(store, g_00C10C0C);
}

// ?Rva000B9468Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva000B9468Parse(INI *ini, void *, void *store, const void *)
{
	((Rva000B937E *)store)->rva000B937E(ini, 0);
}

// ?Rva00288739Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00288739Parse(INI *ini, void *instance, void *, const void *)
{
	if (instance)
		((Rva000B937E *)((char *)instance + 0x58))->rva000B937E(ini, 0);
}

// ?Rva00438176Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva00438176Parse(INI *ini, void *, void *store, const void *)
{
	MultiIniFieldParse p;
	p.add(g_00C3D3A8, 0);
	ini->initFromINIMulti(store, p);
}

// ?Rva004FCB23Parse@@YAXPAVINI@@PAX1PBX@Z
void Rva004FCB23Parse(INI *ini, void *instance, void *store, const void *userData)
{
	INI::Rva004E8EFF_ParseDisabledSlots(ini, instance, store, userData);
	Rva004FCB23IntList &list = *(Rva004FCB23IntList *)store;
	for (unsigned int i = 0; i < list.size(); ++i)
		--list[i];
}
