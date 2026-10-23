// cl: /MD /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7
// stlport
// ??0Rva000AB910@@QAE@ABVAsciiString@@@Z @ 0x000AB910, 70 bytes. Retail
// copies a narrow string and initializes two hash maps; member identities are inferred from offsets.
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "ascii_string.h"
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}

struct Rva000AB8F1Element { char bytes[1]; bool operator<(const Rva000AB8F1Element&) const; bool operator==(const Rva000AB8F1Element&) const; };
namespace _STL { template<> struct hash<Rva000AB8F1Element> { unsigned operator()(const Rva000AB8F1Element&) const; }; }

class Rva000AB910
{
public:
	Rva000AB910(const AsciiString &name);
private:
	AsciiString m_name;
	int m_value;
	_STL::hash_map<int, Rva000AB8F1Element> m_first;
	_STL::hash_map<int, Rva000AB8F1Element> m_second;
};

// bfme link decl-only begin
namespace _STL { template <> hashtable<_STL::pair<int const,Rva000AB8F1Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva000AB8F1Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::hashtable(unsigned int,_STL::hash<int> const &,_STL::equal_to<int> const &,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > const &); }
namespace _STL { template <> hashtable<_STL::pair<int const,Rva000AB8F1Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva000AB8F1Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::~hashtable(); }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva000AB8F1Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva000AB8F1Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::_M_delete_node(_STL::_Hashtable_node<_STL::pair<int const,Rva000AB8F1Element> > *); }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva000AB8F1Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva000AB8F1Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::_M_initialize_buckets(unsigned int); }
namespace _STL { template <> unsigned int hashtable<_STL::pair<int const,Rva000AB8F1Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva000AB8F1Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::_M_next_size(unsigned int) const; }
namespace _STL { template <> void hashtable<_STL::pair<int const,Rva000AB8F1Element>,int,_STL::hash<int>,_STL::_Select1st<_STL::pair<int const,Rva000AB8F1Element> >,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::clear(); }
namespace _STL { template <> void _STLP_alloc_proxy<unsigned int,_STL::_Hashtable_node<_STL::pair<int const,Rva000AB8F1Element> >,_STL::allocator<_STL::_Hashtable_node<_STL::pair<int const,Rva000AB8F1Element> > > >::deallocate(_STL::_Hashtable_node<_STL::pair<int const,Rva000AB8F1Element> > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Hashtable_node<_STL::pair<int const,Rva000AB8F1Element> > >::deallocate(_STL::_Hashtable_node<_STL::pair<int const,Rva000AB8F1Element> > *,unsigned int) const; }
namespace _STL { template <> hash_map<int,Rva000AB8F1Element,_STL::hash<int>,_STL::equal_to<int>,_STL::allocator<_STL::pair<int const,Rva000AB8F1Element> > >::hash_map(); }
// bfme link decl-only end
Rva000AB910::Rva000AB910(const AsciiString &name)
:
	m_name(name),
	m_value(0),
	m_first(),
	m_second()
{
}
