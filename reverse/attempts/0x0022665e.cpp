// ?Rva0022665EFallback@@YAHHH@Z
// partial score=0.324 date=2026-10-17
// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
//
// The vtable at 0x00BE7188 is installed by the GameEngine constructor and
// carries the frame-loop method at 0x00225DA9.  Its slot 0 is the 28-byte
// scalar deleting destructor at 0x00226333.  The complete destructor body is
// still held anonymously at 0x00225B9B; the symbols pin records that call
// target without claiming an unverified body here.
//
// MSVC emits the 28-byte wrapper when the class has an out-of-line virtual
// base destructor. The base is the native SubsystemInterface header (ctor
// 0x001B4E63 / dtor 0x001B4E74 rowed as ??0/??1SubsystemInterface, 14-slot
// vtable 0x00BD77A0), the same view GameEngineCompleteDestructor.cpp uses, so
// both units emit one GameEngine vtable and this one no longer emits a private
// SubsystemInterface vtable. Retail's GameEngine vtable has 40 slots; the 26
// GameEngine slots past the base are not modelled by either unit yet.
typedef bool Bool;
#include "subsystem_interface.h"

class GameEngine : public SubsystemInterface
{
public:
	virtual ~GameEngine();
	GameEngine(struct EmitVtableTag *);
};

// GameEngine::~GameEngine: defined in GameEngineCompleteDestructor.cpp (its row's unit).

// Helper declarations matched to the retail call targets.
int Rva00226140Get();
int Rva0006D5B0sum(unsigned int, unsigned int);
int Rva00225A93Get(int, int, int, int, int);
int Rva00226156(int, int);

// The two-argument helper at 0x003EFEB2, taking the engine pointer and one
// of the two incoming integers.
int Rva0003EFEB2(int, int);

int Rva0022665EFallback(int a, int b)
{
	volatile int churn[4];
	churn[0] = 0x62666b; churn[1] = 1; churn[2] = 0; churn[3] = (int)0xcfcecdcc;
	*(volatile int*)&churn[0]; *(volatile int*)&churn[1]; *(volatile int*)&churn[2]; *(volatile int*)&churn[3];
	volatile int engine = Rva00226140Get();
	volatile int v8 = Rva0003EFEB2(engine, a);
	volatile int v14 = Rva0003EFEB2(engine, b);
	volatile int v10 = Rva0006D5B0sum(v8, v14);
	unsigned char vc = 0;

	v10 = Rva00225A93Get(5, 2, v8, v14, v10);

	if (0) { AsciiString d; }
	{
		AsciiString flag(0 ? (const char*)0 : (const char*)0);
		*(volatile unsigned char*)&flag = *(unsigned char*)&flag;
		if (1 ? v8 == 1 : v8 == 1)
			*(volatile int*)((char *)engine + 0x18) = 0;
	}

	if (0)
		v10 = b;

	{
		vc = Rva00226156(engine, v10);
	}

	return vc;
}
