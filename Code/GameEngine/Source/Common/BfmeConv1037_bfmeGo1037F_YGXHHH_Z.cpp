// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
// Open-BFME5 conversions.

class BfmeG1037
{
public:
	void bfmeDo1037(int b, bool c);
};

BfmeG1037 * __stdcall bfmeFind1037F(int a);

// WB 010C8450 saves the HordeContain receiver and forwards it to its
// module lookup. Retail caller 00473197 sets ECX=primary HordeContain.
// The retail provider never reads ECX, so its former donor free-function
// view reproduced the bytes but omitted the receiver setup in consumers.
// Native 00496EBC compares the final argument byte; WB010C8450 does
// byte loads too. The receiver-unused provider forwards this boolean home.
// Preserve the clean BF1 f98983a7d algorithm; no original name is established.
class HordeContain {
public:
 void rva00468E79(int a, int b, bool c);
};
void HordeContain::rva00468E79(int a, int b, bool c)
{
	BfmeG1037 *g = bfmeFind1037F(a);

	if (g != 0)
		g->bfmeDo1037(b, c);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   4812293 reads ?rva00496E05@BannerCarrierUpdate@@QAEXPAX_N@Z
#pragma comment(linker, "/alternatename:?bfmeDo1037@BfmeG1037@@QAEXH_N@Z=?rva00496E05@BannerCarrierUpdate@@QAEXPAX_N@Z")
//   4623910 reads ?Rva00468E26Get@@YGPAVModule@@PAVObject@@@Z
#pragma comment(linker, "/alternatename:?bfmeFind1037F@@YGPAVBfmeG1037@@H@Z=?Rva00468E26Get@@YGPAVModule@@PAVObject@@@Z")
