// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHs-c-
// RVA 0x000ABC43..0x000ABC71: cdecl destination plus a packed 16-bit value.
// The original name and caller are unknown. The complete native body loads
// the low word of argument two and writes one dword through argument one.
//
// Packed-word semantics (including input bit 15):
//   spread = ((packed & 31) << 3) | (((packed >> 5) & 31) << 11)
//          | ((packed >> 10) << 19);
//   *destination = spread + ((spread >> 5) & 0x003f3f3f);
// This is not assumed to have a 15-bit-only input domain.
//
// Codegen blocker: scalar mask/narrowing expressions and byte/word unions
// do not retain the native high-byte shift and low-word splice in registers.
// See reverse/attempt_support/packed-color-000abc43-astra-s4.md.
// Only the packed-register core uses inline assembly. VC7.1 generates the
// EBX/EDI saves, restores, argument offsets and cdecl return normally.
void Rva000ABC43ExpandColor(unsigned int *destination, unsigned short packed)
{
    __asm {
        movzx eax, packed
        mov ebx, eax
        shr eax, 10
        shl ebx, 3
        shl eax, 19
        shl bh, 3
        mov ax, bx
        mov ebx, eax
        shr ebx, 5
        and ebx, 03f3f3fh
        add eax, ebx
        mov edi, destination
        mov [edi], eax
    }
}
