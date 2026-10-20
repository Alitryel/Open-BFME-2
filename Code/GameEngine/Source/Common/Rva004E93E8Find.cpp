// cl: /MD
// ?getMasterPlayer@AIGameTeam@@QAEPAXXZ @0x004E93E8 49B search ptr array +0xc +0x10 for [elem+0x5c]==1 or global flag caller 0x004E9710
struct Elem004E93E8 { char _pad[0x5c]; int m_5c; };
struct Glob004E93E8 { char _pad[0x860]; unsigned char m_860; };
// TheSkirmishAIManager is owned as a Rva002A8F24 (Rva005EEA20Find.cpp); this
// unit reads it through its own view.
class Rva002A8F24;
extern Rva002A8F24 *TheSkirmishAIManager;
class AIGameTeam
{
public:
    char _pad0[0xc];
    Elem004E93E8 **m_begin;
    Elem004E93E8 **m_end;
    void *getMasterPlayer();
};

void *AIGameTeam::getMasterPlayer()
{
    void *found = 0;
    Elem004E93E8 **p = m_begin;
    Elem004E93E8 **e = m_end;
    for (;;) {
        if (p == e)
            break;
        Elem004E93E8 *cur = *p;
        if (cur->m_5c == 1 || ((Glob004E93E8 *)TheSkirmishAIManager)->m_860 != 0)
            found = cur;
        ++p;
        if (found == 0)
            continue;
        break;
    }
    return found;
}
