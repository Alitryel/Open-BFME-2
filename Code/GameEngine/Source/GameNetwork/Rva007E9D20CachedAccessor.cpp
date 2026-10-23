// cl: /O2
// Transferred unchanged from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/Rva007E9D20CachedAccessor.cpp;
// bfme1_sweep ambiguous: byte-identical bodies placed by the BFME1->BFME2 address map at 0x00656CD0.
// Addresses in the donor text are BFME1.
// Use the cached +0x228 value, else ask the optional object at +0x0C through slot 8.
struct Rva007E9D20Source
{
    virtual void slot0(); virtual void slot1(); virtual void slot2();
    virtual void slot3(); virtual void slot4(); virtual void slot5();
    virtual void slot6(); virtual void slot7();
    virtual void *fallback();
};

struct Rva007E9D20Owner
{
    char m_pad0[12];
    Rva007E9D20Source *m_source;
    char m_pad10[0x218];
    void *m_cached;
    void *get();
};

void *Rva007E9D20Owner::get()
{
    if (m_cached)
        return m_cached;
    return m_source ? m_source->fallback() : 0;
}
