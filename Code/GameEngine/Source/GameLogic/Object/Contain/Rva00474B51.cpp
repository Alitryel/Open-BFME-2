// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native 0x00474B51: Coord3D output, Object* and one word; returns output.
// Target evidence fixes the +60 four-byte-key/value map, +184 gate,
// +1AC provider slot13, Object ID +74 and position +38. The fallback
// receiver is adjusted by -11C; its original class identity is unresolved.
#include <map>
#include "../../../../../Libraries/Include/Lib/Coord3D.h"
// bfme link decl-only begin
namespace _STL { template <> pair<int const,int>::pair(int const &,int const &); }
namespace _STL { template <> pair<_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,bool>::pair(_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > const &,bool const &); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > & _Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >::operator++(); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > & _Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >::operator--(); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::_M_create_node(_STL::pair<int const,int> const &); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,int> > *,_STL::_Rb_tree_node<_STL::pair<int const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > > >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> _STL::_Rb_tree_node<_STL::pair<int const,int> > * allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > >::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<_STL::_Rb_tree_node<_STL::pair<int const,int> > *,_STL::_Rb_tree_node<_STL::pair<int const,int> >,_STL::allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,int> > *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<_STL::_Rb_tree_node<_STL::pair<int const,int> > >::deallocate(_STL::_Rb_tree_node<_STL::pair<int const,int> > *,unsigned int) const; }
namespace _STL { template <> _STL::pair<_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,bool> _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::insert_unique(_STL::pair<int const,int> const &); }
namespace _STL { template <> _STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > > _Rb_tree<int,_STL::pair<int const,int>,_STL::_Select1st<_STL::pair<int const,int> >,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::insert_unique(_STL::_Rb_tree_iterator<_STL::pair<int const,int>,_STL::_Nonconst_traits<_STL::pair<int const,int> > >,_STL::pair<int const,int> const &); }
namespace _STL { template <> int & map<int,int,_STL::less<int>,_STL::allocator<_STL::pair<int const,int> > >::operator[](int const &); }
// bfme link decl-only end

// map/set<int> internals otherwise instantiate the less<int>::operator()
// COMDAT (one byte shape per TU flags); an explicit dllimport+forceinline
// specialization takes those calls inline so this TU emits no external copy.
namespace _STL {
template <> __declspec(dllimport) __forceinline
bool less<int>::operator()(const int &a, const int &b) const
{ return a < b; }
}

class Object;

class Rva00474B51Provider
{
public:
	virtual void v00(); virtual void v01(); virtual void v02(); virtual void v03();
	virtual void v04(); virtual void v05(); virtual void v06(); virtual void v07();
	virtual void v08(); virtual void v09(); virtual void v10(); virtual void v11();
	virtual void v12();
	virtual bool v13(int key, Coord3D *position);
};

class Rva00472620
{
public:
	Coord3D *rva00472620(Coord3D *out, Object *object, int word);
};

class Rva00474B51
{
public:
	Coord3D *rva00474B51(Coord3D *out, Object *object, int word);
private:
	char unknown00[0x60];
	_STL::map<int, int> keys;
	char unknown68[0x184 - 0x60 - sizeof(_STL::map<int, int>)];
	int enabled;
	char unknown188[0x1AC - 0x188];
	Rva00474B51Provider *provider;
};

Coord3D *Rva00474B51::rva00474B51(Coord3D *out, Object *object, int word)
{
	int key = *reinterpret_cast<int *>(reinterpret_cast<char *>(object) + 0x74);
	int mapped = keys[key];
	if (enabled)
	{
		Coord3D position = *reinterpret_cast<const Coord3D *>(reinterpret_cast<char *>(object) + 0x38);
		if (provider->v13(mapped, &position))
		{
			out->x = position.x;
			out->y = position.y;
			out->z = position.z;
			return out;
		}
	}
	reinterpret_cast<Rva00472620 *>(reinterpret_cast<char *>(this) - 0x11C)->rva00472620(out, object, word);
	return out;
}
