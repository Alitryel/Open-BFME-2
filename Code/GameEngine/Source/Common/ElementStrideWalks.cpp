// 36-byte copy walk, retail 0x00161150, 45 bytes.
//
// Bounded-by-end-pointer walk handing each 36-byte slot to the helper at
// 0x001610F0 (rowed STLport placement construction; element identity still opaque). Both
// cursors advance by the retail step 0x24; the returned value is the
// advanced dest cursor. Element identity is not recovered -- Elem36 is a
// stride-sized stand-in in the ElementStrideWalks donor's own convention.

struct Elem36
{
	char m_bytes[36];
};

namespace _STL {
template <class T1, class T2> void _Construct(T1 *, const T2 &);
template <> void _Construct<Elem36, Elem36>(Elem36 *, const Elem36 &);
}

Elem36 *rva00161150CopyWalk(Elem36 *first, Elem36 *last, Elem36 *dest)
{
	Elem36 *cursor = dest;
	for ( ; first != last; ++first)
	{
		_STL::_Construct(cursor, *first);
		++cursor;
	}
	return cursor;
}

// 28-byte copy walk, retail 0x00689750, 45 bytes.
//
// Same shape as the Elem36 walk above: bounded-by-end-pointer walk handing
// each 28-byte slot to the helper at 0x006896F0 (rowed 66-byte pair
// construct body). Both cursors advance by the retail step 0x1c; the returned
// value is the advanced dest cursor. Element identity is not recovered --
// Elem28 is a stride-sized stand-in in the ElementStrideWalks donor's own
// convention.
//
// The callee is the ledger's rowed `_STL::_Construct<Rva001D28F0Element>`
// (0x006896F0, 66 B): the walk's retail REL32 at 0x00689762 lands on that
// address, and the address-derived gen006896F0 spelling had no definition to
// link. The 28-byte stand-in only has to spell the rowed instantiation's
// mangled name; the pointer casts are no-ops, so the walk's bytes do not move.

struct Elem28
{
	char m_bytes[28];
};

struct Rva001D28F0Element
{
	char m_bytes[28];
};

Elem28 *rva00689750CopyWalk(Elem28 *first, Elem28 *last, Elem28 *dest)
{
	Elem28 *cursor = dest;
	for ( ; first != last; ++first)
	{
		_STL::_Construct((Rva001D28F0Element *)cursor, *(const Rva001D28F0Element *)first);
		++cursor;
	}
	return cursor;
}
