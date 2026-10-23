// cl: /O1 /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// stlport
// ?_M_copy_005344C8@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z, RVA 0x005344C8, 115 bytes.
// unlock lane: map<int,int> tree copy via rowed clone 0x0053444F plus self recursion.
// Evidence: callers 0x005344F1 0x0053451E self plus 0x005345DC in 0x00534581; callees all rowed; unblocks 0x00534581.
#define _M_copy _M_copy_005344C8
#include <map>

typedef _STL::_Rb_tree<int, _STL::pair<const int, int>, _STL::_Select1st<_STL::pair<const int, int> >, _STL::less<int>, _STL::allocator<_STL::pair<const int, int> > > MapIntIntTree005344C8;

// Declared only: keeps member clone calls out-of-line so the gate resolves
// them through the rowed 0x0053444F body (no local emission).
template <>
MapIntIntTree005344C8::_Link_type MapIntIntTree005344C8::_M_clone_node(MapIntIntTree005344C8::_Link_type);

// ?_M_copy@?$_Rb_tree@HU?$pair@$$CBHH@_STL@@U?$_Select1st@U?$pair@$$CBHH@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHH@_STL@@@2@@_STL@@AAEPAU?$_Rb_tree_node@U?$pair@$$CBHH@_STL@@@2@PAU32@0@Z present-unmatched
template <>
MapIntIntTree005344C8::_Link_type MapIntIntTree005344C8::_M_copy(MapIntIntTree005344C8::_Link_type __x, MapIntIntTree005344C8::_Link_type __p)
{
	MapIntIntTree005344C8::_Link_type __top = _M_clone_node(__x);
	__top->_M_parent = __p;
	if (__x->_M_right)
		__top->_M_right = _M_copy((MapIntIntTree005344C8::_Link_type)__x->_M_right, __top);
	__p = __top;
	__x = (MapIntIntTree005344C8::_Link_type)__x->_M_left;
	while (__x != 0) {
		MapIntIntTree005344C8::_Link_type __y = _M_clone_node(__x);
		__p->_M_left = __y;
		__y->_M_parent = __p;
		if (__x->_M_right)
			__y->_M_right = _M_copy((MapIntIntTree005344C8::_Link_type)__x->_M_right, __y);
		__p = __y;
		__x = (MapIntIntTree005344C8::_Link_type)__x->_M_left;
	}
	return __top;
}
#undef _M_copy
