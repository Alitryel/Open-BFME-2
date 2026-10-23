// flags: region default (reverse/retail_inventory/flag_regions.csv)
// STLport counted copy of the two trailing words in each eight-byte record.
// The range dispatcher supplies the unused iterator metadata.
struct Rva005DC408Element
{
	char m_pad[4];
	unsigned short m_lo;
	unsigned short m_hi;
};

namespace _STL
{
struct random_access_iterator_tag;
template <class Input, class Output, class Distance>
Output __copy(Input, Input, Output, const random_access_iterator_tag &, Distance *);
}

template <>
Rva005DC408Element *_STL::__copy<Rva005DC408Element *, Rva005DC408Element *, int>(
    Rva005DC408Element *begin, Rva005DC408Element *end, Rva005DC408Element *dst,
    const _STL::random_access_iterator_tag &, int *)
{
	if (end - begin > 0)
	{
		int count = end - begin;
		unsigned short *src = &begin->m_hi;
		do
		{
			dst->m_lo = src[-1];
			dst->m_hi = *src;
			src += 4;
			++dst;
		} while (--count != 0);
	}
	return dst;
}
