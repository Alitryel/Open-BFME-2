// ?Rva0056E0AE@@YAXXZ
// partial score=0.173 date=2026-10-17
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

int Rva0056DD5EGet();
int Rva00225A93Get(int, int, int, int, int);
int rva00549000(short, short);
int rva00226156(int, int);

struct Rva0056E0AE_Rec {
    char pad0[0x18];
    int field18;
};

void Rva0056E0AE()
{
    volatile float _f1 = 3.4f;
    volatile float _f2 = 0.00001f;
    volatile int _p1 = 1;
    volatile int _p2 = 0;
    char _pad[12];
    _pad[0] = 0;
    int v4 = Rva0056DD5EGet();
    int v8 = rva00226156(v4, 0);
    int v14 = rva00226156(v4, 0);
    char c15 = 0;
    *(volatile char*)&c15 = *(volatile char*)&c15;
    int v10 = rva00549000((short)v8, (short)v14);
    v10 = Rva00225A93Get(3, 0x11, v8, v14, v10);

    volatile int _z1 = 0;
    volatile int _z2 = 0;
    volatile int _z3 = 0;
    {
        int t4 = v4;
        int t8 = v8;
        if (_z1 ? 1 : 0) {
            if (t8 == 1) {
                ((Rva0056E0AE_Rec *)t4)->field18 = 0;
            }
        }
    }
    if (_z2 ? 1 : 0) {
        *(volatile int*)&v10 = *(volatile int*)&v10;
    }
    volatile float vf = _f1;
    *(volatile float*)&vf = _f2;
    volatile int vc = 0;
    *(volatile int*)&vc = 0;
    if (_z3 ? 1 : 0) {
        vc = v8;
    } else {
        vc = rva00226156(v4, (1 ? v10 : v10));
    }
    (void)vc;
    (void)c15;
    (void)_f1; (void)_f2; (void)_p1; (void)_p2;
}
