// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x002BBC7A, 183B; Ghidra boundary, ret14 ABI and 52-byte
// arithmetic independently establish the overflow and storage width. The
// address-derived record is an opaque ABI view; no application class or
// member layout is inferred. Each helper pin comes from this target's calls.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

// The 52-byte element is retail's record under another address-derived label:
// its placement copy ctor is rowed at 0x002B90D6 and its placement-copy
// _Construct at 0x002B91ED (StlportConstructFamilyW3G15.cpp), and its
// destructor at 0x002B707E (BfmeAssignRecord52Dtor.cpp). The vector helpers
// below keep this unit's own Rva002BBC7ARecord spelling for their ledger rows,
// but the two special calls they reach must bind to those rowed owners instead
// of the undefined ??$_Construct@URva002BBC7ARecord / ??1Rva002BBC7ARecord:
// the _Construct specialization reproduces retail's null-guarded placement
// copy through the rowed copy ctor (byte-identical to 0x002B91ED), and the
// destructor is a view of the rowed dtor.
struct Rva002B91EDElement { Rva002B91EDElement(const Rva002B91EDElement&); };
class BfmeAssignRecord52 { public: ~BfmeAssignRecord52(); };

struct Rva002BBC7ARecord {
 Rva002BBC7ARecord(); Rva002BBC7ARecord(const Rva002BBC7ARecord&); ~Rva002BBC7ARecord() { ((BfmeAssignRecord52 *)this)->BfmeAssignRecord52::~BfmeAssignRecord52(); } Rva002BBC7ARecord&operator=(const Rva002BBC7ARecord&);
private: char bytes[52];
};
namespace _STL { template<> inline void _Construct<Rva002BBC7ARecord,Rva002BBC7ARecord>(Rva002BBC7ARecord*p,const Rva002BBC7ARecord&v) { _STLP_PLACEMENT_NEW ((void*)p) Rva002B91EDElement(*(const Rva002B91EDElement*)&v); } }
template void _STL::vector<Rva002BBC7ARecord>::_M_insert_overflow(Rva002BBC7ARecord*,const Rva002BBC7ARecord&,const _STL::__false_type&,unsigned int,bool);
template Rva002BBC7ARecord *_STL::uninitialized_fill_n(Rva002BBC7ARecord *,unsigned int,const Rva002BBC7ARecord &);
