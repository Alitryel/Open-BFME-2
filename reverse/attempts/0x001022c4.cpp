// ?Rva001022C4Shutdown@@YAXXZ
// partial score=0.85 date=2026-10-14
// cl: /MD /EHs-c-
//
// ?Rva00102215Get@@YAPAVRva001021F7@@XZ @0x00102215 38B: chain singleton getter
// for Rva001021F7 (0x20) via global g_00DEC268; new + ctor 0x001021F7.
// Evidence: packet disassembly; calls landed ctor; 8 callers.

class ObjectCreationList
{
public:
    ObjectCreationList();
private:
    char m_pad[12];
};

class Rva001021F7
{
public:
    Rva001021F7();
    void *m_a;
    ObjectCreationList m_list1;
    void *m_b;
    ObjectCreationList m_list2;
};

// Singleton pointer (data_ledger RVA 0x9EC268, zero .data, unowned);
// defined here, nothing else defines it.
Rva001021F7 *g_00DEC268 = 0;

Rva001021F7 *Rva00102215Get()
{
    if (g_00DEC268)
        return g_00DEC268;
    Rva001021F7 *p = new Rva001021F7;
    g_00DEC268 = p;
    return p;
}

// ?Rva001022C4Shutdown@@YAXXZ @0x001022C4 49B: the singleton's teardown,
// the getter's counterpart. If the instance exists it runs the rowed
// ?rva0010223B@Rva0010223B@@QAEXXZ (0x0010223B) on it, then destroys it
// with the rowed destructor ??1Rva00102188@@UAE@XZ (0x00102188, called
// directly; it stores no vftable) and the rowed ??3@YAXPAX@Z (0x0002FD60),
// and clears g_00DEC268. No direct caller reaches it in retail. The two
// rowed callees carry their own address-derived class names, so the
// instance is viewed through them here.
class Rva0010223B
{
public:
    void rva0010223B();
};

class Rva00102188
{
public:
    virtual ~Rva00102188();
};

void Rva001022C4Shutdown()
{
    Rva001021F7 *p = g_00DEC268;
    if (p)
    {
        ((Rva0010223B *)p)->rva0010223B();
        p = g_00DEC268;
    }
    if (p)
    {
        ((Rva00102188 *)p)->Rva00102188::~Rva00102188();
        operator delete(p);
    }
    g_00DEC268 = 0;
}
