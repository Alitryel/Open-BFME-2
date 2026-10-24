// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Oy- /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include "../../../../../vendor/stlport/stl/_algobase.h"
#include <deque>
struct Rva00584E85Element { int word0; int word1; char tail[1];
    bool operator<(const Rva00584E85Element&) const;
    bool operator==(const Rva00584E85Element&) const; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> > _STL::__copy_aux<_STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> > >(_STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::_Deque_iterator<Rva00584E85Element, _STL::_Nonconst_traits<Rva00584E85Element> >, _STL::__false_type const &);
