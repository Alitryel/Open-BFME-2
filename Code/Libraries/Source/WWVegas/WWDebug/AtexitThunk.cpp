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

// Remaining native atonexit.obj body and both four-byte COMMON objects.
// The table holds -1 for DLL-backed registration; otherwise __dllonexit grows it.
// Define the real C globals once; startup and free adapters already declare them.
extern "C" {
_onexit_t *__onexitbegin=0;
_onexit_t *__onexitend=0;
extern _onexit_t (__cdecl *_imp___onexit)(_onexit_t);
_onexit_t __cdecl __dllonexit(_onexit_t,_onexit_t **,_onexit_t **);
_onexit_t __cdecl _onexit(_onexit_t callback) {
 if(__onexitbegin==(_onexit_t *)-1)return _imp___onexit(callback);
 return __dllonexit(callback,&__onexitbegin,&__onexitend);
}
}
