// cl: /DNDEBUG /EHsc /MD
// ??1Rva005F5EA6@@UAE@XZ @0x005F5EA6 97B: dtor via rowed erase 0x002B7250 plus pinned 0x005E12D1; caller deleting dtor 0x005F5F0F
class CreateAHeroData;

class Rva002B7250 {
public:
    void rva002B7250(CreateAHeroData *v);
};

class Rva005E12D1 {
public:
    virtual ~Rva005E12D1();
    int m_pad[4];
};

#include "../../Include/Common/Rva005E394EPrimaryBase.h"

#include "../../Include/Common/Rva005E4AE2Listener.h"

class Rva005F5EA6 : public Rva005E394EPrimaryBase, public Rva005E12D1, public Rva005E4AE2Listener {
public:
    virtual ~Rva005F5EA6();
    // Preserve the unread word at+20 outside the minimal interface.
    int m_c;
    Rva002B7250 *m_list;
};

Rva005F5EA6::~Rva005F5EA6()
{
    m_list->rva002B7250((CreateAHeroData *)((char *)this + 0x1c));
}
