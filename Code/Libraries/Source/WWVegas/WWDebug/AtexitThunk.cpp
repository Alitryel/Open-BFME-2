// cl: /DNDEBUG /MD
// BFME1 authored donor at 0x009F6E26; BFME2 native atonexit.obj 0x006291F8.
//
// Native COFF and public stdlib.h identify C atexit: forward to _onexit and map its result to
// 0 or -1. The neg/sbb/neg/dec tail is how MSVC 7.1 materialises that ternary
// without a branch.

typedef void (__cdecl *_PVFV)(void);
typedef int (__cdecl *_onexit_t)(void);

extern "C" _onexit_t __cdecl _onexit(_onexit_t func);
extern "C" int __cdecl atexit(_PVFV func);

extern "C" int __cdecl atexit(_PVFV func)
{
	return (_onexit((_onexit_t)func) == 0) ? -1 : 0;
}
