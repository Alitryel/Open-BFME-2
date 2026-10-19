// cl: /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ??1?$_Rb_tree@URva00286656Element@@U?$pair@$$CBURva00286656Element@@H@_STL@@U?$_Select1st@U?$pair@$$CBURva00286656Element@@H@_STL@@@3@U?$less@URva00286656Element@@@3@V?$allocator@U?$pair@$$CBURva00286656Element@@H@_STL@@@3@@_STL@@QAE@XZ,
// retail 0x00286852, 56 bytes. STLport 4.5.3 _Rb_tree dtor of the Contain and
// ConnectionManager map family (callers: OpenContain/HordeContain/SiegeEngineContain/
// HordeSiegeEngineContain dtors and unwind funclets, ConnectionManager's map via
// the ~map thunk 0x00286921).
// Target fact: it calls clear at 0x00286656 (rowed for the Rva00286656Element
// tree), while the int/void* clear row 0x004ABC5C belongs to the twin dtor
// 0x004ABCFE, so this family is not the int/void* instantiation. Key/value stay
// the address-derived view of 0x00286656 (ZH OpenContain's ObjectID-keyed
// enter/exit map is a structural lead, not proven).
#include <map>

struct Rva00286656Element { short words[1]; bool operator<(const Rva00286656Element &b) const { return words[0] < b.words[0]; } };

typedef _STL::pair<const Rva00286656Element, int> Rva00286852Pair;
typedef _STL::_Rb_tree<Rva00286656Element, Rva00286852Pair, _STL::_Select1st<Rva00286852Pair>, _STL::less<Rva00286656Element>, _STL::allocator<Rva00286852Pair> > Rva00286852Tree;
template <> void Rva00286852Tree::clear();  // rowed at 0x00286656 (StlSweepW5Rva00286656.cpp)
template Rva00286852Tree::~_Rb_tree();

// The family's empty-map construction chain folds into the shared STLport
// bodies (map 0x0033C432 -> tree 0x001F068F -> tree base 0x001F0534).
typedef _STL::map<Rva00286656Element, int> Rva00286852Map;
template Rva00286852Map::map();
