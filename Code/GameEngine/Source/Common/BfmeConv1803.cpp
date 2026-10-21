// flags: region default (reverse/retail_inventory/flag_regions.csv)
//
// Ported from Open-BFME-1 GameEngine/Source/Common/BfmeConv1803.cpp
// (donor revision 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled that way each body
// places uniquely on unclaimed game.dat .text by masked whole-.text search:
//   ??0BfmeOwnerZQ@@QAE@PAX000@Z 0x000EF272 (40B)
// Callee addresses are read off retail call sites (reverse/symbols.csv).
extern int BfmeVfZQ[18];

// ?BfmeVfZQ@@3PAHA @ VA 0x00BCEEF0 (RVA 0x007CEEF0), 72 B, .rdata.
//
// The 18-word table this constructor stores in its first field. The ledger has
// it unowned and 72 bytes long; each word was read back from the image and is
// the address of a matched retail function (several addresses are /OPT:ICF
// folds, so more than one ledger row resolves there; any one of them
// reproduces the same DIR32). A non-const definition lands in .data though
// retail keeps the table in .rdata; the 18 DIR32s are the same.
extern "C" {
void __identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ")();
void __identifier("?PreLoad@Factory@TextureAsset@@QAEXXZ")();
void __identifier("?rva00131CD3@Rva00131CD3Forwarder@@QAEXXZ")();
void __identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ")();
void __identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z")();
void __identifier("?Rva000B3FD0@@YAXHQAPAD@Z")();
void __identifier("?rva00133380@Rva00131BE5@@QAEXXZ")();
void __identifier("?Delete@AssetFactoryBase@@UAEXXZ")();
void __identifier("??_GRva002DB8BA@@UAEPAXI@Z")();
void __identifier("?rva00131CF2@Rva00131CF2@@QAE_NXZ")();
void __identifier("?method@Rva009EB8A0@@QAEXXZ")();
void __identifier("?UnloadNow@BfmeE1024@@QAEXXZ")();
void __identifier("?Rva000EF29AGet@@YAHXZ")();
void __identifier("?rva00131CDB@Rva00131CDB@@QBEIXZ")();
void __identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z")();
void __identifier("?rva000EF961@Rva000EF961@@QAEXH@Z")();
void __identifier("?IsCRC@Xfer@@UBE_NXZ")();
}

extern int BfmeVfZQ[18] =
{
	(int)(void *)&__identifier("?bfmeGo1035G@BfmeG1035@@QAEPADXZ"),
	(int)(void *)&__identifier("?PreLoad@Factory@TextureAsset@@QAEXXZ"),
	(int)(void *)&__identifier("?rva00131CD3@Rva00131CD3Forwarder@@QAEXXZ"),
	(int)(void *)&__identifier("?bfmeGo937B@BfmeThing937B@@QAEXXZ"),
	(int)(void *)&__identifier("?DoXfer@EmissionVelocityInfo@FXParticleSystem@@UAEXAAVXfer@@@Z"),
	(int)(void *)&__identifier("?Rva000B3FD0@@YAXHQAPAD@Z"),
	(int)(void *)&__identifier("?Rva000B3FD0@@YAXHQAPAD@Z"),
	(int)(void *)&__identifier("?rva00133380@Rva00131BE5@@QAEXXZ"),
	(int)(void *)&__identifier("?Delete@AssetFactoryBase@@UAEXXZ"),
	(int)(void *)&__identifier("??_GRva002DB8BA@@UAEPAXI@Z"),
	(int)(void *)&__identifier("?rva00131CF2@Rva00131CF2@@QAE_NXZ"),
	(int)(void *)&__identifier("?method@Rva009EB8A0@@QAEXXZ"),
	(int)(void *)&__identifier("?UnloadNow@BfmeE1024@@QAEXXZ"),
	(int)(void *)&__identifier("?Rva000EF29AGet@@YAHXZ"),
	(int)(void *)&__identifier("?rva00131CDB@Rva00131CDB@@QBEIXZ"),
	(int)(void *)&__identifier("?rva005CB9FF@Rva005CB9FF@@QAE_NH@Z"),
	(int)(void *)&__identifier("?rva000EF961@Rva000EF961@@QAEXH@Z"),
	(int)(void *)&__identifier("?IsCRC@Xfer@@UBE_NXZ"),
};

// The base constructor is rowed as ??0Rva00131BE5 (WW3D2/Rva00131BE5Ctor.cpp).
class Rva00131BE5
{
public:
	Rva00131BE5(void *first, void *second, void *third, void *fourth, int fifth, int sixth);
};

class BfmeOwnerZQ
{
public:
	BfmeOwnerZQ(void *first, void *second, void *third, void *fourth);

	void *m_bfmeVfZQ;
	char unknown04[0x3C-4];
};

BfmeOwnerZQ::BfmeOwnerZQ(void *first, void *second, void *third, void *fourth)
{
	((Rva00131BE5 *)this)->Rva00131BE5::Rva00131BE5(first, second, third, fourth, 1, 0);
	m_bfmeVfZQ = &BfmeVfZQ[0];

}

// Target EF902..EF961 independently proves this is the constructor of a
// newly allocated3C-byte texture resource: four constructor arguments are
// height,width,format,3 and its result is adopted by the existing retaining
// setterEF87B. The old BF1-derived bfmeInitZQ spelling represented exactly
// this body as an initialization method. Rename its sole owner to the
// constructor and keep its complete40B bytes; no alias or added coverage.
// The class name and six-argument base initializer remain donor placeholders.
