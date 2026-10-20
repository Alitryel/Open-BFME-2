// _DeringBlockWeak_C
// partial score=0.973788 date=2026-10-20
// _DeringBlockWeak_C
// cl: /O2 /G6 /DNDEBUG /MD
// Approved clean-room specs 001c22c0 and 001c1ad0 plus retail only.
// All weights precede immediate output stores; alias behavior is retained.
// Separate unsigned horizontal-column lifetime, with signed neighbor offsets.
// Not byte exact: native/compiled extent 1526B, alignment 1441/1526,
// 243 fixed-offset differing bytes, first difference +0x63.
// Existing independent-spec oracle passes 2560 native/C++/spec cases.
// See reverse/attempt_support/dering-weak-mixed-counter-20261019/.
// Weight stores index the arrays flat; the vertical and output loops share one unsigned column, and
// each output reads its centre and right pixels first. See reverse/attempt_support/dering-weak-flat-20261020.md.
// One row counter serves all three loops, and each output reads its five pixels before its weights.
// See reverse/attempt_support/dering-weak-rowcounter-20261020.md.
extern "C" int Vp6FilterEdgeTagTable[];

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
			weight = quality + 2 * (16 - difference);
			if (weight < -64)
				weight = sharpen;
			else if (weight < 0)
				weight = 0;
			else if (weight > cap)
				weight = cap;
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

	for (r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			int centerPixel = source[r * pitch + c];
			int rightPixel = source[r * pitch + c + 1];
			int leftPixel = source[r * pitch + c - 1];
			int belowPixel = below[r * pitch + c];
			int abovePixel = above[r * pitch + c];
			int left = horizontal[r * 9 + c];
			int up = vertical[r * 8 + c];
			int down = vertical[r * 8 + c + 8];
			int right = horizontal[r * 9 + c + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * belowPixel + left * leftPixel
				+ right * rightPixel + up * abovePixel + 64) >> 7;
			int pixel;
			if (value < 0) pixel = 0;
			else if (value > 255) pixel = 255;
			else pixel = (int)value;
			destination[r * pitch + c] = (unsigned char)pixel;
		}
	}
}
