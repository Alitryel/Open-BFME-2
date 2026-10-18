// cl: /Ireference/shims/bfme2_ascii /MD
// Split from Rva007AB85CAtexitInits.cpp: these definitions reference a callee with no matched body yet,
// so they are kept apart from the unit's bodies that already link.
//
// Dynamic initializers from the 0x007AB7DA strip whose atexit cleanup is
// already rowed: the 12-byte ones only register the cleanup (the object's
// constructor folded away), the 27-byte ones first construct a file-scope
// AsciiString from its literal through the out-of-line AsciiString(const
// char *) at 0x0000654A. Each is the compiler-generated initializer of one
// translation unit's file-scope object; the owning TUs are unrecovered, so
// each initializer keeps its address name. Globals with no recovered owner
// are defined here: zero-filled 4-byte slots holding the AsciiString pointer.
// The live camera mode slot has a descriptive name; its original name is unknown.

#include "ascii_string.h"

extern "C" int __cdecl atexit(void (__cdecl *)(void));

void __cdecl rva007B6C9B();
void __cdecl rva007B6F5C();
void __cdecl rva007B6F98();
void __cdecl rva007B7024();
void __cdecl rva007B7090();
void __cdecl rva007B70A0();
void __cdecl rva007B71D0();
void __cdecl rva007B7200();
void __cdecl rva007B7270();
void __cdecl rva007B7300();
void __cdecl rva007B7340();
void __cdecl rva007B7380();
void __cdecl rva007B76E6();
void __cdecl rva007B770E();
void __cdecl rva007B796E();
void __cdecl rva007B7979();
void __cdecl rva007B7DB3();
void __cdecl rva007B7E49();
void __cdecl rva007B80A1();
void __cdecl rva007B8119();
void __cdecl rva007B8123();
void __cdecl rva007B8FA9();
void __cdecl rva007B95A4();
void __cdecl rva007B9680();
void __cdecl rva007B968A();
void __cdecl rva007B9B40();

// VA 0x00DEC290: zero-initialized AsciiString storage, explicitly constructed below.
unsigned BfmeLiveCameraModeNameStorage;
unsigned g_Va00DEC3B8;	// retail RVA 0x009EC3B8 (.bss), defined here
unsigned g_Va00DFF030;
unsigned g_Va00E022E8;
unsigned g_Va00E028C4;
unsigned g_Va00E02D68;
unsigned g_Va00E02E70;
unsigned g_Va00E02E74;
unsigned g_Va00E04490;	// retail RVA 0x00A04490 (.bss), defined here
unsigned g_Va00E063D4;	// retail RVA 0x00A063D4 (.bss), defined here
unsigned g_Va00E06444;	// retail RVA 0x00A06444 (.bss), defined here
unsigned g_Va00E06448;	// retail RVA 0x00A06448 (.bss), defined here

struct Rva007AB85CAtexitInits
{
	static void rva007AC25C();
	static void rva007ACAAA();
	static void rva007ACB5D();
	static void rva007ACCA6();
	static void rva007ACD90();
	static void rva007ACDA0();
	static void rva007ACE50();
	static void rva007ACE60();
	static void rva007ACE80();
	static void rva007ACED0();
	static void rva007ACEE0();
	static void rva007ACEF0();
	static void rva007ADB11();
	static void rva007ADB61();
	static void rva007AE390();
	static void rva007AE3AC();
	static void rva007AF0F1();
	static void rva007AF334();
	static void rva007AF7FE();
	static void rva007AF934();
	static void rva007AF94F();
	static void rva007B31DF();
	static void rva007B434E();
	static void rva007B46A8();
	static void rva007B46C3();
	static void rva007B55D0();
};


#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()



// ?rva007ACD90@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACD90 (12B): atexit(0x007B7090)
void Rva007AB85CAtexitInits::rva007ACD90()
{
	atexit( rva007B7090 );
}

// ?rva007ACDA0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACDA0 (12B): atexit(0x007B70A0)
void Rva007AB85CAtexitInits::rva007ACDA0()
{
	atexit( rva007B70A0 );
}



// ?rva007ACE80@Rva007AB85CAtexitInits@@SAXXZ @ 0x007ACE80 (12B): atexit(0x007B7270)
void Rva007AB85CAtexitInits::rva007ACE80()
{
	atexit( rva007B7270 );
}






// ?rva007AE390@Rva007AB85CAtexitInits@@SAXXZ @ 0x007AE390 (12B): atexit(0x007B796E)
void Rva007AB85CAtexitInits::rva007AE390()
{
	atexit( rva007B796E );
}

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

#pragma inline_depth( 0 )

#pragma inline_depth()

// ?rva007B55D0@Rva007AB85CAtexitInits@@SAXXZ @ 0x007B55D0 (12B): atexit(0x007B9B40)
void Rva007AB85CAtexitInits::rva007B55D0()
{
	atexit( rva007B9B40 );
}
