// ??0Rva00516FA0@@QAE@XZ
// partial score=0.93 date=2026-10-14
// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// ?rva00516F3F@Rva00516F3F@@QAEXXZ @0x00516F3F 36B unlock via copy sibling 0x00516F63.
// Reset three header ints to -1, clear two AsciiStrings via releaseBuffer worker
// rowed 0x00036410, reset tail int to -1. Evidence: same-layout copy method at
// 0x00516F63 copies +0/+4/+8 then set +0x10/+0xC then +0x14; callers jmp here.
#include "ascii_string.h"

struct Rva00516F3F
{
	Rva00516F3F() : m_0(-1), m_4(-1), m_8(-1), m_14(-1) {}
	int m_0;
	int m_4;
	int m_8;
	AsciiString m_C;
	AsciiString m_10;
	int m_14;
	void rva00516F3F();
	Rva00516F3F *rva00516F63(const Rva00516F3F &other);
};

void Rva00516F3F::rva00516F3F()
{
	m_0 = -1;
	m_4 = -1;
	m_8 = -1;
	m_10.clear();
	m_C.clear();
	m_14 = -1;
}

Rva00516F3F *Rva00516F3F::rva00516F63(const Rva00516F3F &other)
{
	m_0 = other.m_0;
	m_8 = other.m_8;
	m_4 = other.m_4;
	((StringBase<char> *)&m_10)->set(*(const StringBase<char> *)&other.m_10);
	((StringBase<char> *)&m_C)->set(*(const StringBase<char> *)&other.m_C);
	m_14 = other.m_14;
	return this;
}

// ?rva00516FA0@Rva00516FA0@@QAEXXZ @0x00516FA0 9B: an owner that embeds the
// Rva00516F3F record at +0 and an int at +0x18: clear the int, then tail into
// the rowed record reset 0x00516F3F.
struct Rva00516FA0
{
	Rva00516F3F m_record;
	int m_18;
	Rva00516FA0();
	void rva00516FA0();
};

// ??0Rva00516FA0@@QAE@XZ @0x0051730E 28B: the owner's constructor: the record's
// inline constructor sets its three header ints and tail int to -1 (the two
// AsciiStrings start empty), then the +0x18 int is cleared.
Rva00516FA0::Rva00516FA0() : m_18(0)
{
}

void Rva00516FA0::rva00516FA0()
{
	m_18 = 0;
	m_record.rva00516F3F();
}

// ??0Rva0051730E@@QAE@XZ
// partial score=0.93 date=2026-10-15
// cl: /O1 /G7 /arch:SSE /MD
// ??0Rva0051730E@@QAE@XZ @0x0051730E 28B
// Native 0x0051730E..0x00517329: thiscall constructor returning this that
// fills a seven-dword record with -1,-1,-1,0,0,-1,0. No direct caller or data
// reference was found, so owner and field roles are unproven and the name is
// address-derived; it sits between the AptOnline shell bodies 0x00517207 and
// the handle constructor 0x0051732A.
struct Rva0051730E
{
	int m_first;
	int m_second;
	int m_third;
	int m_count;
	int m_value;
	int m_index;
	int m_extra;
	Rva0051730E();
};

Rva0051730E::Rva0051730E()
	: m_first(-1), m_second(-1), m_third(-1), m_count(0), m_value(0), m_index(-1), m_extra(0)
{
}
