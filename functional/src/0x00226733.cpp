// ?Rva00226733Fallback@@YAHHH@Z
// partial score=0.253 date=2026-10-17
// cl: /O1 /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP=
// Retail is a SecuROM-marked /Od body: the marker blocks (push eax / mov eax,imm x5 / pop eax)
// and the constant (xor eax,eax [inc eax] / je) branches decide nothing at run time: the
// (field+0x18) clear and the 0x226156 lookup are dead, the result is the first lookup.
int Rva00226140Get(void);
int BfmeLookup003EFEB2(int, int);
int __stdcall Rva0056DD95First(int, int);
int Rva00225A93Get(int, int, int, int, int);

int Rva00226733Fallback(int a, int b)
{
    int ctx = Rva00226140Get();
    int first = BfmeLookup003EFEB2(ctx, a);
    int second = BfmeLookup003EFEB2(ctx, b);
    int pick = Rva0056DD95First(first, second);
    Rva00225A93Get(5, 0xd, first, second, pick);
    return first;
}
