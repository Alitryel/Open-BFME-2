// Open-BFME5 conversions.

extern char g_bfmeEmptyUVA[];

void bfmeCopyUVA(char *dst, unsigned n, const char *src);

class BfmeThingUVA
{
public:
	void bfmeGoUVA(const char *a, const char *b, const char *c);
	char m_bfmePad[4];
	char *m_bfmeBuf;
};

// BfmeThingUVA::bfmeGoUVA is declared (line 10) but not defined here: only
// bfmeGoUVB is served, and the gate refuses unrowed definitions.

class BfmeLogUVB
{
public:
	virtual void bfmeV0UVB() = 0;
	virtual void bfmeV1UVB() = 0;
	virtual void bfmeV2UVB() = 0;
	virtual void bfmeWarnUVB(const char *msg, const char *file, int line) = 0;
};

BfmeLogUVB *bfmeGetLogUVB(void);

struct BfmeRecUVB
{
	char m_bfmePad[4];
	int m_bfmeKind;
	char m_bfmeText[4];
};

int bfmeConvertUVB(char *out, void **v);
void Rva00655700(char *dst, unsigned n, const char *src);

int bfmeGoUVB(BfmeRecUVB *r, char *out)
{
	if (r->m_bfmeKind == 0) {
		void *v = *(void **)r->m_bfmeText;
		*(void **)&r = v;
		return bfmeConvertUVB(out, (void **)&r);
	}
	if (r->m_bfmeKind == 1) {
		*out = '$';
		Rva00655700(out + 1, 0x13, r->m_bfmeText);
		return 1;
	}
	bfmeGetLogUVB()->bfmeWarnUVB((char *)"false", (char *)"\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp", 0x2e);
	return 0;
}
