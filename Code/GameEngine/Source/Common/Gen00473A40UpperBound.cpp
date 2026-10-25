// flags: region default (reverse/retail_inventory/flag_regions.csv)

// STLport __upper_bound over 16-byte records, comparing the first dword.
// Retail 0x00473A40, 72 bytes.

// GameFont.cpp's view of the 16-byte font-substitution record (the TU this
// body belongs to): input size, output size, style flags, name. The name is
// an AsciiString there; this unit's flags do not reach the string shim, and
// the search reads only m_inputSize, so it stays an opaque word here.
struct Gen00473A40Elem
{
	int m_inputSize;
	int m_outputSize;
	int m_flags;
	void *m_name;
};

// The comparator carries one byte retail zeroes with stosb before pushing the
// whole dword to the by-value __upper_bound parameter; an empty functor
// elides that store and the body comes out short.
struct Gen00473A40Less
{
	bool operator()(const int &value, const Gen00473A40Elem &elem) const
	{
		return value < elem.m_inputSize;
	}

	unsigned char m_pad0x00;
};

Gen00473A40Elem *Gen00473A40(Gen00473A40Elem *first, Gen00473A40Elem *last,
	const int &value, Gen00473A40Less, int *)
{
	int length = last - first;
	while (length > 0)
	{
		int half = length >> 1;
		Gen00473A40Elem *middle = first + half;
		if (value < middle->m_inputSize)
			length = half;
		else
		{
			first = middle + 1;
			length -= half + 1;
		}
	}
	return first;
}
