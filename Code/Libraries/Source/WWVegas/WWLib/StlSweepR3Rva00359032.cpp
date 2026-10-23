// STLport 4.5.3 reference instantiation. Target boundary and byte comparison prove operation shape.
// Element spelling/layout is donor inference; opaque records have address-derived identity.
// cl: /O1 /Ob2 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <set>
struct Rva00359032Record {
 Rva00359032Record(); Rva00359032Record(const Rva00359032Record&);
 ~Rva00359032Record(); Rva00359032Record&operator=(const Rva00359032Record&);
 char bytes[8];
};
// Retail's key compare and node construction reach rowed twins: AsciiString's
// operator< 0x0005598C and the pair construction 0x00358CA0: forward to them.
class AsciiString;
bool operator<(const AsciiString&,const AsciiString&);
void Rva00358CA0Construct(void *dest,const void *source);
__declspec(dllimport) __forceinline bool operator<(const Rva00359032Record&a,const Rva00359032Record&b)
{ return reinterpret_cast<const AsciiString&>(a)<reinterpret_cast<const AsciiString&>(b); }
namespace _STL {template<> __declspec(dllimport) __forceinline void _Construct<Rva00359032Record,Rva00359032Record>(Rva00359032Record*p,const Rva00359032Record&v)
{ Rva00358CA0Construct(p,&v); }}


// Instantiate the recovered member; retain only its required template dependencies.
template _STL::pair<_STL::_Rb_tree_iterator<Rva00359032Record, _STL::_Nonconst_traits<Rva00359032Record> >, bool> _STL::_Rb_tree<Rva00359032Record, Rva00359032Record, _STL::_Identity<Rva00359032Record>, _STL::less<Rva00359032Record>, _STL::allocator<Rva00359032Record> >::insert_unique(Rva00359032Record const &);
