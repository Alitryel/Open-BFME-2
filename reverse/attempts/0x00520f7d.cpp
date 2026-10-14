// ?rva00520F7D@@YA_NXZ
// partial score=0.635 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva00520F7D@@YA_NXZ @0x00520F7D 367B. WB 0x13DB420 AptTimeLine::OpenScreen:
// game-mode selection chain then TimeLine.apt push and CollectAllPlayerData.
#include "ascii_string.h"

class GameLogic
{
public:
	bool rva0023C666();
	bool rva00210C66();
private:
	char m_pad000[0x114];
public:
	int m_114; // +0x114
	int m_118; // +0x118
};
extern GameLogic *TheGameLogic; // 0x00DFE78C

class Rva00DFEF10View
{
public:
	bool rva0044253A(); // selection-locked predicate
};
extern Rva00DFEF10View *g_00DFEF10; // 0x00DFEF10

class Bfme939Helper
{
public:
	int get() const;
};
extern Bfme939Helper *TheRecorder; // 0x00E02290

class Rva00DFE6E8Audio
{
public:
#define BFME_V(N) virtual void vslot##N();
	BFME_V(00) BFME_V(01) BFME_V(02) BFME_V(03) BFME_V(04) BFME_V(05) BFME_V(06) BFME_V(07)
	BFME_V(08) BFME_V(09) BFME_V(10) BFME_V(11) BFME_V(12) BFME_V(13) BFME_V(14) BFME_V(15)
	BFME_V(16) BFME_V(17) BFME_V(18) BFME_V(19) BFME_V(20) BFME_V(21) BFME_V(22) BFME_V(23)
	BFME_V(24)
	virtual void vslot25(void *ev);
	BFME_V(26) BFME_V(27) BFME_V(28) BFME_V(29) BFME_V(30) BFME_V(31) BFME_V(32) BFME_V(33)
	BFME_V(34) BFME_V(35) BFME_V(36) BFME_V(37) BFME_V(38) BFME_V(39) BFME_V(40) BFME_V(41)
	BFME_V(42) BFME_V(43) BFME_V(44) BFME_V(45) BFME_V(46) BFME_V(47) BFME_V(48) BFME_V(49)
	BFME_V(50) BFME_V(51) BFME_V(52) BFME_V(53) BFME_V(54) BFME_V(55) BFME_V(56) BFME_V(57)
	BFME_V(58) BFME_V(59) BFME_V(60) BFME_V(61) BFME_V(62) BFME_V(63) BFME_V(64) BFME_V(65)
	BFME_V(66) BFME_V(67) BFME_V(68) BFME_V(69) BFME_V(70) BFME_V(71) BFME_V(72) BFME_V(73)
	BFME_V(74) BFME_V(75) BFME_V(76) BFME_V(77)
	virtual void *vslot78(int which);
#undef BFME_V
};
extern Rva00DFE6E8Audio *TheAudio; // 0x00DFE6E8

class Shell
{
public:
	void push(AsciiString name, bool flag);
};
extern Shell *g_00E01E48; // 0x00E01E48

struct OpaqueRefElement4;
class BfmeAudioEventPrefix136
{
public:
	BfmeAudioEventPrefix136(const OpaqueRefElement4 &ref, int which);
	virtual ~BfmeAudioEventPrefix136();
	void rva002D95FE(bool active);
private:
	char m_pad[0x88 - 4];
};

class AptTimeLine
{
public:
	void rva0051FA13();
private:
	char m_pad000[0x284];
public:
	int m_284;
};
extern AptTimeLine *g_00E0491C; // 0x00E0491C

bool rva00520F7D()
{
	if (g_00E0491C != 0)
		return true;

	int mode;
	if (TheRecorder != 0 && TheRecorder->get() == 1)
	{
		mode = 5;
	}
	else if (TheGameLogic->rva0023C666())
	{
		mode = 1;
	}
	else if (TheGameLogic->m_118 != 3 && !g_00DFEF10->rva0044253A())
	{
		mode = 8;
	}
	else if (TheGameLogic->m_118 == 0 && g_00DFEF10->rva0044253A())
	{
		mode = 6;
	}
	else if ((TheGameLogic->m_118 == 1 || TheGameLogic->m_118 == 2) && g_00DFEF10->rva0044253A())
	{
		mode = 7;
	}
	else if (TheGameLogic->m_114 == 5)
	{
		mode = 4;
	}
	else if (TheGameLogic->m_114 == 1)
	{
		mode = 3;
	}
	else if (TheGameLogic->m_114 == 2)
	{
		mode = 2;
	}
	else
	{
		return false;
	}

	BfmeAudioEventPrefix136 ev(*(const OpaqueRefElement4 *)((const char *)TheAudio->vslot78(2) + 0x94), 2);
	ev.rva002D95FE(true);
	TheAudio->vslot25(&ev);
	Shell *shell = g_00E01E48;
	shell->push(AsciiString("TimeLine.apt"), false);

	if (g_00E0491C == 0)
	{
		return false;
	}
	g_00E0491C->m_284 = mode;
	g_00E0491C->rva0051FA13();
	return true;
}
