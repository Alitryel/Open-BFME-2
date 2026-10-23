// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /D_STLP_USE_MALLOC /D_CRTIMP= /Ireference/shims/bfmealloc
// stlport

// STLport vector operations for the video-record element family.
// The native copy loop and destructor establish the three string members
// followed by the scalar fields and owned pointer.

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include <vector>

struct Rva001D28F0Element
{
	AsciiString m_first;
	AsciiString m_second;
	AsciiString m_third;
	unsigned char m_flag0c;
	int m_word10;
	unsigned char m_flag14;
	void *m_owned;
	Rva001D28F0Element();
	Rva001D28F0Element(const Rva001D28F0Element &other);
	~Rva001D28F0Element();
	__declspec(dllimport) __forceinline
	Rva001D28F0Element &operator=(const Rva001D28F0Element &other)
	{
		m_first.setCopyInline(other.m_first);
		m_second.setCopyInline(other.m_second);
		m_third.setCopyInline(other.m_third);
		m_flag0c = other.m_flag0c;
		m_word10 = other.m_word10;
		m_flag14 = other.m_flag14;
		m_owned = other.m_owned;
		return *this;
	}
};
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> vector<Rva001D28F0Element,allocator<Rva001D28F0Element> >::~vector(); }

typedef _STL::vector<Rva001D28F0Element> ElementVector;

// Instantiate the recovered operations and their required template dependencies.
template void ElementVector::_M_insert_overflow(Rva001D28F0Element *,
    const Rva001D28F0Element &, const _STL::__false_type &, unsigned int, bool);
template void ElementVector::push_back(const Rva001D28F0Element &);
template ElementVector::iterator ElementVector::erase(ElementVector::iterator);
template void ElementVector::_M_clear();
template Rva001D28F0Element &ElementVector::operator[](unsigned int);

template Rva001D28F0Element *_STL::uninitialized_fill_n(
    Rva001D28F0Element *, unsigned int, const Rva001D28F0Element &);
