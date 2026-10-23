// cl: /O1 /MD

// ?Rva000422A0Atan2@@YANMM@Z @0x000422A0 27B
// Unlock: float to double adapter for atan2 import thunk 0x0062992E.
// Caller 0x000422CD is math.h's float atan2 overload. Prev/next are disp trivials.

extern "C" double __cdecl atan2(double y, double x);

double __cdecl Rva000422A0Atan2(float y, float x)
{
	return atan2(y, x);
}

// math.h's x86 inline atan2f: the same body as 0x000422A0 (which the
// Rva000422A0Atan2 row names until its four callers are respelled), and the
// _atan2f copy every non-/Oi unit that includes math.h emits.
extern "C" inline float __cdecl atan2f(float y, float x)
{
	return (float)atan2((double)y, (double)x);
}

// ?atan2@@YAMMM@Z @0x000422CD 25B: math.h's C++ float overload
// (float atan2(float, float) { return atan2f(y, x); }), compiled byte-identical
// by the non-/Oi units that include math.h; 35 retail call sites.
inline float __cdecl atan2(float y, float x)
{
	return atan2f(y, x);
}

extern "C" __declspec(dllimport) double __cdecl ceil(double x);

double __cdecl Rva000422BBCeil(float x)
{
	return ceil(x);
}

// LINK-OWNER anchor: this unit owns atan2(float, float); other units emit it inline, so the
// owner must also emit a select-any (inline) copy.
#pragma inline_depth(0)
// ?bfmeEmitRva000422A0@@YAXXZ present-unmatched
void bfmeEmitRva000422A0()
{
	atan2(0.0f, 0.0f);
}
#pragma inline_depth()
