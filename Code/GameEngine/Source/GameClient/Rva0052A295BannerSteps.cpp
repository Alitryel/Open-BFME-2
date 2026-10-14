// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD
// Level-stepped UI tables at retail 0x0052A295..0x0052A34D (names
// address-derived; the tables' meaning is not established):
//  - two static step tables: five {x0, x1, threshold} records at VA
//    0x00C68440 (thresholds 7, 9, 18, 20) and three {value, threshold}
//    records at VA 0x00C6847C (thresholds 7, 18);
//  - 0x0052A295 (34B): the first record whose threshold exceeds the level
//    (the last one past them all);
//  - 0x0052A2B7 (75B): with a banner UI (VA 0x00DFE32C), set its two slot
//    x offsets from that record through the rowed
//    BannerUI::SetBannerSlotXOffset 0x00216670;
//  - 0x0052A321 (44B): set TheInGameUI's float field (rowed
//    Rva0029A767FloatField::set 0x0029A767) to the second table's value
//    for the level.
// The second table's own standalone lookup 0x0052A302 returns its float in
// xmm0 (a private convention) and is not claimed here.
struct Rva0052A295Step
{
	float x[2];
	int threshold;
};

struct Rva0052A321Step
{
	float value;
	int threshold;
};

extern const Rva0052A295Step g_Va00C68440[5];
extern const Rva0052A321Step g_Va00C6847C[3];

class BannerUI
{
public:
	void SetBannerSlotXOffset(unsigned int index, float value);
};
extern BannerUI *g_00DFE32C;

class Rva0029A767FloatField
{
public:
	void set(float value);
};
class InGameUI;
extern InGameUI *TheInGameUI;

static __forceinline const Rva0052A295Step *findBannerStep(int level)
{
	unsigned int i;
	for (i = 0; i < 4; ++i)
	{
		if (level < g_Va00C68440[i].threshold)
			break;
	}
	return &g_Va00C68440[i];
}

static inline float findScaleStep(int level)
{
	unsigned int i;
	for (i = 0; i < 2; ++i)
	{
		if (level < g_Va00C6847C[i].threshold)
			break;
	}
	return g_Va00C6847C[i].value;
}

const Rva0052A295Step *Rva0052A295(int level)
{
	return findBannerStep(level);
}

void Rva0052A2B7(int level)
{
	if (g_00DFE32C == 0)
		return;
	const Rva0052A295Step *step = findBannerStep(level);
	for (unsigned int i = 0; i < 2; ++i)
		g_00DFE32C->SetBannerSlotXOffset(i, step->x[i]);
}

void Rva0052A321(int level)
{
	((Rva0029A767FloatField *)TheInGameUI)->set(findScaleStep(level));
}
