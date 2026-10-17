// ?Rva0056E40C@@YAXXZ
// partial score=0.16 date=2026-10-17
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

// Helper declarations matching the retail call targets.
int Rva0056DD5EGet();
int Rva0056DD86Second(int, int, int);
int Rva00225A93Get(int, int, int, int, int);
int Rva00226156(int, int);

// A record whose byte at offset 0x18 is cleared by the retail body.
struct Rva0056E40CRecord {
    char m_pad[0x18];
    unsigned int m_field18;
};

void Rva0056E40C()
{
    volatile int pad0 = (int)0xCFCECDCC;
    volatile int pad1 = (int)0x0096E419;
    volatile int pad2 = 1;
    volatile int pad3 = 0;
    volatile int pad4 = (int)0xCFCECDCC;
    int f8 = 0;
    int fc = 0;
    struct { int v; unsigned char pad[3]; } bl;
    bl.v = 0;
    {
        Rva0056E40CRecord *rec = (Rva0056E40CRecord *)Rva0056DD5EGet();
        {
            Rva00222695ByteField fld;
            Rva00222695ByteField *pfld = fld.copyField((Rva00222695ByteField*)rec);
            (void)pfld;
        }
        f8 = ((rec != (Rva0056E40CRecord*)0) ? *(int *)((char *)rec + 8) : *(int *)((char *)rec + 8));
        fc = ((rec != (Rva0056E40CRecord*)0) ? *(int *)((char *)rec + 0xc) : *(int *)((char *)rec + 0xc));
        int a = Rva0056DD86Second(f8, fc, 0);
        int b = Rva00225A93Get(5, 1, f8, fc, a);
        if (b == 0 && f8 == 1) {
            rec->m_field18 = 0;
        }
        if (0) throw 1;
        int d = (b == 0 ? Rva00226156(fc, b) : Rva00226156(fc, b));
        (void)d;
    }
}
