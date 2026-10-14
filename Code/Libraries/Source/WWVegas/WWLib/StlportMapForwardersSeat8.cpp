// cl: /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
//
// Five-byte STLport container forwarders from unrowed .text gaps: each is a
// bare tail jump from the container's inline member to the rowed tree or
// vector member it forwards to (map/set::clear -> _Rb_tree::clear,
// map::swap -> _Rb_tree::swap, vector::insert(pos, n, x) ->
// _M_fill_insert). The callees are only declared so the calls stay out of
// line; element and key types are the ledger's spellings for those rows.
#include <map>
#include <set>
#include <vector>
#include "ascii_string.h"

struct Rva002A1B9DElement { short words[1]; bool operator<(const Rva002A1B9DElement&b)const { return words[0]<b.words[0]; } bool operator==(const Rva002A1B9DElement&b)const {return words[0]==b.words[0];} };
struct TreeHintPayload001F8ACB;
struct Coord3D;
struct BfmeStringRecord002CF550;
struct Rva00215949Element { Rva00215949Element();Rva00215949Element(const Rva00215949Element&);~Rva00215949Element();Rva00215949Element&operator=(const Rva00215949Element&);char bytes[16]; bool operator<(const Rva00215949Element&)const; bool operator==(const Rva00215949Element&)const; };
enum ScienceType { SCIENCE_INVALID = -1 };

typedef _STL::map<Rva002A1B9DElement, int> MapA;                       // 0x002A3F56
typedef _STL::map<AsciiString, TreeHintPayload001F8ACB> MapB;          // 0x002C6C8E
typedef _STL::map<AsciiString, Coord3D> MapC;                          // 0x00301EC2
typedef _STL::map<_STL::pair<AsciiString, AsciiString>, int> MapD;     // 0x0032C366
typedef _STL::set<BfmeStringRecord002CF550> SetE;                     // 0x0033D000
typedef _STL::map<int, int> MapF;                                      // 0x0032B4AD
typedef _STL::vector<Rva00215949Element> VecG;                         // 0x00215A88
typedef _STL::vector<float> VecH;                                      // 0x0030E90B
typedef _STL::vector<_STL::vector<ScienceType> > VecI;                 // 0x0033A271

namespace _STL {
template <> void MapA::_Rep_type::clear();   // 0x002A1B9D
template <> void MapB::_Rep_type::clear();   // 0x001F8927
template <> void MapC::_Rep_type::clear();   // 0x0022D160
template <> void MapD::_Rep_type::clear();   // 0x0032BEBF
template <> void SetE::_Rep_type::clear();   // 0x002572AE
template <> void MapF::_Rep_type::swap(MapF::_Rep_type &);   // 0x0032AC92
template <> void VecG::_M_fill_insert(VecG::iterator, VecG::size_type, const VecG::value_type &);   // 0x00215949
template <> void VecH::_M_fill_insert(VecH::iterator, VecH::size_type, const VecH::value_type &);   // 0x0030E7FE
template <> void VecI::_M_fill_insert(VecI::iterator, VecI::size_type, const VecI::value_type &);   // 0x0033A05E
}

template void MapA::clear();
template void MapB::clear();
template void MapC::clear();
template void MapD::clear();
template void SetE::clear();
template void MapF::swap(MapF &);
template void VecG::insert(VecG::iterator, VecG::size_type, const VecG::value_type &);
template void VecH::insert(VecH::iterator, VecH::size_type, const VecH::value_type &);
template void VecI::insert(VecI::iterator, VecI::size_type, const VecI::value_type &);

// holder destructors (5B each), tail jumps to the rowed _Rb_tree destructors:
//   0x002F1C55 -> 0x002F0B8A, 0x002F1C5A -> 0x002F0BB5, 0x0032C62D -> 0x0032C36B
struct Rva002F0B8AElement;
struct Rva002F0BB5Element;
typedef _STL::map<int, Rva002F0B8AElement> MapJ;
typedef _STL::map<int, Rva002F0BB5Element> MapK;
typedef _STL::pair<const int, Rva002F0B8AElement> ValJ;
typedef _STL::pair<const int, Rva002F0BB5Element> ValK;
typedef _STL::pair<AsciiString, AsciiString> KeyD;
typedef _STL::pair<const KeyD, int> ValD;
namespace _STL {
template <> _Rb_tree<int, ValJ, _Select1st<ValJ>, less<int>, allocator<ValJ> >::~_Rb_tree();
template <> _Rb_tree<int, ValK, _Select1st<ValK>, less<int>, allocator<ValK> >::~_Rb_tree();
template <> _Rb_tree<KeyD, ValD, _Select1st<ValD>, less<KeyD>, allocator<ValD> >::~_Rb_tree();
}
// The owners holding each map as their only member are not recovered, so
// the destructors are spelled on address-named holders.
class Rva002F1C55 { public: ~Rva002F1C55(); private: MapJ m_map; };
Rva002F1C55::~Rva002F1C55() {}
class Rva002F1C5A { public: ~Rva002F1C5A(); private: MapK m_map; };
Rva002F1C5A::~Rva002F1C5A() {}
class Rva0032C62D { public: ~Rva0032C62D(); private: MapD m_map; };
Rva0032C62D::~Rva0032C62D() {}

// 0x002BC5C4 (5B): vector<Rva002BC47DElement>::insert(pos, n, x) -> rowed
// _M_fill_insert 0x002BC47D (StlSweepW4Rva002BC47D.cpp stand-in).
struct Rva002BC47DElement { Rva002BC47DElement();Rva002BC47DElement(const Rva002BC47DElement&);~Rva002BC47DElement();Rva002BC47DElement&operator=(const Rva002BC47DElement&);char bytes[52]; bool operator<(const Rva002BC47DElement&)const; bool operator==(const Rva002BC47DElement&)const; };
typedef _STL::vector<Rva002BC47DElement> VecL;
namespace _STL {
template <> void VecL::_M_fill_insert(VecL::iterator, VecL::size_type, const VecL::value_type &);
}
template void VecL::insert(VecL::iterator, VecL::size_type, const VecL::value_type &);
