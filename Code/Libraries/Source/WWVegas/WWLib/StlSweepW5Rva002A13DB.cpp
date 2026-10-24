// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
#define BFME_ASCII_DTOR_DECL
#include <map>
#include "ascii_string.h"

class NamedTimerInfo;
typedef _STL::pair<const AsciiString, NamedTimerInfo *> NamedTimerValue;
typedef _STL::_Rb_tree<AsciiString, NamedTimerValue, _STL::_Select1st<NamedTimerValue>, _STL::less<AsciiString>, _STL::allocator<NamedTimerValue> > NamedTimerTree;

// Only the string key has a destructor; the mapped timer pointer is trivial.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _Destroy<NamedTimerValue>(NamedTimerValue *value) { value->first.~AsciiString(); }
}

// Instantiate the recovered operation and its required template dependencies.
template void NamedTimerTree::_M_erase(_STL::_Rb_tree_node<NamedTimerValue> *);
