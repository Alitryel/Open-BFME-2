// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00428594PopHeap@@YAXPAUVersionBlockEntry@@00UPivot24@@VVersionBlockKeyCompare@@H@Z RVA 0x00428594 size 95 evidence chain linkbody callers 0x0042864B 0x00428821 callees prereq-assign 0x0042816E narrow-copy 0x00427F75 adjust-heap 0x00428372 version-dtor 0x00238580
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
class ProductionPrerequisite
{
public:
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);
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
// ??1Pivot24@@QAE@XZ present-unmatched
inline Pivot24::~Pivot24() { ((VersionBlockEntry *)&narrow)->~VersionBlockEntry(); }
void __cdecl Rva00428372AdjustHeap(VersionBlockEntry *first, int holeIndex, int len, Pivot24 val, VersionBlockKeyCompare comp);
void __cdecl Rva00428594PopHeap(VersionBlockEntry *first, VersionBlockEntry *last, VersionBlockEntry *result, Pivot24 val, VersionBlockKeyCompare comp, int extra)
{
	*(ProductionPrerequisite *)result = *(const ProductionPrerequisite *)first;
	Rva00428372AdjustHeap(first, 0, last - first, val, comp);
}
