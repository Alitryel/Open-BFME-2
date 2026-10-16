// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme_stlport_int_dealloc_link
// stlport
// ??0Rva004FD1BC@@QAE@XZ (class named by its dtor 0x004FD1BC, vtable 0x00863564 slot 0 deletes through it), retail 0x004FD0DA..0x004FD1BC (226 bytes, EH,
// ret 0): the constructor of the 0xB0-byte scenario object Scenario::ParseINI
// (0x004FD94E) allocates (pinned under this address name). It installs table
// 0x00C63564; the EH state numbering (0x0A..0x0C stored before the three maps)
// counts eight AsciiStrings (+0x04..+0x1C and +0x28) and three vectors
// (+0x2C..+0x44) ahead of the maps, around two ints set to 6 and 2. The three
// int-keyed maps (+0x50/+0x5C/+0x68) and five more vectors (+0x74..+0xA4)
// follow, built through the rowed STLport instantiations each call names.
// Element and field identities are not established.
#include <map>
#include <vector>
#include "int_dealloc.h"
#include "ascii_string.h"

struct Rva00501875Count
{
	int m_count;
};

// Use the verified provider in Rva00501875KeyPresence.cpp for EH cleanup.
namespace _STL {
template <> _Rb_tree<int, pair<const int, Rva00501875Count>,
    _Select1st<pair<const int, Rva00501875Count> >, less<int>,
    allocator<pair<const int, Rva00501875Count> > >::~_Rb_tree();
}

class Rva004FD1BC
{
public:
	Rva004FD1BC();
	virtual ~Rva004FD1BC();

private:
	AsciiString m_04;
	AsciiString m_08;
	AsciiString m_0C;
	AsciiString m_10;
	AsciiString m_14;
	AsciiString m_18;
	AsciiString m_1C;
	int m_20;
	int m_24;
	AsciiString m_28;
	_STL::vector<int> m_2C;
	_STL::vector<int> m_38;
	_STL::vector<int> m_44;
	_STL::map<int, Rva00501875Count> m_50;
	_STL::map<int, Rva00501875Count> m_5C;
	_STL::map<int, Rva00501875Count> m_68;
	_STL::vector<int> m_74;
	_STL::vector<int> m_80;
	_STL::vector<int> m_8C;
	_STL::vector<int> m_98;
	_STL::vector<int> m_A4;
};

Rva004FD1BC::Rva004FD1BC() : m_20(6), m_24(2)
{
}
