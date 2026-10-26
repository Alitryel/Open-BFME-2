// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ICF twin of ??4ProductionPrerequisite@@QAEAAV0@ABV0@@Z (0x0042816E,
// ThingFactory.cpp): the element of the STLport sweep at 0x0042830D is a pair of
// narrow strings, and its assignment is that body: two calls to the out-of-line
// basic_string<char>::operator= at 0x000120C0 (41 bytes; the retail calls are
// both to that address, so the members are strings, not vectors).
#include <string>

namespace _STL {
template<> basic_string<char, char_traits<char>, allocator<char> > &basic_string<char, char_traits<char>, allocator<char> >::operator=(const basic_string<char, char_traits<char>, allocator<char> > &);
}

struct Rva0042830DElement
{
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_first;
	_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > m_second;
	Rva0042830DElement &operator=(const Rva0042830DElement &other);
};

Rva0042830DElement &Rva0042830DElement::operator=(const Rva0042830DElement &other)
{
	m_first = other.m_first;
	m_second = other.m_second;
	return *this;
}
