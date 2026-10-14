// ?rva0041458A@Rva004147CF@@QAEXPAVRva0041458AInterface@@@Z
// partial score=0.9736 date=2026-10-14
// ?rva0041458A@Rva004147CF@@QAEXPAVRva0041458AInterface@@@Z
// partial score=0.907135 date=2026-10-14
// ?rva0041458A@Rva004147CF@@QAEXPAVRva0041458AInterface@@@Z
// partial score=0.871 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ?rva0041458A@Rva004147CF@@QAEXPAVRva0041458AInterface@@@Z @0x0041458A 344B.
// WB 0x12B51A0: register every 0x30-byte ScoredKill element with the EVA
// announcer interface, matching by the element's AsciiString name; the
// interface's own list branch when vslot1 is false.
#include "ascii_string.h"

struct Rva004147CFElem
{
	char m_pad00[4];
	AsciiString m_name; // +0x04
	char m_pad08[0x30 - 0x08];
};

class Rva0041458AInterface
{
public:
#define BFME_V(N) virtual void vslot##N();
	BFME_V(00)
	virtual bool vslot01();
	BFME_V(02) BFME_V(03) BFME_V(04)
	virtual void vslot05(const char *);
	virtual void vslot06();
	virtual void vslot07(const char *);
	BFME_V(08) BFME_V(09)
	virtual void vslot10(void *flags);
	BFME_V(11)
	virtual void vslot12(void *elem);
	BFME_V(13) BFME_V(14) BFME_V(15) BFME_V(16) BFME_V(17) BFME_V(18) BFME_V(19)
	BFME_V(20) BFME_V(21) BFME_V(22) BFME_V(23) BFME_V(24) BFME_V(25) BFME_V(26)
	virtual void vslot27(void *name);
	BFME_V(28) BFME_V(29) BFME_V(30)
	virtual void vslot31(void *count);
#undef BFME_V
};

class Rva004147CF
{
public:
	void rva0041458A(Rva0041458AInterface *iface);
private:
	char m_pad00[4];
	Rva004147CFElem *m_begin; // +0x04
	Rva004147CFElem *m_end;   // +0x08
};

void Rva004147CF::rva0041458A(Rva0041458AInterface *iface)
{
	struct Flags { bool a; bool b; };
	{
	Flags flags;
	flags.a = true;
	flags.b = true;
	iface->vslot10(&flags);
	}

	int count = (int)((char *)m_end - (char *)m_begin) / 0x30;
	iface->vslot31(&count);

	if (iface->vslot01())
	{
		for (int i = 0; i < count; ++i)
		{
			AsciiString name;
			iface->vslot27(&name);
			Rva004147CFElem *found = 0;
			Rva004147CFElem *end = m_end;
			for (Rva004147CFElem *p = m_begin; p != end; p = (Rva004147CFElem *)((char *)p + 0x30))
			{
				if (found)
					break;
				if (p->m_name.compare(name) == 0)
					found = p;
			}
			if (found)
			{
				iface->vslot05("ScoredKillEvaAnnouncer");
				iface->vslot12(found);
				iface->vslot06();
			}
			else
			{
				iface->vslot07("ScoredKillEvaAnnouncer");
			}
		}
	}
	else
	{
		Rva004147CFElem *p = m_begin;
		Rva004147CFElem *end = m_end;
		for (; p != end; p = (Rva004147CFElem *)((char *)p + 0x30))
		{
			AsciiString tmp(p->m_name);
			iface->vslot27(&tmp);
			iface->vslot05("ScoredKillEvaAnnouncer");
			iface->vslot12(p);
			iface->vslot06();
		}
	}
}
