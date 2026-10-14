// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// Target ctor1E0C90 and vtableBDD91C link this cleanup to wrapper1E1152.
// The four-byte field at148 releases a string buffer; the donor vector layout
// does not apply. HelixContainModuleData remains a donor-based name inference.

template <typename T>
class StringBase
{
    void *m_data;
    void releaseBuffer();

protected:
    ~StringBase() { releaseBuffer(); }
};

class BfmeOwnedString4 : private StringBase<char>
{
public:
    ~BfmeOwnedString4() {}
};

class Rva001DFEAABase
{
public:
    virtual ~Rva001DFEAABase();

private:
    unsigned char unknownBaseTail[0x144];
};

// The target dtor has no derived-vptr store. novtable keeps this view's dtor
// body aligned with that fact; no constructor is emitted from this file.
class __declspec(novtable) HelixContainModuleData : public Rva001DFEAABase
{
public:
    virtual ~HelixContainModuleData();

private:
    BfmeOwnedString4 unknownOwnedField148;
    unsigned char unknownByte14C;
};

typedef char BaseExtent[sizeof(Rva001DFEAABase) == 0x148 ? 1 : -1];
typedef char OwnedFieldExtent[sizeof(BfmeOwnedString4) == 4 ? 1 : -1];

inline HelixContainModuleData::~HelixContainModuleData() {}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeHelixContainModuleDataInlineAnchor@@YAXPAVHelixContainModuleData@@@Z absent-from-retail
void _bfmeHelixContainModuleDataInlineAnchor(HelixContainModuleData *p)
{
    p->HelixContainModuleData::~HelixContainModuleData();
}
#pragma inline_depth()
