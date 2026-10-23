// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00428233PushHeap@@YAXPAUVersionBlockEntry@@HHUPivot24@@VVersionBlockKeyCompare@@@Z @0x00428233 138B
// __push_heap sift-up for 0x18-byte version records with pivot by value.
// Evidence: neighbours same flags; callees lessEntries 0x00427C2C row prereq assign 0x0042816E row version dtor 0x00238580 row; caller 0x004283FE; unblocks 0x00428372; same STLport spelling as rowed 0x002059CF with parent hole-top indices and imul 0x18 stride.
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
// ??0Pivot24@@QAE@ABU0@@Z present-unmatched
inline Pivot24::Pivot24(const Pivot24 &other) : narrow(other.narrow) {}
// ??1Pivot24@@QAE@XZ present-unmatched
inline Pivot24::~Pivot24() { ((VersionBlockEntry *)&narrow)->~VersionBlockEntry(); }
void __cdecl Rva00428233PushHeap(VersionBlockEntry *first, int holeIndex, int topIndex, Pivot24 val, VersionBlockKeyCompare comp)
{
	int parent = (holeIndex - 1) / 2;
	while (holeIndex > topIndex)
	{
		if (!comp.lessEntries(first + parent, (const VersionBlockEntry *)&val))
			break;
		*(ProductionPrerequisite *)(first + holeIndex) = *(const ProductionPrerequisite *)(first + parent);
		holeIndex = parent;
		parent = (holeIndex - 1) / 2;
	}
	*(ProductionPrerequisite *)(first + holeIndex) = *(const ProductionPrerequisite *)&val;
}
