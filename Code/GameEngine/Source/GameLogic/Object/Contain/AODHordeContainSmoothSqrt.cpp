// cl: /O1 /G7 /Oy- /DNDEBUG /MD
// Rva0047A673, retail 0x0047A673..0x0047A699 (38 B, cdecl float(float), RET):
// x * sqrt(x) + x*x * (1 - x) through the CRT sqrt at 0x0062921C, x87 with an
// EBP frame. It sits after the AOD horde-contain solver 0x0047A413; identity
// and callers are unproven, so the name is address-derived. Taking the square
// root into its own float before the products is what places the first
// argument-release pop after the reload of x, as retail schedules it.
#include <math.h>

float Rva0047A673(float x)
{
	float s = (float)sqrt((double)x);
	return x * s + (x * x) * (1.0f - x);
}
