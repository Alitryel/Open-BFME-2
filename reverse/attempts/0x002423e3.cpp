// ?rva002423E3@GameLogic@@QAE_NXZ
// partial score=0.94 date=2026-10-20
// cl: /O1 /G7 /DNDEBUG /MD /EHs /arch:SSE /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist
// stlport
//
// Home unit: Code/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// ?deleteLoadScreen@GameLogic@@QAEXXZ @0x002423E3 1436B (SEH).
// Donor: BFME 1 game/GameEngine/Source/GameLogic/System/GameLogicInit.cpp
// (GameLogic::deleteLoadScreen). BFME 2 differs from the donor with moved
// field offsets and out-of-line setters (Rva001DBB82OneSetter::enable /
// Rva001DBB87ZeroSetter::disable). Field names stay offset names: only the
// donor knows their meaning.

// Missing: full definitions for AsciiString, GameWindowTransitionsHandler,
// Mouse, W3DDisplay, GameLogic members, TheGameLogic, Sleep and free-function
// callees (rva0023C7BB / rva0023C7D2 / rva0023DCCE / rva0023DC8E) plus ref1/ref2.
//
// claude-opus-5-5 rebuild (2026-10-20): retail ends every path in mov al,1, so the body
// returns bool and keeps an address-derived name; the Zero Hour deleteLoadScreen shape
// (delete +0x120, clear it) is the separate 0x0023C7D2 this stage calls, with
// updateLoadProgress at 0x0023C7BB. Callees and globals follow GameLogicInit.cpp, the
// home unit (file-static g_00DFE788 lives there). BFME 1 twin: 0x0038D100 bank.
// Remaining mismatch and landing prerequisites:
// reverse/attempt_support/0x002423e3-load-screen-stage/handoff.md

#include "ascii_string.h"

extern "C" __declspec(dllimport) void __stdcall Sleep(unsigned long milliseconds);

class GameEngine
{
public:
	virtual void e00(); virtual void e01(); virtual void e02(); virtual void e03();
	virtual void e04(); virtual void e05(); virtual void e06(); virtual void e07();
	virtual void e08(); virtual void e09(); virtual void e0a(); virtual void e0b();
	virtual void e0c(); virtual void e0d(); virtual void e0e(); virtual void e0f();
	virtual void e10(); virtual void e11(); virtual void e12(); virtual void e13();
	virtual void setQuitting(bool quitting);                             // +0x50
	virtual void e15();
	virtual bool isMultiplayerSession(void);                             // +0x58
	virtual void slot5C(void);                                           // +0x5C
};

class GameWindowTransitionsHandler
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08();
	virtual void slot24();
	virtual void slot28();
	void rva001DC5EC(void);
	void reverse(AsciiString groupName);
	void setGroup(AsciiString groupName, bool immidiate = false);
	bool isFinished(void);
};

class Rva001DBB82OneSetter
{
public:
	void enable(void);
};

class Rva001DBB87ZeroSetter
{
public:
	void disable(void);
};

class Rva001DBAA4
{
public:
	void unlock(void);
};

extern GameWindowTransitionsHandler *TheTransitionHandler;

class Rva0023C565
{
public:
	Rva0023C565();
	~Rva0023C565()
	{
		if (TheTransitionHandler)
			((Rva001DBAA4 *)TheTransitionHandler)->unlock();
	}
};

class Rva0023C7D2
{
public:
	void rva0023C7D2(void);
	void rva0023C7BB(int value);
};

class NetworkInterface
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void v10(); virtual void v11(); virtual void v12(); virtual void v13();
	virtual void v14(); virtual void v15(); virtual void v16(); virtual void v17();
	virtual void v18(); virtual void v19(); virtual void v1a(); virtual void v1b();
	virtual void v1c(); virtual void v1d(); virtual void v1e(); virtual void v1f();
	virtual void v20(); virtual void v21(); virtual void v22(); virtual void v23();
	virtual void v24(); virtual void v25(); virtual void v26(); virtual void v27();
	virtual void v28(); virtual void v29(); virtual void v2a(); virtual void v2b();
	virtual void v2c(); virtual void v2d(); virtual void v2e(); virtual void v2f();
	virtual void v30(); virtual void v31(); virtual void v32(); virtual void v33();
	virtual bool slotD0(void);                                           // +0xD0
};

class Display
{
public:
	virtual void d00(); virtual void d01(); virtual void d02(); virtual void d03();
	virtual void d04(); virtual void d05(); virtual void d06(); virtual void d07();
	virtual void d08(); virtual void d09(); virtual void d0a(); virtual void d0b();
	virtual void d0c(); virtual void d0d(); virtual void d0e(); virtual void d0f();
	virtual void d10(); virtual void d11(); virtual void d12(); virtual void d13();
	virtual void d14(); virtual void d15(); virtual void d16(); virtual void d17();
	virtual void d18(); virtual void d19(); virtual void d1a(); virtual void d1b();
	virtual void d1c(); virtual void d1d(); virtual void d1e(); virtual void d1f();
	virtual void d20(); virtual void d21(); virtual void d22(); virtual void d23();
	virtual void d24(); virtual void d25(); virtual void d26(); virtual void d27();
	virtual void d28(); virtual void d29(); virtual void d2a(); virtual void d2b();
	virtual void d2c(); virtual void d2d(); virtual void d2e(); virtual void d2f();
	virtual void d30(); virtual void d31(); virtual void d32(); virtual void d33();
	virtual void d34(); virtual void d35(); virtual void d36(); virtual void d37();
	virtual void d38(); virtual void d39(); virtual void d3a(); virtual void d3b();
	virtual void d3c(); virtual void d3d(); virtual void d3e(); virtual void d3f();
	virtual void d40(); virtual void d41(); virtual void d42();
	virtual void slot10C(AsciiString movie, int a, int b);              // +0x10C
	virtual void slot110(void);                                          // +0x110
	virtual bool slot114(void);                                          // +0x114
	char m_pad004[0x115 - 0x4];
	bool m_115;
	char m_pad116[0x13c - 0x116];
	int m_13c;
};

class W3DDisplay
{
public:
	void rva0025D2F6(void);
};

class AudioManager
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v0a(); virtual void v0b();
	virtual void v0c(); virtual void v0d(); virtual void v0e(); virtual void v0f();
	virtual void v10();
	virtual void slot44(int a, int b, int c);                            // +0x44
	virtual void v12(); virtual void v13();
	virtual void slot50(bool b);                                         // +0x50
};

class GlobalData
{
public:
	char m_pad000[0x9ad];
	bool m_9ad;
	char m_pad9AE[0x11c8 - 0x9ae];
	bool m_11c8;
};

extern GlobalData *TheWritableGlobalData;

class Mouse
{
public:
	void _bfme_setEngineVisibility(bool visible);
};

class Rva00222A8BTarget
{
public:
	void rva00222F55(bool flag);
	char m_pad[0x31C];
	int m_31c;
};

class OpaqueRefCounted
{
public:
	void Release_Ref(void);
	void Add_Ref(void);
};

struct OpaqueRefElement4
{
	OpaqueRefCounted *referent;
	OpaqueRefElement4() : referent(0) {}
	~OpaqueRefElement4() { if (referent) referent->Release_Ref(); }
	OpaqueRefElement4 &operator=(const OpaqueRefElement4 &other)
	{
		if (other.referent)
			other.referent->Add_Ref();
		if (referent)
			referent->Release_Ref();
		referent = other.referent;
		return *this;
	}
};

struct Rva000A8C9B
{
	OpaqueRefCounted *m_ptr;
	void clear() { if (m_ptr) { m_ptr->Release_Ref(); m_ptr = 0; } }
};

// The rowed setter 0x0023DCCE (Rva0023DCCESet.cpp) shares retail's unit; its body and the
// inline reference ops below stay visible so the caller keeps the temporaries' release out.
class Rva0023DCCE
{
public:
	void rva0023DCCE(const AsciiString &a, const OpaqueRefElement4 &b, const OpaqueRefElement4 &c)
	{
		if (((const StringBase<char> *)&a)->isEmpty() || TheWritableGlobalData->m_9ad)
		{
			m_flag = 0;
			m_str.clear();
			((Rva000A8C9B *)&m_a)->clear();
			((Rva000A8C9B *)&m_b)->clear();
		}
		else
		{
			m_flag = 1;
			m_str = a;
			m_a = b;
			m_b = c;
		}
	}
	char m_00[0x72];
	unsigned char m_flag;
	char m_01[0x11];
	AsciiString m_str;
	OpaqueRefElement4 m_a;
	OpaqueRefElement4 m_b;
};

class Rva0023DC8E
{
public:
	void rva0023DC8E(const AsciiString &a);
};

// The 8-byte (group name, frame) value the timed reverse 0x0023E323 consumes.
class Rva0023E323
{
public:
	Rva0023E323(const AsciiString &groupName, int frame) : m_groupName(groupName), m_frame(frame) {}
	AsciiString m_groupName;
	int m_frame;
};

// Callback holder; the converting constructor is the rowed 0x002419AB.
class Rva00211E75Callback
{
public:
	Rva00211E75Callback(Rva0023E323 value);
	Rva00211E75Callback(const Rva00211E75Callback &other);
	void *m_bfmeNode;
};

bool Rva003FE7E6(Rva00211E75Callback callback, int *id);

class LoadScreen;

class GameLogic
{
public:
	bool rva002423E3(void);
	// Header inline in retail (COMDAT 0x001DCD1C), called out of line here.
	bool rva001DCD1C(void) { return m_110 == 8 || (m_110 == 9 && m_114 != 3); }
	unsigned int getFrame(void) const { return m_40; }

	char m_pad000[0x40];
	unsigned int m_40;
	char m_pad044[0x74 - 0x44];
	AsciiString m_74;
	char m_pad078[0x90 - 0x78];
	int m_90;
	char m_pad094[0x9c - 0x94];
	bool m_9c;
	bool m_9d;
	bool m_9e;
	char m_pad09F[0x110 - 0x9f];
	int m_110;
	int m_114;
	char m_pad118[0x120 - 0x118];
	LoadScreen *m_120;
};

extern GameEngine *TheGameEngine;
extern NetworkInterface *TheNetwork;
extern GameLogic *TheGameLogic;
extern Display *TheDisplay;
extern Mouse *TheMouse;
extern AudioManager *TheAudio;
class BfmeAptWindowManager;
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
extern int g_00E02EC4;
static float g_00DFE788;

// Load-screen teardown stage: pumps the first frames of a network load, then fades the
// screen through FadeWholeScreen by game mode and resets the mouse, audio and map strings.
bool GameLogic::rva002423E3(void)
{
	if (!m_9c)
		return true;

	TheGameEngine->slot5C();

	if (TheNetwork && !TheNetwork->slotD0())
	{
		int mode = m_110;
		if (mode == 1 || mode == 5 || mode == 2)
		{
			unsigned int frame = TheGameLogic->getFrame();
			if (frame < 6)
			{
				if (frame >= 5)
				{
					((Rva0023C7D2 *)this)->rva0023C7BB(100);
					return true;
				}
				((Rva0023C7D2 *)this)->rva0023C7BB((int)g_00DFE788);
				g_00DFE788 += 0.25f;
				return true;
			}
		}
	}

	bool restoreMouse = false;
	m_9c = false;

	if (m_120 && TheDisplay->slot114() && !TheWritableGlobalData->m_11c8)
	{
		if (m_9e)
		{
			{
				Rva0023C565 lock;
				TheTransitionHandler->slot24();
				TheTransitionHandler->setGroup("FadeWholeScreen");
				((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
				TheTransitionHandler->slot28();
			}
			while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
			{
				TheGameEngine->slot5C();
				Sleep(1);
			}
			((W3DDisplay *)TheDisplay)->rva0025D2F6();
			TheTransitionHandler->reverse("FadeWholeScreen");
			TheTransitionHandler->slot28();
			((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
			m_9e = false;
			restoreMouse = true;
		}
		else
		{
			switch (m_110)
			{
				case 0:
				case 6:
					((Rva00222A8BTarget *)g_bfmeAptWindowManager)->rva00222F55(true);
					TheTransitionHandler->setGroup("FadeWholeScreen");
					((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
					while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
					{
						TheGameEngine->slot5C();
						Sleep(5);
					}
					((Rva0023C7D2 *)this)->rva0023C7D2();
					if (!((const StringBase<char> *)&m_74)->isEmpty())
					{
						((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
						TheTransitionHandler->slot24();
						TheTransitionHandler->slot28();
						TheDisplay->slot10C(m_74, 1, 0xa0);
						m_74.clear();
					}
					else
					{
						TheDisplay->slot110();
					}
					restoreMouse = true;
					{
						AsciiString fadeGroup("FadeWholeScreen");
						Rva003FE7E6(Rva0023E323(fadeGroup, m_90), &g_00E02EC4);
					}
					break;

				case 2:
				case 3:
					TheTransitionHandler->setGroup("FadeWholeScreen");
					((Rva001DBB82OneSetter *)TheTransitionHandler)->enable();
					TheTransitionHandler->slot28();
					while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
					{
						TheGameEngine->slot5C();
						Sleep(5);
					}
					{
						AsciiString fadeGroup("FadeWholeScreen");
						Rva003FE7E6(Rva0023E323(fadeGroup, m_90), &g_00E02EC4);
					}
					TheTransitionHandler->slot28();
					break;

				case 4:
				case 7:
					TheTransitionHandler->slot24();
					if (!g_bfmeAptWindowManager || !((Rva00222A8BTarget *)g_bfmeAptWindowManager)->m_31c)
					{
						TheTransitionHandler->setGroup("FadeWholeScreen");
						TheTransitionHandler->slot28();
						while (TheDisplay->slot114() && TheDisplay->m_13c < 100 && !TheTransitionHandler->isFinished())
						{
							TheGameEngine->slot5C();
							Sleep(1);
						}
					}
					restoreMouse = true;
					break;

				default:
					TheDisplay->slot110();
					((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
					restoreMouse = true;
					break;
			}
		}
	}
	else
	{
		((Rva001DBB87ZeroSetter *)TheTransitionHandler)->disable();
		restoreMouse = true;
	}

	if (m_120)
		((Rva0023C7D2 *)this)->rva0023C7D2();
	if (restoreMouse)
		TheMouse->_bfme_setEngineVisibility(true);
	TheDisplay->m_115 = false;
	TheGameEngine->slot5C();
	if (TheAudio)
	{
		if (rva001DCD1C())
		{
			TheAudio->slot50(true);
			TheAudio->slot44(0x3f, 6, 0);
		}
		else
		{
			TheAudio->slot50(false);
			TheAudio->slot44(0x3f, 5, 0);
		}
	}
	((Rva0023DCCE *)this)->rva0023DCCE(AsciiString::TheEmptyString, OpaqueRefElement4(), OpaqueRefElement4());
	((Rva0023DC8E *)this)->rva0023DC8E(AsciiString::TheEmptyString);
	m_90 = 7;
	return true;
}
