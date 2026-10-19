// ?Rva002264B3Fallback@@YAHHH@Z
// partial score=0.203 date=2026-10-17
// cl: /Od /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP=
// Retail is a SecuROM-marked /Od body: the marker blocks (push eax / mov eax,imm x5 / pop eax)
// and the constant-false (xor eax,eax / je) branches decide nothing at run time.
// The less predicate's whole EAX is passed on (retail stores eax, no movzx).
int Rva00226140Get(void);
int BfmeLookup003EFEB2(int, int);
bool __stdcall Rva00226146Less(int, int);
int Rva00225A93Get(int, int, int, int, int);
int BfmeLookup00226156(int, int);

int Rva002264B3Fallback(int a, int b)
{
    int ctx = Rva00226140Get();
    int first = BfmeLookup003EFEB2(ctx, a);
    int second = BfmeLookup003EFEB2(ctx, b);
    int less = ((int (__stdcall *)(int, int))&Rva00226146Less)(first, second);
    int result = Rva00225A93Get(5, 0xe, first, second, less);
    return BfmeLookup00226156(ctx, result);
}
