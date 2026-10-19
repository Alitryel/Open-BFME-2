// cl: /O1 /MD /EHsc /DNDEBUG /Ireference/shims/bfmelist /Ireference/shims/bfmealloc /D_CRTIMP= /D_STLP_USE_STATIC_LIB
// stlport
// Native manager destructor 0x003204D9 and its exact EH graph prove the
// ControlBarScheme pointer-list lifetime. These operations fold with the
// already recovered STLport int-list bodies; compare every callee relocation.
class ControlBarScheme;
#include <list>

namespace _STL {
template <> void _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::clear();

// Unchanged STLport 4.5.3 teardown from stl/_list.h, specialized to match the
// declaration-only consumer. Compiler settings follow RadarObserverListBase.cpp.
template <> _List_base<ControlBarScheme *, allocator<ControlBarScheme *> >::~_List_base()
{
    clear();
    _M_node.deallocate(_M_node._M_data, 1);
}
}
template _STL::_List_base<ControlBarScheme *, _STL::allocator<ControlBarScheme *> >::~_List_base();
