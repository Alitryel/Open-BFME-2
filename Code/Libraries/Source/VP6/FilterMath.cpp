// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001bc390.md 001c01f0.md 001b6970.md
// 001b69c0.md
// plus retail only. No decoder source was consulted.
#include <stdlib.h>
#include <math.h>

extern unsigned char g_bfmeVp6SelectorMap[40]; // 0x00BD8D00 mode-to-frame table

struct MacroblockInfo
{
	int pad0;
	const unsigned short *coefficients; // 0x04
	unsigned int mode;                  // 0x08
	void *blockModes[1];                // 0x0C
};

struct BlockContext
{
	unsigned char pad0[4];
	void *blockMode;           // 0x04
	unsigned short frame;      // 0x08
	unsigned short dc;         // 0x0A
};

// RVA 0x001BC390
extern "C" void __cdecl VP6_UpdateContext(MacroblockInfo *mb, BlockContext *context, unsigned int block)
{
	context->blockMode = mb->blockModes[block];
	context->dc = mb->coefficients[block * 64];
	context->frame = ((const unsigned short *)g_bfmeVp6SelectorMap)[mb->mode * 2];
}

// RVA 0x001C01F0
extern "C" int __cdecl Bound(int limit, int value)
{
	int mask = value >> 31;
	int magnitude = (value ^ mask) - mask;
	int below = (magnitude < limit + limit) ? 1 : 0;
	int t = below * magnitude - limit;
	int tmask = t >> 31;
	int abst = (t ^ tmask) - tmask;
	int r = -abst;
	r = r + mask;
	r = r + limit;
	r = r ^ mask;
	return r;
}

// RVA 0x001B6970
extern "C" double __cdecl gaussian(double sigma, double mu, double x)
{
	return exp(-((x - mu) * (x - mu)) / (sigma * sigma + sigma * sigma)) / (sigma * sqrt(6.2831853));
}

// RVA 0x001B69C0
// The upper clamp is 255 - dist[0], as retail computes it (lea edx,[esi+0xff] with
// esi = -dist[0]); the spec's 255 minus the lower bound differs. Both bounds are
// reference-bound temporaries: they give retail's pixel-loop preheader (an int and
// a separate byte negation) where named locals or plain expressions do not.
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
	for (j = 0; j < height; j++) {
		unsigned char *noisePtr = &noise[rand() & 0xff];
		unsigned char *row = start + j * pitch;
		for (i = 0; i < width; i++) {
			const int &lower = -first;
			const signed char &negFirst = -first;
			if (row[i] < lower)
				row[i] = negFirst;
			if (row[i] > 255 - first)
				row[i] = 255 - first;
			row[i] += noisePtr[i];
		}
	}
}
