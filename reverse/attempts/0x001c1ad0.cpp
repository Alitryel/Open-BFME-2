// _DeringBlockStrong_C
// partial score=0.261011 date=2026-10-18
// _DeringBlockStrong_C
// _DeringBlockStrong_C
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c1ad0.md plus retail only.
// No decoder source was consulted.
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

	// Retail processes four vertical pairs per group, two groups per row.
	const unsigned char *verticalTop = above;
	const unsigned char *verticalBottom = source;
	short *verticalWeights = vertical;
	for (r = 9; r != 0; --r) {
		const unsigned char *pair = verticalTop;
		const unsigned char *lower = verticalBottom;
		short *weights = verticalWeights;
		for (c = 2; c != 0; --c) {
			{
				int difference = lower[0] - pair[0];
				if (difference <= 0) difference = pair[0] - lower[0];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				weights[0] = (short)weight;
			}
			{
				int difference = lower[1] - pair[1];
				if (difference <= 0) difference = pair[1] - lower[1];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				weights[1] = (short)weight;
			}
			{
				int difference = lower[2] - pair[2];
				if (difference <= 0) difference = pair[2] - lower[2];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				weights[2] = (short)weight;
			}
			{
				int difference = lower[3] - pair[3];
				if (difference <= 0) difference = pair[3] - lower[3];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				weights[3] = (short)weight;
			}
			pair += 4;
			lower += 4;
			weights += 4;
		}
		verticalTop += pitch;
		verticalBottom += pitch;
		verticalWeights += 8;
	}

	const unsigned char *hrow = source;
	short *hweight = horizontal;
	for (r = 8; r != 0; --r) {
		for (c = 0; c < 9; c += 3) {
			{
				int difference = hrow[c] - hrow[c - 1];
				if (difference <= 0) difference = hrow[c - 1] - hrow[c];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				hweight[c] = (short)weight;
			}
			{
				int difference = hrow[c + 1] - hrow[c];
				if (difference <= 0) difference = hrow[c] - hrow[c + 1];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				hweight[c + 1] = (short)weight;
			}
			{
				int difference = hrow[c + 2] - hrow[c + 1];
				if (difference <= 0) difference = hrow[c + 1] - hrow[c + 2];
				int weight = quality - difference + 32;
				if (weight < -64) weight = sharpen; else if (weight < 0) weight = 0; else if (weight > cap) weight = cap;
				hweight[c + 2] = (short)weight;
			}
		}
		hrow += pitch;
		hweight += 9;
	}

	// Keep all eight outputs separate until the entire source row is read.
	for (r = 0; r < 8; r++) {
		int temp[8];
		{
			int centerPixel = source[r * pitch + 0];
			int rightPixel = source[r * pitch + 0 + 1];
			int right = horizontal[r * 9 + 0 + 1];
			int left = horizontal[r * 9 + 0];
			int down = vertical[r * 8 + 0 + 8];
			int up = vertical[r * 8 + 0];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 0] + left * source[r * pitch + 0 - 1]
				+ up * above[r * pitch + 0] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[0] = value;
		}
		{
			int centerPixel = source[r * pitch + 1];
			int rightPixel = source[r * pitch + 1 + 1];
			int right = horizontal[r * 9 + 1 + 1];
			int left = horizontal[r * 9 + 1];
			int down = vertical[r * 8 + 1 + 8];
			int up = vertical[r * 8 + 1];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 1] + left * source[r * pitch + 1 - 1]
				+ up * above[r * pitch + 1] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[1] = value;
		}
		{
			int centerPixel = source[r * pitch + 2];
			int rightPixel = source[r * pitch + 2 + 1];
			int right = horizontal[r * 9 + 2 + 1];
			int left = horizontal[r * 9 + 2];
			int down = vertical[r * 8 + 2 + 8];
			int up = vertical[r * 8 + 2];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 2] + left * source[r * pitch + 2 - 1]
				+ up * above[r * pitch + 2] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[2] = value;
		}
		{
			int centerPixel = source[r * pitch + 3];
			int rightPixel = source[r * pitch + 3 + 1];
			int right = horizontal[r * 9 + 3 + 1];
			int left = horizontal[r * 9 + 3];
			int down = vertical[r * 8 + 3 + 8];
			int up = vertical[r * 8 + 3];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 3] + left * source[r * pitch + 3 - 1]
				+ up * above[r * pitch + 3] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[3] = value;
		}
		{
			int centerPixel = source[r * pitch + 4];
			int rightPixel = source[r * pitch + 4 + 1];
			int right = horizontal[r * 9 + 4 + 1];
			int left = horizontal[r * 9 + 4];
			int down = vertical[r * 8 + 4 + 8];
			int up = vertical[r * 8 + 4];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 4] + left * source[r * pitch + 4 - 1]
				+ up * above[r * pitch + 4] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[4] = value;
		}
		{
			int centerPixel = source[r * pitch + 5];
			int rightPixel = source[r * pitch + 5 + 1];
			int right = horizontal[r * 9 + 5 + 1];
			int left = horizontal[r * 9 + 5];
			int down = vertical[r * 8 + 5 + 8];
			int up = vertical[r * 8 + 5];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 5] + left * source[r * pitch + 5 - 1]
				+ up * above[r * pitch + 5] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[5] = value;
		}
		{
			int centerPixel = source[r * pitch + 6];
			int rightPixel = source[r * pitch + 6 + 1];
			int right = horizontal[r * 9 + 6 + 1];
			int left = horizontal[r * 9 + 6];
			int down = vertical[r * 8 + 6 + 8];
			int up = vertical[r * 8 + 6];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 6] + left * source[r * pitch + 6 - 1]
				+ up * above[r * pitch + 6] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[6] = value;
		}
		{
			int centerPixel = source[r * pitch + 7];
			int rightPixel = source[r * pitch + 7 + 1];
			int right = horizontal[r * 9 + 7 + 1];
			int left = horizontal[r * 9 + 7];
			int down = vertical[r * 8 + 7 + 8];
			int up = vertical[r * 8 + 7];
			int value = ((128 - right - down - up - left) * centerPixel
				+ down * below[r * pitch + 7] + left * source[r * pitch + 7 - 1]
				+ up * above[r * pitch + 7] + right * rightPixel + 64) >> 7;
			if (value < 0) value = 0;
			else if (value > 255) value = 255;
			temp[7] = value;
		}
		for (c = 0; c < 8; c++)
			destination[r * pitch + c] = (unsigned char)temp[c];
	}
}
