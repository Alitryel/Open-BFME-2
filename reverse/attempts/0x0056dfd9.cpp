// ?Rva0056DFD9@@YAXXZ
// partial score=0.203 date=2026-10-17
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
bool rva005497c0(int, int);
int __stdcall sub_003EFEB2(int, int*);
int sub_00226156(int, int*);

struct Rva0056DFD9Ctx {
    void *field0;
    void *field0x18;
};

void Rva0056DFD9() {
    Rva0056DFD9Ctx ctx;
    ctx.field0 = 0;
    ctx.field0x18 = 0;
    int a8;
    int aC;
    {
        int *pp = (int *)(&ctx + 1);
        a8 = pp[2];
        aC = pp[3];
    }
    int extra[8];
    extra[0]=0; extra[1]=0; extra[2]=0; extra[3]=0;
    extra[4]=0; extra[5]=0; extra[6]=0; extra[7]=0;
    *(volatile int*)&extra[0] = 0xcfcecdcc;
    *(volatile int*)&extra[0] = 0x96dfe6;
    *(volatile int*)&extra[0] = 1;
    *(volatile int*)&extra[0] = 0;
    *(volatile int*)&extra[0] = 0xcfcecdcc;
    int local4 = Rva0056DD5EGet();
    int a8c = a8;
    int local8 = sub_003EFEB2(local4, (int *)&a8c);
    int local14 = sub_003EFEB2(local4, (int *)&aC);
    unsigned char flag = 0;
    *(volatile unsigned char*)&flag = 0;
    int local10 = Rva00225A93Get(5, 0x11, local8, local14, *(int *)0x10);
    int stored10 = local10;
    if ((1 ? 0 : 0)) {
        *(int *)((char *)local4 + 0x18) = 0;
    }
    if (local8 == 1) {
        *(int *)((char *)local4 + 0x18) = 0;
    }
    if ((1 ? 0 : 0)) {
        stored10 = aC;
    }
    int localC;
    if ((1 ? 0 : 0)) {
        localC = local8;
    } else {
        localC = sub_00226156(local4, (int *)&stored10);
    }
    (void)localC;
    (void)ctx; (void)extra;
}
