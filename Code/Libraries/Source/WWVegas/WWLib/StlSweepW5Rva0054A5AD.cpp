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
#include <deque>
#include <string>
// bfme link decl-only begin
namespace _STL { template <> basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > & basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::operator=(basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> > const &); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null(unsigned short *); }
namespace _STL { template <> void basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::_M_construct_null_aux(unsigned short *, __true_type const &); }
namespace _STL { template <> unsigned short * allocator<unsigned short>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void __char_traits_base<unsigned short, unsigned short>::assign(unsigned short &, unsigned short const &); }
namespace _STL { template <> unsigned short * basic_string<unsigned short, char_traits<unsigned short>, allocator<unsigned short> >::erase(unsigned short *, unsigned short *); }
namespace _STL { template <> unsigned short * __char_traits_base<unsigned short, unsigned short>::move(unsigned short *, unsigned short const *, unsigned int); }
// bfme link decl-only end

// Retail's body calls __copy_backward<deque_iterator<BfmeE8>> (0x0054A152,
// stlport_deque_e8_o1.cpp), so the element is that unit's 8-byte BfmeE8.
struct BfmeE8 { int a, b; };

// Instantiate the recovered operation and its required template dependencies.
template _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> > _STL::__copy_backward_aux<_STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >, _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> > >(_STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >, _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >, _STL::_Deque_iterator<BfmeE8, _STL::_Nonconst_traits<BfmeE8> >, _STL::__false_type const &);
