// Open-BFME5 conversions.

class BfmeMsgVIX
{
public:
	char m_bfmePad[0x1c];
	int m_bfme1c;
};

class Rva007E8810Message
{
public:
	void reset();
	void addString(const char *key, const char *value);
	void addInt64(const char *key, __int64 value);
	void addBool(const char *key, bool value);
	void rva007E8EF0(const char *key, const char *value);
};

extern void *g_bfmeFVIX;
// g_bfmeFVIX: matched references place it at VA 0xe09ec8 (zero-filled .bss).
void * g_bfmeFVIX;
extern void *g_bfmeGVIY;
// g_bfmeGVIY: matched references place it at VA 0xe0a028 (zero-filled .bss).
void * g_bfmeGVIY;

void __stdcall bfmeGoVIX(BfmeMsgVIX *m, void *email, void *parentalEmail, void *countryCode, void *eaMail, void *thirdPartyMail)
{
	void *g = g_bfmeFVIX;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x61636374;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007E8810Message *)m)->addString("email", (const char *)email);
	((Rva007E8810Message *)m)->addString("parentalEmail", (const char *)parentalEmail);
	((Rva007E8810Message *)m)->addString("countryCode", (const char *)countryCode);
	((Rva007E8810Message *)m)->addBool("eaMailFlag", *(bool *)&eaMail);
	((Rva007E8810Message *)m)->addBool("thirdPartyMailFlag", *(bool *)&thirdPartyMail);
}

class BfmeThingVIY
{
public:
	void bfmeGoVIY(BfmeMsgVIX *m, void *a, void *b, void *c, void *d, void *e);
	void bfmeSubVIY(BfmeMsgVIX *m, void *c, void *d);
};

class Rva007EFFC0Allocator
{
public:
	virtual void v0();
	virtual void v1();
	virtual void *allocate(int size, int flags);
	virtual void release(void *block, int flags);
};

struct Rva007EB810Diag
{
public:
	virtual void v0();
	virtual void v1();
	virtual void __cdecl assertValue(void *value, const char *message);
	virtual void fail(const char *expr, const char *file, int line);
};

class BfmeThingCIB
{
public:
	void bfmeGoCIB(void *one, void *two);
	unsigned char m_bfmeHead[0x10];
	void *m_bfmeA;
	void *m_bfmeB;
	unsigned char m_bfmeGap[0xc];
	int m_bfmeErr;
};

extern Rva007EB810Diag *Rva007EB810Get();
class GenAlloc;
GenAlloc *Gen007EFFC0();
void rva007FF100Encode(unsigned int length, const char *source, void *destination);

void BfmeThingVIY::bfmeGoVIY(BfmeMsgVIX *m, void *a, void *b, void *c, void *d, void *e)
{
	void *g = g_bfmeGVIY;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007E8810Message *)m)->addInt64("blobId", *(__int64 *)&a);
	bfmeSubVIY(m, c, d);
	((Rva007E8810Message *)m)->addString("version", (const char *)e);
}

void BfmeThingVIY::bfmeSubVIY(BfmeMsgVIX *m, void *c, void *d)
{
	Rva007EFFC0Allocator *allocator = (Rva007EFFC0Allocator *)Gen007EFFC0();
	unsigned int length = (unsigned int)d;
	unsigned int size = ((length + 2) / 3) * 4 + 1;
	void *content = allocator->allocate(size, 2);
	if (content == 0)
	{
		Rva007EB810Diag *diag = Rva007EB810Get();
		diag->assertValue(content, "--- out of memory\n");
		Rva007EB810Get()->fail("false",
			"\\views\\feslbuild_main\\jabba\\fesl\\source\\blobservice.cpp",
			0x17c);
		return;
	}
	rva007FF100Encode(length, (const char *)c, content);
	((Rva007E8810Message *)m)->rva007E8EF0("content", (const char *)content);
	((Rva007EFFC0Allocator *)Gen007EFFC0())->release(content, 0);
	((BfmeThingCIB *)m)->bfmeGoCIB((void *)"size", d);
}
