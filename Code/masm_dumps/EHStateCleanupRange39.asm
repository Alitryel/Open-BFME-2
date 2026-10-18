.386
.model flat
assume fs:nothing

; Address-named MSVC 7.1 EH cleanups and unwind state helpers from dump range 39.
; Retail boundaries and control flow are verified from bytes; the state mask,
; frame displacement, cleanup-object operation, and destructor target are
; taken from each body. Parent functions, field layouts and concrete cleanup identities remain
; unknown. VC7.1 C++ __try/__finally probes failed to reproduce this compiler
; helper shape, so these bodies use the permitted MASM path for SEH blockers.

EXTERN ??1AsciiString@@QAE@XZ:PROC
EXTERN ??1UnicodeString@@QAE@XZ:PROC
EXTERN ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ:PROC
EXTERN ?call@Rva002E3A80Holder@@QAEXXZ:PROC
EXTERN ??_M@YGXPAXIHP6EX0@Z@Z:PROC
EXTERN ?apply@Rva003F7BC5DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0057A243DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0002B221ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EE006DwordImmSetter@@QAEXXZ:PROC
EXTERN ?rva0053FCB3@Rva0053FCB3@@QAEXXZ:PROC
EXTERN ??1Rva003844D7@@QAE@XZ:PROC
EXTERN ??1Rva0038454E@@QAE@XZ:PROC
EXTERN ??1Rva00385333@@QAE@XZ:PROC
EXTERN ??1Gen_uw_00385371@@QAE@XZ:PROC
EXTERN ??1Rva005F8F96@@QAE@XZ:PROC
EXTERN ??1RefHolder@Rva005CCC07@@QAE@XZ:PROC
EXTERN ??1BfmePoolRef10@@QAE@XZ:PROC
EXTERN ??1BfmeStringTailRecord156@@QAE@XZ:PROC
EXTERN ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005F4179@@UAE@XZ:PROC
EXTERN ??1Rva005F918D@@QAE@XZ:PROC
EXTERN ??1Rva00087A93@@QAE@XZ:PROC
EXTERN ??1Rva005F4AD7@@QAE@XZ:PROC
EXTERN ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ:PROC
EXTERN ??1?$basic_string@DV?$char_traits@D@_STL@@V?$allocator@D@2@@_STL@@QAE@XZ:PROC
EXTERN ??1Q1ReceiverLocalSet@@QAE@XZ:PROC
EXTERN ??1BfmeWideResult@@QAE@XZ:PROC
EXTERN ??1EmissionVelocityInfo@FXParticleSystem@@UAE@XZ:PROC
EXTERN ??1EAStringC@@QAE@XZ:PROC
EXTERN ??1Rva004A9DF3Element@@QAE@XZ:PROC
EXTERN ??1SBServer@@QAE@XZ:PROC
EXTERN ?apply@Rva00574293DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0057428CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0005E186ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva000574265DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva002B2294DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00238D97DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0005D23FEDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005753E2DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00576456DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005CD1A9@@UAE@XZ:PROC
EXTERN ??1Rva00578C23@@UAE@XZ:PROC
EXTERN ??1Rva005D40A6@@UAE@XZ:PROC
EXTERN ?apply@Rva0057A235DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva00506B28DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva004444D2@@UAE@XZ:PROC
EXTERN ?apply@Rva0059EB3ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva004EDFF8DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005C6C7B@@UAE@XZ:PROC
EXTERN ?apply@Rva004EDFFFDwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005EB753@@UAE@XZ:PROC
EXTERN ?apply@Rva005CF843DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005CF84ADwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva0005E211FDwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005E3947DwordImmSetter@@QAEXXZ:PROC
EXTERN ?apply@Rva005E394EDwordImmSetter@@QAEXXZ:PROC
EXTERN ??1Rva005E12D1@@UAE@XZ:PROC
EXTERN ?apply@Rva004EE006DwordImmSetter@@QAEXXZ:PROC
EXTERN ??1SecondaryBase@@UAE@XZ:PROC

_TEXT SEGMENT
; Unwind@00b96d77 at RVA 0x00796D77; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva00796D77@@YAXXZ
?rva00796D77@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00796D77
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00796D77:
    ret
?rva00796D77@@YAXXZ ENDP

; Unwind@00b96e1e at RVA 0x00796E1E; 22-byte eh-vector-dtor passes [ebp-16]+64h with size 20 count 6 and raw dtor VA 0x00929318.
PUBLIC ?rva00796E1E@@YAXXZ
?rva00796E1E@@YAXXZ PROC
    push 00929318h
    push 6
    push 14h
    mov eax, DWORD PTR [ebp-16]
    add eax, 64h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00796E1E@@YAXXZ ENDP

; Unwind@00b97360 at RVA 0x00797360; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-16] + 0x1B594, element size 20, count 56 and destructor pointer 0x00931FCF.
PUBLIC ?rva00797360@@YAXXZ
?rva00797360@@YAXXZ PROC
    push 00931FCFh
    push 56
    push 20
    mov eax, DWORD PTR [ebp-16]
    add eax, 1B594h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00797360@@YAXXZ ENDP

; Unwind@00b973c8 at RVA 0x007973C8; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-16] + 0x1B594, element size 20, count 56 and destructor pointer 0x00931FCF.
PUBLIC ?rva007973C8@@YAXXZ
?rva007973C8@@YAXXZ PROC
    push 00931FCFh
    push 56
    push 20
    mov eax, DWORD PTR [ebp-16]
    add eax, 1B594h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007973C8@@YAXXZ ENDP

; Unwind@00b975a4 at RVA 0x007975A4; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007975A4@@YAXXZ
?rva007975A4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007975A4
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007975A4:
    ret
?rva007975A4@@YAXXZ ENDP

; Unwind@00b975d7 at RVA 0x007975D7; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007975D7@@YAXXZ
?rva007975D7@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007975D7
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007975D7:
    ret
?rva007975D7@@YAXXZ ENDP

; Unwind@00b97602 at RVA 0x00797602; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva00797602@@YAXXZ
?rva00797602@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_00797602
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00797602:
    ret
?rva00797602@@YAXXZ ENDP

; Unwind@00b9764f at RVA 0x0079764F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079764F@@YAXXZ
?rva0079764F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079764F
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079764F:
    ret
?rva0079764F@@YAXXZ ENDP

; Unwind@00b97694 at RVA 0x00797694; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva00797694@@YAXXZ
?rva00797694@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_00797694
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_00797694:
    ret
?rva00797694@@YAXXZ ENDP

; Unwind@00b976e1 at RVA 0x007976E1; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-32], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007976E1@@YAXXZ
?rva007976E1@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_007976E1
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007976E1:
    ret
?rva007976E1@@YAXXZ ENDP

; Unwind@00b9771c at RVA 0x0079771C; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-40], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079771C@@YAXXZ
?rva0079771C@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-40]
    and eax, 1
    jz NEAR PTR cleanup_done_0079771C
    and DWORD PTR [ebp-40], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079771C:
    ret
?rva0079771C@@YAXXZ ENDP

; Unwind@00b97783 at RVA 0x00797783; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva00797783@@YAXXZ
?rva00797783@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_00797783
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_00797783:
    ret
?rva00797783@@YAXXZ ENDP

; Unwind@00b97d25 at RVA 0x00797D25; 20-byte masked-add cleanup adds 4 to [ebp-16] and tail-jumps to the folded vector dtor at 0x0007FAB3.
PUBLIC ?rva00797D25@@YAXXZ
?rva00797D25@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
?rva00797D25@@YAXXZ ENDP

; Unwind@00b98c97 at RVA 0x00798C97; 24-byte interval ends at RET.
; Retail calls matched MSVC 7.1 vector destructor iterator 0x00629110 with object base [ebp-16] + 0x94, element size 12, count 6 and destructor pointer 0x0078356C.
PUBLIC ?rva00798C97@@YAXXZ
?rva00798C97@@YAXXZ PROC
    push 0078356Ch
    push 6
    push 12
    mov eax, DWORD PTR [ebp-16]
    add eax, 94h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva00798C97@@YAXXZ ENDP

; Unwind@00b995e6 at RVA 0x007995E6; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007995E6@@YAXXZ
?rva007995E6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007995E6
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007995E6:
    ret
?rva007995E6@@YAXXZ ENDP

; Unwind@00b9a389 at RVA 0x0079A389; 20-byte masked-add cleanup adds 8 to [ebp-16] and tail-jumps to the dword imm-setter at 0x003F7BC5.
PUBLIC ?rva0079A389@@YAXXZ
?rva0079A389@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F7BC5DwordImmSetter@@QAEXXZ
?rva0079A389@@YAXXZ ENDP

; Unwind@00b9a457 at RVA 0x0079A457; 20-byte masked-add cleanup adds 14h to [ebp-16] and tail-jumps to the dword imm-setter at 0x003F3F7C.
PUBLIC ?rva0079A457@@YAXXZ
?rva0079A457@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 14h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva0079A457@@YAXXZ ENDP

; Unwind@00b9a47d at RVA 0x0079A47D; 20-byte masked-add cleanup adds 14h to [ebp-16] and tail-jumps to the dword imm-setter at 0x002B221A.
PUBLIC ?rva0079A47D@@YAXXZ
?rva0079A47D@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 14h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0002B221ADwordImmSetter@@QAEXXZ
?rva0079A47D@@YAXXZ ENDP

; Unwind@00b9a4a3 at RVA 0x0079A4A3; 20-byte masked-add cleanup adds 14h to [ebp-16] and tail-jumps to the dword imm-setter at 0x004EE006.
PUBLIC ?rva0079A4A3@@YAXXZ
?rva0079A4A3@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 14h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EE006DwordImmSetter@@QAEXXZ
?rva0079A4A3@@YAXXZ ENDP

; Unwind@00b9a605 at RVA 0x0079A605; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-28] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A605@@YAXXZ
?rva0079A605@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A605
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-28]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A605:
    ret
?rva0079A605@@YAXXZ ENDP

; Unwind@00b9a61e at RVA 0x0079A61E; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A61E@@YAXXZ
?rva0079A61E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0079A61E
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-24]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A61E:
    ret
?rva0079A61E@@YAXXZ ENDP

; Unwind@00b9a637 at RVA 0x0079A637; 25-byte interval ends at RET.
; Retail tests and clears bit 2 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva0079A637@@YAXXZ
?rva0079A637@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 4
    jz NEAR PTR cleanup_done_0079A637
    and DWORD PTR [ebp-16], -5
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_0079A637:
    ret
?rva0079A637@@YAXXZ ENDP

; Unwind@00b9a786 at RVA 0x0079A786; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-52], then takes the cleanup object address at [ebp-44] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A786@@YAXXZ
?rva0079A786@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-52]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A786
    and DWORD PTR [ebp-52], -2
    lea ecx, [ebp-44]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A786:
    ret
?rva0079A786@@YAXXZ ENDP

; Unwind@00b9a968 at RVA 0x0079A968; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079A968@@YAXXZ
?rva0079A968@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079A968
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079A968:
    ret
?rva0079A968@@YAXXZ ENDP

; Unwind@00b9b018 at RVA 0x0079B018; 20-byte funclet adds 10h to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00574293.
PUBLIC ?rva0079B018@@YAXXZ
?rva0079B018@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 10h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00574293DwordImmSetter@@QAEXXZ
?rva0079B018@@YAXXZ ENDP

; Unwind@00b9b22a at RVA 0x0079B22A; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva0079B22A@@YAXXZ
?rva0079B22A@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva0079B22A@@YAXXZ ENDP

; Unwind@00b9b250 at RVA 0x0079B250; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva0079B250@@YAXXZ
?rva0079B250@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva0079B250@@YAXXZ ENDP

; Unwind@00b9b276 at RVA 0x0079B276; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva0079B276@@YAXXZ
?rva0079B276@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva0079B276@@YAXXZ ENDP

; Unwind@00b9b603 at RVA 0x0079B603; 20-byte funclet adds 4 to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005CD1A9.
PUBLIC ?rva0079B603@@YAXXZ
?rva0079B603@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005CD1A9@@UAE@XZ
?rva0079B603@@YAXXZ ENDP

; Unwind@00b9b747 at RVA 0x0079B747; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079B747@@YAXXZ
?rva0079B747@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079B747
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079B747:
    ret
?rva0079B747@@YAXXZ ENDP

; Unwind@00b9b88e at RVA 0x0079B88E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079B88E@@YAXXZ
?rva0079B88E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079B88E
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079B88E:
    ret
?rva0079B88E@@YAXXZ ENDP

; Unwind@00b9b8df at RVA 0x0079B8DF; 20-byte funclet adds 18h to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x00578C23.
PUBLIC ?rva0079B8DF@@YAXXZ
?rva0079B8DF@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 18h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva00578C23@@UAE@XZ
?rva0079B8DF@@YAXXZ ENDP

; Unwind@00b9bb1f at RVA 0x0079BB1F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079BB1F@@YAXXZ
?rva0079BB1F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BB1F
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079BB1F:
    ret
?rva0079BB1F@@YAXXZ ENDP

; Unwind@00b9bb52 at RVA 0x0079BB52; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079BB52@@YAXXZ
?rva0079BB52@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079BB52
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079BB52:
    ret
?rva0079BB52@@YAXXZ ENDP

; Unwind@00b9bcb9 at RVA 0x0079BCB9; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005D40A6.
PUBLIC ?rva0079BCB9@@YAXXZ
?rva0079BCB9@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005D40A6@@UAE@XZ
?rva0079BCB9@@YAXXZ ENDP

; Unwind@00b9c871 at RVA 0x0079C871; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079C871@@YAXXZ
?rva0079C871@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079C871
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079C871:
    ret
?rva0079C871@@YAXXZ ENDP

; Unwind@00b9ce78 at RVA 0x0079CE78; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079CE78@@YAXXZ
?rva0079CE78@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_0079CE78
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079CE78:
    ret
?rva0079CE78@@YAXXZ ENDP

; Unwind@00b9d210 at RVA 0x0079D210; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079D210@@YAXXZ
?rva0079D210@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D210
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D210:
    ret
?rva0079D210@@YAXXZ ENDP

; Unwind@00b9d277 at RVA 0x0079D277; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-24] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079D277@@YAXXZ
?rva0079D277@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D277
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-24]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D277:
    ret
?rva0079D277@@YAXXZ ENDP

; Unwind@00b9d290 at RVA 0x0079D290; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079D290@@YAXXZ
?rva0079D290@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 2
    jz NEAR PTR cleanup_done_0079D290
    and DWORD PTR [ebp-16], -3
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D290:
    ret
?rva0079D290@@YAXXZ ENDP

; Unwind@00b9d7e8 at RVA 0x0079D7E8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079D7E8@@YAXXZ
?rva0079D7E8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D7E8
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D7E8:
    ret
?rva0079D7E8@@YAXXZ ENDP

; Unwind@00b9d81b at RVA 0x0079D81B; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-32], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079D81B@@YAXXZ
?rva0079D81B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-32]
    and eax, 1
    jz NEAR PTR cleanup_done_0079D81B
    and DWORD PTR [ebp-32], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079D81B:
    ret
?rva0079D81B@@YAXXZ ENDP

; Unwind@00b9dc5b at RVA 0x0079DC5B; 20-byte funclet adds 60h to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x004444D2.
PUBLIC ?rva0079DC5B@@YAXXZ
?rva0079DC5B@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 60h
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva004444D2@@UAE@XZ
?rva0079DC5B@@YAXXZ ENDP

; Unwind@00b9e339 at RVA 0x0079E339; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp-40] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079E339@@YAXXZ
?rva0079E339@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079E339
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp-40]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079E339:
    ret
?rva0079E339@@YAXXZ ENDP

; Unwind@00b9e352 at RVA 0x0079E352; 25-byte interval ends at RET.
; Retail tests and clears bit 2 at [ebp-20], then takes the cleanup object address at [ebp-40] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva0079E352@@YAXXZ
?rva0079E352@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 4
    jz NEAR PTR cleanup_done_0079E352
    and DWORD PTR [ebp-20], -5
    lea ecx, [ebp-40]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_0079E352:
    ret
?rva0079E352@@YAXXZ ENDP

; Unwind@00b9f669 at RVA 0x0079F669; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva0079F669@@YAXXZ
?rva0079F669@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_0079F669
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_0079F669:
    ret
?rva0079F669@@YAXXZ ENDP

; Unwind@00ba09cd at RVA 0x007A09CD; 22-byte eh-vector-dtor passes [ebp-16]+20h with size 12 count 3 and raw dtor VA 0x009C39EB.
PUBLIC ?rva007A09CD@@YAXXZ
?rva007A09CD@@YAXXZ PROC
    push 009C39EBh
    push 3
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 20h
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A09CD@@YAXXZ ENDP

; Unwind@00ba0af4: masked-add cleanup adds 0Ch to [ebp-16] and tail-jumps to 0x004FAC80.
PUBLIC ?rva007A0AF4@@YAXXZ
?rva007A0AF4@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1SecondaryBase@@UAE@XZ
?rva007A0AF4@@YAXXZ ENDP

; Unwind@00ba0cb6 at RVA 0x007A0CB6; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A0CB6@@YAXXZ
?rva007A0CB6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0CB6
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A0CB6:
    ret
?rva007A0CB6@@YAXXZ ENDP

; Unwind@00ba0eae at RVA 0x007A0EAE; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A0EAE@@YAXXZ
?rva007A0EAE@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A0EAE
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A0EAE:
    ret
?rva007A0EAE@@YAXXZ ENDP

; Unwind@00ba0f4b at RVA 0x007A0F4B; 20-byte masked-add cleanup adds 4 to [ebp-16] and tail-jumps to the folded vector dtor at 0x0007FAB3.
PUBLIC ?rva007A0F4B@@YAXXZ
?rva007A0F4B@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 4
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1?$vector@HV?$allocator@H@_STL@@@_STL@@QAE@XZ
?rva007A0F4B@@YAXXZ ENDP

; Unwind@00ba1414 at RVA 0x007A1414; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 12 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A1414@@YAXXZ
?rva007A1414@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1414
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 12
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A1414:
    ret
?rva007A1414@@YAXXZ ENDP

; Unwind@00ba1641 at RVA 0x007A1641; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 16 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A1641@@YAXXZ
?rva007A1641@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1641
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 16
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A1641:
    ret
?rva007A1641@@YAXXZ ENDP

; Unwind@00ba1683 at RVA 0x007A1683; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva007A1683@@YAXXZ
?rva007A1683@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva007A1683@@YAXXZ ENDP

; Unwind@00ba1726 at RVA 0x007A1726; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva007A1726@@YAXXZ
?rva007A1726@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva007A1726@@YAXXZ ENDP

; Unwind@00ba1744 at RVA 0x007A1744; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then uses [ebp-20] + 16 as ECX and tail-jumps to matched Rva0004E84A4DwordImmSetter::apply at 0x004E84A4.
PUBLIC ?rva007A1744@@YAXXZ
?rva007A1744@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1744
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp-20]
    add ecx, 16
    jmp ?apply@Rva0004E84A4DwordImmSetter@@QAEXXZ
cleanup_done_007A1744:
    ret
?rva007A1744@@YAXXZ ENDP

; Unwind@00ba1af5 at RVA 0x007A1AF5; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to dtor at 0x005EB753.
PUBLIC ?rva007A1AF5@@YAXXZ
?rva007A1AF5@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005EB753@@UAE@XZ
?rva007A1AF5@@YAXXZ ENDP

; Unwind@00ba1b98 at RVA 0x007A1B98; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A1B98@@YAXXZ
?rva007A1B98@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1B98
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A1B98:
    ret
?rva007A1B98@@YAXXZ ENDP

; Unwind@00ba1ef2 at RVA 0x007A1EF2; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x003F3F7C.
PUBLIC ?rva007A1EF2@@YAXXZ
?rva007A1EF2@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva003F3F7CDwordImmSetter@@QAEXXZ
?rva007A1EF2@@YAXXZ ENDP

; Unwind@00ba1fcc at RVA 0x007A1FCC; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A1FCC@@YAXXZ
?rva007A1FCC@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A1FCC
    and DWORD PTR [ebp-28], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A1FCC:
    ret
?rva007A1FCC@@YAXXZ ENDP

; Unwind@00ba2001 at RVA 0x007A2001; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then takes the cleanup object address at [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A2001@@YAXXZ
?rva007A2001@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A2001
    and DWORD PTR [ebp-20], -2
    lea ecx, [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A2001:
    ret
?rva007A2001@@YAXXZ ENDP

; Unwind@00ba214b at RVA 0x007A214B; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A214B@@YAXXZ
?rva007A214B@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A214B
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A214B:
    ret
?rva007A214B@@YAXXZ ENDP

; Unwind@00ba2cf8 at RVA 0x007A2CF8; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A2CF8@@YAXXZ
?rva007A2CF8@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A2CF8
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A2CF8:
    ret
?rva007A2CF8@@YAXXZ ENDP

; Unwind@00ba34fe at RVA 0x007A34FE; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x005E211F.
PUBLIC ?rva007A34FE@@YAXXZ
?rva007A34FE@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva0005E211FDwordImmSetter@@QAEXXZ
?rva007A34FE@@YAXXZ ENDP

; Unwind@00ba3512 at RVA 0x007A3512; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x00238D97.
PUBLIC ?rva007A3512@@YAXXZ
?rva007A3512@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva00238D97DwordImmSetter@@QAEXXZ
?rva007A3512@@YAXXZ ENDP

; Unwind@00ba3648 at RVA 0x007A3648; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A3648@@YAXXZ
?rva007A3648@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3648
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A3648:
    ret
?rva007A3648@@YAXXZ ENDP

; Unwind@00ba3701 at RVA 0x007A3701; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A3701@@YAXXZ
?rva007A3701@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3701
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A3701:
    ret
?rva007A3701@@YAXXZ ENDP

; Unwind@00ba3ce6 at RVA 0x007A3CE6; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A3CE6@@YAXXZ
?rva007A3CE6@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A3CE6
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A3CE6:
    ret
?rva007A3CE6@@YAXXZ ENDP

; Unwind@00ba3ddc at RVA 0x007A3DDC; 20-byte funclet adds 8 to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x002B2294.
PUBLIC ?rva007A3DDC@@YAXXZ
?rva007A3DDC@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva002B2294DwordImmSetter@@QAEXXZ
?rva007A3DDC@@YAXXZ ENDP

; Unwind@00ba3df0 at RVA 0x007A3DF0; 20-byte funclet adds 0Ch to [ebp-10h] (zero stays zero) and tail-jumps to apply at 0x004EE006.
PUBLIC ?rva007A3DF0@@YAXXZ
?rva007A3DF0@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-10h]
    mov eax, DWORD PTR [ebp-10h]
    add eax, 0Ch
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ?apply@Rva004EE006DwordImmSetter@@QAEXXZ
?rva007A3DF0@@YAXXZ ENDP

; Unwind@00ba4374 at RVA 0x007A4374; 22-byte eh-vector-dtor passes [ebp-16]+1Ch with size 12 count 2 and raw dtor VA 0x009EB28A.
PUBLIC ?rva007A4374@@YAXXZ
?rva007A4374@@YAXXZ PROC
    push 009EB28Ah
    push 2
    push 0Ch
    mov eax, DWORD PTR [ebp-16]
    add eax, 1Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A4374@@YAXXZ ENDP

; Unwind@00ba4645 at RVA 0x007A4645; 19-byte eh-vector-dtor passes [ebp-72] with size 12 count 2 and raw dtor VA 0x009EC919.
PUBLIC ?rva007A4645@@YAXXZ
?rva007A4645@@YAXXZ PROC
    push 009EC919h
    push 2
    push 0Ch
    lea eax, DWORD PTR [ebp-72]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A4645@@YAXXZ ENDP

; Unwind@00ba4694 at RVA 0x007A4694; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A4694@@YAXXZ
?rva007A4694@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4694
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A4694:
    ret
?rva007A4694@@YAXXZ ENDP

; Unwind@00ba47d2 at RVA 0x007A47D2; 22-byte eh-vector-dtor passes [ebp-16]+2Ch with size 4 count 6 and raw dtor VA 0x009B804E.
PUBLIC ?rva007A47D2@@YAXXZ
?rva007A47D2@@YAXXZ PROC
    push 009B804Eh
    push 6
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 2Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A47D2@@YAXXZ ENDP

; Unwind@00ba483c at RVA 0x007A483C; 19-byte eh-vector-dtor passes [ebp-124] with size 12 count 4 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva007A483C@@YAXXZ
?rva007A483C@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 0Ch
    lea eax, DWORD PTR [ebp-124]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A483C@@YAXXZ ENDP

; Unwind@00ba4869 at RVA 0x007A4869; 19-byte eh-vector-dtor passes [ebp-128] with size 12 count 4 and raw dtor VA 0x004B3FD0.
PUBLIC ?rva007A4869@@YAXXZ
?rva007A4869@@YAXXZ PROC
    push 004B3FD0h
    push 4
    push 0Ch
    lea eax, DWORD PTR [ebp-128]
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A4869@@YAXXZ ENDP

; Unwind@00ba497e at RVA 0x007A497E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A497E@@YAXXZ
?rva007A497E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A497E
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A497E:
    ret
?rva007A497E@@YAXXZ ENDP

; Unwind@00ba4dc2 at RVA 0x007A4DC2; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A4DC2@@YAXXZ
?rva007A4DC2@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4DC2
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A4DC2:
    ret
?rva007A4DC2@@YAXXZ ENDP

; Unwind@00ba4edf at RVA 0x007A4EDF; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A4EDF@@YAXXZ
?rva007A4EDF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A4EDF
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A4EDF:
    ret
?rva007A4EDF@@YAXXZ ENDP

; Unwind@00ba5241 at RVA 0x007A5241; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F4AD7 destructor at 0x005F4AD7.
PUBLIC ?rva007A5241@@YAXXZ
?rva007A5241@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A5241
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F4AD7@@QAE@XZ
cleanup_done_007A5241:
    ret
?rva007A5241@@YAXXZ ENDP

; Unwind@00ba53cd at RVA 0x007A53CD; 20-byte masked-add cleanup adds 8 to [ebp-16] and tail-jumps to the virtual dtor at 0x005E12D1.
PUBLIC ?rva007A53CD@@YAXXZ
?rva007A53CD@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005E12D1@@UAE@XZ
?rva007A53CD@@YAXXZ ENDP

; Unwind@00ba5449 at RVA 0x007A5449; 20-byte masked-add cleanup adds 8 to [ebp-16] and tail-jumps to the virtual dtor at 0x005E12D1.
PUBLIC ?rva007A5449@@YAXXZ
?rva007A5449@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005E12D1@@UAE@XZ
?rva007A5449@@YAXXZ ENDP

; Unwind@00ba54c5 at RVA 0x007A54C5; 20-byte masked-add cleanup adds 8 to [ebp-16] and tail-jumps to the virtual dtor at 0x005E12D1.
PUBLIC ?rva007A54C5@@YAXXZ
?rva007A54C5@@YAXXZ PROC
    mov ecx, DWORD PTR [ebp-16]
    mov eax, DWORD PTR [ebp-16]
    add eax, 8
    neg ecx
    sbb ecx, ecx
    and ecx, eax
    jmp ??1Rva005E12D1@@UAE@XZ
?rva007A54C5@@YAXXZ ENDP

; Unwind@00ba559a at RVA 0x007A559A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A559A@@YAXXZ
?rva007A559A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A559A
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A559A:
    ret
?rva007A559A@@YAXXZ ENDP

; Unwind@00ba569e at RVA 0x007A569E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A569E@@YAXXZ
?rva007A569E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A569E
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A569E:
    ret
?rva007A569E@@YAXXZ ENDP

; Unwind@00ba56d9 at RVA 0x007A56D9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-28], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A56D9@@YAXXZ
?rva007A56D9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-28]
    and eax, 1
    jz NEAR PTR cleanup_done_007A56D9
    and DWORD PTR [ebp-28], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A56D9:
    ret
?rva007A56D9@@YAXXZ ENDP

; Unwind@00ba57d0 at RVA 0x007A57D0; 22-byte eh-vector-dtor passes [ebp-16]+3Ch with size 4 count 7 and raw dtor VA 0x009F74BA.
PUBLIC ?rva007A57D0@@YAXXZ
?rva007A57D0@@YAXXZ PROC
    push 009F74BAh
    push 7
    push 4
    mov eax, DWORD PTR [ebp-16]
    add eax, 3Ch
    push eax
    call ??_M@YGXPAXIHP6EX0@Z@Z
    ret
?rva007A57D0@@YAXXZ ENDP

; Unwind@00ba5b9e at RVA 0x007A5B9E; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A5B9E@@YAXXZ
?rva007A5B9E@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A5B9E
    and DWORD PTR [ebp-16], -2
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A5B9E:
    ret
?rva007A5B9E@@YAXXZ ENDP

; Unwind@00ba5bc9 at RVA 0x007A5BC9; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007A5BC9@@YAXXZ
?rva007A5BC9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A5BC9
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007A5BC9:
    ret
?rva007A5BC9@@YAXXZ ENDP

; Unwind@00ba621f at RVA 0x007A621F; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-24], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A621F@@YAXXZ
?rva007A621F@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 1
    jz NEAR PTR cleanup_done_007A621F
    and DWORD PTR [ebp-24], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A621F:
    ret
?rva007A621F@@YAXXZ ENDP

; Unwind@00ba6486 at RVA 0x007A6486; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A6486@@YAXXZ
?rva007A6486@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6486
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A6486:
    ret
?rva007A6486@@YAXXZ ENDP

; Unwind@00ba65b4 at RVA 0x007A65B4; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to UnicodeString at 0x005B804E.
PUBLIC ?rva007A65B4@@YAXXZ
?rva007A65B4@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A65B4
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1UnicodeString@@QAE@XZ
cleanup_done_007A65B4:
    ret
?rva007A65B4@@YAXXZ ENDP

; Unwind@00ba67ea at RVA 0x007A67EA; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched Rva005F8F96 destructor at 0x005F8F96.
PUBLIC ?rva007A67EA@@YAXXZ
?rva007A67EA@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A67EA
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1Rva005F8F96@@QAE@XZ
cleanup_done_007A67EA:
    ret
?rva007A67EA@@YAXXZ ENDP

; Unwind@00ba6a40 at RVA 0x007A6A40; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then uses [ebp-16] + 100 as ECX and tail-jumps to matched STLport narrow basic_ios destructor at 0x00013420.
PUBLIC ?rva007A6A40@@YAXXZ
?rva007A6A40@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6A40
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp-16]
    add ecx, 100
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_007A6A40:
    ret
?rva007A6A40@@YAXXZ ENDP

; Unwind@00ba6a80 at RVA 0x007A6A80; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then uses [ebp-16] + 104 as ECX and tail-jumps to matched STLport narrow basic_ios destructor at 0x00013420.
PUBLIC ?rva007A6A80@@YAXXZ
?rva007A6A80@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6A80
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp-16]
    add ecx, 104
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_007A6A80:
    ret
?rva007A6A80@@YAXXZ ENDP

; Unwind@00ba6ac0 at RVA 0x007A6AC0; 28-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-20], then uses [ebp-16] + 108 as ECX and tail-jumps to matched STLport narrow basic_ios destructor at 0x00013420.
PUBLIC ?rva007A6AC0@@YAXXZ
?rva007A6AC0@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-20]
    and eax, 1
    jz NEAR PTR cleanup_done_007A6AC0
    and DWORD PTR [ebp-20], -2
    mov ecx, DWORD PTR [ebp-16]
    add ecx, 108
    jmp ??1?$basic_ios@DV?$char_traits@D@_STL@@@_STL@@UAE@XZ
cleanup_done_007A6AC0:
    ret
?rva007A6AC0@@YAXXZ ENDP

; Unwind@00ba8720 at RVA 0x007A8720; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+4] and tail-jumps to matched EAStringC destructor at 0x006D3010.
PUBLIC ?rva007A8720@@YAXXZ
?rva007A8720@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007A8720
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+4]
    jmp ??1EAStringC@@QAE@XZ
cleanup_done_007A8720:
    ret
?rva007A8720@@YAXXZ ENDP

; Unwind@00bab0e9 at RVA 0x007AB0E9; 25-byte interval ends at RET.
; Retail tests and clears bit 1 at [ebp-24], then takes the cleanup object address at [ebp-20] and tail-jumps to AsciiString at 0x0048BA39.
PUBLIC ?rva007AB0E9@@YAXXZ
?rva007AB0E9@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-24]
    and eax, 2
    jz NEAR PTR cleanup_done_007AB0E9
    and DWORD PTR [ebp-24], -3
    lea ecx, [ebp-20]
    jmp ??1AsciiString@@QAE@XZ
cleanup_done_007AB0E9:
    ret
?rva007AB0E9@@YAXXZ ENDP

; Unwind@00bab2df at RVA 0x007AB2DF; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007AB2DF@@YAXXZ
?rva007AB2DF@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007AB2DF
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007AB2DF:
    ret
?rva007AB2DF@@YAXXZ ENDP

; Unwind@00bab31a at RVA 0x007AB31A; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007AB31A@@YAXXZ
?rva007AB31A@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007AB31A
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007AB31A:
    ret
?rva007AB31A@@YAXXZ ENDP

; Unwind@00bab345 at RVA 0x007AB345; 25-byte interval ends at RET.
; Retail tests and clears bit 0 at [ebp-16], then loads the cleanup pointer from [ebp+8] and tail-jumps to matched BfmeStringTailRecord156 destructor at 0x0010F149.
PUBLIC ?rva007AB345@@YAXXZ
?rva007AB345@@YAXXZ PROC
    mov eax, DWORD PTR [ebp-16]
    and eax, 1
    jz NEAR PTR cleanup_done_007AB345
    and DWORD PTR [ebp-16], -2
    mov ecx, DWORD PTR [ebp+8]
    jmp ??1BfmeStringTailRecord156@@QAE@XZ
cleanup_done_007AB345:
    ret
?rva007AB345@@YAXXZ ENDP

_TEXT ENDS
END
