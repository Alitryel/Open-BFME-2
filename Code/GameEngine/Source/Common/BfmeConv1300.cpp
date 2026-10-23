// cl: /Od
// Open-BFME5 conversions.

// Retail .data at VA 0x00DA71AC points to this exact STL assertion format
// text. Reproduce the string value without asserting literal-address identity.
void *g_bfmeSinkSTA = (void *)"%s(%d): STL assertion failure : %s\n";

void bfmeWriteSTA(void *sink, int a, int b, int c);
void bfmeFlushSTA(void);

void bfmeGoSTA(int a, int b, int c)
{
	bfmeWriteSTA(g_bfmeSinkSTA, b, c, a);
	bfmeFlushSTA();
}
