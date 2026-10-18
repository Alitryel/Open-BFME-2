// cl: /O2 /G7 /Ireference/shims/bfmealloc /D_CRTIMP= /DNDEBUG /MD /GX /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS
// stlport
// Actual GetEdges directed-edge pair map; independently proven unwind7677D0
// of native GetEdges16E450 invokes its5B destructor16E2B0. Existing pair-key
// clear86B provider was fold-proven in RvaMapIndexGenP12pod00928690.cpp.
#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline allocator<void *>::~allocator() {} }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
// bfme link decl-only end
typedef _STL::pair<int, int> Rva00928590Key;
struct Rva00928590Hash { unsigned operator()(const Rva00928590Key &) const; };
struct Rva00928590Eq { bool operator()(const Rva00928590Key &, const Rva00928590Key &) const; };
typedef _STL::pair<const Rva00928590Key, int> Rva00928590Value;
typedef _STL::hashtable<Rva00928590Value, Rva00928590Key, Rva00928590Hash,
    _STL::_Select1st<Rva00928590Value>, Rva00928590Eq,
    _STL::allocator<Rva00928590Value> > Rva00928590Table;
template void Rva00928590Table::clear();

typedef _STL::hash_map<Rva00928590Key,int,Rva00928590Hash,Rva00928590Eq,_STL::allocator<Rva00928590Value> > Rva00928590Map;
template Rva00928590Table::~hashtable();
template Rva00928590Map::~hash_map();

// Force emission of the genuine implicit map destructor used by native EH.
// ?BfmeGetEdgesPairMapArrayDeleteAnchor present-unmatched
void BfmeGetEdgesPairMapArrayDeleteAnchor(Rva00928590Map *p) { delete[] p; }
