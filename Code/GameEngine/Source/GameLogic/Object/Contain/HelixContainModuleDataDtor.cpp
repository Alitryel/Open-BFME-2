// cl: /O1 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??1CursorParticleSystemFXNugget@@UAE@XZ, retail 0x001E116E (56 bytes).
// Identity: the CursorParticleSystemFXNugget ctor 0x001E0C90 installs vtable
// 0x007DD91C (??_7CursorParticleSystemFXNugget in the data ledger), whose
// slot 0 is the scalar deleting dtor 0x001E1152 calling this body, the same
// wrapper-then-dtor pair as its FXNugget siblings (FXListAtBonePos
// 0x1E107A/0x1E1096, ParticleSystem 0x1E10CE/0x1E10EA). The rows were first
// named HelixContainModuleData from a Zero Hour donor; retail has no
// HelixContain string. The four-byte field at +0x148 (the ctor's Anim2D
// template name) releases a string buffer before the shared FXNugget base
// dtor 0x001DFA48 runs.

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
class __declspec(novtable) CursorParticleSystemFXNugget : public Rva001DFEAABase
{
public:
    virtual ~CursorParticleSystemFXNugget();

private:
    BfmeOwnedString4 unknownOwnedField148;
    unsigned char unknownByte14C;
};

typedef char BaseExtent[sizeof(Rva001DFEAABase) == 0x148 ? 1 : -1];
typedef char OwnedFieldExtent[sizeof(BfmeOwnedString4) == 4 ? 1 : -1];

inline CursorParticleSystemFXNugget::~CursorParticleSystemFXNugget() {}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeCursorParticleSystemFXNuggetInlineAnchor@@YAXPAVCursorParticleSystemFXNugget@@@Z absent-from-retail
void _bfmeCursorParticleSystemFXNuggetInlineAnchor(CursorParticleSystemFXNugget *p)
{
    p->CursorParticleSystemFXNugget::~CursorParticleSystemFXNugget();
}
#pragma inline_depth()
