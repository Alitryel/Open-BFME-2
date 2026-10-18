// ?StringCopyWorkerA@@YGJPADIPBD@Z
// partial score=0.9672131148 date=2026-10-18
// cl: /I. /O1 /G7 /MD /DNDEBUG
// Compile the supplied VS2003 Platform SDK's pristine safe-string definitions.
#define STRSAFE_NO_DEPRECATE
#include "reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include/strsafe.h"
// The header discourages direct worker calls with post-definition macros.
// Taking their addresses here retains the archive's independently named bodies.
#undef StringCopyWorkerA
#undef StringCopyWorkerW
#undef StringVPrintfWorkerA
#undef StringVPrintfWorkerW
#undef StringLengthWorkerA
#undef StringLengthWorkerW

typedef void (__cdecl *StrSafeEmissionTarget)();
// ?strSafeEmissionTarget absent-from-retail
StrSafeEmissionTarget strSafeEmissionTarget(unsigned index)
{
    static StrSafeEmissionTarget const targets[] = {
        reinterpret_cast<StrSafeEmissionTarget>(&StringCopyWorkerA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCopyWorkerW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringVPrintfWorkerA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringVPrintfWorkerW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringLengthWorkerA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringLengthWorkerW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchCopyA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchCopyW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchPrintfA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchPrintfW),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchLengthA),
        reinterpret_cast<StrSafeEmissionTarget>(&StringCchLengthW)
    };
    return index < sizeof(targets) / sizeof(targets[0]) ? targets[index] : 0;
}
