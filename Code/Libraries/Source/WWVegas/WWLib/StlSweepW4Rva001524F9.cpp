// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>

struct Rva001524F9Element { Rva001524F9Element();Rva001524F9Element(const Rva001524F9Element&);~Rva001524F9Element();Rva001524F9Element&operator=(const Rva001524F9Element&);char bytes[36]; bool operator<(const Rva001524F9Element&)const; bool operator==(const Rva001524F9Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva001524F9Element, _STL::allocator<Rva001524F9Element> >::_M_fill_insert(Rva001524F9Element *, unsigned int, Rva001524F9Element const &);

// Independent native entry 0x00152659..0x0015265E forwards the unchanged
// receiver and three arguments to the verified fill-insert at 0x001524F9.
// The destination establishes the vector/argument view; the original
// wrapper name and application element identity remain unknown.
class Rva00152659 : public _STL::vector<Rva001524F9Element, _STL::allocator<Rva001524F9Element> >
{
public:
	void rva00152659(Rva001524F9Element *position, unsigned int count, const Rva001524F9Element &value);
};

void Rva00152659::rva00152659(Rva001524F9Element *position, unsigned int count, const Rva001524F9Element &value)
{
	_M_fill_insert(position, count, value);
}
