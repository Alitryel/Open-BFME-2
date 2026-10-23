// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

class BfmeSubA1034
{
public:
	void bfmeAdd1034(int b);
};

struct BfmeX1034
{
	char m_bfmePad[4];
	BfmeSubA1034 m_bfmeSub;
};

BfmeX1034 * __stdcall bfmeFind1034(int a, int n);

void __stdcall bfmeGo1034A(int a, int b)
{
	BfmeX1034 *x = bfmeFind1034(a, 0);

	if (x != 0)
		x->m_bfmeSub.bfmeAdd1034(b);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x000366F0 reads ?set@?$StringBase@D@@QAEXABV1@@Z
#pragma comment(linker, "/alternatename:?bfmeAdd1034@BfmeSubA1034@@QAEXH@Z=?set@?$StringBase@D@@QAEXABV1@@Z")
//   0x0040DAA0 reads ?rva0040DAA0@Rva0040DAA0@@QBEPAXABV?$StringBase@D@@PAH@Z
#pragma comment(linker, "/alternatename:?bfmeFind1034@@YGPAUBfmeX1034@@HH@Z=?rva0040DAA0@Rva0040DAA0@@QBEPAXABV?$StringBase@D@@PAH@Z")
