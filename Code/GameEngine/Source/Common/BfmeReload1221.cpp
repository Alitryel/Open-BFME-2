// Open-BFME5 conversions: the Mersenne-twister table reload (Cokus reloadMT,
// N=624, M=397), called by bfmeNext1221 (BfmeConv1221.cpp) once the index
// runs out; seeds with 4357 first when the table was never seeded. The
// tempered result re-reads state[0] (retail keeps a register copy).

extern int g_bfmeIndexFA;			// retail 0x00DDCF50
extern int g_bfmeStateFA[625];		// retail 0x00E18658
extern unsigned int *g_bfmeNext1221;	// retail 0x00E1901C
void __cdecl bfmeSeed(int seed);
#define hiBit(u)	((u) & 0x80000000U)
#define loBit(u)	((u) & 0x00000001U)
#define loBits(u)	((u) & 0x7FFFFFFFU)
#define mixBits(u, v)	(hiBit(u) | loBits(v))
extern "C" unsigned int bfmeReload1221(void)
{
	register unsigned int *p0 = (unsigned int *)g_bfmeStateFA;
	register unsigned int *p2 = (unsigned int *)g_bfmeStateFA + 2;
	register unsigned int *pM = (unsigned int *)g_bfmeStateFA + 397;
	register unsigned int s0, s1;
	register int j;
	if (g_bfmeIndexFA < -1)
		bfmeSeed(4357);
	g_bfmeIndexFA = 624 - 1;
	g_bfmeNext1221 = (unsigned int *)g_bfmeStateFA + 1;
	for (s0 = g_bfmeStateFA[0], s1 = g_bfmeStateFA[1], j = 624 - 397 + 1; --j; s0 = s1, s1 = *p2++)
		*p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? 0x9908B0DFU : 0U);
	for (pM = (unsigned int *)g_bfmeStateFA, j = 397; --j; s0 = s1, s1 = *p2++)
		*p0++ = *pM++ ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? 0x9908B0DFU : 0U);
	s1 = g_bfmeStateFA[0];
	unsigned int y = g_bfmeStateFA[0];
	*p0 = *pM ^ (mixBits(s0, s1) >> 1) ^ (loBit(s1) ? 0x9908B0DFU : 0U);
	y ^= (y >> 11);
	y ^= (y << 7) & 0x9D2C5680U;
	y ^= (y << 15) & 0xEFC60000U;
	return y ^ (y >> 18);
}
