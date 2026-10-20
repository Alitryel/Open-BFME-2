// cl: /O1 /G6 /EHsc /MD /DNDEBUG /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc
// stlport
// ??0Rva0024076D@@QAE@ABV0@@Z @0x002419E2 188B
// Copy constructor of the 0x50-byte record the rowed _Construct 0x0024314A copies: an AsciiString
// at +0, three 16-byte rows at +4 (default-built through the shared empty row constructor 0x47A6A9,
// then copied word by word), four ints at +0x34, a list at +0x44 copied through the rowed list copy
// constructor 0x00240D34 and two ints at +0x48/+0x4C. Evidence: target bytes (vector constructor
// iterator with count 3 / stride 16 then the 12 word copies in declaration order), the rowed
// list copy constructor, and the record's own ctor/dtor in Rva0024076DCtor.cpp.
// The field meanings are unknown, so every member keeps an offset name. The row block carries its own
// inline copy constructor (a default-built array copied element by element, written out in full) and sits
// before the four ints, which are copied from the record's own initializer list, as in the target.
#include <list>
#include "ascii_string.h"

struct Rva0047A6A9Row16
{
	Rva0047A6A9Row16();
	int x, y, z, w;
};

struct Rva00240D34Element { double words[1]; bool operator<(const Rva00240D34Element &) const; bool operator==(const Rva00240D34Element &) const; };

namespace _STL {
template<> list<Rva00240D34Element, allocator<Rva00240D34Element> >::list(const list<Rva00240D34Element, allocator<Rva00240D34Element> > &);
}

struct Rva0024314ARecordBlock
{
	__forceinline Rva0024314ARecordBlock(const Rva0024314ARecordBlock &o)
	{
		m_rows[0].x = o.m_rows[0].x; m_rows[0].y = o.m_rows[0].y; m_rows[0].z = o.m_rows[0].z; m_rows[0].w = o.m_rows[0].w;
		m_rows[1].x = o.m_rows[1].x; m_rows[1].y = o.m_rows[1].y; m_rows[1].z = o.m_rows[1].z; m_rows[1].w = o.m_rows[1].w;
		m_rows[2].x = o.m_rows[2].x; m_rows[2].y = o.m_rows[2].y; m_rows[2].z = o.m_rows[2].z; m_rows[2].w = o.m_rows[2].w;
	}
	Rva0047A6A9Row16 m_rows[3];
};

class Rva0024076D
{
public:
	Rva0024076D(const Rva0024076D &other);
	AsciiString m_name;
	Rva0024314ARecordBlock m_block;
	int m_34;
	int m_38;
	int m_3c;
	int m_40;
	_STL::list<Rva00240D34Element> m_list;
	int m_48;
	int m_4c;
};

Rva0024076D::Rva0024076D(const Rva0024076D &other)
	: m_name(other.m_name), m_block(other.m_block), m_34(other.m_34), m_38(other.m_38), m_3c(other.m_3c), m_40(other.m_40), m_list(other.m_list), m_48(other.m_48), m_4c(other.m_4c)
{
}
