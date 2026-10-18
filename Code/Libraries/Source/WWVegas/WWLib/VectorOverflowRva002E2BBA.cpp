// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x002E2BBA, 191B; Ghidra boundary, ret14 ABI and 216-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

struct Rva002E2BBARecord {
 Rva002E2BBARecord(); Rva002E2BBARecord(const Rva002E2BBARecord&); ~Rva002E2BBARecord(); Rva002E2BBARecord&operator=(const Rva002E2BBARecord&);
private: char bytes[216];
};
// Retail's helpers construct through the 45B _Construct 0x002E160F and
// _M_clear (0x002E26C3) destroys through the _Destroy forwarder 0x002AF4ED,
// both rowed under twin element names: forward to them.
struct Rva002E160FElement;
struct Rva002E2690Element;
namespace _STL {
template<> void _Construct<Rva002E160FElement,Rva002E160FElement>(Rva002E160FElement*,const Rva002E160FElement&);
template<> void _Destroy<Rva002E2690Element*>(Rva002E2690Element*,Rva002E2690Element*);
template<> __declspec(dllimport) __forceinline void _Construct<Rva002E2BBARecord,Rva002E2BBARecord>(Rva002E2BBARecord*p,const Rva002E2BBARecord&v)
{ _Construct(reinterpret_cast<Rva002E160FElement*>(p),reinterpret_cast<const Rva002E160FElement&>(v)); }
template<> __declspec(dllimport) __forceinline void _Destroy<Rva002E2BBARecord*>(Rva002E2BBARecord*first,Rva002E2BBARecord*last)
{ _Destroy(reinterpret_cast<Rva002E2690Element*>(first),reinterpret_cast<Rva002E2690Element*>(last)); }
}
template void _STL::vector<Rva002E2BBARecord>::_M_insert_overflow(Rva002E2BBARecord*,const Rva002E2BBARecord&,const _STL::__false_type&,unsigned int,bool);
