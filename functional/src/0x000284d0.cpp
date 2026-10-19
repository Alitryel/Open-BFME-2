// ?bfmeImplV23@BfmeStrV23@@QAEXPAD000@Z
// partial score=0.459 date=2026-10-17
// ?bfmeImplV23@BfmeStrV23@@QAEXPAD000@Z
// partial score=0.667 date=2026-10-14
// cl: /DNDEBUG /MD /EHsc /Od /Ob2 /D_STLP_USE_STATIC_LIB
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
// stlport
// ?bfmeImplV23@BfmeStrV23@@QAEXPAD000@Z @0x000284D0 848B, WB 0x6DA630 (848B,
// byte-identical structure). STLport basic_string forward-range insert
// (_M_replace): capacity fast path with memmove tail shift, overlap branch and
// a reallocate path; the bulk moves are __copy_trivial and the trailing moves
// are explicit element loops through char_traits::assign.
extern "C" void *memmove(void *, const void *, unsigned int);
extern "C" void free(void *);

namespace _STL {
char *rva004179B0(char *first, char *last, char *result);
void *rva00307F0(unsigned int n);
void rva0006D5230(void *first, void *last);
void rva0006D5370(char &dest, const char &src);
}

class BfmeStrV23
{
public:
	void bfmeImplV23(char *pos, char *first, char *last, char *arg3);
private:
	char *m_start;  // +0x00
	char *m_finish; // +0x04
	char *m_end;    // +0x08
};

void BfmeStrV23::bfmeImplV23(char *pos, char *first, char *last, char *arg3)
{
	(void)arg3;
	if (first == last)
		return;
	int n = (int)(last - first);
	if ((int)(m_end - m_finish) >= n + 1)
	{
		int p = (int)(m_finish - pos);
		char *oldFinish = m_finish;
		if (p >= n)
		{
			_STL::rva004179B0(m_finish - n + 1, m_finish + 1, m_finish + 1);
			m_finish += n;
			int len = p - n + 1;
			char *dest = pos + n;
			char *tmp = 0;
			if (len != 0)
			{
				tmp = _STL::rva004179B0(pos, pos + len, dest);
			}
			char *d = pos;
			for (char *s = first; s != last; ++d, ++s)
				_STL::rva0006D5370(*d, *s);
		}
		else
		{
			char *q = first + p + 1;
			_STL::rva004179B0(q, last, m_finish + 1);
			m_finish += n - p;
			_STL::rva004179B0(pos, oldFinish + 1, m_finish);
			m_finish += p;
			char *d = pos;
			for (char *s = first; s != q; ++d, ++s)
				_STL::rva0006D5370(*d, *s);
		}
	}
	else
	{
		int oldSize = (int)(m_finish - m_start);
		int cap = (oldSize < n ? n : oldSize) + 1;
		char *buf;
		struct { char *a; char *b; char *c; char *d; unsigned char pad[0x30]; } fr;
		fr.a = 0; fr.b = 0; fr.c = 0; fr.d = 0;
		if (0)
			throw 1;
		(void)fr;
		buf = (char *)_STL::rva00307F0(cap);
		char *q = _STL::rva004179B0(m_start, pos, buf);
		q = _STL::rva004179B0(first, last, q);
		q = _STL::rva004179B0(pos, m_finish, q);
		*q = 0;
		_STL::rva0006D5230(m_start, m_finish + 1);
		if (m_start)
			free(m_start);
		m_start = buf;
		m_finish = q;
		m_end = buf + cap;
	}
}
