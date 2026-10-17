// ?Rva0056E5BC@@YAXXZ
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

class Rva00222695ByteField
{
public:
    Rva00222695ByteField *copyField(const Rva00222695ByteField *other);
private:
    unsigned char value;
};

// Helpers referenced by the target, matching the retail call targets.
int Rva0056DD58Get();
int Rva0056DD95First(int, int);
int Rva00225A93Get(int, int, int, int, int);
int Rva00226156Helper(void *, int);

// The receiver record touched at offset +0x18.
struct Rva0056E5BCOwner {
    char pad[0x18];
    int field18;
};

 // ?Rva0056E5BC@@YAXXZ
void Rva0056E5BC()
{
    BfmeFixedStorage0004543D s1 = *(BfmeFixedStorage0004543D*)0;
    BfmeFixedStorage0004543D s2 = s1;
    (void)s2;
    int a = 0xcfcecdcc;
    int b = 0x96e5c9;
    int c = 1;
    int h = 0;
    unsigned char btmp = 0;
    int h_init = 0;
    (void)h_init;
    *(volatile int*)&a = 0xcfcecdcc;
    *(volatile int*)&h = h_init;
    a = 0;
    Rva0056E5BCOwner *owner = (Rva0056E5BCOwner *)Rva0056DD58Get();
    int aa = *(int *)&owner;
    a = aa;
    b = Rva0056DD95First((aa ? 1 : aa), aa);
    c = Rva00225A93Get(5, 0xd, aa, aa, b);
    if (c == 0) return;
    if (b != 1) return;
    owner->field18 = b - 1;
    int h2 = Rva00226156Helper(&btmp, b);
    (void)a;
    (void)h2;
}
