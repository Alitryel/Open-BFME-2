// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /MD
// Split from Rva007B6A00AtexitThunks.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// More 10-byte atexit cleanup thunks from the 0x007B68xx..0x007B9xxx strip, the
// companions of Rva007B6880Thunks.cpp (kept in a separate unit so concurrent
// work on that file does not collide). Each is ecx = &global then a tail jump
// to an already-rowed destructor or cleanup member: the compiler-generated
// cleanup a translation unit registers for a file-scope object. Many are
// per-TU copies of header-level objects (AsciiString keys, ATL's
// _AtlWinModule, FX default infos). The owning TUs are unrecovered, so each
// keeps an honest address name and its global an address-named extern.

#include "ascii_string.h"
#include "unicode_string.h"
#include "../../Include/Common/Rva00041004Lock.h"

namespace ATL
{
	class CAtlWinModule
	{
	public:
		void Term();
	};
}

class BfmeStringTailRecord144
{
public:
	virtual ~BfmeStringTailRecord144();
};

class TerrainFXShaderParameterSourceNamespace
{
public:
	virtual ~TerrainFXShaderParameterSourceNamespace();
};

class Rva00049C38ADwordImmSetter
{
public:
	void apply();
};

class Rva000AD6F4
{
public:
	void clear();
};

class Rva00221027
{
public:
	virtual ~Rva00221027();
};

class Rva0023DBC3
{
public:
	~Rva0023DBC3();
};

namespace FXParticleSystem
{
	class OutwardEmissionVelocityInfo
	{
	public:
		virtual ~OutwardEmissionVelocityInfo();
	};
}

class Rva004E5654
{
public:
	virtual ~Rva004E5654();
};

class PlayerPosition
{
public:
	~PlayerPosition();
};

class Rva002390CB
{
public:
	~Rva002390CB();
};

class Rva00574499
{
public:
	~Rva00574499();
};

class Rva00579731
{
public:
	virtual ~Rva00579731();
};

class Rva0057A4E7
{
public:
	~Rva0057A4E7();
};

class Rva0005970E6DwordImmSetter
{
public:
	void apply();
};

class Rva005CB3BE
{
public:
	~Rva005CB3BE();
};

class Rva005E16DA
{
public:
	virtual ~Rva005E16DA();
};

class Rva005E3DE8
{
public:
	~Rva005E3DE8();
};

class Rva005E7529
{
public:
	~Rva005E7529();
};

class SimpleFileFactoryClass
{
public:
	virtual ~SimpleFileFactoryClass();
};

class CDCCache
{
public:
	~CDCCache();
};

class BfmeThingDXB
{
public:
	void bfmeGoDXB();
};

class GeometryInfo
{
public:
	virtual ~GeometryInfo();
};

extern unsigned int g_00DDE0AC;
unsigned g_Va00DE1DC0;	// retail RVA 0x009E1DC0 (.bss), defined here
unsigned g_Va00DEBC64;	// retail RVA 0x009EBC64 (.bss), defined here
unsigned g_Va00DEBCA0;	// retail RVA 0x009EBCA0 (.bss), defined here
unsigned g_Va00DFE3E8;	// retail RVA 0x009FE3E8 (.bss), defined here
unsigned g_Va00DFE420;	// retail RVA 0x009FE420 (.bss), defined here
unsigned g_Va00DFE440;	// retail RVA 0x009FE440 (.bss), defined here
unsigned g_Va00DFE448;	// retail RVA 0x009FE448 (.bss), defined here
unsigned g_Va00DFE490;	// retail RVA 0x009FE490 (.bss), defined here
unsigned g_Va00DFE49C;	// retail RVA 0x009FE49C (.bss), defined here
unsigned g_Va00DFE4C4;	// retail RVA 0x009FE4C4 (.bss), defined here
unsigned g_Va00DFE6DC;	// retail RVA 0x009FE6DC (.bss), defined here
unsigned g_Va00DFE72C;	// retail RVA 0x009FE72C (.bss), defined here
extern unsigned g_Va00DFE7A8;
unsigned g_Va00DFE940;	// retail RVA 0x009FE940 (.bss), defined here
unsigned g_Va00DFED90;	// retail RVA 0x009FED90 (.bss), defined here
unsigned g_Va00DFED9C;	// retail RVA 0x009FED9C (.bss), defined here
unsigned g_Va00DFEDA8;	// retail RVA 0x009FEDA8 (.bss), defined here
unsigned g_Va00DFEDB4;	// retail RVA 0x009FEDB4 (.bss), defined here
unsigned g_Va00DFEDC0;	// retail RVA 0x009FEDC0 (.bss), defined here
unsigned g_Va00DFEDCC;	// retail RVA 0x009FEDCC (.bss), defined here
unsigned g_Va00DFEDD8;	// retail RVA 0x009FEDD8 (.bss), defined here
struct BfmeUiResourceEntryState;
extern BfmeUiResourceEntryState BfmeUiResourceEntryCollectorState;
unsigned g_Va00DFEE20;	// retail RVA 0x009FEE20 (.bss), defined here
extern unsigned g_Va00DFF030;
unsigned g_Va00DFF044;	// retail RVA 0x009FF044 (.bss), defined here
unsigned g_Va00DFF048;	// retail RVA 0x009FF048 (.bss), defined here
unsigned g_Va00DFF050;	// retail RVA 0x009FF050 (.bss), defined here
unsigned g_Va00DFF054;	// retail RVA 0x009FF054 (.bss), defined here
unsigned g_Va00DFF05C;	// retail RVA 0x009FF05C (.bss), defined here
unsigned g_Va00DFF060;	// retail RVA 0x009FF060 (.bss), defined here
unsigned g_Va00DFF0A0;	// retail RVA 0x009FF0A0 (.bss), defined here
unsigned g_Va00DFF0A4;	// retail RVA 0x009FF0A4 (.bss), defined here
extern unsigned g_Va00DFF0C4;
unsigned g_Va00DFF168;	// retail RVA 0x009FF168 (.bss), defined here
unsigned g_Va00E02040;	// retail RVA 0x00A02040 (.bss), defined here
unsigned g_Va00E020C8;	// retail RVA 0x00A020C8 (.bss), defined here
unsigned g_Va00E02158;	// retail RVA 0x00A02158 (.bss), defined here
unsigned g_Va00E021F8;	// retail RVA 0x00A021F8 (.bss), defined here
unsigned g_Va00E022A8;	// retail RVA 0x00A022A8 (.bss), defined here
unsigned g_Va00E022AC;	// retail RVA 0x00A022AC (.bss), defined here
extern unsigned g_Va00E022E8;
extern unsigned g_Va00E028C4;
extern unsigned g_Va00E02D68;
extern unsigned g_Va00E02D90;
extern unsigned g_Va00E02D94;
extern unsigned g_Va00E02E70;
extern unsigned g_Va00E02E74;
unsigned g_Va00E03080;	// retail RVA 0x00A03080 (.bss), defined here
unsigned g_Va00E030E4;	// retail RVA 0x00A030E4 (.bss), defined here
unsigned g_Va00E03238;	// retail RVA 0x00A03238 (.bss), defined here
extern unsigned g_Va00E032E8;
unsigned g_Va00E03318;	// retail RVA 0x00A03318 (.bss), defined here
unsigned g_Va00E03324;	// retail RVA 0x00A03324 (.bss), defined here
unsigned g_Va00E03328;	// retail RVA 0x00A03328 (.bss), defined here
unsigned g_Va00E0332C;	// retail RVA 0x00A0332C (.bss), defined here
unsigned g_Va00E03330;	// retail RVA 0x00A03330 (.bss), defined here
unsigned g_Va00E04444;	// retail RVA 0x00A04444 (.bss), defined here
unsigned g_Va00E04448;	// retail RVA 0x00A04448 (.bss), defined here
unsigned g_Va00E0445C;	// retail RVA 0x00A0445C (.bss), defined here
extern unsigned g_Va00E0447C;
extern unsigned g_Va00E04490;
unsigned g_Va00E048F4;	// retail RVA 0x00A048F4 (.bss), defined here
unsigned g_Va00E048FC;	// retail RVA 0x00A048FC (.bss), defined here
unsigned g_Va00E0494C;	// retail RVA 0x00A0494C (.bss), defined here
unsigned g_Va00E04954;	// retail RVA 0x00A04954 (.bss), defined here
unsigned g_Va00E04964;	// retail RVA 0x00A04964 (.bss), defined here
unsigned g_Va00E0498C;	// retail RVA 0x00A0498C (.bss), defined here
unsigned g_Va00E04998;	// retail RVA 0x00A04998 (.bss), defined here
unsigned g_Va00E049A0;	// retail RVA 0x00A049A0 (.bss), defined here
unsigned g_Va00E049A4;	// retail RVA 0x00A049A4 (.bss), defined here
extern unsigned g_Va00E062FC;
extern unsigned g_Va00E0630C;
extern unsigned g_Va00E0631C;
unsigned g_Va00E06360;	// retail RVA 0x00A06360 (.bss), defined here
unsigned g_Va00E063B8;	// retail RVA 0x00A063B8 (.bss), defined here
unsigned g_Va00E063C0;	// retail RVA 0x00A063C0 (.bss), defined here
extern unsigned g_Va00E063D4;
unsigned g_Va00E06458;	// retail RVA 0x00A06458 (.bss), defined here
extern unsigned g_Va00E065EC;
extern unsigned g_Va00E06620;
extern unsigned g_Va00E06710;
unsigned g_Va00E06724;	// retail RVA 0x00A06724 (.bss), defined here
extern unsigned g_Va00E06734;
extern unsigned g_Va00E06748;
unsigned g_Va00E08D48;	// retail RVA 0x00A08D48 (.bss), defined here
unsigned g_Va00E09E50;	// retail RVA 0x00A09E50 (.bss), defined here
extern unsigned g_Va00E09E60;
extern unsigned g_Va00E0C150;
unsigned g_Va00E176A0;void __cdecl rva007B6AE7();

void __cdecl rva007B6B05();

void __cdecl rva007B6DFA();

void __cdecl rva007B6E36();

void __cdecl rva007B7650();

void __cdecl rva007B766E();

void __cdecl rva007B7678();

void __cdecl rva007B76AA();

void __cdecl rva007B76E6();

void __cdecl rva007B76FA();

void __cdecl rva007B770E();

void __cdecl rva007B7718();

void __cdecl rva007B7736();

void __cdecl rva007B7768();


// ?rva007B7786@@YAXXZ @ 0x007B7786 (10B): ecx=&g_Va00DFE7A8, tail-jump to rowed ??1Rva0023DBC3@@QAE@XZ (0x0023DBC3)
void __cdecl rva007B7786()
{
	Rva0023DBC3 *p = (Rva0023DBC3 *)&g_Va00DFE7A8;
	p->~Rva0023DBC3();
}
void __cdecl rva007B7842();

void __cdecl rva007B784C();

void __cdecl rva007B7856();

void __cdecl rva007B7860();

void __cdecl rva007B786A();

void __cdecl rva007B7874();

void __cdecl rva007B787E();

void __cdecl rva007B789C();

void __cdecl rva007B78A6();

void __cdecl rva007B7979();

void __cdecl rva007B798D();

void __cdecl rva007B7997();

void __cdecl rva007B79A1();

void __cdecl rva007B79AB();

void __cdecl rva007B79B5();

void __cdecl rva007B79BF();

void __cdecl rva007B79FB();

void __cdecl rva007B7A05();

void __cdecl rva007B7A19();

void __cdecl rva007B7AA5();

void __cdecl rva007B7C87();

void __cdecl rva007B7D27();

void __cdecl rva007B7D31();

void __cdecl rva007B7D3B();

void __cdecl rva007B7D45();

void __cdecl rva007B7D77();

void __cdecl rva007B7D81();

void __cdecl rva007B7DB3();

void __cdecl rva007B7E49();

void __cdecl rva007B80A1();

void __cdecl rva007B80BF();

void __cdecl rva007B80C9();

void __cdecl rva007B8119();

void __cdecl rva007B8123();

void __cdecl rva007B8265();

void __cdecl rva007B8283();

void __cdecl rva007B8369();

void __cdecl rva007B83A5();

void __cdecl rva007B83E1();

void __cdecl rva007B83EB();

void __cdecl rva007B83F5();

void __cdecl rva007B83FF();

void __cdecl rva007B8409();

void __cdecl rva007B8F12();

void __cdecl rva007B8F1C();

void __cdecl rva007B8F26();

void __cdecl rva007B8F6D();

void __cdecl rva007B8FA9();

void __cdecl rva007B919E();

void __cdecl rva007B91A8();

void __cdecl rva007B9202();

void __cdecl rva007B920C();

void __cdecl rva007B9216();

void __cdecl rva007B9248();

void __cdecl rva007B9252();

void __cdecl rva007B9270();

void __cdecl rva007B927A();

void __cdecl rva007B94AA();

void __cdecl rva007B94B4();

void __cdecl rva007B94C8();

void __cdecl rva007B94D2();

void __cdecl rva007B957C();

void __cdecl rva007B9586();

void __cdecl rva007B95A4();

void __cdecl rva007B969E();

void __cdecl rva007B972A();

void __cdecl rva007B9734();

void __cdecl rva007B9825();

void __cdecl rva007B9947();

void __cdecl rva007B9965();


// ?rva007B9979@@YAXXZ @ 0x007B9979 (10B): ecx=&g_Va00E06734, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9979()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_Va00E06734;
	p->Rva005E16DA::~Rva005E16DA();
}

// ?rva007B9983@@YAXXZ @ 0x007B9983 (10B): ecx=&g_Va00E06748, tail-jump to rowed ??1Rva005E16DA@@UAE@XZ (0x005E16FD)
void __cdecl rva007B9983()
{
	Rva005E16DA *p = (Rva005E16DA *)&g_Va00E06748;
	p->Rva005E16DA::~Rva005E16DA();
}
void __cdecl rva007B9AB0();

void __cdecl rva007B9B00();

void __cdecl rva007B9B0A();

void __cdecl rva007B9B14();

void __cdecl rva007B9B1E();

void __cdecl rva007B9B28();

void __cdecl rva007B9BF0();

void __cdecl rva007B9C00();

void __cdecl rva007B9C20();

