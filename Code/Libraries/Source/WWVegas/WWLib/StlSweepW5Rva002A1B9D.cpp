// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#include <algorithm>
#include <map>
#include "ascii_string.h"

class NamedTimerInfo;

namespace _STL {
template <> void _Rb_tree<AsciiString, pair<const AsciiString, NamedTimerInfo *>, _Select1st<pair<const AsciiString, NamedTimerInfo *> >, less<AsciiString>, allocator<pair<const AsciiString, NamedTimerInfo *> > >::_M_erase(_Rb_tree_node<pair<const AsciiString, NamedTimerInfo *> > *);
}

// Instantiate the recovered operation and its required template dependencies.
template void _STL::_Rb_tree<AsciiString, _STL::pair<AsciiString const, NamedTimerInfo *>, _STL::_Select1st<_STL::pair<AsciiString const, NamedTimerInfo *> >, _STL::less<AsciiString>, _STL::allocator<_STL::pair<AsciiString const, NamedTimerInfo *> > >::clear(void);
