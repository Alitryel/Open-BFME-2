// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
//
// STLport _Construct<AsciiString> placement-copy helper. Retail 0x0002C485
// (45 bytes) is the null-guarded placement-new copy over a single element,
// called per element by the 38B __uninitialized_copy<AsciiString> trio at
// 0x0002C4B2 and by the AsciiString-vector push_back/insert bodies at
// 0x0002D222/0x0002DBF8/0x0001FD696. The AsciiString copy delegates inline to
// the StringBase<char> copy row at 0x000365F0 (AptMap pattern), so no new pin
// is needed for it; __EH_prolog resolves via its matched row.

#include <memory>

template <typename T> struct BfmeStringData
{
	int refCount;
	unsigned short length;
	unsigned short capacity;
	T text[1];
};

#include "ascii_string.h"


void AsciiStringCopyConstructAtRva0002C485(AsciiString *dest, const AsciiString &source)
{
    ::new (dest) AsciiString(source);
}
