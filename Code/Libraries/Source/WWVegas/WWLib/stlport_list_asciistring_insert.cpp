// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// Dedicated unit without the bfmelist __forceinline _M_create_node shim so
// list<AsciiString>::insert calls the out-of-line create_node (pinned at
// 0x001FD682 from the retail REL32), mirroring
// stlport_list_objectptr_insert.cpp. Retail 0x001FD72C (37 bytes) is the
// insert worker; the node is 12 bytes (8 links + 4-byte StringBase-model
// AsciiString) and create delegates per element to the matched StringBase
// _Construct helper at 0x0002C485, which names the element type.
#define BFME_ASCII_DTOR_DECL
#include "ascii_string.h"
#include <list>

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class Traits>
static inline bool operator!=(const _List_iterator<T, Traits>& a,
                              const _List_iterator<T, Traits>& b)
{ return a._M_node != b._M_node; }
}


// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> _List_node<AsciiString> * list<AsciiString,allocator<AsciiString> >::_M_create_node(AsciiString const &); }

// Keep the verified operations and reuse their existing base providers.
// A whole-class instantiation emits incompatible copies of unused members.
extern template _STL::_List_base<AsciiString,_STL::allocator<AsciiString> >::_List_base(const _STL::allocator<AsciiString> &);
extern template _STL::_List_base<AsciiString,_STL::allocator<AsciiString> >::~_List_base();
typedef _STL::list<AsciiString,_STL::allocator<AsciiString> > AsciiList;
template _STL::list<AsciiString,_STL::allocator<AsciiString> >::list(const AsciiList &);
template AsciiList &AsciiList::operator=(const AsciiList &);
template AsciiList::iterator AsciiList::insert(AsciiList::iterator,const AsciiString &);
template void AsciiList::push_back(const AsciiString &);
template AsciiList::iterator AsciiList::erase(AsciiList::iterator);

class Rva001FD42B
{
public:
	~Rva001FD42B();
};

class Rva001FD85E
{
public:
	void rva001FD85E();
};

void Rva001FD85E::rva001FD85E()
{
	((Rva001FD42B *)this)->~Rva001FD42B();
}

class Rva001FD458
{
public:
	~Rva001FD458();
};

class Rva001FD863
{
public:
	void rva001FD863();
};

void Rva001FD863::rva001FD863()
{
	((Rva001FD458 *)this)->~Rva001FD458();
}
