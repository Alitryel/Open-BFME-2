// _DeringBlockWeak_C
// partial score=0.8899082568807339 date=2026-10-19
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: approved specs 001c22c0 and 001c1ad0, plus complete retail bytes.
// Full weak deringing: calculate both weight arrays before immediate output stores.
// Vertical row pointers and distinct row-counter lifetimes restore retail's
// loop structure; conditional absolute differences retain the original samples.
// Not exact: 1523 versus 1526 bytes, frame 0x160, first difference +0x40.
// Remaining differences include stack slots, pointer bias and tail scheduling.
// 2560 paired native/C++/published-spec cases pass, including overlapping buffers,
// both pitch signs and all 64 sharpen indices. No external decoder source read.
// Evidence: reverse/attempt_support/dering-weak-bank-20261019/.
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
		for (c = 0; c < 9; c++) {
			int difference = (hrow[c] - hrow[c - 1]) > 0 ? (hrow[c] - hrow[c - 1]) : (hrow[c - 1] - hrow[c]);
			int weight;
			weight = quality + 2 * (16 - difference);
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			hweight[c] = (short)weight;
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
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			destination[r * pitch + c] = (unsigned char)value;
		}
	}
}
