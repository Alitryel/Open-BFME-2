// cl: /EHsc /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /D_STLP_USE_MALLOC /DNDEBUG /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// Bodies ported from Open-BFME-1's
// GameEngine/Source/Common/Rva00787C20HashOwnerDestructor.cpp (donor revision
// 6d9434269164392c5ba62aaa7c15a86b5b020d76, donor flags plus /O1). Compiled
// that way each body below places uniquely on unclaimed game.dat .text by
// masked whole-.text search, and ./build.sh reproduces it byte for byte:
// Rva00787C20::~Rva00787C20 0x000AAE59 (176B). Callee addresses are read off
// retail's call sites (reverse/symbols.csv). Only the placed bodies are
// carried; the donor's other definitions are omitted.
// The retail body is an owning destructor: it frees the auxiliary buffer,
// then destroys two 12-byte-value hash maps and an AsciiString member.

#include <algorithm>
#include <hash_map>
#include <cstddef>
// Import-inline the vector<void*> accessors: the hashtable members inline them as
// retail does (begin 0x00427195), and this unit's out-of-line copies are not the
// ones the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline size_t vector<void*>::size() const { return size_t(_M_finish - _M_start); }
template <> __declspec(dllimport) __forceinline void **vector<void*>::begin() { return _M_start; }
template <> __declspec(dllimport) __forceinline void **vector<void*>::end() { return _M_finish; }
template <> __declspec(dllimport) __forceinline void *&vector<void*>::operator[](size_t n) { return *(begin() + n); }
}

#include "ascii_string.h"
// Import-inline: every __malloc_alloc<0>::deallocate use here is inlined, and this
// unit's out-of-line copy (referenced from .debug$F alone) is not the one the link keeps.
namespace _STL { template <> __declspec(dllimport) __forceinline void _STLP_CALL __malloc_alloc<0>::deallocate(void *__p, size_t) { free((char *)__p); } }
// bfme link decl-only begin
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

struct Gen_t_00786db0_p12cd
{
	int a[3];
	Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd(const Gen_t_00786db0_p12cd &);
	~Gen_t_00786db0_p12cd();
	Gen_t_00786db0_p12cd &operator=(const Gen_t_00786db0_p12cd &);
};

struct Gen_t_00786e70_p12cd
{
	int a[3];
	Gen_t_00786e70_p12cd();
	Gen_t_00786e70_p12cd(const Gen_t_00786e70_p12cd &);
	~Gen_t_00786e70_p12cd();
	Gen_t_00786e70_p12cd &operator=(const Gen_t_00786e70_p12cd &);
};

bool operator==(const Gen_t_00786db0_p12cd &, const Gen_t_00786db0_p12cd &);
bool operator<(const Gen_t_00786db0_p12cd &, const Gen_t_00786db0_p12cd &);
bool operator==(const Gen_t_00786e70_p12cd &, const Gen_t_00786e70_p12cd &);
bool operator<(const Gen_t_00786e70_p12cd &, const Gen_t_00786e70_p12cd &);

typedef _STL::pair<const int, Gen_t_00786db0_p12cd> Rva00787C20PairA;
typedef _STL::pair<const int, Gen_t_00786e70_p12cd> Rva00787C20PairB;
typedef _STL::hash_map<int, Gen_t_00786db0_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva00787C20PairA> > Rva00787C20MapA;
typedef _STL::hash_map<int, Gen_t_00786e70_p12cd, _STL::hash<int>,
	_STL::equal_to<int>, _STL::allocator<Rva00787C20PairB> > Rva00787C20MapB;

void __cdecl Rva00787C20CleanupA(Rva00787C20PairA &);
void __cdecl Rva00787C20CleanupB(Rva00787C20PairB &);

class Rva00787C20
{
public:
	~Rva00787C20();

private:
	AsciiString m_name;
	void *m_buffer;
	Rva00787C20MapA m_first;
	Rva00787C20MapB m_second;
};

Rva00787C20::~Rva00787C20()
{
	delete [] (char *)m_buffer;
	m_buffer = 0;
	_STL::for_each(m_first.begin(), m_first.end(), Rva00787C20CleanupA);
	_STL::for_each(m_second.begin(), m_second.end(), Rva00787C20CleanupB);
}
