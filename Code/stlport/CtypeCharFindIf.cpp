// cl: /EHsc /MD
// stlport
// Transferred unchanged from Open-BFME-1 5cae4bdff game/stlport/CtypeCharFindIf.cpp (a strict superset of
// the earlier reduced copy); bfme1_sweep ambiguous: ctype<char>::scan_is is
// byte-identical at 2 BFME2 placements and only 0x00017270 calls the BFME2
// __find_if<const char *, _Ctype_c_is_mask> row. Addresses in the donor text are BFME1.
// STLport 4.5.3 ctype<char> scan_is helper: __find_if + mask table.

#include <algorithm>
#include <stl/_iterator_base.h>
#include <stl/_ctype.h>

_STLP_BEGIN_NAMESPACE

struct _Ctype_c_is_mask
{
	typedef char argument_type;
	typedef bool result_type;
	unsigned int M;
	const ctype_base::mask *table;
	bool operator()(unsigned char c) const
	{
		return (table[c] & M) != 0;
	}
};

template const char *__find_if(
	const char *, const char *, _Ctype_c_is_mask,
	const random_access_iterator_tag &);


const char *ctype<char>::scan_is(mask m, const char *first,
	const char *last) const
{
	_Ctype_c_is_mask predicate = { m, table() };
	return find_if(first, last, predicate);
}
_STLP_END_NAMESPACE
