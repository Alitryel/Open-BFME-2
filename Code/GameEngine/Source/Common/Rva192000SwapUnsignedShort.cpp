void rva_192000_swap_unsigned_short(unsigned short *left, unsigned short *right)
{
    unsigned short temporary = *left;
    *left = *right;
    *right = temporary;
}

// ?rva_53229d_copy_unsigned_short@@YAXPAG0@Z @ 0x0053229D 27B
// Null-guarded 4-byte copy as two word moves. Unblocks 0x005322B8,
// 0x005322DE, 0x005334A4 (callers push two pointers, callee plain ret).
void rva_53229d_copy_unsigned_short(unsigned short *dst, unsigned short *src)
{
    if (dst) {
        dst[0] = src[0];
        dst[1] = src[1];
    }
}
