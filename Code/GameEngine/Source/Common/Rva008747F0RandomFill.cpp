// ?fillRandom008747F0@@YAXPAH@Z

extern long randnum(long lngval);
extern unsigned long abs_randwc(unsigned long num);

void __cdecl fillRandom008747F0(int *arr)
{
	randnum(13);
	for (int outer = 0x65; outer; --outer)
	{
		for (int inner = 0x65; inner; --inner)
		{
			*arr = abs_randwc(5000000);	// 0x004C4B40: a bound, not an address
			++arr;
		}
	}
}
