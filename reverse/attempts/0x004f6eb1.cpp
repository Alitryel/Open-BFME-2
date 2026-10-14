// ??$__unguarded_linear_insert@PAURva004F6352@@U1@URva004F6352Cmp@@@_STL@@YAXPAURva004F6352@@U1@URva004F6352Cmp@@@Z
// partial score=0.8 date=2026-10-15
// cl: /O1 /G7 /EHsc /MD /D_STLP_USE_STATIC_LIB
// stlport
//
// Open-BFME5: the sort entry and insertion tail of STLport's sort over the
// 12-byte Rva004F6352 records whose quicksort half is in stlport_rva004f6352_sort.cpp.
// Bodies are accepted only where byte-equal by the REL32 graph from sort 0x004F9EF3.

#include <algorithm>
#include <vector>

struct TargetRef00217D4C
{
	void *m_vtbl;
	int references;
};

void __fastcall ReleaseTreeHintRef00217D4C(TargetRef00217D4C *p);

struct TreeHintRef00217D4C
{
	TargetRef00217D4C *m_ptr;
	TreeHintRef00217D4C(const TreeHintRef00217D4C &other);
	TreeHintRef00217D4C &operator=(const TreeHintRef00217D4C &other);
	~TreeHintRef00217D4C();
};

// ??1TreeHintRef00217D4C@@QAE@XZ present-unmatched
inline TreeHintRef00217D4C::~TreeHintRef00217D4C()
{
	if (m_ptr)
		ReleaseTreeHintRef00217D4C(m_ptr);
}

struct MedianKey004F60EC
{
	int _00[2];
	int m_key;
};

struct Rva004F6352
{
	MedianKey004F60EC *m_ptr;
	int m_04;
	TreeHintRef00217D4C m_08;
	Rva004F6352(const Rva004F6352 &other);
	Rva004F6352 &operator=(const Rva004F6352 &other);
	~Rva004F6352() {}
};

struct Rva004F6352Cmp
{
	bool operator()(const Rva004F6352 &a, const Rva004F6352 &b) const
	{
		int ka = a.m_ptr->m_key;
		int kb = b.m_ptr->m_key;
		return ka > kb;
	}
};

// Native 4F6EB1..4F6F08, 87B: the insertion tail's unguarded linear insert.
// Retail loads the value's key-object pointer once and re-reads the key
// through it each probe.
namespace _STL {
template <> void __unguarded_linear_insert<Rva004F6352 *, Rva004F6352, Rva004F6352Cmp>(
	Rva004F6352 *last, Rva004F6352 val, Rva004F6352Cmp)
{
	Rva004F6352 *next = last - 1;
	MedianKey004F60EC *key = val.m_ptr;
	for (;;)
	{
		int ka = key->m_key;
		int kb = next->m_ptr->m_key;
		if (!(ka > kb))
			break;
		*last = *next;
		last = next;
		--next;
	}
	*last = val;
}
}

template void _STL::sort<Rva004F6352 *, Rva004F6352Cmp>(Rva004F6352 *, Rva004F6352 *, Rva004F6352Cmp);

