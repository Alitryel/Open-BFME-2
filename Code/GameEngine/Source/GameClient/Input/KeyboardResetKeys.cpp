// cl: /MD /EHsc
// BFME2 Keyboard::resetKeys, RVA 0x00232BDD (16 bytes).
// Identity: WndProc's focus-change calls in WinMain.cpp.
// BFME2 differs from the Generals memset implementation: it gathers pending
// input, then synthesizes key releases. Both direct targets have independent
// Ghidra boundaries (0x00232B7B/76 and 0x00232AE8/147 bytes).
// Historical helper names are unknown; retain address-qualified identities.
class Keyboard
{
public:
    void resetKeys();
    void rva00232B7B(); // public, as its row spells it
private:
    void rva00232AE8();
};

void Keyboard::resetKeys()
{
    rva00232B7B();
    rva00232AE8();
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below; bind the donor spelling to that owner so one
// address keeps one definition.
//   0x00232B7B -> ?rva00232B7B@Keyboard@@QAEXXZ (defined by Code/GameEngine/Source/GameClient/Input/rva00232B7BRva00232B7BFarm.cpp)
#pragma comment(linker, "/alternatename:?rva00232B7B@Keyboard@@AAEXXZ=?rva00232B7B@Keyboard@@QAEXXZ")
