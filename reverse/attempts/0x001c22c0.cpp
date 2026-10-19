// _DeringBlockWeak_C
// partial score=0.944298820445609 date=2026-10-19
// _DeringBlockWeak_C
// cl: /O2 /G6 /DNDEBUG /MD
// Approved clean-room specs 001c22c0 and 001c1ad0 plus retail only.
// All weights precede immediate output stores; alias behavior is retained.
// Separate unsigned horizontal-column lifetime, with signed neighbor offsets.
// Not byte exact: native/compiled extent 1526B, alignment 1441/1526,
// 243 fixed-offset differing bytes, first difference +0x63.
// Existing independent-spec oracle passes 2560 native/C++/spec cases.
// See reverse/attempt_support/dering-weak-mixed-counter-20261019/.
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
	int c;

	if (cap > 24)
		cap = 24;

	const unsigned char *vrow = source;
	short *vweight = vertical;
	for (int r = 9; r != 0; --r) {
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
			vweight[c] = (short)weight;
		}
		vrow += pitch;
		vweight += 8;
	}
	const unsigned char *hrow = source;
	short *hweight = horizontal;
	for (int r = 8; r != 0; --r) {
		for (unsigned int hc = 0; hc < 9; hc++) {
			int difference = (hrow[(int)hc] - hrow[(int)hc - 1]) > 0 ? (hrow[(int)hc] - hrow[(int)hc - 1]) : (hrow[(int)hc - 1] - hrow[(int)hc]);
			int weight;
			weight = quality + 2 * (16 - difference);
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			hweight[(int)hc] = (short)weight;
		}
		hrow += pitch;
		hweight += 9;
	}

	for (int r = 0; r < 8; r++) {
		for (c = 0; c < 8; c++) {
			int up = vertical[r * 8 + c];
			int down = vertical[r * 8 + c + 8];
			int left = horizontal[r * 9 + c];
			int right = horizontal[r * 9 + c + 1];
			int value = ((128 - right - down - up - left) * source[r * pitch + c]
				+ down * below[r * pitch + c] + left * source[r * pitch + c - 1]
				+ right * source[r * pitch + c + 1] + up * above[r * pitch + c] + 64) >> 7;
			int pixel;
			if (value < 0) pixel = 0;
			else if (value > 255) pixel = 255;
			else pixel = (int)value;
			destination[r * pitch + c] = (unsigned char)pixel;
		}
	}
}
