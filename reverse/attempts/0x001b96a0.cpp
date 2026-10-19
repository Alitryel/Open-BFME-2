// _UpdateUMVBorder
// partial score=0.8 date=2026-10-19
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b96a0.md plus retail only.
// NEAR (not exact): UpdateUMVBorder retail 0x001B96A0..0x001B9AB6 (1047
// bytes); this body compiles to 1042 bytes with 280 of retail's 353
// instructions in aligned order (the previous bank: 1055 bytes, 130).
// Two source changes moved it: (1) the Y side-fill loop reads the left
// edge pixel into a local and advances srcLeft before the memset, which
// gives retail's whole prologue (border in ECX, buffer loaded late into
// EAX, srcLeft in ESI); (2) the U setup halves the border after srcRight
// is formed. Remaining: the Y loop is entered through a jmp + srcLeft
// reload (retail falls straight in with ESI = srcLeft and reloads
// mid-loop); the side-fill stack slots are rotated (retail srcRight 0x10,
// dstLeft 0x14, srcLeft 0x18, dstRight 0x1c); U shr still issues one
// instruction early; U/V row loops form the bottom-top delta as
// dstBottom - dstTop where retail forms border*stride - src + dstBottom.
// See reverse/attempt_support/001b96a0-20261019-s9.md.
struct Vp6BorderInstance {
	unsigned char unknown0[0x78];
	int ReconYDataOffset;
	int ReconUDataOffset;
	int ReconVDataOffset;
	unsigned char unknown84[0x90 - 0x84];
	int HFragments;
	int VFragments;
	int YStride;
	int UVStride;
	unsigned char unknownA0[0xb4 - 0xa0];
	int MVBorder;
};
extern "C" void *memset(void *, int, unsigned);
extern "C" void *memcpy(void *, const void *, unsigned);
#pragma intrinsic(memset, memcpy)
extern "C" void UpdateUMVBorder(Vp6BorderInstance *pbi, unsigned char *buffer)
{
	int i;
	int rows;
	int border;
	int stride;
	unsigned char *srcLeft, *srcRight, *dstLeft, *dstRight;
	unsigned char *src, *last, *dstTop, *dstBottom;

	rows = pbi->VFragments * 8;
	border = pbi->MVBorder;
	stride = pbi->YStride;
	srcLeft = pbi->ReconYDataOffset + buffer;
	srcRight = srcLeft + pbi->HFragments * 8 - 1;
	dstLeft = srcLeft - border;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		unsigned char left = *srcLeft;
		srcLeft += stride;
		memset(dstLeft, left, border);
		memset(dstRight, srcRight[0], border);
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	src = buffer + border * stride;
	last = src + (pbi->VFragments * 8 - 1) * stride;
	dstTop = buffer;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, src, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}

	stride = pbi->UVStride;
	rows = pbi->VFragments * 4;
	srcLeft = buffer + pbi->ReconUDataOffset;
	srcRight = srcLeft + pbi->HFragments * 4 - 1;
	border = (unsigned)border / 2;
	dstLeft = srcLeft - border;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], border);
		memset(dstRight, srcRight[0], border);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	src = buffer + pbi->ReconUDataOffset - border;
	last = src + (pbi->VFragments * 4 - 1) * stride;
	dstTop = src - border * stride;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, src, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}

	srcLeft = buffer + pbi->ReconVDataOffset;
	srcRight = srcLeft + pbi->HFragments * 4 - 1;
	dstLeft = srcLeft - border;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], border);
		memset(dstRight, srcRight[0], border);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	src = buffer + pbi->ReconVDataOffset - border;
	last = src + (pbi->VFragments * 4 - 1) * stride;
	dstTop = src - border * stride;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, src, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}
}
