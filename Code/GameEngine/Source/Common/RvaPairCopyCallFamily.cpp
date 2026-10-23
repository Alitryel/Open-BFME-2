// cl: /Oy-
// Three pair-copy-calls (30B each): push ebp, mov ebp, esp, push ecx x2,
// copy [ebp+8]/[ebp+0x0C] to [ebp-8]/[ebp-4], lea eax, [ebp-8], push eax,
// call <worker>, leave, ret 8. Each copies its 8-byte pair argument to a
// local and passes its address to a stdcall worker. /O1 gives the
// push-ecx prolog and leave epilog; /Oy- keeps the ebp frame.
// 0x002BFCF5 is a thiscall member (-> 0x002BFA86); 0x003A37DC (-> 0x002ADCE1; row keeps the
// peer Rva000427195::rva003A37DC VideoPair pin),
// 0x005258F8 (-> 0x00525407). Worker identities unproven (opaque pins);
// new names are address-derived. One ledger row per call.

struct VideoPair
{
	int x;
	int y;
};

void __stdcall Rva002ADCE1Worker(VideoPair *pair);

// Native 2BFA86 reads ECX for its hashtable bucket and count members.
// The 30B 2BFCF5 wrapper must preserve this receiver while copying the pair.
struct TwoInts002BFCF5 { int x, y; };
class Rva002BFCF5 {
public:
 void erase(TwoInts002BFCF5 pair);
private:
 void helper(const TwoInts002BFCF5 *pair);
};
void Rva002BFCF5::erase(TwoInts002BFCF5 pair) {
 TwoInts002BFCF5 tmp = pair;
 helper(&tmp);
}

class Rva000427195
{
public:
	void rva003A37DC(VideoPair pair);
};

// Rva000427195::rva003A37DC is defined with its retail-matched body in Code/GameEngine/Source/GameClient/GUI/ControlBar/ControlBarVideoMapErase.cpp (0x003A37DC).


// The retail call in this body reads 0x002BFA86, an address the ledger already
// carries as ?erase@?$hashtable@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@URva002BFA86Record@@U?$hash@URva002BFA86Record@@@2@U?$_Select1st@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@U?$equal_to@URva002BFA86Record@@@2@V?$allocator@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@@_STL@@QAEXABU?$_Ht_iterator@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@U?$_Const_traits@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@URva002BFA86Record@@U?$hash@URva002BFA86Record@@@2@U?$_Select1st@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@U?$equal_to@URva002BFA86Record@@@2@V?$allocator@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@@2@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?helper@Rva002BFCF5@@AAEXPBUTwoInts002BFCF5@@@Z=?erase@?$hashtable@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@URva002BFA86Record@@U?$hash@URva002BFA86Record@@@2@U?$_Select1st@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@U?$equal_to@URva002BFA86Record@@@2@V?$allocator@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@@_STL@@QAEXABU?$_Ht_iterator@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@U?$_Const_traits@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@URva002BFA86Record@@U?$hash@URva002BFA86Record@@@2@U?$_Select1st@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@U?$equal_to@URva002BFA86Record@@@2@V?$allocator@U?$pair@$$CBURva002BFA86Record@@U1@@_STL@@@2@@2@@Z")
