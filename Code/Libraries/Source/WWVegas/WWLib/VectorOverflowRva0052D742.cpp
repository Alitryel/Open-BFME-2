// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// Reference: pristine STLport4.5.3 vector::_M_insert_overflow.
// Retail 0x0052D742, 191B; Ghidra boundary, ret14 ABI and 184-byte
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

// The 184-byte element is retail's record under another address-derived label:
// its placement copy body is rowed as Rva0052D6BEConstruct (0x0052D6BE,
// Rva0052D6BE.cpp, which null-checks and calls its rowed copy ctor 0x0052D555),
// and its (virtual) destructor is rowed at 0x0056616B (LivingWorldCampaignAct.cpp).
// The vector helpers below keep this unit's own Rva0052D742Record spelling for
// their ledger rows, but the two special calls they reach must bind to those
// rowed owners instead of the undefined ??$_Construct@URva0052D742Record /
// ??1Rva0052D742Record: the _Construct specialization reproduces retail's
// null-guarded placement copy (byte-identical to 0x0052D6BE) through the rowed
// copy ctor, and the destructor is a view of the rowed dtor.
class Rva0056616B { public: Rva0056616B(const Rva0056616B&); virtual ~Rva0056616B(); };

struct Rva0052D742Record {
 Rva0052D742Record(); Rva0052D742Record(const Rva0052D742Record&); ~Rva0052D742Record() { ((Rva0056616B *)this)->Rva0056616B::~Rva0056616B(); } Rva0052D742Record&operator=(const Rva0052D742Record&);
private: char bytes[184];
};
namespace _STL { template<> inline void _Construct<Rva0052D742Record,Rva0052D742Record>(Rva0052D742Record*p,const Rva0052D742Record&v) { _STLP_PLACEMENT_NEW ((void*)p) Rva0056616B(*(const Rva0056616B*)&v); } }
template void _STL::vector<Rva0052D742Record>::_M_insert_overflow(Rva0052D742Record*,const Rva0052D742Record&,const _STL::__false_type&,unsigned int,bool);
