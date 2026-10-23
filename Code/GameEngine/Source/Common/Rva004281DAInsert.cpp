// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva004281DAInsert@@YAXPAUVersionBlockEntry@@UPivot24@@VVersionBlockKeyCompare@@@Z @0x004281DA 89B
// __unguarded_linear_insert for 0x18-byte version records with pivot by value.
// Evidence: neighbours swap 0x0042818F same flags; callees prereq assign 0x0042816E row ThingFactory.cpp lessEntries 0x00427C2C row VersionBlockKeyCompare.cpp version dtor 0x00238580 row VersionDestructor.cpp; callers 0x0042835F 0x00428787; same 89B shape as rowed 0x0021BAA3 with EH for non-trivial pivot and per-element assign stride 0x18.
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
void __cdecl Rva004281DAInsert(VersionBlockEntry *last, Pivot24 val, VersionBlockKeyCompare comp)
{
	VersionBlockEntry *next = last - 1;
	while (comp.lessEntries((const VersionBlockEntry *)&val, next))
	{
		*(ProductionPrerequisite *)last = *(const ProductionPrerequisite *)next;
		last = next;
		--next;
	}
	*(ProductionPrerequisite *)last = *(const ProductionPrerequisite *)&val;
}
