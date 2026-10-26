// STLport 4.5.3 hashtable destructors (and their clear) for the two maps
// ~Rva00787C20 (0x000AAE59, Rva00787C20HashOwnerDestructor.cpp) destroys.
// Both destructors fold at 0x000AACAB, the 57-byte EH-framed body that calls
// the shared 72-byte clear 0x001DBCDC; that clear frees each node without
// running a value destructor, so the 12-byte values are trivially
// destructible. The destructor unit only declares the table destructors; this
// unit supplies them, the unmodified official templates at the flags of
// SelectionIDMapDestructor.cpp, which emits the same pair of bodies.
// cl: /O1 /G7 /GX /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#define _STLP_BFME_LOWER_BOUND_EXTERN
#include <hash_map>

struct Gen_t_00786db0_p12cd
{
	int a[3];
};

struct Gen_t_00786e70_p12cd
{
	int a[3];
};

typedef _STL::pair<const int, Gen_t_00786db0_p12cd> Rva00787C20PairA;
typedef _STL::pair<const int, Gen_t_00786e70_p12cd> Rva00787C20PairB;
typedef _STL::hashtable<Rva00787C20PairA, int, _STL::hash<int>, _STL::_Select1st<Rva00787C20PairA>,
	_STL::equal_to<int>, _STL::allocator<Rva00787C20PairA> > Rva00787C20TableA;
typedef _STL::hashtable<Rva00787C20PairB, int, _STL::hash<int>, _STL::_Select1st<Rva00787C20PairB>,
	_STL::equal_to<int>, _STL::allocator<Rva00787C20PairB> > Rva00787C20TableB;

template Rva00787C20TableA::~hashtable();
template Rva00787C20TableB::~hashtable();
template void Rva00787C20TableA::clear();
template void Rva00787C20TableB::clear();
