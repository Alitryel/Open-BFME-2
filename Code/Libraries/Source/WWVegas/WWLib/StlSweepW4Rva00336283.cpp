// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /Og /Os /Ob1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

// 20-byte record keyed by the name at +0. Retail's __lower_bound 0x00335CAE expands this comparison
// inline around the rowed StringBase compare 0x000069D6.
struct Rva00336283Element
{
	AsciiString m_name;
	char m_bytes[16];
	__forceinline bool operator<(const Rva00336283Element &o) const { return ((const StringBase<char> &)m_name).compare((const StringBase<char> &)o.m_name) < 0; }
	bool operator==(const Rva00336283Element &) const;
};

// Instantiate the recovered operation and its required template dependencies.
template Rva00336283Element * _STL::lower_bound<Rva00336283Element *, Rva00336283Element, _STL::less<Rva00336283Element> >(Rva00336283Element *, Rva00336283Element *, Rva00336283Element const &, _STL::less<Rva00336283Element>);
