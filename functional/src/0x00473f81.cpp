// ?rva00473F81@Rva00473F81@@QAEAAVRva00469155@@ABH@Z
// partial score=0.97 date=2026-10-18
// ?rva00473F81@Rva00473F81@@QAEAAVRva00469155@@ABH@Z
// partial score=0.97 date=2026-10-14
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHs /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#define _STLP_NO_EXCEPTIONS
#include <map>

struct Coord3D { float x; float y; float z; };

class Rva00469155
{
public:
	Rva00469155();
	Rva00469155 &operator=(const Rva00469155 &o);
	Coord3D m_pos;
	unsigned int m_value;
};

class Rva00469BEA
{
public:
	Rva00469BEA(const int &a, const Rva00469155 &b);
	~Rva00469BEA() {}
	int m_00;
	Rva00469155 m_04;
};

struct Rva00470205Record { char bytes[1]; };
typedef _STL::map<int, Rva00470205Record, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00470205Record> > > Rva00470205Map;
typedef _STL::map<int, Rva00469155, _STL::less<int>, _STL::allocator<_STL::pair<const int, Rva00469155> > > Rva00469155Map;
typedef _STL::map<int, int> BoneIntMap;
typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > BoneIntTree;
template<> BoneIntTree::_Link_type BoneIntTree::_M_lower_bound(const int &) const;
namespace _STL {
template <> Rva00470205Map::iterator Rva00470205Map::insert(iterator, const value_type &);
typedef Rva00470205Map::iterator (Rva00470205Map::*RecordInsertFn)(Rva00470205Map::iterator, const Rva00470205Map::value_type &);
typedef Rva00469155Map::iterator (Rva00470205Map::*MapInsertFn)(Rva00469155Map::iterator, const Rva00469155Map::value_type &);
}

class Rva00473F81 : public Rva00470205Map
{
public:
	Rva00469155 &rva00473F81(const int &key);
};

Rva00469155 &Rva00473F81::rva00473F81(const int &key)
{
	BoneIntMap::iterator found = ((BoneIntMap *)this)->lower_bound(key);
	iterator i = *(iterator *)&found;
	if (i == end() || key < (*i).first)
	{
		i = insert(i, *(const value_type *)&Rva00469BEA(key, Rva00469155()));
	}
	return *(Rva00469155 *)&(*i).second;
}
