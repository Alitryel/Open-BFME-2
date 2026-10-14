// ??0Rva0024314ARecord@@QAE@ABU0@@Z
// partial score=0.5 date=2026-10-14
// cl: /O1 /G6 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??0Rva0024314ARecord@@QAE@ABU0@@Z @0x002419E2 188B
// Copy constructor of the 0x50-byte record the rowed _Construct 0x0024314A copies: an AsciiString
// at +0, three 16-byte rows at +4 (default-built through the shared empty row constructor 0x47A6A9,
// then copied word by word), four ints at +0x34, a list at +0x44 copied through the rowed list copy
// constructor 0x00240D34 and two ints at +0x48/+0x4C. Evidence: target bytes (vector constructor
// iterator with count 3 / stride 16 then the 12 word copies in declaration order), the rowed
// list copy constructor, and the opaque Rva0024314ARecord spelling in StlSweepR3Rva0024314A.cpp.
// The field meanings are unknown, so every member keeps an offset name.
#include <list>
#include "ascii_string.h"

struct Rva0047A6A9Row16
{
	Rva0047A6A9Row16();
	float x, y, z, w;
};

struct Rva00240D34Element { double words[1]; bool operator<(const Rva00240D34Element &) const; bool operator==(const Rva00240D34Element &) const; };

namespace _STL {
template<> list<Rva00240D34Element, allocator<Rva00240D34Element> >::list(const list<Rva00240D34Element, allocator<Rva00240D34Element> > &);
}

struct Rva0024314ARecordBlock
{
	Rva0047A6A9Row16 m_rows[3];
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
};

struct Rva0024314ARecord
{
	Rva0024314ARecord(const Rva0024314ARecord &other);
	AsciiString m_name;
	Rva0024314ARecordBlock m_block;
	_STL::list<Rva00240D34Element> m_list;
	int m_48;
	int m_4c;
};

Rva0024314ARecord::Rva0024314ARecord(const Rva0024314ARecord &other)
	: m_name(other.m_name), m_block(other.m_block), m_list(other.m_list), m_48(other.m_48), m_4c(other.m_4c)
{
}
