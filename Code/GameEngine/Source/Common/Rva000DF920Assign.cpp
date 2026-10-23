// cl: /Ob0

// The element is a narrow string handle: retail assigns it through the rowed
// StringBase<char>::set 0x000366F0 (the refcounted Rva0036CA00Str handle's own
// assignment is OpaqueRefElement4::operator= 0x00239099, see Rva00403055CopyCtor.cpp).
template <class T> class StringBase
{
public:
	void set(const StringBase<T> &src);
};
#define BFME_STR_SET(dst, src) ((StringBase<char> &)(dst)).set((const StringBase<char> &)(src))

class Rva0036CA00Str
{
private:
	void *m_item;
};

class Rva000DF920
{
	Rva0036CA00Str *m_00;
	Rva0036CA00Str *m_04;

public:
	Rva000DF920 &operator=(const Rva0036CA00Str *pair);
};

Rva000DF920 &Rva000DF920::operator=(const Rva0036CA00Str *pair)
{
	BFME_STR_SET(*m_00, pair[0]);
	BFME_STR_SET(*m_04, pair[1]);
	return *this;
}
