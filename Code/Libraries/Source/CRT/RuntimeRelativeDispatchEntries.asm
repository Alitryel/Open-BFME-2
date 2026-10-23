; Register-saving entries for the return-address-relative dispatch cores.
; There is no normal RET here: the core consumes this CALL's return address
; and jumps onward. The destination sees saved EAX, saved ECX, caller return.
; All flags and the other general-purpose registers are preserved.
; These are machine-entry contracts, not fabricated C++ prototypes; source
; provenance is retail disassembly plus independent register/stack tests.
; Evidence: reverse/attempt_support/runtime-dispatch-20261023/readme.md
.386
.model flat
EXTERN _RuntimeDispatchCore_00007AF3:PROC
EXTERN _RuntimeDispatchCore_00007C63:PROC
_TEXT SEGMENT
; The saved EAX/ECX words remain on the destination's incoming stack.
DISPATCH_ENTRY MACRO procName, targetCore
PUBLIC procName
procName PROC
    push ecx
    push eax
    call targetCore
procName ENDP
ENDM
DISPATCH_ENTRY _RuntimeDispatchEntry_00007ED9, _RuntimeDispatchCore_00007AF3
DISPATCH_ENTRY _RuntimeDispatchEntry_00008449, _RuntimeDispatchCore_00007C63
_TEXT ENDS
END
