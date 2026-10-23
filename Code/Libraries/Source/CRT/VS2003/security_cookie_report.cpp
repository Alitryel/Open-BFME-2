// Visual C++ 7.1 CRT, secchk.obj: complete 49-byte report_failure.
// Reference: ATL atlmincrt/atlsecchk.c (it identifies this as CRT secchk.c),
// from BFME1 64d369b90170b7e9ec917d646f020b11f13eb0d5's VS2003 inputs.
// Reference copyright (C) Microsoft Corporation. All rights reserved.
// Adapted to a separate C++ TU; C linkage makes the originally private
// helper reachable from SecurityCookieCheck.asm without a synthetic alias.
// Retail independently proves callback arguments (1, NULL), filter 1,
// ExitProcess(3), the two native call bindings and the complete SEH extent.
// cl: /O1 /G6 /MD /GX- /GS- /I"reference/open-bfme-1/inputs/toolchains/vs2003/Program Files/Microsoft Visual Studio .NET 2003/Vc7/PlatformSDK/Include"
#include <windows.h>

extern "C" void __cdecl __security_error_handler(int, void *);

extern "C" void __cdecl report_failure(void)
{
    __try
    {
        __security_error_handler(1, 0);
    }
    __except (EXCEPTION_EXECUTE_HANDLER)
    {
    }
    ExitProcess(3);
}
