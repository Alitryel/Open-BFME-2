// cl: /GX-
// jabba util.cpp string-array join @ 0x0066C620 (261B), ported from BFME1
// Y2FeslUtilJoin.cpp. Clears dest; for each parts[i] ensures used+len+1
// < destSize (else diag fail); inserts sep before i>0; strcpy appends.
//
// Same repairs as the sibling Y2FeslUtilJoinI64.cpp: the diag fail
// arguments are the literals retail references ("false" and the util.cpp
// build path), and the diag getter is BFME1's ?Rva007EB810Get@@YAHXZ
// (int(void), pinned at 0x006587A0), cast to the diag pointer here.

#include <string.h>

struct Rva007EB810Diag
{
	virtual void v0();
	virtual void v1();
	virtual void v2();
	virtual void fail(const char *expr, const char *file, int line);
};

Rva007EB810Diag *Rva007EB810Get(void);

void Rva00800170Join(const char **parts, unsigned count, char *dest, unsigned destSize, char sep)
{
	unsigned i;
	unsigned used;
	unsigned len;
	char sepStr[2];

	dest[0] = 0;
	if (count < 1)
		return;

	used = 0;
	sepStr[0] = sep;
	sepStr[1] = 0;

	if (count <= 0)
		return;

	for (i = 0; i < count; i++)
	{
		len = (unsigned)strlen(parts[i]);
		if (used + len + 1 >= destSize)
		{
			Rva007EB810Get()->fail("false", "\\views\\feslbuild_main\\jabba\\fesl\\source\\util.cpp", 0x67);
			return;
		}
		if (i > 0)
		{
			strcat(dest, sepStr);
			used++;
		}
		strcat(dest, parts[i]);
		used += len;
	}
}
