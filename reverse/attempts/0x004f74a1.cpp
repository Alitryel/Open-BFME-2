// ?Rva004F74A1@@YAPAUTreeHintRef00217D4C@@PAU1@00@Z
// partial score=0.8107 date=2026-10-14
// ?Rva004F74A1@@YAPAUTreeHintRef00217D4C@@PAU1@00@Z
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// _STL::__rotate<TreeHintRef00217D4C*, int> (vendor/stlport/stl/_algo.c line
// 354, the random-access gcd overload), retail 0x004F74A1..0x004F75F2 (337B).
// Lexicographic cycle rotation: n=last-first, k=middle-first, l=n-k; k==0
// returns last, k==l calls swap_ranges and returns first+l, otherwise
// __gcd(n,k) cycles copy/move the 4-byte TreeHintRef elements (copy ctor incs
// the +4 refcount, assign is the ICF'd out-of-line worker 0x2174A4, the tmp
// destructor releases through 0x7DEEF). Rowed workers: swap_ranges 0x4F6FFC,
// __gcd 0x23307C.
void rva0007DEEF(void *ref);

struct TreeHintRef00217D4C
{
	void *m_ptr;
	TreeHintRef00217D4C() : m_ptr(0) {}
	TreeHintRef00217D4C(const TreeHintRef00217D4C &o) : m_ptr(o.m_ptr)
	{
		if (m_ptr)
			++*(int *)((char *)m_ptr + 4);
	}
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &o);
	~TreeHintRef00217D4C()
	{
		if (m_ptr)
			rva0007DEEF(m_ptr);
	}
};

int rva0023307C(int n, int k);
void *rva004F6FFC(void **first, void **middle, void **last);

TreeHintRef00217D4C *Rva004F74A1(TreeHintRef00217D4C *first,
	TreeHintRef00217D4C *middle, TreeHintRef00217D4C *last)
{
	int n = (int)(last - first);
	int k = (int)(middle - first);
	int l = n - k;
	TreeHintRef00217D4C *result = first + l;

	if (k == 0)
		return last;

	if (k == l)
	{
		rva004F6FFC((void **)first, (void **)middle, (void **)middle);
		return result;
	}

	int d = rva0023307C(n, k);

	for (int i = 0; i < d; ++i)
	{
		TreeHintRef00217D4C tmp = *first;
		TreeHintRef00217D4C *p = first;

		if (k < l)
		{
			for (int j = 0; j < l / d; ++j)
			{
				if (p > first + l)
				{
					*p = *(p - l);
					p -= l;
				}
				*p = *(p + k);
				p += k;
			}
		}
		else
		{
			for (int j = 0; j < k / d - 1; ++j)
			{
				if (p < last - k)
				{
					*p = *(p + k);
					p += k;
				}
				*p = *(p - l);
				p -= l;
			}
		}
		*p = tmp;
		++first;
	}
	return result;
}
