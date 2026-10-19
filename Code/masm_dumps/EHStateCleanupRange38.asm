.386
.model flat
assume fs:nothing

; Address-derived EH cleanup funclets from dump range 38.
; Parent ownership and concrete field identity remain unknown. These bodies are
; compiler-generated MSVC 7.1 EH helpers; neighboring Range39 C++ probes failed
; to reproduce this standalone frame code, so MASM preserves the SEH behavior.

EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ??1Rva004444D2@@UAE@XZ:PROC
EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1UnicodeString@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1Rva0038465B@@QAE@XZ:PROC
EXTERN ??1Rva003ED94FDtor@@QAE@XZ:PROC
EXTERN ??1Rva002606AFDtor@@QAE@XZ:PROC
EXTERN ?call@Rva002E3A80Holder@@QAEXXZ:PROC
EXTERN ??1Rva005F8F96@@QAE@XZ:PROC
EXTERN ??1Rva004F6093Holder@@QAE@XZ:PROC
EXTERN ??1Rva00410688@@QAE@XZ:PROC
EXTERN ??1Rva0045EF90Object@@UAE@XZ:PROC
EXTERN ??1Rva004104C9@@QAE@XZ:PROC
EXTERN ??1CameraMarker@@QAE@XZ:PROC
EXTERN ??1Rva005A9562@@QAE@XZ:PROC
EXTERN ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:PROC
EXTERN ?apply@Rva00049C38ADwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva002390CB@@QAE@XZ:PROC

EXTERN ??1Rva004E6A37@@QAE@XZ:PROC
EXTERN ??1Rva0055B0CC@@UAE@XZ:PROC
EXTERN ??1?$map@VAsciiString@@V1@U?$less@VAsciiString@@@_STL@@V?$allocator@U?$pair@$$CBVAsciiString@@V1@@_STL@@@3@@_STL@@QAE@XZ:PROC
EXTERN ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00238D97DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00506B28DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva00574A8A@@UAE@XZ:PROC
EXTERN ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ:PROC
EXTERN ??1UpdateModule@@UAE@XZ:PROC
EXTERN ??1Rva005248D0@@UAE@XZ:PROC
EXTERN ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ:PROC
EXTERN ??1Gen_uw_0049b47c@@QAE@XZ:PROC
EXTERN ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ:PROC
EXTERN ?clear@Rva003B4071@@QAEXXZ:PROC
EXTERN ?apply@Rva002B2294DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0002B221ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva002B228DDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EE006DwordImmSetter@@QAEXXZ:PROC

_TEXT SEGMENT
; Unwind@00b7c75e at RVA 0x0077C75E; 22-byte body ends at RET.
PUBLIC ?rva0077c75e@@YAXXZ
?rva0077c75e@@YAXXZ PROC
    push 0088BA39h
    push 5
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 7Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077c75e@@YAXXZ ENDP

; Unwind@00b7c8c4 at RVA 0x0077C8C4; 24-byte body ends at RET.
; Target bytes pass the base at [ebp-16]+0x3c4 to eh-vector-dtor with stride
; 20, count 2, and raw destructor VA 0x0046C94B.
PUBLIC ?rva0077c8c4@@YAXXZ
?rva0077c8c4@@YAXXZ PROC
    push 0046C94Bh
    push 2
    push 14h
    mov eax, DWORD PTR [ebp-16]
    add eax, 3C4h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077c8c4@@YAXXZ ENDP

; Unwind@00b7e855 at RVA 0x0077E855; 20-byte masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to the EmissionVelocityInfo dtor at 0x0049B47C.
PUBLIC ?rva0077e855@@YAXXZ
?rva0077e855@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva0077e855@@YAXXZ ENDP

; Unwind@00b7ed0d at RVA 0x0077ED0D; 25-byte state-bit cleanup ends at RET.
; Retail clears bit 0 at [ebp-20] and conditionally tail-jumps through [ebp+8].
PUBLIC ?rva0077ed0d@@YAXXZ
?rva0077ed0d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0077ed0d
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0077ed0d:
    ret
?rva0077ed0d@@YAXXZ ENDP

; Unwind@00b7f57f at RVA 0x0077F57F; 27-byte array cleanup ends at RET.
; Target passes [ebp-16]+0xdc to eh-vector-dtor with size 0x1e0 count 8 and
; raw destructor VA 0x00782398.
PUBLIC ?rva0077f57f@@YAXXZ
?rva0077f57f@@YAXXZ PROC
    push 00782398h
    push 8
    push 1E0h
    mov eax, DWORD PTR [ebp-16]
    add eax, 0DCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077f57f@@YAXXZ ENDP

; Unwind@00b7f708 at RVA 0x0077F708; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0x94 to eh-vector-dtor with size 12 count 6 and
; raw destructor VA 0x0078356C.
PUBLIC ?rva0077f708@@YAXXZ
?rva0077f708@@YAXXZ PROC
    push 0078356Ch
    push 6
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 94h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0077f708@@YAXXZ ENDP

; Unwind@00b8059a at RVA 0x0078059A; 24-byte array cleanup ends at RET.
; Same target type and array parameters as 0x7804A6; frame slot is [ebp-16].
PUBLIC ?rva0078059a@@YAXXZ
?rva0078059a@@YAXXZ PROC
    push 00542D70h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 0D0h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078059a@@YAXXZ ENDP

; Unwind@00b812ad at RVA 0x007812AD; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0x1fc with size 12 count 20 and raw dtor VA 0x00757CD9.
PUBLIC ?rva007812ad@@YAXXZ
?rva007812ad@@YAXXZ PROC
    push 00757CD9h
    push 14h
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 1FCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007812ad@@YAXXZ ENDP

; Unwind@00b81431 at RVA 0x00781431; 22-byte eh-vector-dtor passes [ebp-16]+4 with size 24 count 7 and raw dtor VA 0x0079EAB7.
PUBLIC ?rva00781431@@YAXXZ
?rva00781431@@YAXXZ PROC
    push 0079EAB7h
    push 7
    push 18h
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00781431@@YAXXZ ENDP

; Unwind@00b817fb at RVA 0x007817FB; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0x118 with size 4 count 32 and raw dtor VA 0x0088BA39.
PUBLIC ?rva007817fb@@YAXXZ
?rva007817fb@@YAXXZ PROC
    push 0088BA39h
    push 20h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 118h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007817fb@@YAXXZ ENDP

; Unwind@00b818a6 at RVA 0x007818A6; 24-byte array cleanup ends at RET.
; Target passes [ebp-16]+0xac with size 4 count 32 and raw dtor VA 0x0088BA39.
PUBLIC ?rva007818a6@@YAXXZ
?rva007818a6@@YAXXZ PROC
    push 0088BA39h
    push 20h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 0ACh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007818a6@@YAXXZ ENDP

; Unwind@00b8190d at RVA 0x0078190D; 24-byte array cleanup ends at RET.
; Same target type and array parameters as 0x7818A6; frame slot is [ebp-20].
PUBLIC ?rva0078190d@@YAXXZ
?rva0078190d@@YAXXZ PROC
    push 0088BA39h
    push 20h
    push 4
    mov eax, DWORD PTR [ebp-20]
    add eax, 0ACh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078190d@@YAXXZ ENDP

PUBLIC ?rva007819ce@@YAXXZ
?rva007819ce@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007819ce@@YAXXZ ENDP

; Unwind@00b82404 at RVA 0x00782404; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-36] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00782404@@YAXXZ
?rva00782404@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-36]
    and eax, 1
    jz NEAR PTR cleanup_done_00782404
    and DWORD PTR [ebp-36], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00782404:
    ret
?rva00782404@@YAXXZ ENDP

PUBLIC ?rva0078258c@@YAXXZ
?rva0078258c@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 04h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?clear@Rva003B4071@@QAEXXZ
?rva0078258c@@YAXXZ ENDP

; Unwind@00b836e8 at RVA 0x007836E8; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007836e8@@YAXXZ
?rva007836e8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007836e8
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007836e8:
    ret
?rva007836e8@@YAXXZ ENDP

; Unwind@00b8398a at RVA 0x0078398A; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to the rowed UnicodeString thunk.
PUBLIC ?rva0078398a@@YAXXZ
?rva0078398a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078398a
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_0078398a:
    ret
?rva0078398a@@YAXXZ ENDP

; Unwind@00b839a3 at RVA 0x007839A3; 25-byte state-bit cleanup ends at RET.
; Target clears bit 1 at [ebp-16] and tail-jumps through [ebp+8] to the rowed UnicodeString thunk.
PUBLIC ?rva007839a3@@YAXXZ
?rva007839a3@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_007839a3
    and DWORD PTR [ebp-16], -3
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva002606AFDtor@@QAE@XZ
cleanup_done_007839a3:
    ret
?rva007839a3@@YAXXZ ENDP

PUBLIC ?rva00784e61@@YAXXZ
?rva00784e61@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00784e61@@YAXXZ ENDP

; Unwind@00b85033 at RVA 0x00785033; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-80] and tail-jumps through [ebp+8] to the rowed dtor.
PUBLIC ?rva00785033@@YAXXZ
?rva00785033@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-80]
    and eax, 1
    jz NEAR PTR cleanup_done_00785033
    and DWORD PTR [ebp-80], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_00785033:
    ret
?rva00785033@@YAXXZ ENDP

; Unwind@00b850cc at RVA 0x007850CC; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to the rowed holder call.
PUBLIC ?rva007850cc@@YAXXZ
?rva007850cc@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007850cc
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ?call@Rva002E3A80Holder@@QAEXXZ
cleanup_done_007850cc:
    ret
?rva007850cc@@YAXXZ ENDP

; Unwind@00b8539a at RVA 0x0078539A; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x80 to the rowed iterator with element size 12 count 15 and AsciiString dtor VA 0x0088BA39.
PUBLIC ?rva0078539a@@YAXXZ
?rva0078539a@@YAXXZ PROC
    push 0088BA39h
    push 0Fh
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 80h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078539a@@YAXXZ ENDP

PUBLIC ?rva0078582c@@YAXXZ
?rva0078582c@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 04h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
?rva0078582c@@YAXXZ ENDP

; Unwind@00b85e8a at RVA 0x00785E8A; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00785e8a@@YAXXZ
?rva00785e8a@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00785e8a
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00785e8a:
    ret
?rva00785e8a@@YAXXZ ENDP

; Unwind@00b860ce: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x0049B47C.
PUBLIC ?rva007860ce@@YAXXZ
?rva007860ce@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva007860ce@@YAXXZ ENDP

PUBLIC ?rva00786f3c@@YAXXZ
?rva00786f3c@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Gen_uw_0049b47c@@QAE@XZ
?rva00786f3c@@YAXXZ ENDP

; Unwind@00b8787d at RVA 0x0078787D; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps with [ebp-20] to AsciiString dtor.
PUBLIC ?rva0078787d@@YAXXZ
?rva0078787d@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0078787d
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0078787d:
    ret
?rva0078787d@@YAXXZ ENDP

; Unwind@00b88604 at RVA 0x00788604; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00788604@@YAXXZ
?rva00788604@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00788604
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00788604:
    ret
?rva00788604@@YAXXZ ENDP

; Unwind@00b88cba at RVA 0x00788CBA; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x2f4 to the rowed iterator with element size 4 count 8 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva00788cba@@YAXXZ
?rva00788cba@@YAXXZ PROC
    push 004B3FD0h
    push 8
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 2F4h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00788cba@@YAXXZ ENDP

; Unwind@00b88e8a at RVA 0x00788E8A; 22-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00788e8a@@YAXXZ
?rva00788e8a@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-20]
    mov eax, DWORD PTR [ebp-20]
    add eax, 27Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva004444D2@@UAE@XZ
?rva00788e8a@@YAXXZ ENDP

; Unwind@00b89325 at RVA 0x00789325; 27-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0xdc to the rowed iterator with element size 0x1d0 count 8 and raw dtor VA 0x00847B0E.
PUBLIC ?rva00789325@@YAXXZ
?rva00789325@@YAXXZ PROC
    push 00847B0Eh
    push 8
    push 1D0h
    mov eax, DWORD PTR [ebp-16]
    add eax, 0DCh
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00789325@@YAXXZ ENDP

; Unwind@00b8937e at RVA 0x0078937E; 25-byte vector cleanup ends at RET.
; Target passes [ebp-0xe40] to the rowed iterator with element size 0x1ac count 8 and raw dtor VA 0x006294FD.
PUBLIC ?rva0078937e@@YAXXZ
?rva0078937e@@YAXXZ PROC
    push 006294FDh
    push 8
    push 1ACh
    lea eax, DWORD PTR [ebp-0E40h]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078937e@@YAXXZ ENDP

; Unwind@00b89417 at RVA 0x00789417; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x40e0c to the rowed iterator with element size 12 count 8 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva00789417@@YAXXZ
?rva00789417@@YAXXZ PROC
    push 004B3FD0h
    push 8
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 40E0Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00789417@@YAXXZ ENDP

; Unwind@00b89799 at RVA 0x00789799; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-20] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789799@@YAXXZ
?rva00789799@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00789799
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789799:
    ret
?rva00789799@@YAXXZ ENDP

; Unwind@00b897c4 at RVA 0x007897C4; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-16] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva007897c4@@YAXXZ
?rva007897c4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007897c4
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007897c4:
    ret
?rva007897c4@@YAXXZ ENDP

; Unwind@00b89807 at RVA 0x00789807; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-28] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789807@@YAXXZ
?rva00789807@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00789807
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789807:
    ret
?rva00789807@@YAXXZ ENDP

; Unwind@00b89842 at RVA 0x00789842; 25-byte state-bit cleanup ends at RET.
; Target clears bit 0 at [ebp-24] and tail-jumps through [ebp+8] to AsciiString dtor.
PUBLIC ?rva00789842@@YAXXZ
?rva00789842@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_00789842
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00789842:
    ret
?rva00789842@@YAXXZ ENDP

; Unwind@00b8a463 at RVA 0x0078A463; 19-byte eh-vector-dtor lea target passes [ebp-80] with size 12 count 4 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a463@@YAXXZ
?rva0078a463@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 0Ch
    lea eax, [ebp-80]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a463@@YAXXZ ENDP

; Unwind@00b8a669 at RVA 0x0078A669; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x88 to the rowed iterator with element size 12 count 4 and raw dtor VA 0x0047FAB3.
PUBLIC ?rva0078a669@@YAXXZ
?rva0078a669@@YAXXZ PROC
    push 0047FAB3h
    push 4
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 88h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a669@@YAXXZ ENDP

; Unwind@00b8a681 at RVA 0x0078A681; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0xb8 to the rowed iterator with element size 12 count 4 and raw dtor VA 0x0047FAB3.
PUBLIC ?rva0078a681@@YAXXZ
?rva0078a681@@YAXXZ PROC
    push 0047FAB3h
    push 4
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 0B8h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a681@@YAXXZ ENDP

; Unwind@00b8a813 at RVA 0x0078A813; 22-byte eh-vector-dtor lea target passes [ebp-216] with size 12 count 16 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a813@@YAXXZ
?rva0078a813@@YAXXZ PROC
    push 004B3FD0h
    push 10h
    push 0Ch
    lea eax, [ebp-216]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a813@@YAXXZ ENDP

; Unwind@00b8a84b at RVA 0x0078A84B; 22-byte eh-vector-dtor lea target passes [ebp-260] with size 12 count 16 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078a84b@@YAXXZ
?rva0078a84b@@YAXXZ PROC
    push 004B3FD0h
    push 10h
    push 0Ch
    lea eax, [ebp-260]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078a84b@@YAXXZ ENDP

; Unwind@00b8b58e at RVA 0x0078B58E; 24-byte vector cleanup ends at RET.
; Target passes [ebp-16]+0x338 to the rowed iterator with element size 16 count 60 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva0078b58e@@YAXXZ
?rva0078b58e@@YAXXZ PROC
    push 004B3FD0h
    push 3Ch
    push 10h
    mov eax, DWORD PTR [ebp-16]
    add eax, 338h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078b58e@@YAXXZ ENDP

; Unwind@00b8d24f at RVA 0x0078D24F; 22-byte eh-vector-dtor target passes [ebp-16]+0x44 with size 4 count 16 and raw dtor VA 0x0050F149.
PUBLIC ?rva0078d24f@@YAXXZ
?rva0078d24f@@YAXXZ PROC
    push 0050F149h
    push 10h
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 44h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva0078d24f@@YAXXZ ENDP

; Unwind@00b8d398 at RVA 0x0078D398; 20-byte masked-add cleanup adds 4 to [ebp-16] and tail-jumps to the matched dtor at 0x0024A797.
PUBLIC ?rva0078d398@@YAXXZ
?rva0078d398@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1UpdateModule@@UAE@XZ
?rva0078d398@@YAXXZ ENDP

; Unwind@00b90c05 at RVA 0x00790C05; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00790c05@@YAXXZ
?rva00790c05@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00790c05
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00790c05:
    ret
?rva00790c05@@YAXXZ ENDP

; Unwind@00b910c8 at RVA 0x007910C8; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-24]; loads ECX with MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007910c8@@YAXXZ
?rva007910c8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007910c8
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007910c8:
    ret
?rva007910c8@@YAXXZ ENDP

; Unwind@00b94872 at RVA 0x00794872; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva00794872@@YAXXZ
?rva00794872@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00794872
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00794872:
    ret
?rva00794872@@YAXXZ ENDP

; Unwind@00b949a2 at RVA 0x007949A2; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-24]; uses LEA from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007949a2@@YAXXZ
?rva007949a2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007949a2
    and DWORD PTR [ebp-24], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007949a2:
    ret
?rva007949a2@@YAXXZ ENDP

; Unwind@00b949c5 at RVA 0x007949C5; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 1 at [ebp-24]; uses LEA from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x0048BA39; parent identity/layout remain unproven.
PUBLIC ?rva007949c5@@YAXXZ
?rva007949c5@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 2
    jz NEAR PTR cleanup_done_007949c5
    and DWORD PTR [ebp-24], -3
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007949c5:
    ret
?rva007949c5@@YAXXZ ENDP

PUBLIC ?rva00794e32@@YAXXZ
?rva00794e32@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 218h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005248D0@@UAE@XZ
?rva00794e32@@YAXXZ ENDP

; Unwind@00b9504c at RVA 0x0079504C; 25-byte state-bit cleanup ends at RET.
; Retail tests and clears bit 0 at [ebp-20]; uses MOV from [ebp+8] only when set.
; The tail-jump target is a matched function at RVA 0x005B804E; parent identity/layout remain unproven.
PUBLIC ?rva0079504c@@YAXXZ
?rva0079504c@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079504c
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079504c:
    ret
?rva0079504c@@YAXXZ ENDP

; Unwind@00b962c3 at RVA 0x007962C3; 22-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva007962c3@@YAXXZ
?rva007962c3@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-20]
    mov eax, DWORD PTR [ebp-20]
    add eax, 27Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva004444D2@@UAE@XZ
?rva007962c3@@YAXXZ ENDP

; Unwind@00b81953 at RVA 0x00781953; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00781953@@YAXXZ
?rva00781953@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva0055B0CC@@UAE@XZ
?rva00781953@@YAXXZ ENDP

; Unwind@00b873e9 at RVA 0x007873E9; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva007873e9@@YAXXZ
?rva007873e9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ
?rva007873e9@@YAXXZ ENDP

; Unwind@00b8768e at RVA 0x0078768E; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva0078768e@@YAXXZ
?rva0078768e@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva00574A8A@@UAE@XZ
?rva0078768e@@YAXXZ ENDP

; Unwind@00b93655 at RVA 0x00793655; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00793655@@YAXXZ
?rva00793655@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ
?rva00793655@@YAXXZ ENDP

; Unwind@00b93669 at RVA 0x00793669; 20-byte masked-add funclet tail-jumps to apply.
PUBLIC ?rva00793669@@YAXXZ
?rva00793669@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ
?rva00793669@@YAXXZ ENDP

; Unwind@00b94a43 at RVA 0x00794A43; 20-byte masked-add funclet tail-jumps to dtor.
PUBLIC ?rva00794a43@@YAXXZ
?rva00794a43@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 14h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005248D0@@UAE@XZ
?rva00794a43@@YAXXZ ENDP

_TEXT ENDS
END
