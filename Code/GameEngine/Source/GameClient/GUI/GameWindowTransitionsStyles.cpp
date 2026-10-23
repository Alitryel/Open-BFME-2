// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD
// GameWindowTransitionsStyles: FullFadeTransition::FullFadeTransition
// (0x0035F2B3, 67B). Donor: Open-BFME-1 Code/GameEngine/Source/GameClient/GUI/
// GameWindowTransitionsStyles.cpp (frameLength, win NULL, drawState -1,
// forward TRUE); retail adds start 0 / end 30, zero position and size and a
// zero percent, and copies the frame length from the end frame. Base is the
// rowed opaque transition ctor ??0Rva001DBAA4@@QAE@XZ (0x001DBAA4); vtable
// 0x0081663C (the class of the rowed init/update/draw). Layout from
// FullFadeTransitionInit.cpp.

typedef int Int;
typedef bool Bool;
typedef float Real;

#ifndef FALSE
#define FALSE 0
#define TRUE 1
#endif

#include "../../../../Libraries/Include/Lib/ICoord2D.h"

class GameWindow;

class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();

	Int m_frameLength;		// +0x04
	Bool m_isFinished;		// +0x08
	Bool m_isForward;		// +0x09
	Bool m_isReversed;		// +0x0a
	unsigned char m_pad0B;		// +0x0b
	GameWindow *m_win;		// +0x0c
};

class FullFadeTransition : public Rva001DBAA4
{
public:
	FullFadeTransition(void);
	virtual ~FullFadeTransition(void);
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse(void) = 0;
	virtual void draw(void);
	virtual void skip(void) = 0;

	Int m_startFrame;		// +0x10
	Int m_endFrame;			// +0x14
	ICoord2D m_pos;			// +0x18
	ICoord2D m_size;		// +0x20
	Real m_percent;			// +0x28
	Int m_drawState;		// +0x2c
};

// Zeroes a coordinate through a reference. Retail reloads m_endFrame for the
// frame length after these stores: cl cannot prove a store through the
// helper's reference misses +0x14, which direct member stores would let it
// forward.
static inline void zeroCoord(ICoord2D &c)
{
	c.x = 0;
	c.y = 0;
}

// ??0FullFadeTransition@@QAE@XZ @0x0035F2B3 67B
FullFadeTransition::FullFadeTransition(void) : m_startFrame(0), m_endFrame(30)
{
	zeroCoord(m_pos);
	zeroCoord(m_size);
	m_percent = 0.0f;
	m_frameLength = m_endFrame;
	m_win = 0;
	m_drawState = -1;
	m_isForward = TRUE;
}

// The class's destructor: this unit's constructor row stores the vftable whose slot 0 is the
// deleting destructor at 0x0035F2F6, and its body calls 0x0035F1D0, where the destructor row lives.
#pragma comment(linker, "/alternatename:??1FullFadeTransition@@UAE@XZ=??1Rva0035F1D0@@UAE@XZ")
