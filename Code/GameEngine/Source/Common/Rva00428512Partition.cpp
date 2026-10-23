// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00428512Partition@@YAPAUVersionBlockEntry@@PAU1@0UPivot24@@VVersionBlockKeyCompare@@@Z @0x00428512 107B
// Quicksort unguarded partition over 0x18-byte version records with pivot by value.
// Evidence: chain lane calls just-landed swap 0x0042818F; callees lessEntries 0x00427C2C row VersionBlockKeyCompare.cpp version dtor 0x00238580 row VersionDestructor.cpp; caller 0x004288E9 introsort constructs pivot via narrow copy 0x00427F75; same 107B shape as rowed 0x0021C6CB with EH for non-trivial pivot.
struct BfmeNarrowRecord00427F75
{
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
	char m_data[24];
};
struct VersionBlockEntry
{
	const char *m_key; // +0
	char m_padAfterKey[8]; // +4
	const char *m_value; // +0xC
	char m_padTail[8]; // +0x10
	~VersionBlockEntry();
};
class VersionBlockKeyCompare
{
public:
	bool lessEntries(const VersionBlockEntry *left, const VersionBlockEntry *right) const;
};
struct Pivot24
{
	Pivot24(const Pivot24 &other);
	~Pivot24();
	BfmeNarrowRecord00427F75 narrow;
};
void __cdecl Rva0042818FSwap(void *a, void *b);
// ??0Pivot24@@QAE@ABU0@@Z present-unmatched
inline Pivot24::Pivot24(const Pivot24 &other) : narrow(other.narrow) {}
// ??1Pivot24@@QAE@XZ present-unmatched
inline Pivot24::~Pivot24() { ((VersionBlockEntry *)&narrow)->~VersionBlockEntry(); }
VersionBlockEntry *__cdecl Rva00428512Partition(VersionBlockEntry *first, VersionBlockEntry *last, Pivot24 pivot, VersionBlockKeyCompare comp)
{
	while (true)
	{
		while (comp.lessEntries(first, (const VersionBlockEntry *)&pivot))
			++first;
		--last;
		while (comp.lessEntries((const VersionBlockEntry *)&pivot, last))
			--last;
		if (!(first < last))
			return first;
		Rva0042818FSwap(first, last);
		++first;
	}
}
