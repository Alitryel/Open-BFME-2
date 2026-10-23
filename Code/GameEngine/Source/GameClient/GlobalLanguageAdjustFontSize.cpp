// cl: /DNDEBUG /MD /EHsc
// ?adjustFontSize@GlobalLanguage@@QAEHH@Z retail 0x001EA40D 54 bytes.
// GlobalLanguage font-size scaler: point size scaled by display width over
// 1024 and floored. BFME1 donor is GlobalLanguage::adjustFontSize in
// reference/open-bfme-1 (ZH donor GlobalLanguage.cpp plus the simple-ratio
// GlobalLanguage_adjustFontSize.cpp): TheGlobalData xResolution over 1024
// floored through REAL_TO_INT_FLOOR. BFME2 deltas retail-measured: xResolution
// at TheGlobalData +0x30 (GlobalDataOptionPreferences.cpp row) and the 1024
// divisor folded to a 1/1024 multiply at 0x007CF7C0. Identity: callers pass
// ecx from TheGlobalLanguageData literal 0x00DFDC84 (GameEngine init pushes
// that literal for initSubsystem<GlobalLanguage>) and feed eax to
// FontLibrary::getFont float size; floor reaches msvcr71 through IAT.

typedef int Int;
typedef float Real;

extern "C" __declspec(dllimport) double __cdecl floor(double);

// BaseType.h verbatim: C cast emits out-of-line _ftol plus qword shape;
// retail holds inline fld/fistp so the helper is load-bearing.
__forceinline long fast_float2long_round(float f)
{
	long i;
	__asm {
		fld [f]
		fistp [i]
	}
	return i;
}

#define REAL_TO_INT_FLOOR(x) (fast_float2long_round((Real)floor((double)(x))))

class GlobalData
{
public:
	unsigned char m_unreconstructed_00[0x30];
	Int m_xResolution;
};

extern class GlobalData *TheWritableGlobalData;

class GlobalLanguage
{
public:
	Int adjustFontSize(Int theFontSize);
	static void parseFontDesc(class INI *ini, void *instance, void *store, const void *userData);
};

Int GlobalLanguage::adjustFontSize(Int theFontSize)
{
	Real ratio = TheWritableGlobalData->m_xResolution / 1024.0f;
	Real size = theFontSize;
	return REAL_TO_INT_FLOOR(size * ratio);
}

// INI::parseLanguageDefinition, retail 0x001EA3F4 (25 bytes): the "Language"
// block parser (registration VA 0x00DB8F98 binds the token to 0x001EA3F4,
// reached only through it, so Ghidra never started a function there). The
// BFME1 donor body (GlobalLanguage.cpp) unchanged: skip without
// TheGlobalLanguageData (0x00DFDC84), else initFromINI it against the field
// table at VA 0x00BDEAA0.
class INI;
struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};
typedef void (*FieldParseProc)(INI *ini, void *instance, void *store, const void *userData);

class INI
{
public:
	void initFromINI(void *what, const FieldParse *parseTable);
	static void parseLanguageDefinition(INI *ini);
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseBool(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
};

struct Rva001EAD69Owner;
void parseStringEntryRva001EAD69(INI *ini, Rva001EAD69Owner *owner);

extern GlobalLanguage *TheGlobalLanguageData;

// Retail's language field table at VA 0x00BDEAA0 (.rdata, 512 bytes: 31
// records and the zero sentinel), transcribed from retail's own bytes; the
// BFME1 donor's TheGlobalLanguageDataFieldParseTable keeps the name.
extern const FieldParse TheGlobalLanguageDataFieldParseTable[] =
{
	{ "DecimalSeparator",               &INI::parseAsciiString,                       0, 0x0C },
	{ "ThousandSeparator",              &INI::parseAsciiString,                       0, 0x10 },
	{ "TimeMinuteToSecondSeparator",    &INI::parseAsciiString,                       0, 0x14 },
	{ "UnicodeFontName",                &INI::parseAsciiString,                       0, 0x18 },
	{ "LocalFontFile",                  (FieldParseProc)&parseStringEntryRva001EAD69, 0, 0x00 },
	{ "MilitaryCaptionSpeed",           &INI::parseInt,                               0, 0x28 },
	{ "UseHardWordWrap",                &INI::parseBool,                              0, 0x24 },
	{ "ResolutionFontAdjustment",       &INI::parseReal,                              0, 0x134 },
	{ "AudioLanguage",                  &INI::parseAsciiString,                       0, 0x20 },
	{ "CopyrightFont",                  &GlobalLanguage::parseFontDesc,               0, 0x2C },
	{ "MessageFont",                    &GlobalLanguage::parseFontDesc,               0, 0x38 },
	{ "MilitaryCaptionTitleFont",       &GlobalLanguage::parseFontDesc,               0, 0x44 },
	{ "MilitaryCaptionFont",            &GlobalLanguage::parseFontDesc,               0, 0x50 },
	{ "AudioSubtitleFont",              &GlobalLanguage::parseFontDesc,               0, 0x5C },
	{ "SuperweaponCountdownNormalFont", &GlobalLanguage::parseFontDesc,               0, 0x68 },
	{ "SuperweaponCountdownReadyFont",  &GlobalLanguage::parseFontDesc,               0, 0x74 },
	{ "NamedTimerCountdownNormalFont",  &GlobalLanguage::parseFontDesc,               0, 0x80 },
	{ "NamedTimerCountdownReadyFont",   &GlobalLanguage::parseFontDesc,               0, 0x8C },
	{ "DrawableCaptionFont",            &GlobalLanguage::parseFontDesc,               0, 0x98 },
	{ "DefaultWindowFont",              &GlobalLanguage::parseFontDesc,               0, 0xA4 },
	{ "DefaultDisplayStringFont",       &GlobalLanguage::parseFontDesc,               0, 0xB0 },
	{ "TooltipFontName",                &GlobalLanguage::parseFontDesc,               0, 0xBC },
	{ "NativeDebugDisplay",             &GlobalLanguage::parseFontDesc,               0, 0xC8 },
	{ "DrawGroupInfoFont",              &GlobalLanguage::parseFontDesc,               0, 0xD4 },
	{ "CreditsTitleFont",               &GlobalLanguage::parseFontDesc,               0, 0xE0 },
	{ "CreditsMinorTitleFont",          &GlobalLanguage::parseFontDesc,               0, 0xEC },
	{ "CreditsNormalFont",              &GlobalLanguage::parseFontDesc,               0, 0xF8 },
	{ "HelpBoxNameFont",                &GlobalLanguage::parseFontDesc,               0, 0x104 },
	{ "HelpBoxCostFont",                &GlobalLanguage::parseFontDesc,               0, 0x110 },
	{ "HelpBoxShortcutFont",            &GlobalLanguage::parseFontDesc,               0, 0x11C },
	{ "HelpBoxDescriptionFont",         &GlobalLanguage::parseFontDesc,               0, 0x128 },
	{ 0, 0, 0, 0 }
};


void INI::parseLanguageDefinition(INI *ini)
{
	if (!TheGlobalLanguageData)
		return;
	// parse the ini weapon definition
	ini->initFromINI(TheGlobalLanguageData, TheGlobalLanguageDataFieldParseTable);
}
