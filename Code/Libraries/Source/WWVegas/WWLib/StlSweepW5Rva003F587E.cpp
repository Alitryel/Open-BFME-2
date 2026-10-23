// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element: the 48-byte Rva003F610FElement (copy ctor 0x003F54DC). The overflow 0x003F610F
// calls this fill, and both bodies construct through the rowed _Construct 0x003F5822.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva003F610FElement {
	char opaque[48];
	Rva003F610FElement(const Rva003F610FElement &);
	Rva003F610FElement &operator=(const Rva003F610FElement &);
	~Rva003F610FElement();
};

// Rowed in StlportConstructRva003F610F.cpp; declare it so this TU calls that body.
namespace _STL {
template <> void _Construct<Rva003F610FElement, Rva003F610FElement>(Rva003F610FElement *, const Rva003F610FElement &);
}

// Instantiate the recovered operation and its required template dependencies.
template Rva003F610FElement * _STL::__uninitialized_fill_n<Rva003F610FElement *, unsigned int, Rva003F610FElement>(Rva003F610FElement *, unsigned int, Rva003F610FElement const &, _STL::__false_type const &);

// 0x003F58DD calls this fill through the out-of-line uninitialized_fill_n wrapper
// (three arguments plus the __false_type tag at [ebp-1]).
template Rva003F610FElement * _STL::uninitialized_fill_n<Rva003F610FElement *, unsigned int, Rva003F610FElement>(Rva003F610FElement *, unsigned int, Rva003F610FElement const &);
