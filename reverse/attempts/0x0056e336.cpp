// ?Rva0056E336@@YAXXZ
// partial score=0.227 date=2026-10-17
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

struct Rva0056E336Ctx {
    char pad0[0x18];
    int field18;
};

int Rva0056DD58Get();
int Rva0056DD86Second(int, int);
int Rva00225A93Get(int, int, int, int, int);
int Rva00226156(int, int);

void Rva0056E336()
{
    Rva0056E336Ctx *ctx;
    int a = 0;
    int b = 0;
    int c = 0;
    int d = 0;
    int e = 0;
    int f = 0;
    volatile int pad1 = 0;
    volatile int pad2 = 0;
    char flag = 0;
    volatile int vf1 = 0xCFCECDCC;
    volatile int vf2 = 0x0096E343;
    volatile int fi1 = 1;
    volatile int fi2 = 0;
    volatile int vf3 = 0xCFCECDCC;
    volatile int frameGrow[4];

    ctx = (Rva0056E336Ctx *)Rva0056DD58Get();
    *(volatile Rva0056E336Ctx **)&ctx = ctx;
    a = 0;
    b = 0;
    c = 0;
    d = 0;
    *(volatile int *)&a = 0;
    *(volatile int *)&b = 0;

    {
        int x = Rva0056DD58Get();
        a = x;
    }
    {
        int y = (int)Rva0056DD58Get();
        b = y;
    }
    {
        flag = 0;
        *(volatile char *)&flag = flag;
        c = 0;
    }

    {
        int x = Rva0056DD86Second((1 ? a : a), (float)(double)(1 ? b : b));
        d = x;
        d = Rva00225A93Get(5, 1, (c ? a : a), (c ? b : b), (c ? x : x));
    }

    if (b == 1)
        *(volatile int *)&ctx->field18 = 0;

    d = 0;
    *(volatile int *)&d = 0;
    {
        int q = (1 ? d : d);
        int ar = (1 ? a : a);
        d = Rva00226156(ar, q);
    }
    {
        int bc = b;
        c = bc;
    }
    (void)c;
}
