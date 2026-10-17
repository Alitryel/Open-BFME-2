// ?Rva002264B3Fallback@@YAHHH@Z
// partial score=0.203 date=2026-10-17
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

// Helpers referenced by the fallback body.  Only the declarations the body
// needs to call are given here; their real bodies live in other units.
int Rva00226140Get();
Bool Rva00226146Less(int, int);
int Rva00225A93Get(int, int, int, int, int);
int Rva00226156(int, GameEngine *);
int sub_003EFEB2(int, int);

int Rva002264B3Fallback(int a, int b)
{
	volatile int fill1 = (int)0xCFCECDCC;
	volatile int fill2 = 0;
	int dummyFrame[8]; dummyFrame[0]=(int)0xCFCECDCC; dummyFrame[1]=0; dummyFrame[2]=1; dummyFrame[3]=0x6264C0; dummyFrame[4]=(int)0xCFCECDCC; dummyFrame[5]=0; dummyFrame[6]=0; dummyFrame[7]=0;
	int _ediSave = 0; *(volatile int*)&_ediSave = _ediSave;
	GameEngine *p = (GameEngine *)Rva00226140Get();
	*(volatile GameEngine **)&p = p;
	int x = sub_003EFEB2((int)*(volatile GameEngine **)&p, a);
	*(volatile int*)&x = x;
	int y = sub_003EFEB2((int)*(volatile GameEngine **)&p, b);
	*(volatile int*)&y = y;
	struct PadX { int v; unsigned char pad[8]; } px; px.v = x;
	struct PadY { int v; Bool b; unsigned char pad[10]; } py; py.v = y;
	Bool flag = 0;
	*(volatile Bool*)&flag = Rva00226146Less(px.v, py.v);

	int r;
	{
		int xa = *(volatile int *)&x;
		int ya = *(volatile int *)&y;
		Bool f = flag;
		r = Rva00225A93Get(5, 0xe, xa, ya, (int)f);
	}

	if (flag)
	{
		if (x == 1)
		{
			*(volatile int *)((char *)p + 0x18) = 0;
		}
	}

	int result;
	if (0)
	{
		int t = b;
		result = t;
	}
	else if (0)
	{
		result = x;
	}
	else
	{
		result = Rva00226156(r, p);
	}

	return result;
}
