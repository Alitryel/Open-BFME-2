// cl: /O1 /G7 /Oy /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// STLport4.5.3 _deque.h operator[](size_type) forwards to the established
// same-element iterator operator[](int) at422D82. That provider uses /Oy-;
// this caller uses frame-pointer omission. Keep the actual provider external.
#include <deque>
#include <string>
struct Rva00422D82Element {
 _STL::basic_string<wchar_t> strings[1];
 bool operator<(const Rva00422D82Element&) const;
 bool operator==(const Rva00422D82Element&) const;
};
namespace _STL {
template<> Rva00422D82Element &_Deque_iterator<Rva00422D82Element,_Nonconst_traits<Rva00422D82Element> >::operator[](int) const;
}
template Rva00422D82Element &_STL::deque<Rva00422D82Element,_STL::allocator<Rva00422D82Element> >::operator[](unsigned int);
