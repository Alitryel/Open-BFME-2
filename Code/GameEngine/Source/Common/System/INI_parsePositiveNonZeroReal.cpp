// cl: /O1 /Oy- /arch:SSE /DNDEBUG /MD /GX /Oi-
//
// ?parsePositiveNonZeroReal@INI@@SAXPAV1@PAX1PBX@Z, retail 0x002EFDC, 83 bytes.
// Dedicated ebp-frame TU (same INI scanner family as INI_scanBool.cpp).
//
// BFME1 reference (reference/open-bfme-1/Code/GameEngine/Source/Common/INI/ini_parsers.cpp,
// INI::parsePositiveNonZeroReal): verbatim logic (store, throw iff <= 0).
// BFME2 deltas: explicit NULL seps, member scanReal, filler plus throw. The
// named value is load-bearing: it keeps the scan result on the x87 stack
// (fld-dup for the store, fld-dup plus fldz plus fcompi for the check) where
// the reference's store-reload form would emit an fld from memory.

class INI
{
public:
	const char *getNextToken(const char *seps);
	float scanReal(const char *token);
	static void parsePositiveNonZeroReal(INI *ini, void *instance, void *store, const void *userData);
};

class INIException
{
public:
	INIException(int argCount, const char *format, ...);
	char *mFailureMessage;
	int mErrorCode;
	INIException(const INIException &that);
	~INIException();
};


// ?parsePositiveNonZeroReal@INI@@SAXPAV1@PAX1PBX@Z
void INI::parsePositiveNonZeroReal(INI *ini, void *instance, void *store, const void *userData)
{
	float value = ini->scanReal(ini->getNextToken(0));
	*(float *)store = value;
	if (value <= 0.0f) {
		throw INIException(3, "invalid Real value %1.7f -- expected > 0", value);
	}
}
