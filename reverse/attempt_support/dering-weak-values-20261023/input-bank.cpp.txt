// _DeringBlockWeak_C
// partial score=0.9954 date=2026-10-21
// _DeringBlockWeak_C
// cl: /O2 /G6 /DNDEBUG /MD
// Approved clean-room specs 001c22c0 and 001c1ad0 plus retail only.
// All weights precede immediate output stores; alias behavior is retained.
// Not byte exact: 1526 B (retail size), 7 differing bytes, 7 instructions:
// SIB base/index order of a few stores and one stack-load order. The residue
// follows the function's total count of distinct variables (see
// reverse/attempt_support/dering-weak-offset-20261021.md): row-offset IV as in the
// landed strong twin, plus the ClampWeight helper in the vertical weight loop.
extern "C" int Vp6FilterEdgeTagTable[];

static inline int ClampWeight(int weight, int sharpen, int cap)
{
	if (weight < -64)
		return sharpen;
	if (weight < 0)
		return 0;
	if (weight > cap)
		return cap;
	return weight;
}

extern "C" void __cdecl DeringBlockWeak_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = Vp6FilterEdgeTagTable[qIndex];
	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	unsigned int c;
	int r;

	if (cap > 24)
		cap = 24;

	const unsigned char *vrow = source;
	for (r = 0; r < 9; r++) {
		for (c = 0; c < 8; c++) {
			int difference = (vrow[c] - vrow[c - pitch]) > 0 ? (vrow[c] - vrow[c - pitch]) : (vrow[c - pitch] - vrow[c]);
			int weight;
			weight = ClampWeight(quality + 2 * (16 - difference), sharpen, cap);
			vertical[r * 8 + c] = (short)weight;
		}
		vrow += pitch;
	}
	const unsigned char *hrow = source;
	for (r = 0; r < 8; r++) {
		for (unsigned int hc = 0; hc < 9; hc++) {
			int difference = (hrow[(int)hc] - hrow[(int)hc - 1]) > 0 ? (hrow[(int)hc] - hrow[(int)hc - 1]) : (hrow[(int)hc - 1] - hrow[(int)hc]);
			int weight;
			weight = quality + 2 * (16 - difference);
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			horizontal[r * 9 + (int)hc] = (short)weight;
		}
		hrow += pitch;
	}

	int off = 0;
	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			int centerPixel = source[off + c];
			int rightPixel = source[off + c + 1];
			int leftPixel = source[off + c - 1];
			int left = horizontal[r * 9 + c];
			int up = vertical[r * 8 + c];
			int down = vertical[r * 8 + c + 8];
			int right = horizontal[r * 9 + c + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[off + c] + left * leftPixel
				+ right * rightPixel + up * above[off + c] + 64) >> 7;
			int pixel;
			if (value < 0) pixel = 0;
			else if (value > 255) pixel = 255;
			else pixel = (int)value;
			destination[off + c] = (unsigned char)pixel;
		}
		off += pitch;
	}
}
