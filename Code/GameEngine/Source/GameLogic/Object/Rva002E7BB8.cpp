// cl: /DNDEBUG /MD /EHsc
// ?Rva002E7BB8Get@@YAMXZ @0x002E7BB8 56B
// Native SSE loads accumulatorDFF0D0 before adding deltaC050CC; source operand
// order preserves the compiler-selected relocation roles and both addresses.
// Wraps g_00DFF0D0 by g_00C050CC against g_Va00BBB8D8; callers at 0x002EFD62 0x002EFD6A 0x002EFD72.

extern float g_00DFF0D0;
// Owned here (its only reader); retail .bss zero-initializes it (VA 0x00DFF0D0).
float g_00DFF0D0 = 0.0f;
// Owned here (its only reader); retail .rdata holds 0.18409086763858795f (VA 0x00C050CC).
float g_00C050CC = 0.18409086763858795f;
extern float g_Va00BBB8D8;

float __cdecl Rva002E7BB8Get()
{
	float v = g_00C050CC + g_00DFF0D0;
	g_00DFF0D0 = v;
	if (v > g_Va00BBB8D8)
	{
		v -= g_Va00BBB8D8;
		g_00DFF0D0 = v;
	}
	return g_00DFF0D0;
}
