// ?Rva0073C450Fill@@YADPAH0HVRva0073BB40@@@Z
// partial score=0.097 date=2026-10-17
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
// ?Rva0073C3B0Raster@@YADHHHVRva0073BAA0Base@@@Z @0x0073C3B0 155B: shroud circle raster decrement twin via rowed 0x0073BB40.
// Same midpoint-circle shape as 0x0073BF40 (donor taintmanager_impl.cpp bfmeRasterCircleFC);
// per-row gate is the rowed rva0073BB40 decrement updater, checked with 1 on full sweep 0 on early out.
// Caller 0x0073CD2A; unblocks 0x0073CCC0.
class BfmeCellFD;

class Gen_008F7CD0
{
public:
	void rva0073A2A0(BfmeCellFD **first, BfmeCellFD **last, int x1, int x2, int y);
};

class ShroudManagerImpl;
class ShroudManagerImpl008FBA40Element;

class Rva0073BB40
{
public:
	virtual char testFunc(int x, int y);
	char rva0073BB40(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

inline int crop_round(int v)
{
	return v;
}

char Rva0073C450Fill(int *a, int *b, int n, Rva0073BB40 cell)
{
	int m;
	int i;
	int nCopy = *(volatile int*)&n;
	int *bCopy = b;
	m = 1;
	for (i = 1; i < nCopy; i++)
	{
		int av = a[i];
		int am = a[m - 1];
		int bv = bCopy[i];
		int bm = bCopy[m - 1];
		if (av != am || bv != bm)
		{
			a[m] = av;
			b[m] = bv;
			m++;
		}
	}
	n = m;

	while (n > 2 && a[0] == a[n - 1] && b[0] == b[n - 1])
		n--;

	if (n < 3)
		return 1;

	int idx = 0;
	int iScan;
	for (iScan = 1; iScan < n; iScan++)
	{
		if (b[iScan] < b[idx] || (b[iScan] == b[idx] && a[iScan] < a[idx]))
			idx = iScan;
	}
	i = idx;

	int yA = b[idx];
	int i0 = idx;
	int iPrev = (i0 != 0) ? i0 - 1 : n - 1;

	int dB = b[iPrev] - b[i0];
	int& dyB = dB;
	int yTop = a[iPrev];
	int yBot = a[i0];

	int slopeB = dyB;
	if (dyB > 0)
	{
		slopeB = ((yTop - yBot) << 8) / dyB;
	}

	int xFrac = 0;
	if (dyB > 0)
	{
		xFrac = (yBot << 8) + crop_round(slopeB);
	}

	i0 = (i0 != 0) ? i0 - 1 : n - 1;

	int prev;
	while ((prev = (idx + 1 == n) ? 0 : idx + 1), b[idx] == b[prev])
		idx = prev;

	int j = idx;
	int jNext = (j + 1 == n) ? 0 : j + 1;
	int jNext2 = (j + 1 == n) ? 0 : j + 1;

	int dC = b[jNext] - b[j];
	int& dyC = dC;
	int yTop2 = a[jNext2];
	int yBot2 = a[j];

	int slopeC = dyC;
	if (dyC > 0)
	{
		slopeC = ((yTop2 - yBot2) << 8) / dyC;
	}

	int xFrac2 = 0;
	if (dyC > 0)
	{
		xFrac2 = ((yBot2 << 8) + crop_round(slopeC));
	}
	else
	{
		xFrac2 = 0;
	}

	int slopeB_first = slopeB;

	char ok = cell.rva0073BB40((xFrac + 0x80) >> 8, (slopeB_first + 0x80) >> 8, iPrev);
	if (!ok)
		return 0;

	while (true)
	{
		xFrac += slopeC;
		slopeB--;
		iPrev++;
		if (slopeB == 0)
		{
			i0 = (i0 != 0) ? i0 - 1 : n - 1;
			int cur = i0;
			int nxt = (cur != 0) ? cur - 1 : n - 1;
			int e = b[cur];
			int eTop = b[nxt];
			int f = a[cur];
			int fTop = a[nxt];
			int dB2 = eTop - e;
			if (dB2 > 0)
			{
				slopeB = ((fTop - f) << 8) / dB2;
				xFrac = (f << 8) + crop_round(slopeB_first);
			}
			if (dB2 < 0)
				return 0;
		}

		xFrac2 += slopeC;
		dyC--;
		if (dyC == 0)
		{
			j = (j + 1 == n) ? 0 : j + 1;
			int jn = (j + 1 == n) ? 0 : j + 1;
			int dC2 = b[jn] - b[j];
			if (dC2 > 0)
			{
				slopeC = ((a[jn] - a[j]) << 8) / dC2;
				xFrac2 = (a[j] << 8) + crop_round(slopeC);
			}
			if (dC2 < 0)
				return 0;
		}

		ok = cell.rva0073BB40((xFrac + 0x80) >> 8, (xFrac2 + 0x80) >> 8, iPrev);
		if (!ok)
			return 0;
	}
	return 1;
}
