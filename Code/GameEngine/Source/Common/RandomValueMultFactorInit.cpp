// cl: /DNDEBUG /MD /O1 /G7 /arch:SSE
// ?rva007ADBFF@RandomValueMultFactorInit@@SAXXZ, retail 0x007ADBFF (47B):
// the dynamic initializer of RandomValue.cpp's multiplier at VA 0x00DFE738
// (the data ledger's _theMultFactor, which the three getValueReal units
// read): 1.0f / (powf(2, 8 * sizeof(UnsignedInt)) - 1.0f), Zero Hour's
// GeneralsMD RandomValue.cpp line 54. Retail evaluates it at static-init
// time through the C powf (0x00116DC0) with the float constants 2.0 and
// 32.0. As in the other static-init strips, the compiler-local initializer
// is written as an explicit address-named function storing the global.
typedef float Real;
typedef unsigned int UnsignedInt;

extern "C" float __cdecl powf(float x, float y);
inline Real Rva007ADBFFPow(Real x, Real y) { return powf(x, y); }

// The native initializer and three real-value readers share this writable
// float at VA 0x00DFE738. The image starts it at zero before initialization.
extern "C" Real theMultFactor;

struct RandomValueMultFactorInit
{
	static void rva007ADBFF();
};

void RandomValueMultFactorInit::rva007ADBFF()
{
	theMultFactor = 1.0f / (Rva007ADBFFPow(2, 8 * sizeof(UnsignedInt)) - 1.0f);
}
