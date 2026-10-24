// Visual C++ 7.1 ehvecdtr.obj, recovered from retail: the array-unwind
// exception filter (006290A0), __ArrayUnwind (006290B2) and the compiler's
// vector destructor iterator __ehvec_dtor, ??_M (00629110).
// The callbacks are real __thiscall function pointers (P6E in the archive's
// mangled names). VC7.1 reserves that keyword (C4234) unless the undocumented
// c1xx switch /d1Binl admits it; without the switch a suppressed diagnostic
// silently demotes the type to cdecl (P6A), see
// reverse/attempt_support/family-compiler-prerequisites-20261024/.
// cl: /O1 /G6 /MD /EHsc /d1Binl /Ireference/shims/sweep
#include <windows.h>

// The existing verified import owner forwards to the PE-named
// msvcr71.dll!?terminate@@YAXXZ at 00629BC0 (IAT VA 00BBA438).
__declspec(noreturn) void __cdecl ji_00629bc0();

// A C++ exception thrown by a destructor while an array is already being
// unwound terminates; anything else keeps searching.
static int ArrayUnwindFilter(_EXCEPTION_POINTERS *exception)
{
    EXCEPTION_RECORD *record = exception->ExceptionRecord;
    switch (record->ExceptionCode)
    {
    case 0xE06D7363UL:
        ji_00629bc0();
    default:
        return 0;
    }
}

// Destroy the count elements below ptr, last first, after a constructor or
// destructor of the same array threw.
void __stdcall __ArrayUnwind(void *ptr, unsigned size, int count, void (__thiscall *pDtor)(void *))
{
    __try
    {
        while (--count >= 0)
        {
            ptr = (char *)ptr - size;
            (*pDtor)(ptr);
        }
    }
    __except (ArrayUnwindFilter((_EXCEPTION_POINTERS *)_exception_info()))
    {
    }
}

void __stdcall __ehvec_dtor(void *ptr, unsigned size, int count, void (__thiscall *pDtor)(void *))
{
    int success = 0;
    ptr = (char *)ptr + size * count;
    __try
    {
        while (--count >= 0)
        {
            ptr = (char *)ptr - size;
            (*pDtor)(ptr);
        }
        success = 1;
    }
    __finally
    {
        if (!success)
            __ArrayUnwind(ptr, size, count, pDtor);
    }
}
