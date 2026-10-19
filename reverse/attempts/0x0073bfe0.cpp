// ?Rva0073BFE0Raster@@YADPAH0HVRva0073BAA0Base@@@Z
// partial score=0.45 date=2026-10-19
// cl: /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB /DBFME_STLP_NODE_ALLOC /D_STLP_NO_EXCEPTIONS /Ireference/shims/stlp_nodealloc
class Gen_008F7CD0;
class Rva0073BAA0Base
{
public:
	virtual char testFunc(int x, int y);
	char rva0073BAA0(int x1, int x2, int y);
private:
	Gen_008F7CD0 *m_grid;
	unsigned int m_mask;
};

struct RasterEdge
{
#define value f[0]
#define step f[1]
#define remaining f[2]
	int f[3];
	__forceinline void set(const int *xs, const int *ys, int from, int to)
	{
		remaining = ys[to] - ys[from];
		if (remaining > 0)
		{
			step = ((xs[to] - xs[from]) << 8) / remaining;
			value = (xs[from] << 8) + step / 2;
		}
	}
	__forceinline int x() const { return (value + 128) / 256; }
};
#define PREV(i) ((i) ? (i) - 1 : count - 1)
#define NEXT(i) ((i) + 1 == count ? 0 : (i) + 1)

char __cdecl Rva0073BFE0Raster(int *xs, int *ys, int count, Rva0073BAA0Base updater)
{
	int kept = 1;
	for (int i = 1; i < count; ++i)
	{
		if (xs[i] != xs[kept - 1] || ys[i] != ys[kept - 1])
		{
			xs[kept] = xs[i];
			ys[kept] = ys[i];
			++kept;
		}
	}
	count = kept;
	while (count > 2 && xs[0] == xs[count - 1] && ys[0] == ys[count - 1])
		--count;
	if (count < 3)
		return 1;

	int top = 0;
	for (int i = 1; i < count; ++i)
	{
		if (ys[i] < ys[top] || (ys[i] == ys[top] && xs[i] < xs[top]))
			top = i;
	}

	int y = ys[top];
	RasterEdge leftEdge;
	leftEdge.set(xs, ys, top, PREV(top));
	int left = PREV(top);
	while (ys[top] == ys[NEXT(top)])
		top = NEXT(top);
	RasterEdge rightEdge;
	rightEdge.set(xs, ys, top, NEXT(top));
	int right = NEXT(top);

	if (!updater.rva0073BAA0(leftEdge.x(), rightEdge.x(), y))
		return 0;
	for (;;)
	{
		leftEdge.value += leftEdge.step;
		++y;
		if (--leftEdge.remaining == 0)
		{
			do
			{
				leftEdge.set(xs, ys, left, PREV(left));
				left = PREV(left);
				if (leftEdge.remaining < 0)
					return 1;
			} while (leftEdge.remaining == 0);
		}
		rightEdge.value += rightEdge.step;
		if (--rightEdge.remaining == 0)
		{
			do
			{
				rightEdge.set(xs, ys, right, NEXT(right));
				right = NEXT(right);
				if (rightEdge.remaining < 0)
					return 1;
			} while (rightEdge.remaining == 0);
		}
		if (!updater.rva0073BAA0(leftEdge.x(), rightEdge.x(), y))
			return 0;
	}
}
