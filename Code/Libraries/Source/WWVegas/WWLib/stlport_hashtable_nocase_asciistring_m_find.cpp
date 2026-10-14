// cl: /Ireference/shims/bfme2_ascii /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
//
// STLport 4.5.3 hashtable::_M_find for a case-insensitive AsciiString-keyed
// hash map, retail 0x0002C9E7 (63 bytes, RET4): bucket = rts::hash<AsciiString>
// (the rowed lowering hash 0x0002BF8C, called with the table as the empty
// hasher) modulo the bucket count, then walk the chain until the node key's
// compareNoCase (rowed 0x00006A00) against the probe is zero; returns the
// node. Callers: the iterator find at 0x0002CB7D and 0x0002D0E5.
//
// The equality functor is BFME 2's case-insensitive one (retail calls
// compareNoCase, not compare). The mapped type is not established by this
// body (only the key at node+4 and the chain link at node+0 are read), so a
// placeholder stands for it.
#define _STLP_NO_EXCEPTIONS 1
#include "ascii_string.h"

namespace rts
{
	template <class T> struct hash
	{
	};
	template <> struct hash<AsciiString>
	{
		unsigned int operator()(const AsciiString &key) const;
	};
	template <class T> struct equal_to
	{
	};
	template <> struct equal_to<AsciiString>
	{
		bool operator()(const AsciiString &a, const AsciiString &b) const
		{
			return a.compareNoCase(b) == 0;
		}
	};
}

#include <hash_map>

struct Rva0002C9E7Value
{
	int m_value;
};

typedef _STL::hashtable<
	_STL::pair<const AsciiString, Rva0002C9E7Value>, AsciiString,
	rts::hash<AsciiString>,
	_STL::_Select1st<_STL::pair<const AsciiString, Rva0002C9E7Value> >,
	rts::equal_to<AsciiString>,
	_STL::allocator<_STL::pair<const AsciiString, Rva0002C9E7Value> > > NoCaseAsciiHashtable;

template NoCaseAsciiHashtable::_Node *NoCaseAsciiHashtable::_M_find(const AsciiString &) const;
