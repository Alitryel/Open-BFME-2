// cl: /O2
// 0x007EBAA0: allocate the 0x14-byte FESL diagnostic singleton at
// 0x0130A5A0 if it is still null.

void *Gen007F0130(unsigned int size);

extern int vftable_01129D30;
// The +4 slot is the rowed Rva006587B0Print (BfmeConv1321.cpp, 0x006587B0).
void Rva006587B0Print(void *p, const char *text);
extern void *g_Va0130A5A0;

void Rva007EBAA0(void)
{
	if (g_Va0130A5A0)
		return;
	void *p = Gen007F0130(0x14);
	if (p)
	{
		*((int *)p + 2) = 0;
		*((int *)p + 3) = 0;
		*((int *)p + 4) = 0;
		*(int *)p = (int)&vftable_01129D30;
		*((int *)p + 1) = (int)&Rva006587B0Print;
		g_Va0130A5A0 = p;
	}
	else
		g_Va0130A5A0 = 0;
}

// ?vftable_01129D30@@3HA: matched references place it at VA 0xce157c; also referenced as ?g_bfmeVftTQD@@3PAPAXA, ?g_bfmeVftTDA@@3PAPAXA.
int vftable_01129D30 = 10847984;
#pragma comment(linker, "/alternatename:?g_bfmeVftTQD@@3PAPAXA=?vftable_01129D30@@3HA")
#pragma comment(linker, "/alternatename:?g_bfmeVftTDA@@3PAPAXA=?vftable_01129D30@@3HA")
// ?g_Va0130A5A0@@3PAXA: the global at VA 0xe09fbc is ?g_Va0130A5A0@@3PAURva007EB810Diag@@A.
#pragma comment(linker, "/alternatename:?g_Va0130A5A0@@3PAXA=?g_Va0130A5A0@@3PAURva007EB810Diag@@A")
