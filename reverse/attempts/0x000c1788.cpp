// ?rva000C1788@Rva000C1788@@QAEXPAX@Z
// partial score=0.8557 date=2026-10-14
// ?rva000C1788@Rva000C1788@@QAEXPAX@Z
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
//
// Renderable/water-area state snapshot, retail 0x000C1788 (347 B, EH, RET4).
// The +0x44 object supplies a string through vtable +0x18, a no-arg call at
// +0x50 and a 12-float block at +0x18; the +0x104 object (when set) supplies a
// string through +8 and the +0x108 scalar. The chain arg->+0x7C / node->+0x6C /
// Rva003062FEXfer / node->+0x6C / node->+0x70 serialises the pair through the
// StringBase temporaries.
#include <stl/_algobase.h>
#include "ascii_string.h"

class XferArg
{
public:
	virtual void xferarg0();
	virtual void xferarg1();
	virtual void xferarg2();
	virtual void xferarg3();
	virtual void xferarg4();
	virtual void xferarg5();
	virtual void xferarg6();
	virtual void xferarg7();
	virtual void xferarg8();
	virtual void xferarg9();
	virtual void xferarg10();
	virtual void xferarg11();
	virtual void xferarg12();
	virtual void xferarg13();
	virtual void xferarg14();
	virtual void xferarg15();
	virtual void xferarg16();
	virtual void xferarg17();
	virtual void xferarg18();
	virtual void xferarg19();
	virtual void xferarg20();
	virtual void xferarg21();
	virtual void xferarg22();
	virtual void xferarg23();
	virtual void xferarg24();
	virtual void xferarg25();
	virtual void xferarg26();
	virtual void xferarg27();
	virtual void xferarg28();
	virtual void xferarg29();
	virtual void xferarg30();
	virtual void *a31(void *p);
};

class XferNode1
{
public:
	virtual void xfernode10();
	virtual void xfernode11();
	virtual const char *b02();
	virtual void xfernode13();
	virtual void xfernode14();
	virtual void xfernode15();
	virtual const char *b06();
	virtual void xfernode17();
	virtual void xfernode18();
	virtual void xfernode19();
	virtual void xfernode110();
	virtual void xfernode111();
	virtual void xfernode112();
	virtual void xfernode113();
	virtual void xfernode114();
	virtual void xfernode115();
	virtual void xfernode116();
	virtual void xfernode117();
	virtual void xfernode118();
	virtual void xfernode119();
	virtual void b20();
	virtual void xfernode121();
	virtual void xfernode122();
	virtual void xfernode123();
	virtual void xfernode124();
	virtual void xfernode125();
	virtual void xfernode126();
	virtual void *b27(AsciiString &s, float *f);
};

class XferNode2
{
public:
	virtual void xfernode20();
	virtual void xfernode21();
	virtual void xfernode22();
	virtual void xfernode23();
	virtual void xfernode24();
	virtual void xfernode25();
	virtual void xfernode26();
	virtual void xfernode27();
	virtual void xfernode28();
	virtual void xfernode29();
	virtual void xfernode210();
	virtual void xfernode211();
	virtual void xfernode212();
	virtual void xfernode213();
	virtual void xfernode214();
	virtual void xfernode215();
	virtual void xfernode216();
	virtual void xfernode217();
	virtual void xfernode218();
	virtual void xfernode219();
	virtual void xfernode220();
	virtual void xfernode221();
	virtual void xfernode222();
	virtual void xfernode223();
	virtual void xfernode224();
	virtual void xfernode225();
	virtual void xfernode226();
	virtual void *d27(AsciiString &s);
	virtual void d28(float *f);
};

class Rva000C1788Base { public: void rva000C0386(); };

class Rva000C1788
{
public:
	void rva000C1788(void *arg);
private:
	char m_pad00[0x44];
	XferNode1 *m_44;		// +0x44
	char m_pad48[0x104 - 0x48];
	XferNode1 *m_104;		// +0x104
	float m_108;			// +0x108
};

extern void *Rva003062FEXfer(void *p);

void Rva000C1788::rva000C1788(void *arg)
{
	if (m_44 == 0)
		return;
	((Rva000C1788Base *)((char *)this - 0xc))->rva000C0386();
	AsciiString s18(m_44->b06());
	m_44->b20();
	float block[12];
	const float *srcf = (const float *)((char *)m_44 + 0x18);
	block[0] = srcf[0]; block[1] = srcf[1]; block[2] = srcf[2]; block[3] = srcf[3];
	block[4] = srcf[4]; block[5] = srcf[5]; block[6] = srcf[6]; block[7] = srcf[7];
	block[8] = srcf[8]; block[9] = srcf[9]; block[10] = srcf[10]; block[11] = srcf[11];
	int flag = 1;
	AsciiString s10;
	float value = 0.0f;
	if (m_104 != 0)
	{
		s10.set(m_104->b02());
		value = m_108;
	}
	XferNode1 *r = (XferNode1 *)((XferArg *)arg)->a31(&flag);
	void *r2 = r->b27(s10, block);
	void *r3 = Rva003062FEXfer(r2);
	void *r4 = ((XferNode2 *)r3)->d27(s10);
	((XferNode2 *)r4)->d28(&value);
}
