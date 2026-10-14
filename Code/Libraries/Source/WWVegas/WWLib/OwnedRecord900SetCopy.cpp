// cl: /O1 /G7 /arch:SSE /EHs /D_STLP_NO_EXCEPTIONS /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// set<BfmeStringRecord002CF550>'s copy constructor at 0x00415676 (18B): the
// set-level wrapper over the tree copy constructor 0x0041559E
// (OwnedRecord900TreeCopy.cpp), which retail calls out of line from here.
// Skeleton twin of AsciiString::operator= 0x00001733. The tree constructor is
// declared as a specialization so this unit calls it instead of expanding it.
#include <set>
#include "OwnedRecord900.h"

namespace _STL {
template <> BfmeStringRecordTree900::_Rb_tree(const BfmeStringRecordTree900 &);
}

template _STL::set<BfmeStringRecord002CF550>::set(const _STL::set<BfmeStringRecord002CF550> &);
