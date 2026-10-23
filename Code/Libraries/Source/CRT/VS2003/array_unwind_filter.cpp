// Visual C++ 7.1 ehvecdtr.obj exception filter, recovered from retail.
// Complete native 006290A0..006290B2: terminate on a C++ exception raised
// during array unwinding; let other exception codes continue searching.
// The archive's static symbol and retail EAX input establish its private ABI.
// cl: /O1 /G6 /MD /EHsc /Ireference/shims/sweep
#include <windows.h>

// The existing verified import owner forwards to the PE-named
// msvcr71.dll!?terminate@@YAXXZ at 00629BC0 (IAT VA 00BBA438).
__declspec(noreturn) void __cdecl ji_00629bc0();

static __declspec(noinline) int ArrayUnwindFilter(_EXCEPTION_POINTERS *exception)
{
    if (exception->ExceptionRecord->ExceptionCode != 0xE06D7363UL)
        return 0;
    ji_00629bc0();
}

// Keep the static filter's native EAX parameter convention without taking
// its address. This emission context has no retail claim.
// ?arrayFilterEmissionAnchor absent-from-retail
int arrayFilterEmissionAnchor(_EXCEPTION_POINTERS *exception)
{
    return ArrayUnwindFilter(exception);
}
