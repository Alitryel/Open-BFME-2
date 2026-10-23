// A Mersenne-twister-style table seeder.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5SeventyFour.cpp); trimmed to the single
// T1 body the sweep places.

extern int g_bfmeIndexFA;					// retail 0x012D5DC8
// g_bfmeIndexFA: VA 0xddcf50 (retail .data initial value -1).
int g_bfmeIndexFA = -1;
// g_bfmeStateFA: matched references place it at VA 0xe18658; zero-filled at retail, sized to the
// 0x9c4-byte gap before the next known global there.
int g_bfmeStateFA[625];

// ?bfmeSeed@@YAXH@Z
void __cdecl bfmeSeed(int seed)
{
	int value = seed | 1;

	g_bfmeIndexFA = 0;

	g_bfmeStateFA[0] = value;

	// A walking pointer with its own countdown; an index loop is strength
	// reduced into an address compare instead.
	int *entry = &g_bfmeStateFA[1];

	int count = 623;

	do
	{
		value = value * 0x10DCD;

		*entry = value;

		++entry;
	}
	while (--count != 0);
}
