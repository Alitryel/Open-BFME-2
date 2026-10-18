.386
.model flat

; Visual C++ 7.1 secchk.obj, complete 14-byte compiler entry.
; The VS2003 ATL atlmincrt/atlsecchk.c reference explicitly uses x86 asm
; to preserve live return registers. This is a proven entry-ABI blocker,
; stays assembly, and receives zero C++ credit. The reporting helper is C++.
; ___security_cookie is the real external CRT datum originally owned by seccook.obj;
; this unit creates no duplicate datum or address-named substitute.
EXTERN ___security_cookie:DWORD
EXTERN _report_failure:PROC

_TEXT SEGMENT
PUBLIC @__security_check_cookie@4
@__security_check_cookie@4 PROC
    cmp ecx,DWORD PTR [___security_cookie]
    jne cookie_failure
    ret
cookie_failure:
    jmp _report_failure
@__security_check_cookie@4 ENDP
_TEXT ENDS
END
