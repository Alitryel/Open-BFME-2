// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Map<int,int> tree copy at 0x00418E05 (115B): address-scoped spelling (fleet
// _M_copy_00383C34 precedent: unsuffixed name claimed by 0x2CF6CF build).
// Clones through the rowed member _M_clone_node at 0x0053444F, parent store,
// recursive right copy, iterative left descent. Self callers at 0x00418E2E
// and 0x00418E5B; callers 0x00418EAF and 0x00419090.
#define _M_copy _M_copy_00418E05
#include <map>

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > MapIntIntTree00418E05;

// Declared only: keeps member clone calls out-of-line so the gate resolves
// them through the rowed 0x0053444F body (no local emission).
template <>
MapIntIntTree00418E05::_Link_type MapIntIntTree00418E05::_M_clone_node(MapIntIntTree00418E05::_Link_type);

// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z present-unmatched
template <>
MapIntIntTree00418E05::_Link_type MapIntIntTree00418E05::_M_copy(MapIntIntTree00418E05::_Link_type __x, MapIntIntTree00418E05::_Link_type __p)
{
	MapIntIntTree00418E05::_Link_type __top = _M_clone_node(__x);
	__top->_M_parent = __p;
	if (__x->_M_right)
		__top->_M_right = _M_copy((MapIntIntTree00418E05::_Link_type)__x->_M_right, __top);
	__p = __top;
	__x = (MapIntIntTree00418E05::_Link_type)__x->_M_left;
	while (__x != 0) {
		MapIntIntTree00418E05::_Link_type __y = _M_clone_node(__x);
		__p->_M_left = __y;
		__y->_M_parent = __p;
		if (__x->_M_right)
			__y->_M_right = _M_copy((MapIntIntTree00418E05::_Link_type)__x->_M_right, __y);
		__p = __y;
		__x = (MapIntIntTree00418E05::_Link_type)__x->_M_left;
	}
	return __top;
}
#undef _M_copy
