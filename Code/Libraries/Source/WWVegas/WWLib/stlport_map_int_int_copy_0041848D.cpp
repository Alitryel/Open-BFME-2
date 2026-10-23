// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
//
// Map<int,int> tree copy at 0x0041848D (115B): address-scoped spelling (fleet
// _M_copy_00383C34 precedent: unsuffixed name claimed by 0x2CF6CF build).
// Clones through the rowed member _M_clone_node at 0x0053444F, parent store,
// recursive right copy, iterative left descent. Self callers at 0x004184B6
// and 0x004184E3; callers 0x00418537 and 0x0041874D.
#define _M_copy _M_copy_0041848D
#include <map>

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > MapIntIntTree0041848D;

// Declared only: keeps member clone calls out-of-line so the gate resolves
// them through the rowed 0x0053444F body (no local emission).
template <>
MapIntIntTree0041848D::_Link_type MapIntIntTree0041848D::_M_clone_node(MapIntIntTree0041848D::_Link_type);

// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z present-unmatched
template <>
MapIntIntTree0041848D::_Link_type MapIntIntTree0041848D::_M_copy(MapIntIntTree0041848D::_Link_type __x, MapIntIntTree0041848D::_Link_type __p)
{
	MapIntIntTree0041848D::_Link_type __top = _M_clone_node(__x);
	__top->_M_parent = __p;
	if (__x->_M_right)
		__top->_M_right = _M_copy((MapIntIntTree0041848D::_Link_type)__x->_M_right, __top);
	__p = __top;
	__x = (MapIntIntTree0041848D::_Link_type)__x->_M_left;
	while (__x != 0) {
		MapIntIntTree0041848D::_Link_type __y = _M_clone_node(__x);
		__p->_M_left = __y;
		__y->_M_parent = __p;
		if (__x->_M_right)
			__y->_M_right = _M_copy((MapIntIntTree0041848D::_Link_type)__x->_M_right, __y);
		__p = __y;
		__x = (MapIntIntTree0041848D::_Link_type)__x->_M_left;
	}
	return __top;
}
#undef _M_copy
