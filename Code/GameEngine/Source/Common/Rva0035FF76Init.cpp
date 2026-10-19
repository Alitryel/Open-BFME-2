// cl: /MD
// ?init@Rva0035FF76@@UAEXPAVGameWindow@@@Z
// retail 0x0035FF85, 234 bytes. Virtual slot 1 (offset 0x4) of vtable 0x0081670C,
// the class of ??1Rva0035FF76@@UAE@XZ (dtor clears +0xC then tail-calls base
// 0x001DBAC3). Init ignores win, runs one update step from m_startFrame (+0x10)
// via slot 2 (0x0036044A), then m_percent (+0x28) is 1.0f over (m_endFrame
// (+0x14) - 1) and the three fade floats (+0x30/+0x34/+0x38) are scaled by
// 255.0f, clamped to [0,255] and stored as bytes (+0x3C/+0x3D/+0x3E).
// Evidence: vtable 0x0081670C slot 1 plus string FadeColor after the vtable,
// BFME1 donor Rva0059F720FadeColorInit.cpp plus FullFadeTransition init/update
// shape, rowed update 0x0036044A and shared reverse 0x0035D1BD and draw
// 0x0036012D in neighboring slots, ctor-like 0x0036006F defaults.

class GameWindow;

// Same 16-byte base view as Rva001DBAA4Ctor.cpp and the destructor family.
class Rva001DBAA4
{
public:
    virtual ~Rva001DBAA4();
    Rva001DBAA4();
    int m_4;
    bool m_8;
    bool m_9;
    bool m_A;
    GameWindow *m_C; // +0x0C: shared window slot, used by the derived transitions.
};

class Rva0035FF76 : public Rva001DBAA4
{
public:
	virtual ~Rva0035FF76();
	virtual void init(GameWindow *win);
	virtual void update(int frame);
	virtual void reverse();
	virtual void draw();
	virtual void skip();
	virtual bool isFinished();
	virtual int getFrameLength();

	int m_startFrame;		// +0x10
	int m_endFrame;			// +0x14
	int m_posX;			// +0x18
	int m_posY;			// +0x1C
	int m_sizeX;			// +0x20
	int m_sizeY;			// +0x24
	float m_percent;		// +0x28
	int m_drawState;		// +0x2C
	float m_fadeRed;		// +0x30
	float m_fadeGreen;		// +0x34
	float m_fadeBlue;		// +0x38
	unsigned char m_red;		// +0x3C
	unsigned char m_green;		// +0x3D
	unsigned char m_blue;		// +0x3E
};

void Rva0035FF76::init(GameWindow *)
{
	m_9 = false;
	update(m_startFrame);
	m_8 = false;
	m_9 = true;
	m_percent = 1.0f / (m_endFrame - 1);
	float scaled = m_fadeRed;
	scaled *= 255.0f;
	if (!(scaled < 255.0f))
		scaled = 255.0f;
	if (!(scaled > 0.0f))
		scaled = 0.0f;
	m_red = (unsigned char)scaled;
	scaled = m_fadeGreen;
	scaled *= 255.0f;
	if (!(scaled < 255.0f))
		scaled = 255.0f;
	if (!(scaled > 0.0f))
		scaled = 0.0f;
	m_green = (unsigned char)scaled;
	scaled = m_fadeBlue;
	scaled *= 255.0f;
	if (!(scaled < 255.0f))
		scaled = 255.0f;
	if (!(scaled > 0.0f))
		scaled = 0.0f;
	m_blue = (unsigned char)scaled;
}
