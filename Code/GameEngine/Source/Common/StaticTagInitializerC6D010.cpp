// cl: /O2 /Ob0
// Carried from the Open-BFME-1 donor at submodule revision 77db49c3
// (game/GameEngine/Source/Common/StaticTagInitializers.cpp). Target evidence:
// the 22B body is byte-identical at BFME2 0x007B5DF0 (donor b1 0x00C6D010).
// The name and tag slot are donor assertions; it lives in its own TU because
// StaticTagInitializers.cpp here already holds the sibling initializers.

class Rva007F0210
{
    int m_00;
    int m_04;
    int m_08;

public:
    Rva007F0210 &set(int a, int b);
};

extern int bfmeRva012C3B38TagValue;
// bfmeRva012C3B38TagValue: matched references place it at VA 0xdd8290 (retail .data initial value 13513928).
int bfmeRva012C3B38TagValue = 13513928;
// bfmeRva0130A98CTagSlot: matched references place it at VA 0xe0a3a4 (zero-filled; a plain-data view).
Rva007F0210 bfmeRva0130A98CTagSlot;

void bfmeRva00C6D010InitializeTag()
{
    bfmeRva0130A98CTagSlot.set(bfmeRva012C3B38TagValue, 0x41555448);
}
