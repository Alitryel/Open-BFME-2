// _PlaneAddNoise_C
// partial score=0.82 date=2026-10-20
// _PlaneAddNoise_C
// partial score=0.816 date=2026-10-15
// _PlaneAddNoise_C
// partial score=0.8 date=2026-10-14
// _PlaneAddNoise_C
// partial score=0.8 date=2026-10-13
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b69c0.md plus retail only. The upper clamp is 255 - dist[0]
// as retail computes it (lea edx,[esi+0xff] with esi = -dist[0]); the spec's 255 minus the lower bound differs.
#include <stdlib.h>
#include <math.h>

extern "C" void __cdecl PlaneAddNoise_C(unsigned char *start, unsigned width, unsigned height, int pitch, int q)
{
	unsigned i;
	unsigned j;
	double sigma;
	double x;
	int next;
	signed char dist[300];
	unsigned char noise[2048];
	signed char first;

	sigma = 1 + 0.012698412698412698 * (63 - q);
	next = 0;
	for (x = -32; x < 32; x++) {
		int count = (int)(256 * (exp(-((x - 0) * (x - 0)) / (sigma * sigma + sigma * sigma)) / (sigma * sqrt(6.2831853))) + 0.5);
		if (count) {
			int k;
			for (k = 0; k < count; k++)
				dist[next + k] = (signed char)(int)x;
			next += k;
		}
	}
	for (; next < 256; next++)
		dist[next] = 0;
	for (i = 0; i < 2048; i++)
		noise[i] = dist[rand() & 0xff];
	first = dist[0];
	for (j = 0; j < height; j++) {
		unsigned char *noisePtr = &noise[rand() & 0xff];
		unsigned char *row = start + j * pitch;
		for (i = 0; i < width; i++) {
			int upper = 255 - first;
			if (row[i] < -first)
				row[i] = -first;
			if (row[i] > upper)
				row[i] = 255 - first;
			row[i] += noisePtr[i];
		}
	}
}
