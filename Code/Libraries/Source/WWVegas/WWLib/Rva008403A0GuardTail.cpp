// cl: /DNDEBUG /MD /EHsc
// stlport
// The separate 20-byte wide-streambuf guard-tail candidate at 0x008403A0
// overlaps a different matched BFME2 range and is not represented here.
// Target semantics for this unambiguous byte placement remain donor-derived.

// ?dup_00843ef0@@YAHPBG0PAD@Z
int dup_00843ef0(const unsigned short *first, const unsigned short *last, char *out)
{
	int count = (int)(last - first);
	if (count > 0)
	{
		int left = count;
		const unsigned short *src = first;
		char *dst = out;
		do
		{
			char v = (char)*src;
			src = (const unsigned short *)((const char *)src + 2);
			*dst = v;
			++dst;
			--left;
		} while (left != 0);
		return (int)dst;
	}
	return (int)out;
}
