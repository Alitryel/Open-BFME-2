// cl: /DNDEBUG /MD
// ??0TextOnFrameTransition@@QAE@XZ @0x0035FA03 39B: ctor stores vtable 0x0081669C, calls rowed base ??0Rva001DBAA4 at 0x001DBAA4, then startFrame +0x10 zero endFrame +0x14 30 frameLength +0x04 30 forward +0x09 true win +0x0C zero. Evidence: vtable-proven TextOnFrameTransition with rowed update reverse init plus base ctor row plus prev CountUp deleting dtor next honest dtor 0x0035FA2A; BFME2 END 30 vs donor 1 follow retail.
typedef int Int;
class GameWindow;


class Rva001DBAA4
{
public:
	virtual ~Rva001DBAA4();
	Rva001DBAA4();

	Int m_frameLength;		// +0x04
	bool m_isFinished;		// +0x08
	bool m_isForward;		// +0x09
	bool m_isReversed;		// +0x0a
	unsigned char m_pad0B;		// +0x0b
	GameWindow *m_win;		// +0x0c
};

class TextOnFrameTransition : public Rva001DBAA4
{
public:
	// Retail vftable 0x00C1669C: the destructor (0x0035FA2A) clears +0x0C and chains to
	// the base; draw and skip are the shared empty body 0x000B3FD0.
	virtual ~TextOnFrameTransition(void) { m_win = 0; }
	virtual void init(GameWindow *win);
	virtual void update(Int frame);
	virtual void reverse(void);
	virtual void draw(void) {}
	virtual void skip(void) {}
	TextOnFrameTransition(void);

	Int m_startFrame;	// +0x10
	Int m_endFrame;		// +0x14
};

TextOnFrameTransition::TextOnFrameTransition(void)
{
	m_startFrame = 0;
	m_win = 0;
	m_endFrame = 30;
	m_frameLength = 30;
	m_isForward = true;
}

