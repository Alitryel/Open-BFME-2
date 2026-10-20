// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x0048D48F, 178B; Ghidra boundary, ret14 ABI and 8-byte
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

struct Rva0048D48FRecord {
 Rva0048D48FRecord(); Rva0048D48FRecord(const Rva0048D48FRecord&); ~Rva0048D48FRecord(); Rva0048D48FRecord&operator=(const Rva0048D48FRecord&);
private: char bytes[8];
};
// Retail's construction and teardown reach rowed twins: Rva0048C81FConstruct
// 0x0048C81F and _Destroy<CameraMarker *> 0x0048CE25: forward to them.
struct TreeKey00242F5E;
class CameraMarker;
void __cdecl Rva0048C81FConstruct(TreeKey00242F5E *dst, const TreeKey00242F5E &src);
namespace _STL {
template<> void _Destroy<CameraMarker*>(CameraMarker*,CameraMarker*);
template<> __declspec(dllimport) __forceinline void _Construct<Rva0048D48FRecord,Rva0048D48FRecord>(Rva0048D48FRecord*p,const Rva0048D48FRecord&v)
{ Rva0048C81FConstruct(reinterpret_cast<TreeKey00242F5E*>(p),reinterpret_cast<const TreeKey00242F5E&>(v)); }
template<> __declspec(dllimport) __forceinline void _Destroy<Rva0048D48FRecord*>(Rva0048D48FRecord*f,Rva0048D48FRecord*l)
{ _Destroy(reinterpret_cast<CameraMarker*>(f),reinterpret_cast<CameraMarker*>(l)); }
}
template void _STL::vector<Rva0048D48FRecord>::_M_insert_overflow(Rva0048D48FRecord*,const Rva0048D48FRecord&,const _STL::__false_type&,unsigned int,bool);
