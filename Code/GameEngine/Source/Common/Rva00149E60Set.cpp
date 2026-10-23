// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common

// The retail table at RVA 0x007F91B0: 3 slots, each a rowed code owner (the
// next word after slot 2 is not a code address). The name is the consumer's
// spelling; the table has no other owner.
extern "C" {
void __identifier("??_GPartitionFilterRejectByKindOf@@UAEPAXI@Z")();
void __identifier("?allow@PartitionFilterPossibleToAttack@@UAE_NPAVObject@@@Z")();
void __identifier("?Get_File_Handle@FileClass@@UAEPAXXZ")();
}
extern "C" const void *const __identifier("?g_010956C4@@3PAPBXA")[3] = {
	(const void *)&__identifier("??_GPartitionFilterRejectByKindOf@@UAEPAXI@Z"), // slot 0 0x00395A19
	(const void *)&__identifier("?allow@PartitionFilterPossibleToAttack@@UAE_NPAVObject@@@Z"), // slot 1 0x00260FD0
	(const void *)&__identifier("?Get_File_Handle@FileClass@@UAEPAXXZ"), // slot 2 0x0036CC7A
};

extern const void *g_010956C4[];

class Rva00149E60
{
	void *m_00;
	int m_04;
	int m_08;
	int m_0C;
	int m_10;

public:
	Rva00149E60 &set(int a, int b, int c);
};

Rva00149E60 &Rva00149E60::set(int a, int b, int c)
{
	m_08 = b;
	m_04 = 0;
	m_00 = (void *)g_010956C4;
	m_0C = c;
	m_10 = a;
	return *this;
}
