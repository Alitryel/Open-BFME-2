// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// Clear the named-timer map at +0x750 through its rowed tree clear.
// The owner class remains unrecovered.
#include <map>
#include "ascii_string.h"

class NamedTimerInfo;

typedef _STL::map<AsciiString, NamedTimerInfo *> Rva002A463BMap;
namespace _STL {
template <> void _Rb_tree<AsciiString, pair<const AsciiString, NamedTimerInfo *>, _Select1st<pair<const AsciiString, NamedTimerInfo *> >, less<AsciiString>, allocator<pair<const AsciiString, NamedTimerInfo *> > >::clear();
}

class Rva002A463B
{
public:
	void rva002A463B();
private:
	char m_pad000[0x750];
	Rva002A463BMap m_map;
};

void Rva002A463B::rva002A463B()
{
	m_map.clear();
}
