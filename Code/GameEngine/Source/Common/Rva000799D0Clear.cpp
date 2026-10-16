// cl: /Ireference/shims/bfme2_ascii /Ireference/shims/bfmelist /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?rva000799D0@Rva000799D0@@QAEXXZ @0x000799D0 23B via list clear plus sentinel free
// Evidence: thiscall ret0; rowed List_base<string> clear at +0 then rowed _free 0x00030830 of node ptr; callers 0x0007A52E 0x004251A8 plus thunk 0x00424A09
#include <list>
#include <string>
#include <cstddef>
// bfme link decl-only begin
namespace _STL { template <> _String_base<char,_STL::allocator<char> >::~_String_base(); }
namespace _STL { template <> basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >::~basic_string(); }
namespace _STL { template <> void _String_base<char,_STL::allocator<char> >::_M_deallocate_block(); }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_List_node<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > > *,_STL::_List_node<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > >,_STL::allocator<_STL::_List_node<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > > > >::deallocate(_STL::_List_node<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > > *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_List_node<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > > >::deallocate(_STL::_List_node<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > > *,unsigned int) const; }
namespace _STL { template <> void _List_base<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> >,_STL::allocator<_STL::basic_string<char,_STL::char_traits<char>,_STL::allocator<char> > > >::clear(); }
// bfme link decl-only end
// Suppress this TU's non-retail proxy<char> deallocate copy (family2-LK3 row 28):
// the kept copy serves the link. Plain declaration-only form (no __imp_).
namespace _STL {
template <> void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char*, size_t);
}

extern "C" void __cdecl free(void *);

class Rva000799D0
{
public:
	void rva000799D0();
private:
	_STL::list<_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > > m_list;
};

void Rva000799D0::rva000799D0()
{
	m_list.clear();
	void *p = *(void **)&m_list;
	if (p != 0)
		free(p);
}
