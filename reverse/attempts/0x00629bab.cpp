// @__security_check_cookie@4
// partial score=0.571429 date=2026-10-18
// cl: /O1 /G6 /MD /GX- /GS-
// Near body for Code/Libraries/Source/CRT/VS2003/security_cookie_report.cpp.
// Native629BAB..629BB9 receives the cookie in ECX and preserves EAX/EDX.
// The ordinary fastcall body does too, but emits JE/JMP/RET where retail has
// JNE/RET/JMP. Both complete functions are14 bytes; no relocation trick fixes
// that branch layout. Noreturn and visible actual49B report_failure are inert.
extern "C" unsigned int __security_cookie;
extern "C" void __cdecl report_failure(void);
extern "C" void __fastcall __security_check_cookie(unsigned int cookie)
{
    if (cookie == __security_cookie)
        return;
    report_failure();
}
