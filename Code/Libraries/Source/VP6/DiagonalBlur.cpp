// cl: /O2 /G6 /DNDEBUG /MD
// Clean room: reverse/vp6_cleanroom/specs/001c2b80.md plus retail only. No
// decoder source was consulted.
//
// DiagonalBlur (retail 0x001C2B80, 916 bytes, unreferenced in retail): cdecl
// two-pass 8x8 filter. Pass 1 blurs a block with its four diagonal neighbours
// one pixel away (weight 4) and two pixels away (weight 2); pass 2 continues
// eight rows further down both pointers and sharpens each pixel against its
// four direct neighbours, clamped to 0..255.
// Codegen notes (see reverse/attempt_support/diagonal-1c2b80-20261023c/):
// c2 orders commutative operands and SIB base/index by symbol ids, which it
// hands out in 32-id chunks. The second pass's own row and column counters,
// its count-down row loop and the named centre pixel give retail's numbering.
extern "C" void DiagonalBlur(void *instance, unsigned char *source, unsigned char *dest, int pitch)
{
	unsigned char *src = source;
	unsigned char *dst = dest;
	int row, row2, col, col2;
	for (row = 0; row < 8; row++) {
		for (col = 0; col < 8; col++) {
			dst[col] = (unsigned char)((16 + 8 * src[col]
				+ 4 * (src[col - pitch - 1] + src[col + pitch - 1] + src[col - pitch + 1] + src[col + pitch + 1])
				+ 2 * (src[col - 2 * pitch - 2] + src[col + 2 * pitch + 2] + src[col + 2 * pitch - 2] + src[col - 2 * pitch + 2])) >> 5);
		}
		dst += pitch;
		src += pitch;
	}
	row2 = 8;
	while (row2--) {
		for (col2 = 0; col2 < 8; col2++) {
			int center = src[col2];
			int value = (1 + 6 * center - src[col2 - 1] - src[col2 - pitch] - src[col2 + pitch] - src[col2 + 1]) >> 1;
			if (value < 0)
				value = 0;
			else if (value > 255)
				value = 255;
			dst[col2] = (unsigned char)value;
		}
		dst += pitch;
		src += pitch;
	}
}
