// cl: /O1 /MD
//
// ?Rva002DBF66Copy@@YAPAURva002DBF66Elem@@PAU1@00@Z @0x002DBF66 71B: forward
// copy of 20-byte records over [first,last) into out, returning the end of
// the output. The record assignment keeps the leading word and copies the
// +4 word and the 12-byte +8 block. Address-named.

struct Rva002DBF66Block
{
	int m_words[3];
};

struct Rva002DBF66Elem
{
	int m_keep00;
	int m_value04;
	Rva002DBF66Block m_block08;
	Rva002DBF66Elem &operator=(const Rva002DBF66Elem &o)
	{
		m_value04 = o.m_value04;
		m_block08 = o.m_block08;
		return *this;
	}
};

Rva002DBF66Elem *Rva002DBF66Copy(Rva002DBF66Elem *first, Rva002DBF66Elem *last, Rva002DBF66Elem *out)
{
	for (int n = last - first; n > 0; --n, ++first, ++out)
		*out = *first;
	return out;
}