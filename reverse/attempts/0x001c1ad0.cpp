// _DeringBlockStrong_C
// partial score=0.814778 date=2026-10-20
// cl: /O2 /G6 /DNDEBUG /MD
// Clean-room specs 001c1ad0 and 001c22c0, plus complete retail disassembly.
// The weak sibling's row-pointer weight loops also restore the strong loop shape.
// Keep all eight clipped outputs in the row buffer before any destination store.
// Not exact: 2046 versus 2030 bytes, frame0x174 versus0x178; first diff+2.
// Actual whole-body byte alignment after the real sharpen-table relocation is
// 1633/2030=.804433. Stack/register allocation and instruction scheduling differ.
// No external decoder source was consulted. Evidence: dering-strong-followup-20261019.
// Weight stores index the arrays flat (row * 8 + column, row * 9 + column), which puts
// retail's store cursors at +1 element; up weights read through their own base pointer.
// Not exact: 2046 versus 2030 bytes, frame 0x174 versus 0x178. Evidence:
// reverse/attempt_support/dering-strong-cursor-20261020.md. No decoder source consulted.
extern "C" int Vp6FilterEdgeTagTable[];

extern "C" void __cdecl DeringBlockStrong_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = Vp6FilterEdgeTagTable[qIndex];
	const unsigned char *above = source - pitch;
	const unsigned char *below = source + pitch;
	int cap = 3 * quality;
	short vertical[72];
	short horizontal[72];
	int r;
	unsigned int c;

	if (cap > 32)
		cap = 32;

	const unsigned char *vrow = source;
	for (r = 0; r < 9; r++) {
		for (c = 0; c < 8; c++) {
			int difference = (vrow[c] - vrow[c - pitch]) > 0 ? (vrow[c] - vrow[c - pitch]) : (vrow[c - pitch] - vrow[c]);
			int weight;
			weight = quality - difference + 32;
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
		for (c = 0; c < 9; c++) {
			int difference = (hrow[c] - hrow[c - 1]) > 0 ? (hrow[c] - hrow[c - 1]) : (hrow[c - 1] - hrow[c]);
			int weight;
			weight = quality - difference + 32;
			if (weight < -64) weight = sharpen;
			else if (weight < 0) weight = 0;
			else if (weight > cap) weight = cap;
			horizontal[r * 9 + c] = (short)weight;
		}
		hrow += pitch;
	}

	short *downWeights = vertical + 8;
	short *upWeights = vertical;
	// Keep all eight outputs separate until the entire source row is read.
	for (r = 0; r < 8; r++) {
		int temp[8];
		{
			int centerPixel = source[r * pitch + 0];
			int rightPixel = source[r * pitch + 0 + 1];
			int right = horizontal[r * 9 + 0 + 1];
			int left = horizontal[r * 9 + 0];
			int down = downWeights[r * 8 + 0];
			int up = upWeights[r * 8 + 0];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 0] + left * source[r * pitch + 0 - 1]
				+ up * above[r * pitch + 0] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[0] = 0;
			else if (value > 255) temp[0] = 255;
			else temp[0] = value;
		}
		{
			int centerPixel = source[r * pitch + 1];
			int rightPixel = source[r * pitch + 1 + 1];
			int right = horizontal[r * 9 + 1 + 1];
			int left = horizontal[r * 9 + 1];
			int down = downWeights[r * 8 + 1];
			int up = upWeights[r * 8 + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 1] + left * source[r * pitch + 1 - 1]
				+ up * above[r * pitch + 1] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[1] = 0;
			else if (value > 255) temp[1] = 255;
			else temp[1] = value;
		}
		{
			int centerPixel = source[r * pitch + 2];
			int rightPixel = source[r * pitch + 2 + 1];
			int right = horizontal[r * 9 + 2 + 1];
			int left = horizontal[r * 9 + 2];
			int down = downWeights[r * 8 + 2];
			int up = upWeights[r * 8 + 2];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 2] + left * source[r * pitch + 2 - 1]
				+ up * above[r * pitch + 2] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[2] = 0;
			else if (value > 255) temp[2] = 255;
			else temp[2] = value;
		}
		{
			int centerPixel = source[r * pitch + 3];
			int rightPixel = source[r * pitch + 3 + 1];
			int right = horizontal[r * 9 + 3 + 1];
			int left = horizontal[r * 9 + 3];
			int down = downWeights[r * 8 + 3];
			int up = upWeights[r * 8 + 3];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 3] + left * source[r * pitch + 3 - 1]
				+ up * above[r * pitch + 3] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[3] = 0;
			else if (value > 255) temp[3] = 255;
			else temp[3] = value;
		}
		{
			int centerPixel = source[r * pitch + 4];
			int rightPixel = source[r * pitch + 4 + 1];
			int right = horizontal[r * 9 + 4 + 1];
			int left = horizontal[r * 9 + 4];
			int down = downWeights[r * 8 + 4];
			int up = upWeights[r * 8 + 4];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 4] + left * source[r * pitch + 4 - 1]
				+ up * above[r * pitch + 4] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[4] = 0;
			else if (value > 255) temp[4] = 255;
			else temp[4] = value;
		}
		{
			int centerPixel = source[r * pitch + 5];
			int rightPixel = source[r * pitch + 5 + 1];
			int right = horizontal[r * 9 + 5 + 1];
			int left = horizontal[r * 9 + 5];
			int down = downWeights[r * 8 + 5];
			int up = upWeights[r * 8 + 5];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 5] + left * source[r * pitch + 5 - 1]
				+ up * above[r * pitch + 5] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[5] = 0;
			else if (value > 255) temp[5] = 255;
			else temp[5] = value;
		}
		{
			int centerPixel = source[r * pitch + 6];
			int rightPixel = source[r * pitch + 6 + 1];
			int right = horizontal[r * 9 + 6 + 1];
			int left = horizontal[r * 9 + 6];
			int down = downWeights[r * 8 + 6];
			int up = upWeights[r * 8 + 6];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 6] + left * source[r * pitch + 6 - 1]
				+ up * above[r * pitch + 6] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[6] = 0;
			else if (value > 255) temp[6] = 255;
			else temp[6] = value;
		}
		{
			int centerPixel = source[r * pitch + 7];
			int rightPixel = source[r * pitch + 7 + 1];
			int right = horizontal[r * 9 + 7 + 1];
			int left = horizontal[r * 9 + 7];
			int down = downWeights[r * 8 + 7];
			int up = upWeights[r * 8 + 7];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 7] + left * source[r * pitch + 7 - 1]
				+ up * above[r * pitch + 7] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[7] = 0;
			else if (value > 255) temp[7] = 255;
			else temp[7] = value;
		}
		for (c = 0; c < 8; c++)
			destination[r * pitch + c] = (unsigned char)temp[c];
	}
}
