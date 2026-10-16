// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
//
// ?bfmeGoDGH@@YGXPAX0@Z, retail 0x00212183, 27 bytes. The free function at
// 0x002120C2 is pinned as ?rva002120C2@Rva002120C2@@YGPAXPAX@Z from this body's
// own REL32 displacement; it walks this+0x24C, a pointer array, and tests each
// element's +0x1C against the key. The second callee 0x003FD690 is already
// rowed as ?rva003FD690@Rva003FD690@@QAEXPBUCoord@@@Z and is pinned under the
// donor's spelling for this TU.

class BfmeSubDGH
{
public:
	void bfmeRunDGH(void *b);
};

BfmeSubDGH *__stdcall rva002120C2(void *a);

void __stdcall bfmeGoDGH(void *a, void *b)
{
	BfmeSubDGH *s = rva002120C2(a);
	if (s != 0)
		s->bfmeRunDGH(b);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x003FD690 reads ?rva003FD690@Rva003FD690@@QAEXPBUCoord@@@Z
#pragma comment(linker, "/alternatename:?bfmeRunDGH@BfmeSubDGH@@QAEXPAX@Z=?rva003FD690@Rva003FD690@@QAEXPBUCoord@@@Z")
//   0x002120C2 reads ?rva002120C2@Rva002120A4@@QAEPAURva002120C2Entry@@ABVAsciiString@@@Z
#pragma comment(linker, "/alternatename:?rva002120C2@@YGPAVBfmeSubDGH@@PAX@Z=?rva002120C2@Rva002120A4@@QAEPAURva002120C2Entry@@ABVAsciiString@@@Z")
