// cl: /O2
// Partial transfer from Open-BFME-1 5cae4bdff game/GameEngine/Source/GameNetwork/
// Rva007FCF10DescriptorLookups.cpp: only Rva007FBAB0Codec::findEntry, which the
// BFME1->BFME2 address map places at 0x00667FC0 (bfme1_sweep ambiguous, error 2B);
// its unplaced twin Rva007FCF10Codec::findEntry is left out. Addresses in the
// donor text are BFME1.
// FESL message-codec descriptor lookups at retail 0x007FCF10 (vtable slot
// 0x00D2BFA8) and 0x007FBAB0 (vtable slot 0x00D2BD48). Each codec vtable is
// deleting destructor (Gen007FCF50 / Gen007FBAF0), fetch, this lookup, then
// the per-message encoders. The lookup ignores the codec, reads the message
// id at +0x1c and scans a null-terminated static table of descriptor
// pointers (VA 0x012C3BC8 / 0x012C3B40) for the entry whose +8 id matches.

struct Rva007FCF10Entry
{
    char m_pad00[8];
    int m_id;
};

struct Rva007FCF10Message
{
    char m_pad00[0x1c];
    int m_id;
};

extern Rva007FCF10Entry *g_00DD8298[];

// The descriptor table itself, VA 0x00DD8298 (RVA 0x009D8298): 29 pointers to
// the Rva007F0210 tag slots, in the retail order, then a null terminator. The
// slots are owned by StaticTagInitializers.cpp / StaticTagInitializerC6D010.cpp;
// each address below was read back from the image and matched against the
// ledger rows at RVA 0x00A0A26C..0x00A0A3BC.
class Rva007F0210;

extern Rva007F0210 bfmeRva0130A98CTagSlot;
extern Rva007F0210 bfmeRva0130A968TagSlot;
extern Rva007F0210 bfmeRva0130A8E4TagSlot;
extern Rva007F0210 bfmeRva0130A89CTagSlot;
extern Rva007F0210 bfmeRva0130A938TagSlot;
extern Rva007F0210 bfmeRva0130A908TagSlot;
extern Rva007F0210 bfmeRva0130A9A4TagSlot;
extern Rva007F0210 bfmeRva0130A920TagSlot;
extern Rva007F0210 bfmeRva0130A8CCTagSlot;
extern Rva007F0210 bfmeRva0130A854TagSlot;
extern Rva007F0210 bfmeRva0130A878TagSlot;
extern Rva007F0210 bfmeRva0130A914TagSlot;
extern Rva007F0210 bfmeRva0130A95CTagSlot;
extern Rva007F0210 bfmeRva0130A92CTagSlot;
extern Rva007F0210 bfmeRva0130A884TagSlot;
extern Rva007F0210 bfmeRva0130A950TagSlot;
extern Rva007F0210 bfmeRva0130A980TagSlot;
extern Rva007F0210 bfmeRva0130A8D8TagSlot;
extern Rva007F0210 bfmeRva0130A944TagSlot;
extern Rva007F0210 bfmeRva0130A890TagSlot;
extern Rva007F0210 bfmeRva0130A8B4TagSlot;
extern Rva007F0210 bfmeRva0130A8C0TagSlot;
extern Rva007F0210 bfmeRva0130A998TagSlot;
extern Rva007F0210 bfmeRva0130A974TagSlot;
extern Rva007F0210 bfmeRva0130A860TagSlot;
extern Rva007F0210 bfmeRva0130A8F0TagSlot;
extern Rva007F0210 bfmeRva0130A86CTagSlot;
extern Rva007F0210 bfmeRva0130A8FCTagSlot;
extern Rva007F0210 bfmeRva0130A8A8TagSlot;

Rva007FCF10Entry *g_00DD8298[] =
{
    (Rva007FCF10Entry *)&bfmeRva0130A98CTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A968TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8E4TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A89CTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A938TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A908TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A9A4TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A920TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8CCTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A854TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A878TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A914TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A95CTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A92CTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A884TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A950TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A980TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8D8TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A944TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A890TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8B4TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8C0TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A998TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A974TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A860TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8F0TagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A86CTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8FCTagSlot,
    (Rva007FCF10Entry *)&bfmeRva0130A8A8TagSlot,
    0
};

class Rva007FBAB0Codec
{
public:
    virtual ~Rva007FBAB0Codec();
    virtual int fetch();
    virtual Rva007FCF10Entry *findEntry(Rva007FCF10Message *message);
};

Rva007FCF10Entry *Rva007FBAB0Codec::findEntry(Rva007FCF10Message *message)
{
    int id = message->m_id;
    if (id == -1)
        return 0;
    for (Rva007FCF10Entry **entry = g_00DD8298; *entry; ++entry)
        if ((*entry)->m_id == id)
            return *entry;
    return 0;
}
