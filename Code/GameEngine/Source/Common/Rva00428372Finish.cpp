// cl: /O1 /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva00428372AdjustHeap@@YAXPAUVersionBlockEntry@@HHUPivot24@@VVersionBlockKeyCompare@@@Z @0x00428372 175B
// __adjust_heap sift-down for 0x18-byte version records with pivot by value tail-calling push-heap.
// Evidence: chain calls just-landed push-heap 0x00428233; callees lessEntries 0x00427C2C row prereq assign 0x0042816E row narrow copy 0x00427F75 row version dtor 0x00238580 row; callers 0x004285D3 0x00428634; unblocks 0x004285F3 0x00428594; same STLport spelling as rowed 0x00625C70 with child pick and imul 0x18 stride.
// The by-value pivot's copy constructor must be an out-of-line call: with it
// inlined the /O1 scheduler emits the EH ESP save before `mov ecx,esp`, while
// retail emits `mov ecx,esp` first. `??0Pivot24@@QAE@ABU0@@Z` is pinned to the
// rowed 24-byte record copy at 0x00427F75 in reverse/symbols.csv.
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
void __cdecl Rva00428233PushHeap(VersionBlockEntry *first, int holeIndex, int topIndex, Pivot24 val, VersionBlockKeyCompare comp);
void __cdecl Rva00428372AdjustHeap(VersionBlockEntry *first, int holeIndex, int len, Pivot24 val, VersionBlockKeyCompare comp)
{
	int topIndex = holeIndex;
	int secondChild = 2 * holeIndex + 2;
	while (secondChild < len)
	{
		if (comp.lessEntries(first + secondChild, first + (secondChild - 1)))
			secondChild--;
		*(ProductionPrerequisite *)(first + holeIndex) = *(const ProductionPrerequisite *)(first + secondChild);
		holeIndex = secondChild;
		secondChild = 2 * (secondChild + 1);
	}
	if (secondChild == len)
	{
		*(ProductionPrerequisite *)(first + holeIndex) = *(const ProductionPrerequisite *)(first + (secondChild - 1));
		holeIndex = secondChild - 1;
	}
	Rva00428233PushHeap(first, holeIndex, topIndex, val, comp);
}
