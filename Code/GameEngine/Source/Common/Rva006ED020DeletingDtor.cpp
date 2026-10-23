// cl: /O2 /MD
// ??_GRva006ED020@@UAEPAXI@Z, retail 0x006ED020, 61 bytes.
// Deleting dtor storing vtable 0x008EC9CC (same as Rva006F8460) with member
// +0x10 via 0x0070A840 plus pool free 0x14, then global delete. Evidence:
// chain lane via freeBlock 0x006DB270; vslot 1 of 0x008EC9CC; callees rowed
// freeBlock plus pinned 0x0070A840 plus global delete 0x0002FD60.
class Rva0070A840
{
public:
    ~Rva0070A840();
};
class Rva006DB270
{
public:
    void freeBlock(void *p, int size);
};
extern Rva006DB270 *g_pChainBlockAllocator;
class Rva006ED020
{
public:
    virtual ~Rva006ED020();
private:
    char m_pad[0x0C];
    Rva0070A840 *m_10;
};
// ??1Rva006ED020@@UAE@XZ present-unmatched
Rva006ED020::~Rva006ED020()
{
    Rva0070A840 *p = m_10;
    if (p) {
        p->Rva0070A840::~Rva0070A840();
        g_pChainBlockAllocator->freeBlock(p, 0x14);
    }
}
void deleteRva006ED020(Rva006ED020 *p) { delete p; }
