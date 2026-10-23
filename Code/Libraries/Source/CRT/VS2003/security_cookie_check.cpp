// Microsoft Visual C++ .NET 2003 CRT 13.10.3077, secchk.obj.
// Reconstructed from retail 0x00629BAB..0x00629BB9 and the established
// ATL atlmincrt/atlsecchk.c entry contract. ECX carries the cookie; EAX and
// EDX must survive the successful return. The whole emitted body verifies
// both preservation and the tail transfer to the original failure helper.
// compiler: clang23-x86
// cl: /GS- /clang:-mllvm /clang:-branch-folder-reorder-blocks=false

// DWORD_PTR is unsigned long in the established 32-bit cookie owner.
extern "C" unsigned long __security_cookie;
extern "C" void __cdecl report_failure();

extern "C" void __fastcall __security_check_cookie(unsigned long cookie)
{
    if (cookie != __security_cookie)
        report_failure();
}
