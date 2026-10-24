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

struct Rva00002926Element { ~Rva00002926Element(); // declared only: retail's destructor is the rowed body at its pinned address

    _STL::list<short> values[1];
};

// ?trigger absent-from-retail
void trigger(Rva00002926Element *p) {
    delete p;
}
// The declared destructor binds to that row (tools/allowed_symbols.py --alternatenames).
#pragma comment(linker, "/alternatename:??1Rva00002926Element@@QAE@XZ=??1CImage@ATL@@UAE@XZ")
