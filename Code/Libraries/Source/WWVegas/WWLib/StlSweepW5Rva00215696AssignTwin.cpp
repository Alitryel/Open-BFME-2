// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /O1 /Ob2 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// ICF twin of ??4BfmeVectorRecord0002154F3@@QAEAAU0@ABU0@@Z (0x00215530,
// StringVectorRecordCopyBFME2.cpp): the element of the STLport sweep at
// 0x00215696 is the same AsciiString-plus-vector<AsciiString> record, and its
// assignment is that body. Same flags and declarations as the owner.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <memory>
#include <vector>
#include "ascii_string.h"
#include "unicode_string.h"

// A declaration-only specialization stops this TU emitting its own
// vector<AsciiString> dtor COMDAT, so the call binds the kept copy.
namespace _STL {
template <> vector<AsciiString, allocator<AsciiString> >::~vector();
template <> _Vector_base<AsciiString, allocator<AsciiString> >::~_Vector_base();
template <> void _STLP_alloc_proxy<AsciiString*, AsciiString, allocator<AsciiString> >::deallocate(AsciiString*, size_t);
template <> void allocator<AsciiString>::deallocate(AsciiString*, size_t) const;
template <> vector<AsciiString, allocator<AsciiString> >::vector(const vector<AsciiString, allocator<AsciiString> >&);
template <> _Vector_base<AsciiString, allocator<AsciiString> >::_Vector_base(size_t, const allocator<AsciiString>&);
template <> AsciiString *__uninitialized_copy(const AsciiString*, const AsciiString*, AsciiString*, const __false_type&);
template <> vector<AsciiString, allocator<AsciiString> > &vector<AsciiString, allocator<AsciiString> >::operator=(const vector<AsciiString, allocator<AsciiString> >&);
}

struct Rva00215696Element {
    AsciiString text; _STL::vector<AsciiString> names;
    Rva00215696Element &operator=(const Rva00215696Element &o);
};
Rva00215696Element &Rva00215696Element::operator=(const Rva00215696Element &o)
{
    text = o.text;
    names = o.names;
    return *this;
}
