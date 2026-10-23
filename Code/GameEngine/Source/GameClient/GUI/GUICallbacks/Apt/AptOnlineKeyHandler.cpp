// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Gy
// Screen key handler 0x0051759E..0x00517724 (390 B, thiscall RET 0xC), slot 4 of
// the vftable at 0x0086641C: Esc (message 0x15, key 1, modifier bit 1) asks
// for logoff confirmation unless a chat dialog is open, Enter (0x1C/0x9C) with
// the modifier bits 0xC feeds the GameSpy login, every other key is offered to
// the +0x280 handler vector first. The confirmation is the YesNo prompt
// "APT:LogoffConfirmationTitle/Msg" through the pair-holder ctor 0x0044BF40
// (callbacks: folded CloseWindow 0x00412731 and the shared bare-ret 0x004B3FD0).
// Target facts: the call-site shape (receiver slot first, pair copied inline by
// the rowed copy ctor 0x0044BD00) and the string labels; the class name is the
// ledger's vftable owner (the screen class itself is not named).
#include "ascii_string.h"
#include "unicode_string.h"

typedef int Int;
typedef unsigned int UnsignedInt;
typedef unsigned char UnsignedByte;
typedef bool Bool;

class GameTextInterface
{
public:
	virtual ~GameTextInterface() {}
	virtual void slot00() = 0;
	virtual void slot04() = 0;
	virtual void slot08() = 0;
	virtual void slot0c() = 0;
	virtual void slot10() = 0;
	virtual void slot14() = 0;
	virtual void slot18() = 0;
	virtual void slot1c() = 0;
	virtual void slot20() = 0;
	virtual void slot24() = 0;
	virtual void slot28() = 0;
	virtual void slot2c() = 0;
	virtual void slot30() = 0;
	virtual UnicodeString fetch(const char *label, bool *exists = 0) = 0;
	virtual UnicodeString fetch(const AsciiString &label, bool *exists = 0) = 0;
};
extern GameTextInterface *TheGameText;

#define GAMESPY_SLOT(n) virtual void slot##n();
class GameSpyInfoInterface
{
public:
	GAMESPY_SLOT(00) GAMESPY_SLOT(01) GAMESPY_SLOT(02) GAMESPY_SLOT(03) GAMESPY_SLOT(04)
	GAMESPY_SLOT(05) GAMESPY_SLOT(06) GAMESPY_SLOT(07) GAMESPY_SLOT(08) GAMESPY_SLOT(09)
	GAMESPY_SLOT(10) GAMESPY_SLOT(11) GAMESPY_SLOT(12) GAMESPY_SLOT(13) GAMESPY_SLOT(14)
	GAMESPY_SLOT(15) GAMESPY_SLOT(16) GAMESPY_SLOT(17) GAMESPY_SLOT(18) GAMESPY_SLOT(19)
	GAMESPY_SLOT(20) GAMESPY_SLOT(21) GAMESPY_SLOT(22) GAMESPY_SLOT(23) GAMESPY_SLOT(24)
	GAMESPY_SLOT(25) GAMESPY_SLOT(26) GAMESPY_SLOT(27) GAMESPY_SLOT(28) GAMESPY_SLOT(29)
	GAMESPY_SLOT(30) GAMESPY_SLOT(31) GAMESPY_SLOT(32) GAMESPY_SLOT(33) GAMESPY_SLOT(34)
	GAMESPY_SLOT(35) GAMESPY_SLOT(36) GAMESPY_SLOT(37) GAMESPY_SLOT(38) GAMESPY_SLOT(39)
	GAMESPY_SLOT(40) GAMESPY_SLOT(41) GAMESPY_SLOT(42) GAMESPY_SLOT(43) GAMESPY_SLOT(44)
	GAMESPY_SLOT(45) GAMESPY_SLOT(46) GAMESPY_SLOT(47) GAMESPY_SLOT(48) GAMESPY_SLOT(49)
	GAMESPY_SLOT(50) GAMESPY_SLOT(51) GAMESPY_SLOT(52) GAMESPY_SLOT(53) GAMESPY_SLOT(54)
	GAMESPY_SLOT(55) GAMESPY_SLOT(56) GAMESPY_SLOT(57) GAMESPY_SLOT(58) GAMESPY_SLOT(59)
	GAMESPY_SLOT(60) GAMESPY_SLOT(61) GAMESPY_SLOT(62) GAMESPY_SLOT(63) GAMESPY_SLOT(64)
	GAMESPY_SLOT(65) GAMESPY_SLOT(66) GAMESPY_SLOT(67) GAMESPY_SLOT(68) GAMESPY_SLOT(69)
	GAMESPY_SLOT(70) GAMESPY_SLOT(71) GAMESPY_SLOT(72) GAMESPY_SLOT(73) GAMESPY_SLOT(74)
	GAMESPY_SLOT(75) GAMESPY_SLOT(76) GAMESPY_SLOT(77) GAMESPY_SLOT(78) GAMESPY_SLOT(79)
	GAMESPY_SLOT(80) GAMESPY_SLOT(81) GAMESPY_SLOT(82) GAMESPY_SLOT(83) GAMESPY_SLOT(84)
	GAMESPY_SLOT(85) GAMESPY_SLOT(86) GAMESPY_SLOT(87) GAMESPY_SLOT(88) GAMESPY_SLOT(89)
	GAMESPY_SLOT(90) GAMESPY_SLOT(91) GAMESPY_SLOT(92) GAMESPY_SLOT(93) GAMESPY_SLOT(94)
	GAMESPY_SLOT(95) GAMESPY_SLOT(96)
	virtual bool slot97();				// +0x184
};
extern GameSpyInfoInterface *TheGameSpyInfo;

void Rva00511730(int a);
class AptMessenger { public: static void OpenScreen(); static AptMessenger *s_instance; };

// Reference-counted callback handles (address-derived views; the callee
// releases its by-value handles).
struct TargetRef00217D4C { void *m_vtbl; int references; };
void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *);
void *__cdecl operator new(unsigned int size);
class Rva0044BC76 {
public:
    Rva0044BC76(const int *);
    __forceinline Rva0044BC76(const Rva0044BC76 &o) : m_ptr(o.m_ptr) {}
    TargetRef00217D4C *m_ptr;
};
struct ImplRef0044BC76 { virtual ~ImplRef0044BC76() {} int m_ref; ImplRef0044BC76() : m_ref(0) {} };
struct Impl0044BC76 : ImplRef0044BC76 { int m_value; Impl0044BC76(const int &v) : m_value(v) {} };
// Select-any (row: MessageBox.cpp); a strong copy here duplicated it at link.
__declspec(noinline) inline Rva0044BC76::Rva0044BC76(const int *arg)
{
    Impl0044BC76 *p = new Impl0044BC76(*arg);
    m_ptr = (TargetRef00217D4C *)p;
    if (p != 0) ++p->m_ref;
}
typedef void (*CallbackFn)();
struct Rva004F6986Member : public Rva0044BC76 {
    __forceinline Rva004F6986Member(CallbackFn fn) : Rva0044BC76((const int *)&fn) {}
    __forceinline Rva004F6986Member(const Rva004F6986Member &other) : Rva0044BC76(*(const Rva0044BC76*)&other) {
        if (m_ptr) ++m_ptr->references;
    }
    __forceinline ~Rva004F6986Member() { if (m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
class Rva004C5DD0 { public: TargetRef00217D4C *m_00,*m_04; Rva004C5DD0(const Rva004C5DD0 &o); };
struct Rva0044BA4E : Rva004C5DD0 {
    Rva0044BA4E(Rva004F6986Member,Rva004F6986Member);
    ~Rva0044BA4E();
};
struct Rva0044BF40 {
    TargetRef00217D4C *m_ptr;
    Rva0044BF40(Rva004C5DD0 pair);
    __forceinline Rva0044BF40(const Rva0044BF40 &other):m_ptr(other.m_ptr) { if(m_ptr) ++m_ptr->references; }
    __forceinline ~Rva0044BF40(){ if(m_ptr) ReleaseTreeHintRef00217D4C(m_ptr); }
};
extern "C" void __cdecl Rva00437F61(int,const UnicodeString &,const UnicodeString &,Rva0044BF40);

void CloseWindow(const char *);
class DebugDisplayInterface;
struct _iobuf;
void __cdecl rva000B3FD0DebugDisplay(DebugDisplayInterface *, void *, _iobuf *);

class Rva00517345;

class Rva0051759EHandler
{
public:
	virtual void slot00();
	virtual void slot04();
	virtual void slot08();
	virtual void slot0C();
	virtual Int handle(Rva00517345 *screen, UnsignedInt msg, UnsignedByte key, UnsignedInt state);
};

class Rva00517345
{
public:
	virtual Int rva0051759E(UnsignedInt msg, UnsignedByte key, UnsignedInt state);

private:
	char m_pad004[0x280 - 0x004];
	Rva0051759EHandler **m_handlersBegin;	// +0x280
	Rva0051759EHandler **m_handlersEnd;		// +0x284
};

Int Rva00517345::rva0051759E(UnsignedInt msg, UnsignedByte key, UnsignedInt state)
{
	Bool showLogoff = false;
	if (msg == 0x15)
	{
		if (key == 1)
		{
			if (state & 1)
			{
				if (AptMessenger::s_instance)
				{
					Rva00511730(0);
					return 1;
				}
				showLogoff = true;
			}
		}
		else if ((key == 0x1c || key == 0x9c) && (state & 0xc) && TheGameSpyInfo && TheGameSpyInfo->slot97())
		{
			if (state & 1)
			{
				if (AptMessenger::s_instance)
					Rva00511730(0);
				else
					AptMessenger::OpenScreen();
			}
			return 1;
		}
	}
	for (Rva0051759EHandler **it = m_handlersBegin; it != m_handlersEnd; ++it)
	{
		if ((*it)->handle(this, msg, key, state) == 1)
			return 1;
	}
	if (showLogoff)
	{
		UnicodeString title = TheGameText->fetch("APT:LogoffConfirmationTitle");
		UnicodeString message = TheGameText->fetch("APT:LogoffConfirmationMsg");
		Rva00437F61(2, title, message, Rva0044BF40(Rva0044BA4E(Rva004F6986Member((CallbackFn)CloseWindow), Rva004F6986Member((CallbackFn)rva000B3FD0DebugDisplay))));
	}
	return 0;
}
