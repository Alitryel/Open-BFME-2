// A record made around an item it then wakes (trimmed from a five-body donor;
// the other four are declared-only here).

class BfmeItemDC;

struct BfmeOpsDC
{
	void (__stdcall *m_bfmeSpare)(BfmeItemDC *item);
	void (__stdcall *m_bfmeDo)(BfmeItemDC *item);
};

struct BfmeItemDC
{
	BfmeOpsDC *m_bfmeOps;			// 0x0
};

class BfmeThingDC
{
public:
	BfmeThingDC(BfmeItemDC *item);

private:
	BfmeItemDC *m_bfmeItem;			// 0x0
};

// ??0BfmeThingDC@@QAE@PAUBfmeItemDC@@@Z
BfmeThingDC::BfmeThingDC(BfmeItemDC *item)
{
	m_bfmeItem = item;

	if (item != 0)
		item->m_bfmeOps->m_bfmeDo(item);
}

class BfmeThingDD
{
public:
	void bfmeGoDD(int first, int second, int third, int fourth);
};

class BfmeThingDF
{
public:
	int bfmeDropDF(void);
};

struct BfmeThingDG;
class BfmeTargetDG;
int __stdcall bfmeAskDG(BfmeThingDG *thing);
int __stdcall bfmeAlsoDG(BfmeThingDG *thing);

// Callers elsewhere reach bodies in this unit through other spellings; retail's
// call sites in their matched rows land on these addresses (same ABI). Bind them.
#pragma comment(linker, "/alternatename:??0W3DRadarResetSurface@@QAE@PAVSurfaceResource@@@Z=??0BfmeThingDC@@QAE@PAUBfmeItemDC@@@Z")
