// cl: /Ireference/shims/bfme2_ascii /MD
// stlport
// ?rva00223CBD@Rva00223CBD@@QAEXPBVModuleData@@@Z @0x00223CBD 30B
// Vector push_back at +0x2FC via rowed 0x004DFCB0 then flag at +0x308 set to 1.
// Evidence: lea eax esp+8 plus lea ecx esi+0x2FC matches const-ref push_back; ret 4 one pointer arg; neighbours share /O1 /MD; unblocks 0x0040FB9C 0x002B5195 0x00224296 0x005157EE.
// Use the native 17-byte specialization at RVA 0x00013740 rather than
// emitting a separately optimized copy from this unit.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <vector>

class ModuleData;

class Rva00223CBD
{
public:
	void rva00223CBD(const ModuleData *p);
private:
	char m_pad[0x2FC];
	_STL::vector<const ModuleData *> m_vec;
	bool m_flag;
};

// bfme link decl-only begin
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_clear(); }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::_M_insert_overflow(ModuleData const * *,ModuleData const * const &,_STL::__true_type const &,unsigned int,bool); }
namespace _STL { template <> ModuleData const * * allocator<ModuleData const *>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ModuleData const * *,ModuleData const *,_STL::allocator<ModuleData const *> >::deallocate(ModuleData const * *,unsigned int); }
namespace _STL { template <> void allocator<ModuleData const *>::deallocate(ModuleData const * *,unsigned int) const; }
namespace _STL { template <> void vector<ModuleData const *,_STL::allocator<ModuleData const *> >::push_back(ModuleData const * const &); }
// bfme link decl-only end
void Rva00223CBD::rva00223CBD(const ModuleData *p)
{
	m_vec.push_back(p);
	m_flag = true;
}
