// ?Rva0056E5BCFallback@@YAHHH@Z
// partial score=0.227 date=2026-10-19
// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD

// ?Rva0056E5BC@@YAXXZ
// partial score=0.227 date=2026-10-17
// cl: /DNDEBUG /MD
// BFME2 fixed-storage member copies. Complete retail constructors copy
// exactly 0x1C or 4 bytes through memcpy; application type names are unknown.
// As with the BFME1-derived WeaponTemplateSetHead copy, keep these helpers
// separate from their owning records so callers preserve the out-of-line ABI.
// Helpers referenced by the target, matching the retail call targets.
// The receiver record touched at offset +0x18.
 // ?Rva0056E5BC@@YAXXZ

// Earlier comments are retained as evidence; the fixed-storage copies
// and void signature above do not describe this retail boundary.

// Retail returns decoded argument one; its constant predicates skip
// the field write and final helper call. Identity remains address-derived.
int Rva0056DD58Get();
int Rva003EFEB2(int, int);
int __stdcall Rva0056DD95First(int, int);
int Rva00225A93Get(int, int, int, int, int);

int Rva0056E5BCFallback(int a, int b)
{
    int result = 0;
    int owner = Rva0056DD58Get();
    int first = Rva003EFEB2(owner, a);
    int second = Rva003EFEB2(owner, b);
    unsigned char byteTemporary = 0;
    int intermediate = Rva0056DD95First(first, second);
    intermediate = Rva00225A93Get(5, 13, first, second, intermediate);
    result = first;
    return result;
}
