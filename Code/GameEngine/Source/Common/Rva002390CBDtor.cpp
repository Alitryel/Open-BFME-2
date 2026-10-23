// cl: /O1 /MD /D_CRTIMP= /DNDEBUG
// Target cleanup for the shared-reference member at +4; original type unknown.
class OpaqueRefCounted {
public:
    virtual ~OpaqueRefCounted();
    void Release_Ref();
private:
    long refs;
};
class Rva002390CB {
    void *unknown00;
    OpaqueRefCounted *owner04;
public:
    ~Rva002390CB();
};
inline Rva002390CB::~Rva002390CB() {
    if (owner04) owner04->Release_Ref();
}

// Header inlines that the units including the header emit as select-any
// copies, which plain definitions here collided with. The anchor keeps this
// unit's copies for the rows; it is not retail code.
#pragma inline_depth(0)
// ?_bfmeRva002390CBInlineAnchor@@YAXPAVRva002390CB@@@Z absent-from-retail
void _bfmeRva002390CBInlineAnchor(Rva002390CB *p)
{
    p->Rva002390CB::~Rva002390CB();
}
#pragma inline_depth()

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??1VoiceSlot@@QAE@XZ=??1Rva002390CB@@QAE@XZ")
