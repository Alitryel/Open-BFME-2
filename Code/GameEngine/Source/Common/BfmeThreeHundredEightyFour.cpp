struct BfmeKeyAEA
{
	unsigned char m_bfmeHead[4];
	void *m_bfmeId;
};

// The player browser passes its player record and transaction through this
// lookup; the matched handler at 0x0066DAE0 consumes that same pair.
#pragma comment(linker, "/alternatename:?bfmeHitAEA@BfmeEntryAEA@@QAE_NPAUBfmeKeyAEA@@PAX@Z=?bfmeHit1173@BfmeE1173@@QAE_NPAX0@Z")

class BfmeEntryAEA
{
public:
	bool bfmeHitAEA(BfmeKeyAEA *key, void *extra);
	unsigned char m_bfmeHead[8];
	void *m_bfmeId;
	unsigned char m_bfmeRest[0x74];
};

class BfmeThingAEA
{
public:
	bool bfmeFindAEA(BfmeKeyAEA *key, void *extra);
	unsigned char m_bfmeHead[0x1c];
	BfmeEntryAEA *m_bfmeBase;
	int m_bfmeCount;
};

bool BfmeThingAEA::bfmeFindAEA(BfmeKeyAEA *key, void *extra)
{
	BfmeEntryAEA *at = m_bfmeBase;
	BfmeEntryAEA *end = at + m_bfmeCount;
	void *want = key->m_bfmeId;
	while (at < end)
	{
		if (at->m_bfmeId == want)
			return at->bfmeHitAEA(key, extra);
		++at;
	}
	return false;
}
