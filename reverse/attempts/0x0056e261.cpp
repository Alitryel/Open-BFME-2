// ?Rva0056E261@@YAXXZ
// partial score=0.189 date=2026-10-17
// cl: /DNDEBUG /MD
// BFME2 fixed-storage member copies. Complete retail constructors copy
// exactly 0x1C or 4 bytes through memcpy; application type names are unknown.
// As with the BFME1-derived WeaponTemplateSetHead copy, keep these helpers
// separate from their owning records so callers preserve the out-of-line ABI.
extern "C" void *memcpy(void *, const void *, unsigned);

// Call targets named by the retail disassembly.
int Rva0056DD58Get(void);
int Rva00225A93Get(int, int, int, int, int);
struct Rva0006D5B0 { static unsigned int sum(unsigned int, unsigned int); };

// Opaque record accessed through the pointer returned by Rva0056DD58Get();
// only the dword field at offset 0x18 is touched by this function.
struct Rva0056DD58Record {
    char m_unused[0x18];
    unsigned int m_field18;
};

int Rva0056DD70Get(Rva0056DD58Record *, int);
int Rva0056DD80Get(Rva0056DD58Record *, int);
void Rva0056E261()
{
    volatile int _pad0 = (int)0xcfcecdcc;
    volatile int _pad1 = (int)0x096e26e;
    volatile int _pad2 = 1;
    volatile int _pad3 = 0;
    volatile int _pad4 = (int)0xcfcecdcc;
    struct { unsigned char v; unsigned char pad[3]; } flag = { 0 };
    int _force20[8] = { 0, 0, 0, 0, 0, 0, 0, 0 };
    (void)_force20;
    volatile int _tail = 0;
    Rva0056DD58Record *rec = (Rva0056DD58Record *)Rva0056DD58Get();
    int b = Rva0056DD70Get(rec, 0);
    int c = Rva0056DD80Get(rec, 0);
    *(volatile int*)&b = b;
    unsigned int s = Rva0006D5B0::sum((unsigned int)c, (unsigned int)b);
    if (s == 0) {
        s = (unsigned int)Rva00225A93Get(5, 2, b, c, (int)s);
    }
    *(volatile int*)&c = c;
    *(volatile Rva0056DD58Record **)&rec = rec;
    if (s == 0) {
        if (b == 1) {
            rec->m_field18 = 0;
        }
    }
    if (s == 0) {
        s = (unsigned int)c;
    }
    if (s == 0) {
        b = (int)s;
    }
    (s == 0 ? Rva0056DD70Get(rec, (int)s) : Rva0056DD70Get(rec, (int)s));
}
