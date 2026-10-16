// cl: /O1 /arch:SSE /G7 /Ireference/shims/bfme2_ascii /EHsc /DNDEBUG /MD
//
// ?helper001DA770@@YAXPAVINI@@HPAVAsciiString@@PBD@Z @0x001DA770 528B.
// Shared cdecl audio-block parser for the five Default-name wrappers.
// Evidence: callers 0x001DA9AA/0x001DA9F4/0x001DAA3E/0x001DAA88/0x001DAAD2,
// strings "You cannot define or override a %s in map.ini",
// "Control flag 'RANDOMSTART' is not valid for ",
// ". Streaming sound types only, please.", TheAudio 0x009FE6E8,
// theDebug 0x009E0880, field table g_00BD9D68. WorldBuilder twin 0x00ABEF30
// (AudioEventInfo::parseAudioEventInfoDefintion, Audio/AudioEventInfo.cpp)
// reads every field through the event handle's operator->; the rowed handle
// assignment 0x00239099 is defined here so cl sees the handle's address does
// not escape and keeps the referent in ESI. Pitch clamps store -99.0f.
#include "ascii_string.h"

class INIException
{
public:
	char *mFailureMessage;
	int m_argCount;
	INIException(int argCount, const char *format, ...);
	INIException(const INIException &that);
	~INIException();
};

struct FieldParse;
class INI;
struct FieldParse
{
	const char *token;
	void (*parse)(INI *ini, void *instance, void *store, const void *userData);
	const void *userData;
	int offset;
};

class INI
{
public:
	static void parseAsciiString(INI *ini, void *instance, void *store, const void *userData);
	static void parsePercentToReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseInt(INI *ini, void *instance, void *store, const void *userData);
	static void parseReal(INI *ini, void *instance, void *store, const void *userData);
	static void parseIndexList(INI *ini, void *instance, void *store, const void *userData);
	static void parseBitString32(INI *ini, void *instance, void *store, const void *userData);

	int getLoadType() { return m_loadType; }
	const char *getNextToken(const char *seps = 0);
	void initFromINI(void *what, const struct FieldParse *table);
private:
	char m_pad00[8];
	int m_loadType;
};

extern const struct FieldParse g_00BD9D68[];

// AudioEventInfo's INI field tables (.rdata 0x00BD9D58..0x00BD9F4B) and the
// name lists they index (.data 0x00DB8A80..0x00DB8B07), read from retail.
// Both tables sit together with their userData ints, so one unit owned them;
// they are defined here beside the audio-event parser that uses the first
// (parseMultisoundDefinition, AudioEventInfoParseMultisound.cpp, uses the
// second). Entry order, tokens, parsers and offsets are retail's; the list
// names follow Zero Hour's AudioEventInfo.cpp where it has the same list.
void parsePitchShift(INI *ini, void *instance, void *store, const void *userData);
void parseDelay(INI *ini, void *instance, void *store, const void *userData);

class AudioEventInfo
{
public:
	static void parseSoundsList(INI *ini, void *instance, void *store, const void *userData);
	static void parseSubsoundsList(INI *ini, void *instance, void *store, const void *userData);
	static void parseVolumeSliderMultiplier(INI *ini, void *instance, void *store, const void *userData);
};

static const char *theAudioPriorityNames[] =
{
	"LOWEST", "LOW", "NORMAL", "HIGH", "CRITICAL", 0
};

static const char *theSoundTypeNames[] =
{
	"UI", "WORLD", "SHROUDED", "GLOBAL", "VOICE", "PLAYER", "ALLIES",
	"ENEMIES", "EVERYONE", "FAKE", "DEFAULT", 0
};

static const char *theAudioControlNames[] =
{
	"LOOP", "SEQUENTIAL", "RANDOMSTART", "INTERRUPT", "FADE_ON_KILL",
	"FADE_ON_START", "\not used by INI files", "PLAY_ONE", 0
};

// Also the slider list parseVolumeSliderMultiplier scans.
extern const char *theSubmixSliderNames[] =
{
	"SOUNDFX", "VOICE", "MUSIC", "AMBIENT", "MOVIE", "NONE", 0
};

// parseSoundsList's userData: offsets 0x5C / 0x6C / 0x7C.
static const int theSoundsListOffset = 0x5C;
static const int theAttackListOffset = 0x6C;
static const int theDecayListOffset = 0x7C;

extern const FieldParse g_00BD9D68[] =
{
	{ "Filename", INI::parseAsciiString, 0, 0x0C },
	{ "Volume", INI::parsePercentToReal, 0, 0x10 },
	{ "VolumeShift", INI::parsePercentToReal, 0, 0x14 },
	{ "PerFileVolumeShift", INI::parsePercentToReal, 0, 0x18 },
	{ "MinVolume", INI::parsePercentToReal, 0, 0x1C },
	{ "PitchShift", parsePitchShift, 0, 0x20 },
	{ "PerFilePitchShift", parsePitchShift, 0, 0x28 },
	{ "PlayPercent", INI::parsePercentToReal, 0, 0x30 },
	{ "Delay", parseDelay, 0, 0x34 },
	{ "Limit", INI::parseInt, 0, 0x3C },
	{ "Priority", INI::parseIndexList, theAudioPriorityNames, 0x44 },
	{ "Type", INI::parseBitString32, theSoundTypeNames, 0x48 },
	{ "Control", INI::parseBitString32, theAudioControlNames, 0x4C },
	{ "Sounds", AudioEventInfo::parseSoundsList, &theSoundsListOffset, 0x50 },
	{ "Attack", AudioEventInfo::parseSoundsList, &theAttackListOffset, 0x60 },
	{ "Decay", AudioEventInfo::parseSoundsList, &theDecayListOffset, 0x70 },
	{ "MinRange", INI::parseReal, 0, 0x94 },
	{ "MaxRange", INI::parseReal, 0, 0x98 },
	{ "LowPassCutoff", INI::parsePercentToReal, 0, 0x90 },
	{ "ZoomedInOffscreenVolumePercent", INI::parsePercentToReal, 0, 0x9C },
	{ "ZoomedInOffscreenMinVolumePercent", INI::parsePercentToReal, 0, 0xA0 },
	{ "ZoomedInOffscreenOcclusionPercent", INI::parsePercentToReal, 0, 0xA4 },
	{ "ReverbEffectLevel", INI::parsePercentToReal, 0, 0xA8 },
	{ "DryLevel", INI::parsePercentToReal, 0, 0xAC },
	{ "SubmixSlider", INI::parseIndexList, theSubmixSliderNames, 0xB4 },
	{ "VolumeSliderMultiplier", AudioEventInfo::parseVolumeSliderMultiplier, 0, 0xB8 },
	{ 0, 0, 0, 0 }
};

// parseSubsoundsList's userData: the total-weight offset 0x8C.
static const int theSubsoundsWeightOffset = 0x8C;

extern const FieldParse g_00BD9F1C[] =
{
	{ "Control", INI::parseBitString32, theAudioControlNames, 0x4C },
	{ "Subsounds", AudioEventInfo::parseSubsoundsList, &theSubsoundsWeightOffset, 0x80 },
	{ 0, 0, 0, 0 }
};

extern "C" __declspec(dllimport) long __stdcall InterlockedIncrement(long volatile *);

class OpaqueRefCounted
{
public:
	virtual ~OpaqueRefCounted();
	void Add_Ref() { InterlockedIncrement(&refs); }
	void Release_Ref();
private:
	long refs;
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4() : referent(0) {}
	~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other);
	class Rva001DA379 *operator->() const { return (class Rva001DA379 *)referent; }
};

inline __declspec(noinline) OpaqueRefElement4 &OpaqueRefElement4::operator=(const OpaqueRefElement4 &other)
{
	if (this != &other) {
		if (other.referent)
			other.referent->Add_Ref();
		if (referent)
			referent->Release_Ref();
		referent = other.referent;
	}
	return *this;
}

class Rva001DA379
{
public:
	Rva001DA379 *rva001DA379(const Rva001DA379 &other);
	AsciiString &getName() { return m_audioName; }
public:
	char m_pad00[8];
	AsciiString m_audioName;
	AsciiString m_filename;
	int m_10;
	float m_volumeShift;
	float m_volumeShift2;
	int m_1C;
	float m_pitchShiftMin;
	float m_pitchShiftMax;
	float m_pitchShift2Min;
	float m_pitchShift2Max;
	int m_30;
	int m_delayMin;
	int m_delayMax;
	int m_3C;
	int m_40;
	int m_44;
	unsigned int m_type;
	unsigned int m_control;
	char m_pad50[0xB0 - 0x50];
	int m_soundType;
};

class AudioManager
{
public:
	virtual void slot00(); virtual void slot01(); virtual void slot02(); virtual void slot03();
	virtual void slot04(); virtual void slot05(); virtual void slot06(); virtual void slot07();
	virtual void slot08(); virtual void slot09(); virtual void slot10(); virtual void slot11();
	virtual void slot12(); virtual void slot13(); virtual void slot14(); virtual void slot15();
	virtual void slot16(); virtual void slot17(); virtual void slot18(); virtual void slot19();
	virtual void slot20(); virtual void slot21(); virtual void slot22(); virtual void slot23();
	virtual void slot24(); virtual void slot25(); virtual void slot26(); virtual void slot27();
	virtual void slot28(); virtual void slot29(); virtual void slot30(); virtual void slot31();
	virtual void slot32(); virtual void slot33(); virtual void slot34(); virtual void slot35();
	virtual void slot36(); virtual void slot37(); virtual void slot38(); virtual void slot39();
	virtual void slot40(); virtual void slot41(); virtual void slot42(); virtual void slot43();
	virtual void slot44(); virtual void slot45(); virtual void slot46(); virtual void slot47();
	virtual void slot48(); virtual void slot49(); virtual void slot50(); virtual void slot51();
	virtual void slot52(); virtual void slot53(); virtual void slot54(); virtual void slot55();
	virtual void slot56(); virtual void slot57(); virtual void slot58(); virtual void slot59();
	virtual void slot60(); virtual void slot61(); virtual void slot62(); virtual void slot63();
	virtual void slot64(); virtual void slot65(); virtual void slot66(); virtual void slot67();
	virtual void slot68(); virtual void slot69(); virtual void slot70(); virtual void slot71();
	virtual void slot72();
	virtual OpaqueRefElement4 newAudioEventInfo(const AsciiString &name, int create);
	virtual void slot74();
	virtual OpaqueRefElement4 findAudioEventInfo(const AsciiString &name) const;
};

extern AudioManager *TheAudio;

class Debug
{
public:
	virtual void pad00(); virtual void pad01(); virtual void pad02(); virtual void pad03();
	virtual void pad04(); virtual void pad05(); virtual void pad06(); virtual void pad07();
	virtual void pad08(); virtual void pad09(); virtual void pad10(); virtual void pad11();
	virtual void pad12(); virtual void pad13();
	virtual Debug &operator<<(const char *str);
	virtual void pad15(); virtual void pad16(); virtual void pad17(); virtual void pad18();
	virtual bool CrashDone(int mode);
	virtual void pad20(); virtual void pad21(); virtual void pad22();
	virtual void SetCrashAddress(void *returnAddress, int set);
	virtual void SkipNext();
	virtual void pad25(); virtual void pad26();
	virtual Debug &CrashBegin(const char *file, int line, int reserved);
};

extern Debug *theDebug;
void _bfme_debugRecordCallsite(int kind);
bool bfmeRva000387C0();

void __cdecl helper001DA770(INI *ini, int kind, AsciiString *defName, const char *typeName)
{
	int allow = 1;
	if (ini->getLoadType() == 2)
		throw INIException(3, "You cannot define or override a %s in map.ini", typeName);
	if (ini->getLoadType() == 5)
		allow = 0;
	AsciiString name;
	OpaqueRefElement4 track;
	((StringBase<char> *)&name)->set(ini->getNextToken(0));
	track = TheAudio->newAudioEventInfo(name, allow);
	if (!track.referent)
		return;
	OpaqueRefElement4 defInfo = TheAudio->findAudioEventInfo(*defName);
	if (defInfo.referent != 0) {
		track->rva001DA379((const Rva001DA379 &)*(Rva001DA379 *)defInfo.referent);
		track->m_type &= ~0x400;
	}
	track->m_audioName = name;
	track->m_soundType = kind;
	ini->initFromINI(track.referent, g_00BD9D68);
	if (kind == 2 && (track->m_control & 4)) {
		if (bfmeRva000387C0()) {
			_bfme_debugRecordCallsite(1);
			theDebug->SkipNext();
			(theDebug->CrashBegin(0, 0, 0) << "Control flag 'RANDOMSTART' is not valid for " << typeName << ". Streaming sound types only, please.").CrashDone(2);
		}
		track->m_control &= ~4;
	}
	if (track->m_control & 0x80)
		track->m_control &= ~0x80;
	if (track->m_delayMin < 0) {
		track->m_delayMin = 0;
		if (track->m_delayMax < 0)
			track->m_delayMax = 0;
	}
	if (track->m_pitchShiftMin <= -100.0f) {
		track->m_pitchShiftMin = -99.0f;
		if (track->m_pitchShiftMax <= -100.0f)
			track->m_pitchShiftMax = -99.0f;
	}
	if (track->m_pitchShift2Min <= -100.0f) {
		track->m_pitchShift2Min = -99.0f;
		if (track->m_pitchShift2Max <= -100.0f)
			track->m_pitchShift2Max = -99.0f;
	}
	if (track->m_volumeShift < -100.0f || track->m_volumeShift > 0.0f)
		track->m_volumeShift = 0.0f;
	if (track->m_volumeShift2 < -100.0f || track->m_volumeShift2 > 0.0f)
		track->m_volumeShift2 = 0.0f;
}
