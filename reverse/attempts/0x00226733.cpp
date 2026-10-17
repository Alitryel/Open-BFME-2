// ?Rva00226733Fallback@@YAHHH@Z
// partial score=0.253 date=2026-10-17
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

int Rva00226140Get(void);
int Rva00226156Get(GameEngine *, int);
int Rva0056DD95First(int, int);
int Rva00225A93Get(int, int, int, int, int);

int Rva00226733Fallback(int a, int b)
{
	GameEngine *engine;
	int v8;
	int v14;
	int v10;
	unsigned char flag;
	int vc;
	volatile int force_frame[8];

	vc = 0;
	*(volatile int *)&force_frame[0] = 0;

	engine = (GameEngine *)Rva00226140Get();

	v8 = Rva00226156Get(engine, a);
	v14 = Rva00226156Get(engine, b);

	*(volatile unsigned char *)&flag = 0;

	v10 = Rva0056DD95First(v8, v14);

	v10 = Rva00225A93Get(5, 0xd, v8, v14, v10);

	*(volatile int *)&force_frame[1] = v10;

	if (*(volatile int *)&vc == 1)
	{
		if (v8 == 1)
		{
			*(volatile int *)((char *)engine + 0x18) = 0;
		}
	}

	if (*(volatile int *)&vc == 2)
	{
		v10 = b;
	}

	if (*(volatile int *)&vc == 0 ? 1 : 1)
	{
		vc = v8;
	}
	else
	{
		vc = Rva00226156Get(engine, v10);
	}

	return vc;
}
