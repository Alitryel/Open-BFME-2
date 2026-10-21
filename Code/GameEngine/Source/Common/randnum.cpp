// nbench misc.c randnum: the BYTEmark linear congruential generator
// (254754, 529562, mod 999563), reseeded to 13/117 on a nonzero argument.
// g_bfmeSeedJC/g_bfmeCarryJC are its static randw[2] = {13, 117}.
extern int g_bfmeSeedJC;
extern int g_bfmeCarryJC;

long randnum(long reset)
{
	int carry;
	int seed;
	if (reset) {
		seed = 13;
		carry = 117;
	} else {
		carry = g_bfmeCarryJC;
		seed = g_bfmeSeedJC;
	}
	int next = (seed * 0x3E322 + carry * 0x8149A) % 0xF408B;
	g_bfmeCarryJC = seed;
	g_bfmeSeedJC = next;
	return next;
}
