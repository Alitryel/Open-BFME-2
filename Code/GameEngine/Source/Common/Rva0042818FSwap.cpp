// cl: /O1 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ?Rva0042818FSwap@@YAXPAX0@Z @0x0042818F 75B
// Swap 24B records via narrow copy then two prereq assigns then version dtor.
// Evidence: callees 0x00427F75 row narrow copy 0x0042816E row prereq assign 0x00238580 row version dtor; callers 0x00428558 0x0042833F; next copy_backward same flags.
struct BfmeNarrowRecord00427F75
{
	BfmeNarrowRecord00427F75(const BfmeNarrowRecord00427F75 &other);
	char m_data[24];
};
class ProductionPrerequisite
{
public:
	ProductionPrerequisite &operator=(const ProductionPrerequisite &other);
};
struct VersionBlockEntry
{
	~VersionBlockEntry();
};
struct Tmp24
{
	Tmp24(const Tmp24 &other);
	~Tmp24();
	BfmeNarrowRecord00427F75 narrow;
};
// ??0Tmp24@@QAE@ABV0@@Z present-unmatched
inline Tmp24::Tmp24(const Tmp24 &other) : narrow(other.narrow) {}
// ??1Tmp24@@QAE@XZ present-unmatched
inline Tmp24::~Tmp24() { ((VersionBlockEntry *)&narrow)->~VersionBlockEntry(); }
void __cdecl Rva0042818FSwap(void *a, void *b)
{
	Tmp24 tmp(*(const Tmp24 *)a);
	*(ProductionPrerequisite *)a = *(const ProductionPrerequisite *)b;
	*(ProductionPrerequisite *)b = *(const ProductionPrerequisite *)&tmp;
}
