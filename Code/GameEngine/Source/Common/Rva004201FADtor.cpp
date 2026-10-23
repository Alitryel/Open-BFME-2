// cl: /O1 /Ob2 /EHs /MD /Ireference/shims/subsystem_bfme2 /Ireference/shims/bfme2_ascii
// ??1VictoryConditions@@UAE@XZ, retail 0x004201FA, 62 bytes. Derived dtor of
// VictoryConditions over Rva0041FE0E over SubsystemInterface: installs derived
// vtable 0x00C3BA28 then calls rowed this->rva00420110 0x00420110 then
// installs base vtable 0x00C3B988 via inlined base dtor then calls rowed
// SubsystemInterface dtor 0x001B4E74 with __EH_prolog 0x00629188.
// Evidence: sole caller deleting-dtor 0x00420238 calls this; callee 0x00420110
// takes same this; base ctor 0x0041FDF8 sets vtable 0x00C3B988 and caller
// 0x0042017F overwrites to 0x00C3BA28; layout +0x10/+0x85 matches neighbours.

// Base ctor 0x001B4E63 / dtor 0x001B4E74 by their row names ??0/??1SubsystemInterface (SubsystemInterface.cpp).
// The shared native header gives Rva0041FE0E the same vtable (retail 0x00C3B988) as
// GameEngineDeletingBaseDerived.cpp's view.
typedef bool Bool;
#include "subsystem_interface.h"

class Rva0041FE0E : public SubsystemInterface
{
public:
	Rva0041FE0E();
	virtual ~Rva0041FE0E();
	int m_0C;
};

inline Rva0041FE0E::~Rva0041FE0E()
{
}

class VictoryConditions : public Rva0041FE0E
{
public:
	VictoryConditions();
    virtual ~VictoryConditions();
    // Retail slot 1 of 0x00C3BA28 is the shared forwarder 0x000D20D6 to slot 9 (reset), as
    // Zero Hour's VictoryConditions::init.
    virtual void init() { reset(); }
    virtual void reset();
    virtual void update();
    void rva00420110();
private:
    bool m_endGameShowing; // +10
    unsigned m_endGameShowTime; // +14
    char m_state18[0x8c-0x18];
    int m_field8C;
    bool m_field90;
    bool m_field91;
};

VictoryConditions::~VictoryConditions()
{
	rva00420110();
}

VictoryConditions::VictoryConditions()
{
    m_endGameShowing = false;
    m_endGameShowTime = 0;
    m_field8C = 0;
    m_field90 = false;
    m_field91 = false;
    VictoryConditions::reset();
}
typedef char NativeVictorySize[sizeof(VictoryConditions)==0x94 ? 1 : -1];

// Constructor identity: WorldBuilder identifies the C3BA28 family as
// VictoryConditions; native GameEngine init registers factory420353 as
// TheVictoryConditions. Native base ctor41FDF8 and reset41FE86 are matched.
// BFME1 1399ad37d42ea52a63829e417c46a1ba9ed2cd20 VictoryConditions.cpp
// supplies the construct-then-reset subsystem pattern, while all offsets and
// pre-reset stores above come from BFME2's 79-byte body. +8C/+90/+91 meanings
// remain unknown. Native factory allocation and field extent prove size94.

class VictoryConditionsInterface;
VictoryConditionsInterface *Rva00420353CreateVictoryConditions()
{ return (VictoryConditionsInterface *)new VictoryConditions; }
