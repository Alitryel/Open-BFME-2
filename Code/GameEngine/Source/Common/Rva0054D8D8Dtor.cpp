// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??1Rva0054D8D8@@QAE@XZ @0x0054D8D8 128B. Non-virtual dtor with EH: three
// UnicodeString at +0x00/+0x04/+0x08, two list<AsciiString> at +0x1C/+0x20,
// three AsciiString at +0x24/+0x28/+0x30. Evidence: 8 calls in descending
// offset order with EH states 6..0 then -1; rowed releaseBuffer D 0x00036410
// G 0x00036E70 and List_base 0x002FECBC; unblocks deleting dtor 0x0054D958.
#include <list>
#include "ascii_string.h"

namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<_List_node<AsciiString> >::deallocate(_List_node<AsciiString>* __p, size_t __n) const {
 _STLP_ASSERT( (__p == 0) == (__n == 0) )
 if (__p != 0) ::free((void*)__p);
}
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<_List_node<AsciiString>*,_List_node<AsciiString>,allocator<_List_node<AsciiString> > >::deallocate(_List_node<AsciiString>* __p, size_t __n) {
 __stl_alloc_rebind(static_cast<allocator<_List_node<AsciiString> >&>(*this),(_List_node<AsciiString>*)0).deallocate(__p,__n);
}
}

#include "unicode_string.h"

class Rva0054D8D8
{
public:
	~Rva0054D8D8();
private:
	UnicodeString m00;
	UnicodeString m04;
	UnicodeString m08;
	int m0C;
	int m10;
	int m14;
	int m18;
	_STL::list<AsciiString, _STL::allocator<AsciiString> > m1C;
	_STL::list<AsciiString, _STL::allocator<AsciiString> > m20;
	AsciiString m24;
	AsciiString m28;
	int m2C;
	AsciiString m30;
};

Rva0054D8D8::~Rva0054D8D8()
{
}
