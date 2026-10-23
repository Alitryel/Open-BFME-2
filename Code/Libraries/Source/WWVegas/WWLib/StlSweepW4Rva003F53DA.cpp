// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
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

struct Rva003F53DAElement { Rva003F53DAElement();Rva003F53DAElement(const Rva003F53DAElement&);~Rva003F53DAElement();Rva003F53DAElement&operator=(const Rva003F53DAElement&);char bytes[104]; bool operator<(const Rva003F53DAElement&)const; bool operator==(const Rva003F53DAElement&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::vector<Rva003F53DAElement, _STL::allocator<Rva003F53DAElement> >::_M_fill_insert(Rva003F53DAElement *, unsigned int, Rva003F53DAElement const &);

// Independent native 0x003F5724..0x003F5729 follows the complete
// RemoveArmy RET4 and precedes another body. It forwards the unchanged
// receiver and three arguments to verified fill-insert 0x003F53DA.
// The containing wrapper and application element identity remain unknown.
class Rva003F5724 : public _STL::vector<Rva003F53DAElement, _STL::allocator<Rva003F53DAElement> >
{
public:
    void rva003F5724(Rva003F53DAElement *position, unsigned int count, const Rva003F53DAElement &value);
};
void Rva003F5724::rva003F5724(Rva003F53DAElement *position, unsigned int count, const Rva003F53DAElement &value)
{
    _M_fill_insert(position, count, value);
}
