// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common
class BfmeTmpCF
{
public:
	BfmeTmpCF(void);
	~BfmeTmpCF();

	void bfmeRunCF(void *first, void *second);

	unsigned char m_bfmeHeadCF[0x24];
};

void __cdecl bfmeMakeCF(void *first, void *second)
{
	BfmeTmpCF tmp;

	tmp.bfmeRunCF(first, second);
}

// Each retail call in this body reads an address the ledger already carries
// under the rowed name below. Bind the donor spelling to that owner so one
// address keeps one definition and the unit links.
//   0x001E86D0 reads ??1Rva001E7087@@MAE@XZ
#pragma comment(linker, "/alternatename:??1BfmeTmpCF@@QAE@XZ=??1Rva001E7087@@MAE@XZ")
//   0x001EA3AE reads ?rva001EA3AE@Rva001EA2CFLocomotorDefinition@@QAEXPAVINI@@PAVThingTemplate@@@Z
#pragma comment(linker, "/alternatename:?bfmeRunCF@BfmeTmpCF@@QAEXPAX0@Z=?rva001EA3AE@Rva001EA2CFLocomotorDefinition@@QAEXPAVINI@@PAVThingTemplate@@@Z")
//   0x001E7087 reads ??0Rva001E7087@@QAE@XZ
#pragma comment(linker, "/alternatename:??0BfmeTmpCF@@QAE@XZ=??0Rva001E7087@@QAE@XZ")
