// cl: /Ireference/shims/bfme2_ascii /GX /DNDEBUG /MD /D_STLP_USE_STATIC_LIB
// stlport
// ?rva003F255C@Rva003F255C@@QAEXPBVModuleData@@@Z @0x003F255C 26B
// Null-checked push_back into vector at +0xfc. Retail cmp [esp+4] je then
// lea eax [esp+4] push eax add ecx 0xfc call push_back vector PBVModuleData.
// Evidence: unlock lane, callee rowed push_back 0x004DFCB0, caller 0x003F2576
// (LivingWorldRegion ModuleData INI string), prev LivingWorldRegionConnection
// dtor / next Rva003F26AAFinish give flags and stlport vector usage.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

class ModuleData;

class Rva003F255C
{
public:
	void rva003F255C(const ModuleData *p);
private:
	char _pad[0xfc];
	_STL::vector<const ModuleData *> m_vec; // +0xfc
};

// bfme link decl-only begin
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_clear(); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_insert_overflow(ModuleData const * *,ModuleData const * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> ModuleData const * * _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::allocate(unsigned int); }
namespace _STL { template <> void * __node_alloc<1,0>::allocate(unsigned int); }
namespace _STL { template <> ModuleData const * * allocator<ModuleData const *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::deallocate(ModuleData const * *,unsigned int); }
namespace _STL { template <> void __node_alloc<1,0>::deallocate(void *,unsigned int); }
namespace _STL { template <> void allocator<ModuleData const *>::deallocate(ModuleData const * *,unsigned int) const; }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::push_back(ModuleData const * const &); }
// bfme link decl-only end
void Rva003F255C::rva003F255C(const ModuleData *p)
{
	if (p != 0)
		m_vec.push_back(p);
}
