// cl: /EHs /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
//
// ??1BfmeNarrowRecord0041A5D2@@QAE@XZ @0x0041A200, 65B: dtor of the
// two-string record (text0 +0, text1 +0x10) whose default ctor 0x0041A1CF
// and copy assign 0x0041A7F7 are rowed in NarrowStringRecordCopyBFME2.cpp.
// Retail frees both string buffers with EH states around the extern "C"
// _free calls, so this TU uses /EHs (the /EHsc sibling drops those states).
// Callers: 0x0041A241/0x0041A3C4/0x0041A486/0x0041A843/0x0041A96D.
#include <memory>
#include <string>
#include "BfmeNarrowRecord0041A5D2.h"
// Keep _String_base<char>::~_String_base inline-only: no call here leaves it out
// of line, and this TU's frameless COMDAT copy is not retail's 0x0000B3C0 body.
namespace _STL {
template <> __declspec(dllimport) __declspec(nothrow) __forceinline
_String_base<char, allocator<char> >::~_String_base() { _M_deallocate_block(); }
}
// Keep _STLP_alloc_proxy<char*>::deallocate inline-only: this TU never calls it
// out of line, and its COMDAT copy (unit flags) differs from retail's 0x006892B0 body.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_alloc_proxy<char*, char, allocator<char> >::deallocate(char *__p, size_t __n)
{ allocator<char>::deallocate(__p, __n); }
}

// __malloc_alloc<0> allocate/deallocate otherwise instantiate per-TU
// COMDATs (one byte shape per TU malloc/free wiring); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *__malloc_alloc<0>::allocate(size_t __n)
{ void *__r = malloc(__n); if (!__r) __r = _S_oom_malloc(__n); return __r; }
template <> __declspec(dllimport) __forceinline
void __malloc_alloc<0>::deallocate(void *__p, size_t)
{ free((char *)__p); }
}
BfmeNarrowRecord0041A5D2::~BfmeNarrowRecord0041A5D2() {}
