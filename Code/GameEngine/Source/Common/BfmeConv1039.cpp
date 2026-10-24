// Open-BFME5 conversions (Go1039C only; Go1039D is the ICF twin and
// Go1039E lives elsewhere -- kept out so the TU holds only claimed bodies).
// Near-miss repair: alloc size 0x34 in BFME1, 0x38 in BFME2.

extern "C" void *bfmeVft1039C[];

class BfmeD1039;

class BfmeC1039
{
public:
	void bfmeInit1039(BfmeD1039 *o);

	void *m_vtable;
};

void *__cdecl operator new(unsigned int size);

class BfmeD1039
{
public:
	BfmeC1039 *Clone(void);
};

BfmeC1039 *BfmeD1039::Clone(void)
{
	BfmeC1039 *mapper = (BfmeC1039 *)::operator new(0x38);

	if (mapper != 0) {
		mapper->bfmeInit1039(this);
		mapper->m_vtable = bfmeVft1039C;
		return mapper;
	}

	return 0;
}

// Retail's data references in this unit's matched rows land on globals defined
// under other spellings at the same addresses (addend-corrected DIR32). Bind them.
#pragma comment(linker, "/alternatename:_bfmeVft1039C=??_7GridWSClassicEnvironmentMapperClass@@6B@")
