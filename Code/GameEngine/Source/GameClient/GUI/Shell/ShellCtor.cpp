// cl: /DNDEBUG /MD /EHs /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// ??0Shell@@QAE@XZ @0x0035BFBC (203B): chain ctor calls baseConstruct 0x001B4E63 then sets vtable 0x00816208; clears stack +0xC-0x4B; String set at +0x58 with empty string; NEW AnimateWindowManager 0x38 at +0x60 via 0x0053B550; NEW Rva002007D5 8 at +0x64 via 0x00200774.
// Retail's unwind map destroys the SubsystemInterface-style base (0x001B4E74)
// in state 0 and the narrow string at +0x58 in state 1, then guards both
// allocations (states 2 and 3). The string therefore has a destructor; the
// banked 0.93 attempt gave it none and lost state 1.
// The constructor and ShellTop's destructor use the rowed subsystem base.
typedef bool Bool;
#define BFME_ASCII_DTOR_DECL
#include "subsystem_interface.h"

class WindowLayout;
class AnimateWindowManager
{
public:
	AnimateWindowManager();
private:
	char m_pad[0x38];
};

class Rva002007D5
{
public:
	Rva002007D5();
private:
	char m_pad[8];
};

class Shell : public SubsystemInterface
{
public:
	Shell();
	virtual void update();
private:
	WindowLayout *m_screenStack[16];
	int m_screenCount;
	unsigned char m_50;
	unsigned char m_51;
	unsigned char m_52;
	unsigned char m_53;
	unsigned char m_54;
	unsigned char m_pad55[3];
	AsciiString m_pendingPushName;
	bool m_isShellActive;
	bool m_shellMapOn;
	unsigned char m_pad5E[2];
	AnimateWindowManager *m_animate;
	Rva002007D5 *m_scheme;
	int m_68;
	bool m_6c;
	bool m_6d;
	unsigned char m_pad6E[2];
	int m_70;
	int m_74;
public:
	virtual ~Shell();	// rowed elsewhere; declared so this unit binds to it
};

Shell::Shell()
{
	int i;
	m_screenCount = 0;
	for (i = 0; i < 16; i++)
		m_screenStack[i] = 0;
	m_52 = 0;
	m_53 = 0;
	m_50 = 0;
	m_51 = 0;
	m_54 = 0;
	m_pendingPushName.set("");
	m_isShellActive = true;
	m_shellMapOn = false;
	m_animate = new AnimateWindowManager;
	m_scheme = new Rva002007D5;
	m_68 = 1;
	m_6c = true;
	m_6d = true;
	m_70 = 0;
	m_74 = 0;
	m_screenCount = 0;
}
