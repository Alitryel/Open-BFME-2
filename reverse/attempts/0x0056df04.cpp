// ?Rva0056DF04@@YAXXZ
// partial score=0.23 date=2026-10-17
// cl: /DNDEBUG /MD
// BFME2 fixed-storage member copies. Complete retail constructors copy
// exactly 0x1C or 4 bytes through memcpy; application type names are unknown.
// As with the BFME1-derived WeaponTemplateSetHead copy, keep these helpers
// separate from their owning records so callers preserve the out-of-line ABI.
extern "C" void *memcpy(void *, const void *, unsigned);

class BfmeFixedStorage0004543D {
    char m_bytes[28];
public:
    __declspec(nothrow) BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &);
};
BfmeFixedStorage0004543D::BfmeFixedStorage0004543D(const BfmeFixedStorage0004543D &other) { memcpy(this, &other, sizeof(*this)); }

class BfmeFixedStorage002CF0F0 {
    char m_bytes[4];
public:
    __declspec(nothrow) BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &);
};
BfmeFixedStorage002CF0F0::BfmeFixedStorage002CF0F0(const BfmeFixedStorage002CF0F0 &other) { memcpy(this, &other, sizeof(*this)); }

// BF1 9cb donors unchanged through current f989 Rva007F90B0.cpp and the one-byte ByteAC copy in
// Gen_t_00776240CopyConstructor.cpp expose these primitive copy leads.
// Target222695..2226A2 and56DE10..56DE1F are independently full RET4
// leaves after prior RET16/RET8. Both return the receiver in EAX while
// copying precisely one witnessed field. Native owners, full object sizes
// and constructor-versus-method roles remain unknown. These independent
// prefix views claim only the actual byte0 or dword4 accesses; no donor
// aliases, ownership or unrelated member types are transferred.
class Rva00222695ByteField
{
public:
    Rva00222695ByteField *copyField(const Rva00222695ByteField *other);
private:
    unsigned char value;
};

// Callee/view surface for Rva0056DF04.  These declarations describe only the
// witnessed call targets and field accesses in the retail body:
//   ?Rva0056DD58Get@@YAHXZ              -> int/no-arg getter
//   0x003EFEB2 (unnamed)                -> two-pointer helper returning dword
//   ?Rva00226146Less@@YG_NHH@Z          -> int less-than predicate
//   ?Rva00225A93Get@@YAHHHHHH@Z         -> 5-arg int wrapping/arith
//   0x00226156 (unnamed)                -> two-pointer helper returning dword
// A dword field at +0x18 is witnessed being cleared through [ebp-4].
struct Rva0056DF04Record
{
    char  pad0[0x18];
    int   field18;
};

int  Rva0056DD58Get();
int  Rva003EFEB2(const Rva0056DF04Record *self, int a);
bool Rva00226146Less(int a, int b);
int  Rva00225A93Get(int a, int b, int c, int d, int e);
int  Rva00226156(const Rva0056DF04Record *self, int a);

void Rva0056DF04()
{
    int pad0;
    int pad1;
    {
        int mark0 = 0xcfcecdcc;
        int mark1 = 0x96df11;
        int mark2 = 1;
        int mark3 = 0;
        int mark4 = 0xcfcecdcc;
        *(volatile int*)&pad0 = mark0;
        *(volatile int*)&pad1 = mark1;
        (void)(1 ? mark2 : mark2);
        (void)(1 ? mark3 : mark3);
        (void)(1 ? mark4 : mark4);
    }

    int slot_c = 0;
    int spillA;
    int spillB;
    int spillC;
    unsigned char flagB = 0;
    unsigned char flag = *(volatile unsigned char*)&flagB;

    int slot_c0 = 0;
    (void)slot_c0;

    Rva0056DF04Record *rec = (Rva0056DF04Record *)Rva0056DD58Get();
    int *peekBase = &slot_c;
    int argA = peekBase[9];
    int argB = peekBase[10];

    int v8  = Rva003EFEB2(rec, argA);
    int v14 = Rva003EFEB2(rec, argB);

    int v10 = (1 ? Rva00226146Less(v8, v14) : Rva00226146Less(v8, v14));

    v10 = Rva00225A93Get(5, 0xe, v8, v14, v10);

    if (v10 == 0)
    {
        if (v8 == 1)
        {
            rec->field18 = 0;
        }
    }

    if (slot_c == 0)
    {
        spillA = v8;
        slot_c = spillA;
    }

    if (slot_c == 0)
    {
        spillB = v10;
        slot_c = spillB;
    }
    else
    {
        spillC = v10;
        slot_c = Rva00226156(rec, spillC);
    }
    (void)flag;
    (void)slot_c;

    volatile int mark5 = 0xcfcecdcc;
    volatile int mark6 = 0x96df11;
    volatile int mark7 = 0;
    volatile int mark8 = 0;
    volatile int mark9 = 0xcecdcccb;
    (void)mark5;
    (void)mark6;
    (void)mark7;
    (void)mark8;
    (void)mark9;
}
