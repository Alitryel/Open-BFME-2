// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// stlport
// ?rva000BC057@W3DScriptedModelDraw@@QAEXH@Z, retail 0x000BC057 (39 bytes, RET 4), a slot of the
// model-draw table 0x007CC588: removes the key's entry from the int-keyed map at +0x9C when
// present. The lookup and the erase are the ICF-folded STLport bodies rowed under the
// map<int,int> _M_find (0x00388F63) and map<int,void*> erase (0x005530A8) names, so the map
// is reached through those two views; W3DScriptedModelDraw.cpp holds the rest of the class.
#include <map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<int>::operator()(int const &x,int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> bool less<int>::operator()(int const &, int const &) const; }
namespace _STL { template <> void _Rb_tree<int, pair<int const, void *>, _Select1st<pair<int const, void *> >, less<int>, allocator<pair<int const, void *> > >::erase(_Rb_tree_iterator<pair<int const, void *>, _Nonconst_traits<pair<int const, void *> > >); }
// bfme link decl-only end
// Retail inlines the typed node comparison. Keep that comparison local so
// this unit does not emit a competing tree-base operator!= COMDAT.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

typedef _STL::map<int, int> Rva000BC057FindView;
typedef _STL::map<int, void *> Rva000BC057EraseView;

class W3DScriptedModelDraw
{
public:
	void rva000BC057(int key);
private:
	unsigned char m_pad00[0x9C];
	Rva000BC057EraseView m_map;		// +0x9C
};

void W3DScriptedModelDraw::rva000BC057(int key)
{
	Rva000BC057FindView &lookup = reinterpret_cast<Rva000BC057FindView &>(m_map);
	Rva000BC057FindView::iterator it = lookup.find(key);
	if (it != lookup.end())
		m_map.erase(reinterpret_cast<Rva000BC057EraseView::iterator &>(it));
}
