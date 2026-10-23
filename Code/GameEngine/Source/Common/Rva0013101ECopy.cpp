// cl: /O1 /MD
// ?rva0013101E@Rva0013101E@@QAEAAV1@PBV1@@Z @ 0x0013101E (68B), unlock lane: preserves bit31 of dword0, copies low31 + 3 dwords. Callers 0x00132171 0x00136794 0x00137364. Returns *this (EAX=this at ret per shape lever 31).

class Rva0013101E
{
public:
    Rva0013101E &rva0013101E(Rva0013101E const *src);
    unsigned m_a : 3;
    unsigned m_b : 27;
    unsigned m_c : 1;
    unsigned m_keep : 1;
    unsigned m_d1;
    unsigned m_d2;
    unsigned m_d3;
};

Rva0013101E &Rva0013101E::rva0013101E(Rva0013101E const *src)
{
    m_a = src->m_a;
    m_b = src->m_b;
    m_c = src->m_c;
    m_d1 = src->m_d1;
    m_d2 = src->m_d2;
    m_d3 = src->m_d3;
    return *this;
}
