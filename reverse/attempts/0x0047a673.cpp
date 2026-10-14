// ?bfmeSmoothSqrt@@YAMM@Z
// partial score=0.95 date=2026-10-14
// cl: /O1 /G7 /Oy- /DNDEBUG /MD
#include <math.h>
float bfmeSmoothSqrt(float x)
{
	return x * sqrt((double)x) + (x * x) * (1.0f - x);
}
