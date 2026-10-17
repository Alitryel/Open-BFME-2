// ?Rva0056E4E2@@YAXXZ
// partial score=0.25 date=2026-10-17
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

// Forward declarations of the retail callees used by ?Rva0056E4E2@@YAXXZ.
int Rva0056DD5EGet();
short Rva0056DD8DSecond(int, int, char);
int Rva00225A93Get(int, int, int, int, int);
int Rva00226156Get(int, int);

// The receiver object whose dword at offset 0x18 is cleared.
struct Rva0056E4E2Receiver {
    char m_pad[0x18];
    int m_field18;
};

void Rva0056E4E2()
{
    int pad_arr[5];
    *(volatile int*)&pad_arr[0] = 0;
    *(volatile int*)&pad_arr[1] = 0;
    *(volatile int*)&pad_arr[2] = 0;
    *(volatile int*)&pad_arr[0];
    *(volatile int*)&pad_arr[1];
    *(volatile int*)&pad_arr[2];
    int local_c = 0;
    int local_4 = Rva0056DD5EGet();
    int local_8 = Rva00226156Get(local_4, *(volatile int*)&pad_arr[1]);
    int local_14 = Rva00226156Get(local_4, *(volatile int*)&pad_arr[2]);

    char local_15;
    *(volatile char*)&local_15;
    {
        int tmp_c;
        *(volatile int*)&tmp_c;
        local_c = 0;
        *(volatile int*)&local_c;
    }

    local_14 = (1 ? local_8 : local_8);

    int local_10 = (int)(short)Rva0056DD8DSecond(local_8, pad_arr[11], local_15);

    local_10 = Rva00225A93Get(3, 1, *(volatile int*)&local_8, *(volatile int*)&local_14, local_10);

    if (local_c == 1 && local_8 == 1) {
        ((Rva0056E4E2Receiver *)local_4)->m_field18 = 0;
    }

    if ((*(volatile int*)&local_c) == 1) {
        local_10 = (int)(short)0;
    }

    if ((*(volatile int*)&local_c) == 1) {
        local_c = local_8;
    } else {
        local_c = Rva00226156Get(local_4, local_10);
    }

    *(volatile int*)&local_c;
}
