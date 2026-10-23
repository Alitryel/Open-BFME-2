// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <vector>

// Retail's copy calls __uninitialized_copy 0x005FE226 (StlSweepW5Rva005FE226.cpp),
// rowed over Rva005FE226Element, so this vector holds that 12-byte element.
struct Rva005FE226Element {Rva005FE226Element();Rva005FE226Element(const Rva005FE226Element&);Rva005FE226Element&operator=(const Rva005FE226Element&);~Rva005FE226Element(){}char bytes[12]; bool operator==(const Rva005FE226Element&)const;};
// Its _Construct forwards to the rowed placement-copy owner Rva005FE0F5Construct
// 0x005FE0F5 exactly as StlSweepW5Rva005FE226.cpp does, so this TU's
// __uninitialized_copy copy is retail's 0x005FE226 body.
struct BfmeStringRecord005F93E3;
void Rva005FE0F5Construct(BfmeStringRecord005F93E3 *, const BfmeStringRecord005F93E3 &);
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline void _Construct<Rva005FE226Element, Rva005FE226Element>(Rva005FE226Element *__p, const Rva005FE226Element &__val)
{ Rva005FE0F5Construct((BfmeStringRecord005F93E3 *)__p, *(const BfmeStringRecord005F93E3 *)&__val); }
}

// Instantiate the recovered operation and its required template dependencies.
template Rva005FE226Element * _STL::vector<Rva005FE226Element, _STL::allocator<Rva005FE226Element> >::_M_allocate_and_copy<Rva005FE226Element const *>(unsigned int, Rva005FE226Element const *, Rva005FE226Element const *);
