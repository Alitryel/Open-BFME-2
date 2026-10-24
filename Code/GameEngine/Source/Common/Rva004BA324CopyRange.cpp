// cl: /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva004BA324CopyRange@@YAPAVRva004BA1C8@@PAV1@00H@Z, retail 0x004BA324 29B: tag temp plus null distance forwarder.
// Evidence: same 29B shape as rowed ?Rva002915EBCopyRange at 0x002915EB; callee 0x004BA2E9 is 50B assign loop via rowed assign; caller 0x004BA399 is 51B erase-range like rowed EraseRange at 0x002983DA.
namespace _STL {
struct random_access_iterator_tag {
};
// STLport 4.5.3 random-access __copy (vendor/stlport/stl/_algobase.h). Retail
// keeps it out of line: 0x004BA2E9 is the 50B assign loop (stride 0x2C) rowed as
// Rva004BA2E9Copy, which this instantiation folds with.
template <class _RandomAccessIter, class _OutputIter, class _Distance>
__declspec(noinline) inline _OutputIter
__copy(_RandomAccessIter __first, _RandomAccessIter __last,
       _OutputIter __result, const random_access_iterator_tag &, _Distance*) {
  for (_Distance __n = __last - __first; __n > 0; --__n) {
    *__result = *__first;
    ++__first;
    ++__result;
  }
  return __result;
}
}
// The 0x2C record of Rva004BA1C8Record.cpp; only its rowed assignment
// (0x004BA291) is used here.
class Rva004BA1C8 {
public:
	Rva004BA1C8 &operator=(const Rva004BA1C8 &other);
private:
	unsigned char m_bytes[0x2C];
};
Rva004BA1C8 *Rva004BA324CopyRange(Rva004BA1C8 *first, Rva004BA1C8 *last, Rva004BA1C8 *result, int dummy)
{
	_STL::random_access_iterator_tag tag;
	(void)dummy;
	return _STL::__copy(first, last, result, tag, (int *)0);
}
