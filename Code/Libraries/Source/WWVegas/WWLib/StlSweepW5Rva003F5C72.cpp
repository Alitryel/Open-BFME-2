// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element: the 48-byte Rva003F610FElement (dtor 0x003F535B). vector::erase(iterator)
// 0x003F5C72 calls the element's __copy_ptrs forwarder 0x003F5B3E and its dtor;
// Rva003F5DBD::rva003F5DBD 0x003F5DBD erases one element through it.
// cl: /Os /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
#include <vector>

struct Rva003F610FElement {
	char opaque[48];
	Rva003F610FElement(const Rva003F610FElement &);
	Rva003F610FElement &operator=(const Rva003F610FElement &);
	~Rva003F610FElement();
};

// The forwarder's body stays visible (retail passes its empty tag as lea [ebp+0Bh]).
// Its __copy loop is retail's out-of-line 0x003F58F8 (50B, stride 48), rowed as
// Rva003F58F8Copy; this unit supplies the same STLport 4.5.3 random-access body
// (vendor/stlport/stl/_algobase.h) out of line, which folds with it.
namespace _STL {
template <> __declspec(noinline) inline Rva003F610FElement *__copy<Rva003F610FElement *, Rva003F610FElement *, int>(Rva003F610FElement *__first, Rva003F610FElement *__last, Rva003F610FElement *__result, const random_access_iterator_tag &, int *)
{
  for (int __n = __last - __first; __n > 0; --__n) {
    *__result = *__first;
    ++__first;
    ++__result;
  }
  return __result;
}
}

template Rva003F610FElement *_STL::vector<Rva003F610FElement>::erase(Rva003F610FElement *);
