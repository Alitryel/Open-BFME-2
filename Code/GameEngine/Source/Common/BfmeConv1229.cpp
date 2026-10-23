// Open-BFME5 conversions.

extern "C" int __cdecl memcmp(const void *a, const void *b, unsigned int n);

struct BfmeW1229
{
	const char *m_bfme00;
	int m_bfme04;
};

extern BfmeW1229 g_bfmeWords1229[];
extern signed char g_bfmeLookup1229[];
// g_bfmeWords1229: VA 0xddc370 (.data); its 0xd0-byte interval ends at the
// next known global, g_bfmeLens1229 at VA 0xddc440. Retail's pointer targets
// contain the strings below; local literals preserve their text, not pointer
// identity. The second field values are the retail DWORDs.
BfmeW1229 g_bfmeWords1229[26] = {
	{ "UP", 18 }, { "TAB", 17 }, { "HOME", 9 }, { "SPACE", 16 },
	{ "getCode", 102 }, { "getAscii", 107 }, { "DELETEKEY", 4 }, { "SHIFT", 15 },
	{ "addListener", 104 }, { "ESCAPED", 8 }, { "getController", 103 }, { "removeListener", 105 },
	{ "RIGHT", 14 }, { "getAnalogStickInfo", 106 }, { "LEFT", 11 }, { "CONTROL", 3 },
	{ "END", 6 }, { "DOWN", 5 }, { "ENTER", 7 }, { "INSERT", 10 },
	{ "PGUP", 13 }, { "isDown", 100 }, { "isToggled", 101 }, { "BACKSPACE", 1 },
	{ "CAPSLOCK", 2 }, { "PGDN", 12 },
};
// g_bfmeLookup1229: VA 0xddc45c (.data); key indexes are checked to 0..49,
// and the array stops before the next known global at VA 0xddc490.
signed char g_bfmeLookup1229[50] = {
	-1, -1, 0, 1, 2, 3, -1, 4, 5, 6,
	7, 8, 9, 10, 11, 12, -1, -1, 13, 14,
	-1, -1, 15, 16, 17, 18, 19, -1, -1, 20,
	-1, 21, -1, -1, 22, -1, -1, -1, -1, 23,
	-1, -1, -1, 24, -1, -1, -1, -1, -1, 25,
};
// g_bfmeLens1229: matched references place it at VA 0xddc440; retail contents, sized to the
// 0x1c-byte gap before the next known global there.
unsigned char g_bfmeLens1229[28] = {
	2, 3, 4, 5, 7, 8, 9, 5,
	11, 7, 13, 14, 5, 18, 4, 7,
	3, 4, 5, 6, 4, 6, 9, 9,
	8, 4, 0, 0,
};

extern "C" int bfmeHash1229(const char *str, unsigned int len)
{
	const unsigned char asso_values[256] =
	{
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 0, 50, 0, 50, 0, 5, 25, 0, 10, 50, 30, 0, 50, 20, 0,
	0, 50, 50, 5, 15, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 0, 0, 50, 50, 50, 0, 50, 50, 50, 50, 50, 0,
	50, 50, 0, 25, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50, 50,
	};
	register unsigned int hval = len;

	switch (hval)
	{
	default:
		hval += asso_values[(unsigned char)str[7]];
		/*FALLTHROUGH*/
	case 7:
	case 6:
	case 5:
	case 4:
		hval += asso_values[(unsigned char)str[3]];
		/*FALLTHROUGH*/
	case 3:
	case 2:
		hval += asso_values[(unsigned char)str[1]];
		break;
	}
	return hval;
}

const BfmeW1229 *bfmeFind1229(const char *str, unsigned int len)
{
	int key;
	int index;
	const char *s;

	if (len <= 18 && len >= 2) {
		key = bfmeHash1229(str, len);
		if (key <= 49 && key >= 0) {
			index = g_bfmeLookup1229[key];
			if (index >= 0) {
				if (len == g_bfmeLens1229[index]) {
					s = g_bfmeWords1229[index].m_bfme00;
					if (*str == *s && !memcmp(str + 1, s + 1, len - 1))
						return &g_bfmeWords1229[index];
				}
			}
		}
	}
	return 0;
}
