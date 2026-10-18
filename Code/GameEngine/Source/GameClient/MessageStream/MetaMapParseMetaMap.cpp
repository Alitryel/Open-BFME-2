// cl: /Oy- /DNDEBUG /MD /GX /Oi-
//
// ?parseMetaMap@MetaMap@@SAXPAVINI@@@Z, retail 0x001DB5A2, 109 bytes.
// Static INI scanner: tokenize, resolve GameMessage::Type via rowed
// findGameMessageMetaType 0x001DB3FE, throw on MSG_INVALID, fetch-or-create
// via rowed getMetaMapRec 0x001DB537, throw on null, then rowed initFromINI
// with the MetaMap field table. Both throws share one construction tail.
// ZH donor MetaEvent.cpp MetaMap::parseMetaMap body; throw shape follows the
// INI_parseUnsignedShort family (fill helper plus throwinfo anchor).

class INI
{
public:
	const char *getNextToken(const char *seps);
	void initFromINI(void *instance, const struct FieldParse *table);
};

typedef void (*FieldParseProc)(class INI *, void *, void *, const void *);
struct FieldParse { const char *token; FieldParseProc parse; const void *userData; int offset; };

class GameMessage
{
public:
	enum Type { MSG_INVALID = 0 };
};

class MetaMapRec;

class MetaMap
{
protected:
	GameMessage::Type findGameMessageMetaType(const char *name);
	MetaMapRec *getMetaMapRec(GameMessage::Type t);
public:
	static void parseMetaMap(INI *ini);
};

class MetaMap;
extern MetaMap *TheMetaMap;
struct LookupListRec { const char *name; int value; };
// The retail lookup list at RVA 0x007DAA78 (86 names and the null terminator).
extern const LookupListRec g_00BDAA78[87] = { { "KEY_ESC", 1 }, { "KEY_BACKSPACE", 14 }, { "KEY_ENTER", 28 }, { "KEY_SPACE", 57 }, { "KEY_TAB", 15 }, { "KEY_F1", 59 }, { "KEY_F2", 60 }, { "KEY_F3", 61 }, { "KEY_F4", 62 }, { "KEY_F5", 63 }, { "KEY_F6", 64 }, { "KEY_F7", 65 }, { "KEY_F8", 66 }, { "KEY_F9", 67 }, { "KEY_F10", 68 }, { "KEY_F11", 87 }, { "KEY_F12", 88 }, { "KEY_A", 30 }, { "KEY_B", 48 }, { "KEY_C", 46 }, { "KEY_D", 32 }, { "KEY_E", 18 }, { "KEY_F", 33 }, { "KEY_G", 34 }, { "KEY_H", 35 }, { "KEY_I", 23 }, { "KEY_J", 36 }, { "KEY_K", 37 }, { "KEY_L", 38 }, { "KEY_M", 50 }, { "KEY_N", 49 }, { "KEY_O", 24 }, { "KEY_P", 25 }, { "KEY_Q", 16 }, { "KEY_R", 19 }, { "KEY_S", 31 }, { "KEY_T", 20 }, { "KEY_U", 22 }, { "KEY_V", 47 }, { "KEY_W", 17 }, { "KEY_X", 45 }, { "KEY_Y", 21 }, { "KEY_Z", 44 }, { "KEY_1", 2 }, { "KEY_2", 3 }, { "KEY_3", 4 }, { "KEY_4", 5 }, { "KEY_5", 6 }, { "KEY_6", 7 }, { "KEY_7", 8 }, { "KEY_8", 9 }, { "KEY_9", 10 }, { "KEY_0", 11 }, { "KEY_KP1", 79 }, { "KEY_KP2", 80 }, { "KEY_KP3", 81 }, { "KEY_KP4", 75 }, { "KEY_KP5", 76 }, { "KEY_KP6", 77 }, { "KEY_KP7", 71 }, { "KEY_KP8", 72 }, { "KEY_KP9", 73 }, { "KEY_KP0", 82 }, { "KEY_MINUS", 12 }, { "KEY_EQUAL", 13 }, { "KEY_LBRACKET", 26 }, { "KEY_RBRACKET", 27 }, { "KEY_SEMICOLON", 39 }, { "KEY_APOSTROPHE", 40 }, { "KEY_TICK", 41 }, { "KEY_BACKSLASH", 43 }, { "KEY_COMMA", 51 }, { "KEY_PERIOD", 52 }, { "KEY_SLASH", 53 }, { "KEY_UP", 200 }, { "KEY_DOWN", 208 }, { "KEY_LEFT", 203 }, { "KEY_RIGHT", 205 }, { "KEY_HOME", 199 }, { "KEY_END", 207 }, { "KEY_PGUP", 201 }, { "KEY_PGDN", 209 }, { "KEY_INS", 210 }, { "KEY_DEL", 211 }, { "KEY_KPSLASH", 181 }, { "KEY_NONE", 0 }, { 0, 0 } };
// The retail lookup list at RVA 0x007DAD30 (3 names and the null terminator).
extern const LookupListRec g_00BDAD30[4] = { { "DOWN", 0 }, { "UP", 1 }, { "DOUBLEDOWN", 2 }, { 0, 0 } };
// The retail lookup list at RVA 0x007DAD50 (8 names and the null terminator).
extern const LookupListRec g_00BDAD50[9] = { { "NONE", 0 }, { "CTRL", 4 }, { "ALT", 64 }, { "SHIFT", 16 }, { "CTRL_ALT", 68 }, { "SHIFT_CTRL", 20 }, { "SHIFT_ALT", 80 }, { "SHIFT_ALT_CTRL", 84 }, { 0, 0 } };
// The retail name list at RVA 0x009B8C04 (3 names and the null terminator).
extern const char *const g_00DB8C04[4] = { "SHELL", "GAME", "PLANNING", 0 };
// The retail lookup list at RVA 0x007DAA30 (8 names and the null terminator).
extern const LookupListRec g_00BDAA30[9] = { { "CONTROL", 0 }, { "INFORMATION", 1 }, { "INTERFACE", 2 }, { "SELECTION", 3 }, { "TAUNT", 4 }, { "TEAM", 5 }, { "MISC", 6 }, { "DEBUG", 7 }, { 0, 0 } };
extern "C" {
void __identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z")();
void __identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z")();
}
// The retail table at 0x007DAD98: 7 entries and the null terminator; every parser is a rowed code owner.
// DebugCommandMap and MetaMap share this one native table. Give its existing
// owner the consumer's established name rather than defining a second datum.
struct DebugCommandMapEntry
{
    static const FieldParse m_fieldParseTable[8];
};
const FieldParse DebugCommandMapEntry::m_fieldParseTable[8] = {
	{ "Key", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), g_00BDAA78, 0x8 },
	{ "Transition", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), g_00BDAD30, 0xC },
	{ "Modifiers", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), g_00BDAD50, 0x10 },
	{ "UseableIn", (FieldParseProc)&__identifier("?parseBitString32@INI@@SAXPAV1@PAX1PBX@Z"), g_00DB8C04, 0x14 },
	{ "Category", (FieldParseProc)&__identifier("?parseLookupList@INI@@SAXPAV1@PAX1PBX@Z"), g_00BDAA30, 0x18 },
	{ "Description", (FieldParseProc)&__identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x1C },
	{ "DisplayName", (FieldParseProc)&__identifier("?parseAndTranslateLabel@INI@@SAXPAV1@PAX1PBX@Z"), 0, 0x20 },
	{ 0, 0, 0, 0 }
};

struct INIException
{
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
};

extern "C" void __stdcall _CxxThrowException(void *pExceptionObject, const _s__ThrowInfo *pThrowInfo);

// Address anchor only: the throw site pushes this object's address as an
// immediate (DIR32, copied from retail's throwinfo at 0x8FE2FC). Content is
// never compared; the real chain lives in the retail image.
struct ParseMetaMapThrowInfoAnchor { int a; int b; int c; int d; };
static const ParseMetaMapThrowInfoAnchor parseMetaMapThrowInfoAnchor = { 0, 0, 0, 0 };

void MetaMap::parseMetaMap(INI *ini)
{
	const char *token = ini->getNextToken(0);
	GameMessage::Type t = TheMetaMap->findGameMessageMetaType(token);
	if (t == GameMessage::MSG_INVALID) {
		INIException e(3, "Game message meta type for '%s' not found", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&parseMetaMapThrowInfoAnchor); __assume(0);
	}
	MetaMapRec *map = TheMetaMap->getMetaMapRec(t);
	if (map == 0) {
		INIException e(3, "Meta map entry for '%s' not found", token);
		_CxxThrowException(&e, (const _s__ThrowInfo *)&parseMetaMapThrowInfoAnchor); __assume(0);
	}
	ini->initFromINI(map, DebugCommandMapEntry::m_fieldParseTable);
}
