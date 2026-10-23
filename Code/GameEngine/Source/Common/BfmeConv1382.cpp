// Open-BFME5 conversions.

class BfmeMsgVJC
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
	void addInt(const char *key, int value);
};

class Rva007F1800Search
{
public:
	void serialize(Rva007E8810Message *message, int count, void *data);
};

extern void *g_bfmeVJC;
// g_bfmeVJC: matched references place it at VA 0xe09ff8 (zero-filled .bss).
void * g_bfmeVJC;

class BfmeThingVJC
{
public:
	void bfmeGoVJC(BfmeMsgVJC *m, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *a, void *b);
};

void BfmeThingVJC::bfmeGoVJC(BfmeMsgVJC *m, int ratingMin, int ratingMax, int downloadMin, int downloadMax, void *a, void *b)
{
	void *g = g_bfmeVJC;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m,
		(int)(unsigned long)a, b);
	if (ratingMin > -1)
		((Rva007E8810Message *)m)->addInt("ratingMin", ratingMin);
	if (ratingMax > -1)
		((Rva007E8810Message *)m)->addInt("ratingMax", ratingMax);
	if (downloadMin > -1)
		((Rva007E8810Message *)m)->addInt("downloadMin", downloadMin);
	if (downloadMax > -1)
		((Rva007E8810Message *)m)->addInt("downloadMax", downloadMax);
}

extern void *g_bfmeVJD;
// g_bfmeVJD: matched references place it at VA 0xe0a034 (zero-filled .bss).
void * g_bfmeVJD;

class BfmeThingVJD
{
public:
	void bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b);
};

void BfmeThingVJD::bfmeGoVJD(BfmeMsgVJC *m, int ratingMin, int ratingMax, int topN, int periodType, int periodsPast, void *b)
{
	void *g = g_bfmeVJD;
	((Rva007E8810Message *)m)->reset();
	m->m_bfme1c = 0x626c6f62;
	((Rva007E8810Message *)m)->addString("TXN", (const char *)g);
	((Rva007F1800Search *)this)->serialize((Rva007E8810Message *)m,
		topN, b);
	if (ratingMin > -1)
		((Rva007E8810Message *)m)->addInt("ratingMin", ratingMin);
	if (ratingMax > -1)
		((Rva007E8810Message *)m)->addInt("ratingMax", ratingMax);
	if (topN > 0)
		((Rva007E8810Message *)m)->addInt("topN", topN);
	if (periodType > -1)
		((Rva007E8810Message *)m)->addInt("periodType", periodType);
	if (periodsPast > -1)
		((Rva007E8810Message *)m)->addInt("periodsPast", periodsPast);
}
