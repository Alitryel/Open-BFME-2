// _PlaneAddNoise_C
// partial score=0.977 date=2026-10-22
// cl: /O2 /G6 /DNDEBUG /MD
#include <math.h>
#include <stdlib.h>

extern "C" double __cdecl gaussian(double sigma, double mu, double x)
{
	return exp(-((x - mu) * (x - mu)) / (sigma * sigma + sigma * sigma)) / (sigma * sqrt(6.2831853));
}

extern "C" void __cdecl PlaneAddNoise_C(unsigned char *start, unsigned width, unsigned height, int pitch, int q)
{
	unsigned i;
	double sigma;
	double x;
	int next;
	signed char dist[300];
	signed char noise[2048];
	signed char first;
	unsigned char *src;
	signed char *noisePtr;
	unsigned char *row;
	unsigned rows;

	sigma = 1 + 0.012698412698412698 * (63 - q);
	next = 0;
	for (x = -32; x < 32; x++) {
		int count = (int)(256 * gaussian(sigma, 0, x) + 0.5);
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
	if (height > 0) {
		for (row = start, rows = height; rows; rows--) {
			src = row;
			noisePtr = &noise[rand() & 0xff];
			for (i = 0; i < width; i++) {
				signed char negFirst = -first;
				if (src[i] < negFirst)
					src[i] = negFirst;
				if (src[i] > 255 - first)
					src[i] = 255 - first;
				src[i] += noisePtr[i];
			}
			row += pitch;
		}
	}
}
