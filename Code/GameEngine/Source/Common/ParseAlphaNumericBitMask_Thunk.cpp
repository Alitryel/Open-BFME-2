// cl: /Od /GZ
// Convert a compact alphanumeric set description to a bit mask. The retail
// table maps @ and ` to bit 0, A-Z/a-z to bits 1-26, and 0-3 to bits 27-30;
// every other byte is -1 and terminates the scan. A null description preserves
// the fallback.

// Matched DIR32 witness places this 256-byte lookup at VA 0x00CE1C80 (.rdata).
// Its declared extent and full-byte indexing end at VA 0x00CE1D80, where the
// next observed retail data block begins; that adjacent block's identity is not
// asserted. These are the exact signed byte values read from retail.
#pragma data_seg(".rdata")
signed char GenCharToBit0012A430[256] = {
	// 0x00-0x0F
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0x10-0x1F
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0x20-0x2F
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0x30-0x3F
	27, 28, 29, 30, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0x40-0x4F
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	// 0x50-0x5F
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1, -1, -1, -1,
	// 0x60-0x6F
	0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
	// 0x70-0x7F
	16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, -1, -1, -1, -1, -1,
	// 0x80-0x8F
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0x90-0x9F
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0xA0-0xAF
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0xB0-0xBF
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0xC0-0xCF
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0xD0-0xDF
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0xE0-0xEF
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
	// 0xF0-0xFF
	-1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
};
#pragma data_seg()

unsigned int ParseAlphaNumericBitMask(const char *description, unsigned int fallback)
{
	if (description == 0) {
		return fallback;
	}

	unsigned int mask = 0;
	int bit;
	for (; (bit = GenCharToBit0012A430[*description]) >= 0; ++description) {
		mask |= 1U << bit;
	}

	return mask;
}
