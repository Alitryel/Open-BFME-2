// _UpdateUMVBorder
// partial score=0.88 date=2026-10-23
// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001b96a0.md plus retail only.
// NEAR (not exact): UpdateUMVBorder retail 0x001B96A0..0x001B9AB6 (1047
// bytes); this body compiles to 1042 bytes with 321 of retail's 353
// instructions in aligned order (the 2026-10-19 bank: 289 by the same
// difflib metric, 280 by the s9 one). The new step: the U/V side fills
// and U/V row copies reuse the four side-fill pointers (srcLeft,
// srcRight, dstLeft, dstRight), and the Y row copy reads from srcLeft;
// that gives retail's side-fill slot order (srcRight 0x10, dstLeft 0x14,
// srcLeft 0x18, dstRight 0x1c) and retail's U/V loops apart from the
// delta. Remaining: Y side loop enters through jmp + srcLeft reload and
// hoists the srcRight advance into ESI (retail keeps srcLeft in ESI
// across the back edge and advances srcRight last through EDI); Y row
// copy slots rotated (retail last 0x10, dstTop 0x14, delta 0x28,
// counter 0x20); U shr one instruction early; U/V bottom-top delta is
// dstBottom - dstTop where retail recomputes uvBorder*stride - src +
// dstBottom; V copy advance in ECX instead of EDI.
// See reverse/attempt_support/001b96a0-20261023-reuse.md.
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
	int uvBorder;
	unsigned char *srcLeft, *srcRight, *dstLeft, *dstRight;
	unsigned char *last, *dstTop, *dstBottom;

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
	srcLeft = buffer + border * stride;
	last = srcLeft + (pbi->VFragments * 8 - 1) * stride;
	dstTop = buffer;
	dstBottom = last + stride;
	for (i = 0; i < border; i++) {
		memcpy(dstTop, srcLeft, stride);
		memcpy(dstBottom, last, stride);
		dstTop += stride;
		dstBottom += stride;
	}

	stride = pbi->UVStride;
	rows = pbi->VFragments * 4;
	srcLeft = buffer + pbi->ReconUDataOffset;
	srcRight = srcLeft + pbi->HFragments * 4 - 1;
	uvBorder = (unsigned)border / 2;
	dstLeft = srcLeft - uvBorder;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], uvBorder);
		memset(dstRight, srcRight[0], uvBorder);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	srcLeft = buffer + pbi->ReconUDataOffset - uvBorder;
	srcRight = srcLeft + (pbi->VFragments * 4 - 1) * stride;
	dstLeft = srcLeft - uvBorder * stride;
	dstRight = srcRight + stride;
	for (i = 0; i < uvBorder; i++) {
		memcpy(dstLeft, srcLeft, stride);
		memcpy(dstRight, srcRight, stride);
		dstLeft += stride;
		dstRight += stride;
	}

	srcLeft = buffer + pbi->ReconVDataOffset;
	srcRight = srcLeft + pbi->HFragments * 4 - 1;
	dstLeft = srcLeft - uvBorder;
	dstRight = srcRight + 1;
	for (i = 0; i < rows; i++) {
		memset(dstLeft, srcLeft[0], uvBorder);
		memset(dstRight, srcRight[0], uvBorder);
		srcLeft += stride;
		srcRight += stride;
		dstLeft += stride;
		dstRight += stride;
	}
	srcLeft = buffer + pbi->ReconVDataOffset - uvBorder;
	srcRight = srcLeft + (pbi->VFragments * 4 - 1) * stride;
	dstLeft = srcLeft - uvBorder * stride;
	dstRight = srcRight + stride;
	for (i = 0; i < uvBorder; i++) {
		memcpy(dstLeft, srcLeft, stride);
		memcpy(dstRight, srcRight, stride);
		dstLeft += stride;
		dstRight += stride;
	}
}
