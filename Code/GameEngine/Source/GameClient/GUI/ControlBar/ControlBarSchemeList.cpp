// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native manager destructor 0x003204D9 and its exact EH graph prove the
// ControlBarScheme pointer-list lifetime. These operations fold with the
// already recovered STLport int-list bodies; compare every callee relocation.
class ControlBarScheme;
#include <list>

namespace _STL {
// Unchanged STLport 4.5.3 clear from stl/_list.c, with its template arguments
// fixed for the consumer's specialization declaration. Pointer elements are
// destroyed without deleting the pointed-to schemes (the manager does that).
template <> void _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::clear()
{
    _List_node<ControlBarScheme *> *cur = (_List_node<ControlBarScheme *> *)_M_node._M_data->_M_next;
    while (cur != _M_node._M_data) {
        _List_node<ControlBarScheme *> *tmp = cur;
        cur = (_List_node<ControlBarScheme *> *)cur->_M_next;
        _STL::_Destroy(&tmp->_M_data);
        _M_node.deallocate(tmp, 1);
    }
    _M_node._M_data->_M_next = _M_node._M_data;
    _M_node._M_data->_M_prev = _M_node._M_data;
}

// Unchanged STLport 4.5.3 teardown from stl/_list.h, specialized to match the
// declaration-only consumer. Compiler settings follow RadarObserverListBase.cpp.
template <> _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::~_List_base()
{
    clear();
    _M_node.deallocate(_M_node._M_data, 1);
}
}
template _STL::_List_base<ControlBarScheme *, _STL::allocator<ControlBarScheme *> >::~_List_base();
template void _STL::_List_base<ControlBarScheme *, _STL::allocator<ControlBarScheme *> >::clear();
