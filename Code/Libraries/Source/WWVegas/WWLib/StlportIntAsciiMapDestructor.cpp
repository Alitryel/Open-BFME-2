// cl: /O1 /G7 /arch:SSE /MD /EHsc /Ireference/shims/bfme2_ascii
// stlport
// STLport4.5.3 map ownership adaptor over the verified int/AsciiString tree.
#include "ascii_string.h"
#include <map>
// bfme link decl-only begin
namespace _STL { template <> _Rb_tree<int, pair<int const, AsciiString>, _Select1st<pair<int const, AsciiString> >, less<int>, allocator<pair<int const, AsciiString> > >::~_Rb_tree(); }
// bfme link decl-only end
namespace _STL {
typedef pair<const int,AsciiString> IntAsciiValue;
typedef _Rb_tree<int,IntAsciiValue,_Select1st<IntAsciiValue>,less<int>,allocator<IntAsciiValue> > IntAsciiTree;
template<> IntAsciiTree::~_Rb_tree();
template map<int,AsciiString,less<int>,allocator<IntAsciiValue> >::~map();
}

// ?EmitIntAsciiMapArrayDelete absent-from-retail
void EmitIntAsciiMapArrayDelete(_STL::map<int,AsciiString> *p){delete[] p;}
