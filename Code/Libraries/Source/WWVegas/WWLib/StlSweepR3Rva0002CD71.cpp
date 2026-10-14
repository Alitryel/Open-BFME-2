// cl: /O1 /EHs /D_BFME_RETAIL_TREE_INSERT_LAYOUT /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /D_STLP_NO_EXCEPTIONS /Ireference/shims/bfmealloc
// stlport
// 0x0002CD71 (5B), unreferenced: the destructor of a holder whose only
// member is the Rva0002CCC3Record hash set at +0, a tail jump into the rowed
// hashtable destructor (0x0002CCC3, StlSweepR3Rva0002CCC3.cpp). The
// declaration-only specialisation keeps that call out of line, as retail
// does. Record spelling copied from that unit; the owner is address-derived.
#include <hash_set>

struct Rva0002CCC3Record {char bytes[1];bool operator<(const Rva0002CCC3Record&)const;bool operator==(const Rva0002CCC3Record&)const;};
namespace _STL {template<>struct hash<Rva0002CCC3Record> {unsigned int operator()(const Rva0002CCC3Record&)const;};}
typedef _STL::hashtable<Rva0002CCC3Record,Rva0002CCC3Record,_STL::hash<Rva0002CCC3Record>,_STL::_Identity<Rva0002CCC3Record>,_STL::equal_to<Rva0002CCC3Record>,_STL::allocator<Rva0002CCC3Record> > Rva0002CCC3Table;
namespace _STL {template <> Rva0002CCC3Table::~hashtable();}

class Rva0002CD71
{
public:
	~Rva0002CD71();
private:
	Rva0002CCC3Table m_00;
};

Rva0002CD71::~Rva0002CD71()
{
}
