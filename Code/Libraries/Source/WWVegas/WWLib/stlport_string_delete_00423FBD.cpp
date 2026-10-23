// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?Delete@Rva00423FBDThis@@QAEXPAV?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@@Z retail 0x00423FBD 27B
// Free scalar delete of a narrow basic_string: null check then rowed
// basic_string char dtor at 0x0007FAB3 then rowed operator delete at
// 0x0002FD60. Evidence: 5 callers incl small loop 0x003F2BEB plus STLport
// neighbours with same bfmealloc flags. The callers pass a functor in ECX
// (thiscall, unused) and the body pops its one argument either way; every
// unit names it as the member below.
namespace _STL
{
template <class T> class char_traits {};
template <class T> class allocator {};
template <class CharT, class Traits, class Alloc> class basic_string
{
public:
	~basic_string();
};
}

void __cdecl operator delete(void *p);

class Rva00423FBDThis
{
public:
	void Delete(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p);
};

void Rva00423FBDThis::Delete(_STL::basic_string<char, _STL::char_traits<char>, _STL::allocator<char> > *p)
{
	if (p != 0)
	{
		p->~basic_string();
		operator delete(p);
	}
}
