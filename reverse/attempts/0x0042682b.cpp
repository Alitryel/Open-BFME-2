// ?rva0042682B@Rva004266A1@@QAEXHE@Z
// partial score=0.909 date=2026-10-15
// ?rva0042682B@Rva004266A1@@QAEXHE@Z
// partial score=0.92 date=2026-10-03
// cl: /Ireference/shims/bfme2_ascii /ICode/GameEngine/Include /arch:SSE /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Oa
// stlport
// ?rva0042682B@Rva004266A1@@QAEXHE@Z @0x0042682B 203B evidence: same Rva004266A1 vector at +4 as rowed 0x4266A1 plus flag1 store +5 via callers 0x3BA7DF 0x3BD345 0x3BD367; TheAudio ThePlayerList plus BfmeAudioEventPrefix136 ctor 0x2D97D6 plus dword slot set 0x33F15D plus tail dtor 0x2D9A43 via prefix alias plus AudioManager slot 0x64
#include <vector>

#include "Common/BfmeAudioEventPrefix136.h"

extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)

struct Rva004266A1Rec
{
	AsciiString text;
	unsigned char flag0;
	unsigned char flag1;
	unsigned char flag2;
};

class Rva004266A1
{
public:
	bool rva004266A1(int index);
	void rva0042682B(int index, unsigned char value);
private:
	char m_00[4];
	_STL::vector<Rva004266A1Rec> m_04;
};

// ?rva004266A1@Rva004266A1@@QAE_NH@Z present-unmatched
class Rva0033F15DDwordSlot
{
public:
	void set(int value);
};

struct Bfield
{
	char m_pad[0x1a8];
	OpaqueRefElement4 m_ref;
};

class Afield
{
public:
	char m_pad0[0x34];
	Bfield *m_34;
	char m_pad1[0x54 - 0x38];
	int m_54;
};

class PlayerList
{
public:
	char m_pad[0x10];
	Afield *m_10;
};

extern PlayerList *ThePlayerList;

class AudioManager
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void s16();
	virtual void s17();
	virtual void s18();
	virtual void s19();
	virtual void s20();
	virtual void s21();
	virtual void s22();
	virtual void s23();
	virtual void s24();
	virtual void audioEvent(BfmeAudioEventPrefix136 *ev);
};

extern AudioManager *TheAudio;

// ?rva0042682B@Rva004266A1@@QAEXHE@Z present-unmatched
void Rva004266A1::rva0042682B(int index, unsigned char value)
{
	if (!rva004266A1(index))
		return;
	unsigned char old = m_04[index].flag1;
	m_04[index].flag1 = value;
	_ReadWriteBarrier();
	if (TheAudio == 0 || old != 0 || value == 0)
		return;
	if (ThePlayerList->m_10 == 0)
		return;
	if (ThePlayerList->m_10->m_34 == 0)
		return;
	if (ThePlayerList->m_10->m_34->m_ref.referent == 0)
		return;
	_ReadWriteBarrier();
	BfmeAudioEventPrefix136 ev(ThePlayerList->m_10->m_34->m_ref, 2);
	((Rva0033F15DDwordSlot *)&ev)->set(ThePlayerList->m_10->m_54);
	TheAudio->audioEvent(&ev);
}
