// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <list>

// The element is short: retail push_back calls insert 0x002ABB61, the rowed
// list<short>::insert (stlport_list_s_insert.cpp), whose node copy is a word move.

// Instantiate the recovered operation and its required template dependencies.
template void _STL::list<short, _STL::allocator<short> >::push_back(short const &);
