// Open-BFME5 conversions.
// Trimmed subset of the BFME1 donor: only BfmeThingTA::bfmeGoTA is defined
// here. The donor also defines BfmeThingSG::bfmeGoSG and BfmeThingTB::bfmeGoTB,
// which this ledger does not declare, so they are omitted (see Rva00885920
// precedent: declare-only would also work, omission is simpler).

class Gen_00832090
{
public:
	void m();
};

extern char g_bfmeVftTA[];
void __cdecl operator delete[](void *block);

class BfmeThingTA
{
public:
	void bfmeGoTA();
	char *m_bfmeVft;
	char m_bfmePad[8];
	void *m_bfmeP;
	char m_bfmeFlag;
};

void BfmeThingTA::bfmeGoTA()
{
	m_bfmeVft = g_bfmeVftTA;
	if (m_bfmeFlag)
		::operator delete[](m_bfmeP);
	((Gen_00832090 *)this)->m();
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:?g_bfmeVftTA@@3PADA=??_7?$ctype@D@_STL@@6B@")
