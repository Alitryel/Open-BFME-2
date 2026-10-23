// Character-classification members use two 256-byte case maps and a
// 256-entry classification-mask table. Each table base is established by a
// matched BFME2 DIR32 reference; the element widths and byte-range checks
// establish the spans. All initialized table bytes match BFME2 retail.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/T2CtypeTableFacets.cpp); trimmed to the seven
// bodies the sweep places. The donor's remaining sibling defs (under 16B or
// ambiguous) are omitted: only declared here, never defined, so the
// find_declared_unmatched gate stays green. The donor declares t2_block_copy
// but retail reaches memmove, so the declaration is renamed to the real
// import (Import-ref verify refuses it otherwise; no pin can fix this).
typedef unsigned short T2WChar;

// BFME2 VA 0x00BBC1E0; all 256 table bytes match retail.
extern const char g_ctypeUppercaseMap[256] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 91, 92, 93, 94, 95,
    96, 65, 66, 67, 68, 69, 70, 71, 72, 73, 74, 75, 76, 77, 78, 79,
    80, 81, 82, 83, 84, 85, 86, 87, 88, 89, 90, 123, 124, 125, 126, 127,
    -128, -127, -126, -125, -124, -123, -122, -121, -120, -119, -118, -117, -116, -115, -114, -113,
    -112, -111, -110, -109, -108, -107, -106, -105, -104, -103, -102, -101, -100, -99, -98, -97,
    -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81,
    -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65,
    -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49,
    -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33,
    -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17,
    -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1
};
// BFME2 VA 0x00BBC2E0; all 256 table bytes match retail.
extern const char g_ctypeLowercaseMap[256] = {
    0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15,
    16, 17, 18, 19, 20, 21, 22, 23, 24, 25, 26, 27, 28, 29, 30, 31,
    32, 33, 34, 35, 36, 37, 38, 39, 40, 41, 42, 43, 44, 45, 46, 47,
    48, 49, 50, 51, 52, 53, 54, 55, 56, 57, 58, 59, 60, 61, 62, 63,
    64, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 91, 92, 93, 94, 95,
    96, 97, 98, 99, 100, 101, 102, 103, 104, 105, 106, 107, 108, 109, 110, 111,
    112, 113, 114, 115, 116, 117, 118, 119, 120, 121, 122, 123, 124, 125, 126, 127,
    -128, -127, -126, -125, -124, -123, -122, -121, -120, -119, -118, -117, -116, -115, -114, -113,
    -112, -111, -110, -109, -108, -107, -106, -105, -104, -103, -102, -101, -100, -99, -98, -97,
    -96, -95, -94, -93, -92, -91, -90, -89, -88, -87, -86, -85, -84, -83, -82, -81,
    -80, -79, -78, -77, -76, -75, -74, -73, -72, -71, -70, -69, -68, -67, -66, -65,
    -64, -63, -62, -61, -60, -59, -58, -57, -56, -55, -54, -53, -52, -51, -50, -49,
    -48, -47, -46, -45, -44, -43, -42, -41, -40, -39, -38, -37, -36, -35, -34, -33,
    -32, -31, -30, -29, -28, -27, -26, -25, -24, -23, -22, -21, -20, -19, -18, -17,
    -16, -15, -14, -13, -12, -11, -10, -9, -8, -7, -6, -5, -4, -3, -2, -1
};
// BFME2 VA 0x00BBBDDC; all 1024 table bytes match retail.
extern const unsigned int g_ctypeClassificationMasks[256] = {
    0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u,
    0x00000020u, 0x00000028u, 0x00000028u, 0x00000028u, 0x00000028u, 0x00000028u, 0x00000020u, 0x00000020u,
    0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u,
    0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u, 0x00000020u,
    0x00000048u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u, 0x000000C4u,
    0x000000C4u, 0x000000C4u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x00000050u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x000001C1u, 0x00000141u,
    0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u,
    0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u, 0x00000141u,
    0x00000141u, 0x00000141u, 0x00000141u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u,
    0x00000050u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x000001C2u, 0x00000142u,
    0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u,
    0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u, 0x00000142u,
    0x00000142u, 0x00000142u, 0x00000142u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000050u, 0x00000020u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u,
    0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u, 0x00000000u
};

extern "C" __declspec(dllimport) void *__cdecl memmove(void *dst, const void *src, unsigned int n);

struct T2NarrowCtype
{
	char toUpper(char c) const;
	const char *toLowerRange(char *low, char *high) const;
	const char *widenRange(const char *low, const char *high, char *to) const;
	const char *narrowRange(const char *low, const char *high, char dflt, char *to) const;
};

const char *T2NarrowCtype::widenRange(const char *low, const char *high, char *to) const
{
	if (high != low)
		memmove(to, low, (unsigned int)(high - low));
	return high;
}

const char *T2NarrowCtype::narrowRange(const char *low, const char *high, char, char *to) const
{
	if (high != low)
		memmove(to, low, (unsigned int)(high - low));
	return high;
}

struct T2WideCtype
{
	const T2WChar *isRange(const T2WChar *low, const T2WChar *high, unsigned int *vec) const;
	T2WChar toUpper(unsigned int c) const;
	const T2WChar *toUpperRange(T2WChar *low, T2WChar *high) const;
	T2WChar toLower(unsigned int c) const;
	const T2WChar *toLowerRange(T2WChar *low, T2WChar *high) const;
	T2WChar widen(char c) const;
	const char *widenRange(const char *low, const char *high, T2WChar *to) const;
	int narrow(T2WChar c, char dflt) const;
	const T2WChar *narrowRange(const T2WChar *low, const T2WChar *high, char dflt, char *to) const;
};

const T2WChar *T2WideCtype::isRange(const T2WChar *low, const T2WChar *high,
                                    unsigned int *vec) const
{
	while (low < high)
	{
		*vec = (*low < 0x100) ? g_ctypeClassificationMasks[*low] : 0;
		++low;
		++vec;
	}
	return high;
}

const char *T2WideCtype::widenRange(const char *low, const char *high, T2WChar *to) const
{
	while (low != high)
	{
		*to = (T2WChar)(signed char)*low;
		++to;
		++low;
	}
	return high;
}

const T2WChar *T2WideCtype::narrowRange(const T2WChar *low, const T2WChar *high,
                                        char dflt, char *to) const
{
	while (low != high)
	{
		T2WChar c = *low;
		++low;
		int v = ((int)(char)c == (int)c) ? (int)c : (int)dflt;
		*to = (char)v;
		++to;
	}
	return high;
}

const T2WChar *T2WideCtype::toUpperRange(T2WChar *low, T2WChar *high) const
{
	while (low < high)
	{
		T2WChar c = *low;
		*low = (c < 0x100) ? (T2WChar)(unsigned char)g_ctypeUppercaseMap[c] : c;
		++low;
	}
	return high;
}

const T2WChar *T2WideCtype::toLowerRange(T2WChar *low, T2WChar *high) const
{
	while (low < high)
	{
		T2WChar c = *low;
		*low = (c < 0x100) ? (T2WChar)(unsigned char)g_ctypeLowercaseMap[c] : c;
		++low;
	}
	return high;
}
