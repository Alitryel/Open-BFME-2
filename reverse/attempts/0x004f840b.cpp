// ?Rva004F840B@@YAXPAPAX00HHPAX@Z
// partial score=0.882556 date=2026-10-14
// ?Rva004F840B@@YAXPAPAX00HHPAX@Z
// partial score=0.882556 date=2026-10-14
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_STLP_USE_STATIC_LIB /D_CRTIMP=
// stlport
//
// ?Rva004F840B@@YAXPAPAX00HHPAX@Z, retail 0x004F840B..0x004F8539 (303B).
// _STL::__merge_without_buffer<...> instantiation (vendor/stlport/stl/_algo.c
// line 1263): recursively merges two adjacent sorted runs of 4-byte TreeHintRef
// elements. The four STLport workers are rowed: lower_bound 0x004F6D4B,
// upper_bound 0x004F6D66, rotate 0x004F8049 and swap<TreeHintRef> 0x004F6542;
// the release helper is 0x0007DEEF. The inlined comparator reads the unsigned
// key at (*element+8)+0xC, strictly greater.
struct RvaKey { char pad[0xC]; int key; };

void rva0007DEEF(void *ref);

struct TreeHintRef
{
	void *m_ptr;
	TreeHintRef() : m_ptr(0) {}
	TreeHintRef(const TreeHintRef &o) : m_ptr(o.m_ptr)
	{
		if (m_ptr)
			++*(int *)((char *)m_ptr + 4);
	}
	~TreeHintRef()
	{
		if (m_ptr)
			rva0007DEEF(m_ptr);
	}
};

static __forceinline bool rvaCompGreater(TreeHintRef a, TreeHintRef b)
{
	return *(int *)((char *)*(void **)((char *)a.m_ptr + 8) + 0xC) >
		*(int *)((char *)*(void **)((char *)b.m_ptr + 8) + 0xC);
}

void *rva004F6D4B(void **first, void **last, const void *value, void *comp);
void *rva004F6D66(void **first, void **last, const void *value, void *comp);
void *rva004F8049(void **first, void **middle, void **last);
void rva004F6542(void *&a, void *&b);

void __cdecl Rva004F840B(void **first, void **middle, void **last,
	int len1, int len2, void *comp)
{
	if (len1 == 0 || len2 == 0)
		return;
	if (len1 + len2 == 2)
	{
		if (rvaCompGreater(*(TreeHintRef *)middle, *(TreeHintRef *)first))
			rva004F6542(*first, *middle);
		return;
	}

	void **firstCut;
	void **secondCut;
	int len11 = 0;
	int len22 = 0;
	if (len1 > len2)
	{
		len11 = len1 / 2;
		firstCut = first + len11;
		secondCut = (void **)rva004F6D4B(middle, last, firstCut, comp);
		len22 += (int)(secondCut - middle);
	}
	else
	{
		len22 = len2 / 2;
		secondCut = middle + len22;
		firstCut = (void **)rva004F6D66(first, middle, secondCut, comp);
		len11 += (int)(firstCut - first);
	}
	void **newMiddle = (void **)rva004F8049(firstCut, middle, secondCut);
	Rva004F840B(first, firstCut, newMiddle, len11, len22, comp);
	Rva004F840B(newMiddle, secondCut, last, len1 - len11, len2 - len22, comp);
}
