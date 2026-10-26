// cl: /MD
// ?rva006FE400@Rva006FE400@@QAEHPAXPAURva008A4570Owner@@@Z @0x006FE400 42B
// Evidence: chain from 0x0070DFB0 landing; calls virtual slot 7 (0x1C) on this+0x20
// with same args then rowed 0x0070DFB0 on this; test-je shares int return; ret 8.
struct Rva008A4570Owner;

struct Slot7Obj {
    virtual void f0();
    virtual void f1();
    virtual void f2();
    virtual void f3();
    virtual void f4();
    virtual void f5();
    virtual void f6();
    virtual int slot7(void *a1, Rva008A4570Owner *a2);
};

class AptValue;
class EAStringC;
class AptObject {
public:
    virtual AptValue *objectMemberLookup(AptValue *const, const EAStringC *const) const;
};

class Rva006FE400 {
    char m_pad[0x20];
    Slot7Obj *m_stringObject;
public:
    int rva006FE400(void *context, Rva008A4570Owner *memberName);
};

int Rva006FE400::rva006FE400(void *context, Rva008A4570Owner *memberName)
{
    int memberValue = m_stringObject->slot7(context, memberName);
    if (memberValue)
        return memberValue;
    return (int)((AptObject *)this)->AptObject::objectMemberLookup((AptValue *)context, (const EAStringC *)memberName);
}
