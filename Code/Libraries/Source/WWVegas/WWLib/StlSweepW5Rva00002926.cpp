// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

// Suppress non-retail list<short> bodies:
namespace _STL {
template <> void _List_base<short, allocator<short> >::clear();
template <> _List_base<short, allocator<short> >::~_List_base();
}

struct Rva00002926Element {
    _STL::list<short> values[1];
};

// ?trigger absent-from-retail
void trigger(Rva00002926Element *p) {
    delete p;
}
