// ?initBlocksRva009B3E40@@YAXPAX@Z
// g_Rva009B3E40Arr0: matched references place it at VA 0xdb7c28; zero-filled at retail, sized to the
// 0x4-byte gap before the next known global there.
extern int g_Rva009B3E40Arr0[1];
// g_Rva009B3E40Arr1: matched references place it at VA 0xdb7c2c; retail contents, sized to the
// 0x4-byte gap before the next known global there.
int g_Rva009B3E40Arr1[1] = {
	1,
};
// g_Rva009B3E40Arr2: matched references place it at VA 0xdb7c30; retail contents, sized to the
// 0x4-byte gap before the next known global there.
int g_Rva009B3E40Arr2[1] = {
	5,
};
// g_Rva009B3E40Arr3: matched references place it at VA 0xdb7c34; retail contents, sized to the
// 0xf4-byte gap before the next known global there.
int g_Rva009B3E40Arr3[61] = {
	6, 14, 15, 27, 28, 2, 4, 7,
	13, 16, 26, 29, 42, 3, 8, 12,
	17, 25, 30, 41, 43, 9, 11, 18,
	24, 31, 40, 44, 53, 10, 19, 23,
	32, 39, 45, 52, 54, 20, 22, 33,
	38, 46, 51, 55, 60, 21, 34, 37,
	47, 50, 56, 59, 61, 35, 36, 48,
	49, 57, 58, 62, 63,
};
extern void* g_Rva009B3E40Blocks[];

void initBlocksRva009B3E40(void* self)
{
	*(void***)((char*)self + 0x13c) = g_Rva009B3E40Blocks;

	for (int i = 0; i < 0x40; i += 4) {
		*((char*)g_Rva009B3E40Blocks[g_Rva009B3E40Arr0[i]] + (unsigned)self + 0x140) = (char)(i + 0);
		*((char*)g_Rva009B3E40Blocks[g_Rva009B3E40Arr1[i]] + (unsigned)self + 0x140) = (char)(i + 1);
		*((char*)g_Rva009B3E40Blocks[g_Rva009B3E40Arr2[i]] + (unsigned)self + 0x140) = (char)(i + 2);
		*((char*)g_Rva009B3E40Blocks[g_Rva009B3E40Arr3[i]] + (unsigned)self + 0x140) = (char)(i + 3);
	}
}
