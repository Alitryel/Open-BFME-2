// ?Rva004347D4Fallback@@YAHHH@Z
// partial score=0.276 date=2026-10-17
// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP= /D_BFME_RETAIL_TREE_INSERT_LAYOUT
// Retail is a SecuROM-marked /Od body: the marker blocks (push eax / mov eax,imm x5 / pop eax)
// and the constant (xor eax,eax [inc eax] / je) branches decide nothing at run time: the
// (field+0x18) clear and the 0x226156 lookup are dead, the result is the first lookup.
int Rva00434091Get(void);
int BfmeLookup003EFEB2(int, int);
int Rva00225A93Get(int, int, int, int, int);
class Rva004340A4 { public: short rva004340A4(short, int); };

int Rva004347D4Fallback(int a, int b)
{
    int ctx = Rva00434091Get();
    int first = BfmeLookup003EFEB2(ctx, a);
    int second = BfmeLookup003EFEB2(ctx, b);
    Rva004340A4 cmp = Rva004340A4();
    int sum = cmp.rva004340A4((short)first, second);
    Rva00225A93Get(3, 0xd, first, second, sum);
    return first;
}
