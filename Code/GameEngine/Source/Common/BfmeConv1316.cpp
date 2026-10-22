// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1316.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ??0BfmeThingTKB@@QAE@XZ 0x000EF7A1 (23B)
//   ?bfmeGoTKD@@YAXNH@Z 0x00069130 (22B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
// Open-BFME5 conversions.

extern char g_bfmeInfoTKB[];
extern void *g_bfmeVftTKB[];

// Retail RVA 0x007CEF38 (.rdata, 72 B): the 18-word table the constructor
// installs at +0. Every slot is the address of a matched retail row; slots 5
// and 6 are an /OPT:ICF fold of the Region2D destructor, and slot 4 is the
// folded Xfer::DoXfer body.
extern "C" {
void __identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ")();
void __identifier("?PreLoad@Factory@TextureAsset@@QAEXXZ")();
void __identifier("?rva00131CD3@Rva00131CD3Forwarder@@QAEXXZ")();
void __identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("??1Region2D@@QAE@XZ")();
void __identifier("?rva00133380@Rva00131BE5@@QAEXXZ")();
void __identifier("?Delete@AssetFactoryBase@@UAEXXZ")();
void __identifier("??_GRva002DB8BA@@UAEPAXI@Z")();
void __identifier("?rva00131CF2@Rva00131CF2@@QAE_NXZ")();
void __identifier("?method@Rva009EB8A0@@QAEXXZ")();
void __identifier("?UnloadNow@BfmeE1024@@QAEXXZ")();
void __identifier("?Rva000EF29AGet@@YAHXZ")();
void __identifier("?rva00131CDB@Rva00131CDB@@QBEIXZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva000EF7B8@Rva000EF7B8Texture@@UAEXH@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}

void *g_bfmeVftTKB[18] =
{
	(void *)&__identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ"),
	(void *)&__identifier("?PreLoad@Factory@TextureAsset@@QAEXXZ"),
	(void *)&__identifier("?rva00131CD3@Rva00131CD3Forwarder@@QAEXXZ"),
	(void *)&__identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ"),
	(void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(void *)&__identifier("??1Region2D@@QAE@XZ"),
	(void *)&__identifier("??1Region2D@@QAE@XZ"),
	(void *)&__identifier("?rva00133380@Rva00131BE5@@QAEXXZ"),
	(void *)&__identifier("?Delete@AssetFactoryBase@@UAEXXZ"),
	(void *)&__identifier("??_GRva002DB8BA@@UAEPAXI@Z"),
	(void *)&__identifier("?rva00131CF2@Rva00131CF2@@QAE_NXZ"),
	(void *)&__identifier("?method@Rva009EB8A0@@QAEXXZ"),
	(void *)&__identifier("?UnloadNow@BfmeE1024@@QAEXXZ"),
	(void *)&__identifier("?Rva000EF29AGet@@YAHXZ"),
	(void *)&__identifier("?rva00131CDB@Rva00131CDB@@QBEIXZ"),
	(void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"),
	(void *)&__identifier("?rva000EF7B8@Rva000EF7B8Texture@@UAEXH@Z"),
	(void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
};

// Retail RVA 0x007CEF80 (.rdata, 20 B): the 16-byte chunk name the
// constructor hands to bfmeBaseSJ followed by the image's four trailing
// bytes, which no ledger row names.
char g_bfmeInfoTKB[20] =
{
	'E','X','S','c','o','r','c','h','0','1','.','t','g','a',0,0,
	(char)0xf3,(char)0x4f,(char)0xc3,(char)0xc7,
};

// The retail call target 0x000664BE is the matched row
// ?Rva006C5BE0@@YANNH@Z; the unit keeps its own spelling of the callee.
#pragma comment(linker, "/alternatename:?bfmeStepTKD@@YAXNH@Z=?Rva006C5BE0@@YANNH@Z")

// The constructor's retail call target 0x001320D0 is the matched row
// ??0BfmeThingSJ@@QAE@H@Z, which the port spells as the member helper.
#pragma comment(linker, "/alternatename:?bfmeBaseSJ@BfmeThingSJ@@QAEXH@Z=??0BfmeThingSJ@@QAE@H@Z")

// The retail call target at 0x0090E3D0 is the already-matched BfmeThingSJ
// member helper ?bfmeBaseSJ@BfmeThingSJ@@QAEXH@Z; spell the reference with
// its defining mangling (a plain member call through this, which leaves
// `this` already in ecx and therefore compiles to the same bytes).
class BfmeThingSJ
{
public:
	void bfmeBaseSJ(int what);
};

class BfmeThingTKB
{
public:
	BfmeThingTKB();
	void *m_bfmeVft;
};

BfmeThingTKB::BfmeThingTKB()
{
	reinterpret_cast<BfmeThingSJ *>(this)->bfmeBaseSJ(reinterpret_cast<int>(g_bfmeInfoTKB));
	m_bfmeVft = g_bfmeVftTKB;
}

void bfmeStepTKD(double d, int a);

void bfmeGoTKD(double d, int a)
{
	bfmeStepTKD(d, a);
}
