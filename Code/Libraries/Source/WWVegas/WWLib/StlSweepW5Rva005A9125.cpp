// STLport4.5.3 reference operation. Target boundary, calls and full bytes are verified.
// Element identity and unconstrained fields remain address-derived structural inference.
// cl: /O1 /G7 /Ob0 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
#include <algorithm>
#include <memory>

struct Rva005A9125Element { char bytes[8]; bool operator<(const Rva005A9125Element&)const; bool operator==(const Rva005A9125Element&)const; };

// Instantiate the recovered operation and its required template dependencies.
template void _STL::swap<Rva005A9125Element>(Rva005A9125Element &, Rva005A9125Element &);

// Native 0x004C70CF..0x004C70D4 is the complete entry after RET8
// and before the next body. Its unmodified cdecl arguments reach the
// verified 0x005A9125 swap, which exchanges exactly two 4-byte words.
// Preserve the established opaque 8-byte carrier; neither a pair type nor
// an original iter_swap template identity is established by this entry.
void __cdecl rva004C70CF(Rva005A9125Element &left, Rva005A9125Element &right)
{
    _STL::swap(left, right);
}
