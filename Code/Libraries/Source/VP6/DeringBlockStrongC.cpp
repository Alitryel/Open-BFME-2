// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c1ad0.md plus retail only. No
// decoder source was consulted.
//
// DeringBlockStrong_C (retail 0x001C1AD0, 2030 bytes): cdecl adaptive smoothing
// of one 8x8 block. Vertical and horizontal neighbour weights come from the
// pixel differences, capped at 3 * Q (at most 32) and replaced by the sharpen
// modifier for strong edges; each output pixel blends itself with its four
// neighbours, and a row is computed into temporaries before it is stored.
// Codegen notes (see reverse/attempt_support/dering-strong-offset-20261021.md):
// the row offset is a basic induction variable (off += pitch); pixels 0 and 7
// keep centre/right pixel locals loaded before the weights while pixels 1-6
// read inline; the row store is eight explicit c = k statements.
extern "C" int g_vp6SharpenModifier[64];

extern "C" void __cdecl DeringBlockStrong_C(void *instance, const unsigned char *source,
	unsigned char *destination, int pitch, int qIndex, const int *scaleTable)
{
	int quality = scaleTable[qIndex];
	int sharpen = g_vp6SharpenModifier[qIndex];
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

	short *downWeights = vertical + 8 + 1;
	short *upWeights = vertical + 1;
	int off = 0;
	for (r = 0; r < 8; r++) {
		int temp[8];
		{
			int centerPixel = source[off + 0];
			int rightPixel = source[off + 1];
			int left = horizontal[r * 9 + 0];
			int up = upWeights[r * 8 + -1];
			int down = downWeights[r * 8 + -1];
			int right = horizontal[r * 9 + 0 + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[off + 0] + left * source[off + -1]
				+ up * above[off + 0] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[0] = 0;
			else if (value > 255) temp[0] = 255;
			else temp[0] = value;
		}
		{
			int left = horizontal[r * 9 + 1];
			int up = upWeights[r * 8 + 0];
			int down = downWeights[r * 8 + 0];
			int right = horizontal[r * 9 + 1 + 1];
			int value = ((128 - right - down - up - left) * source[off + 1]
				+ down * below[off + 1] + left * source[off + 0]
				+ up * above[off + 1] + right * source[off + 2] + 64) >> 7;
			if (value < 0) temp[1] = 0;
			else if (value > 255) temp[1] = 255;
			else temp[1] = value;
		}
		{
			int left = horizontal[r * 9 + 2];
			int up = upWeights[r * 8 + 1];
			int down = downWeights[r * 8 + 1];
			int right = horizontal[r * 9 + 2 + 1];
			int value = ((128 - right - down - up - left) * source[off + 2]
				+ down * below[off + 2] + left * source[off + 1]
				+ up * above[off + 2] + right * source[off + 3] + 64) >> 7;
			if (value < 0) temp[2] = 0;
			else if (value > 255) temp[2] = 255;
			else temp[2] = value;
		}
		{
			int left = horizontal[r * 9 + 3];
			int up = upWeights[r * 8 + 2];
			int down = downWeights[r * 8 + 2];
			int right = horizontal[r * 9 + 3 + 1];
			int value = ((128 - right - down - up - left) * source[off + 3]
				+ down * below[off + 3] + left * source[off + 2]
				+ up * above[off + 3] + right * source[off + 4] + 64) >> 7;
			if (value < 0) temp[3] = 0;
			else if (value > 255) temp[3] = 255;
			else temp[3] = value;
		}
		{
			int left = horizontal[r * 9 + 4];
			int up = upWeights[r * 8 + 3];
			int down = downWeights[r * 8 + 3];
			int right = horizontal[r * 9 + 4 + 1];
			int value = ((128 - right - down - up - left) * source[off + 4]
				+ down * below[off + 4] + left * source[off + 3]
				+ up * above[off + 4] + right * source[off + 5] + 64) >> 7;
			if (value < 0) temp[4] = 0;
			else if (value > 255) temp[4] = 255;
			else temp[4] = value;
		}
		{
			int left = horizontal[r * 9 + 5];
			int up = upWeights[r * 8 + 4];
			int down = downWeights[r * 8 + 4];
			int right = horizontal[r * 9 + 5 + 1];
			int value = ((128 - right - down - up - left) * source[off + 5]
				+ down * below[off + 5] + left * source[off + 4]
				+ up * above[off + 5] + right * source[off + 6] + 64) >> 7;
			if (value < 0) temp[5] = 0;
			else if (value > 255) temp[5] = 255;
			else temp[5] = value;
		}
		{
			int left = horizontal[r * 9 + 6];
			int up = upWeights[r * 8 + 5];
			int down = downWeights[r * 8 + 5];
			int right = horizontal[r * 9 + 6 + 1];
			int value = ((128 - right - down - up - left) * source[off + 6]
				+ down * below[off + 6] + left * source[off + 5]
				+ up * above[off + 6] + right * source[off + 7] + 64) >> 7;
			if (value < 0) temp[6] = 0;
			else if (value > 255) temp[6] = 255;
			else temp[6] = value;
		}
		{
			int centerPixel = source[off + 7];
			int rightPixel = source[off + 8];
			int left = horizontal[r * 9 + 7];
			int up = upWeights[r * 8 + 6];
			int down = downWeights[r * 8 + 6];
			int right = horizontal[r * 9 + 7 + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[off + 7] + left * source[off + 6]
				+ up * above[off + 7] + right * rightPixel + 64) >> 7;
			if (value < 0) temp[7] = 0;
			else if (value > 255) temp[7] = 255;
			else temp[7] = value;
		}

		c = 0; destination[off + c] = (unsigned char)temp[c];
		c = 1; destination[off + c] = (unsigned char)temp[c];
		c = 2; destination[off + c] = (unsigned char)temp[c];
		c = 3; destination[off + c] = (unsigned char)temp[c];
		c = 4; destination[off + c] = (unsigned char)temp[c];
		c = 5; destination[off + c] = (unsigned char)temp[c];
		c = 6; destination[off + c] = (unsigned char)temp[c];
		c = 7; destination[off + c] = (unsigned char)temp[c];
		off += pitch;
	}
}
