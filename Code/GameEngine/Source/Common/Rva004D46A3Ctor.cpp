// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /Ireference/shims/bfmealloc
// stlport
// ??0Rva004D46A3@@QAE@XZ @0x004D46A3 12B: default constructor of a record whose first member
// is a narrow STL string (default constructed through the rowed 0x00007850). The owner
// identity is open; only the string at +0 is witnessed.
#include <string>

namespace _STL {
template <> basic_string<char, char_traits<char>, allocator<char> >::basic_string();
}

class Rva004D46A3
{
public:
	Rva004D46A3();
private:
	_STL::string m_text;
};

Rva004D46A3::Rva004D46A3()
{
}
