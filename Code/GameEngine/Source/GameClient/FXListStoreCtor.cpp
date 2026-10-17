// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib
// stlport

#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include "PreRTS.h"
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include <hash_map>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
}
#include "Common/NameKeyGenerator.h"
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::size() const; }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

// vector<int>/char destruction otherwise instantiates per-TU allocator
// deallocate COMDATs (one byte shape per TU flags); explicit
// dllimport+forceinline specializations take those calls inline so this
// TU emits no external copies. Bodies are verbatim primary.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void allocator<int>::deallocate(int* __p, size_t __n) const {
  _STLP_ASSERT( (__p == 0) == (__n == 0) )
    if (__p != 0) __sgi_alloc::deallocate((void*)__p, __n * sizeof(value_type));
}
template <> void _STLP_alloc_proxy<int*, int, allocator<int> >::deallocate(int*, size_t);
// Declaration-only: retail keeps one 14-byte copy of the vector<int> teardown
// (0x0007FAB3); this TU's flags would emit a private 24-byte one.
template <> vector<int, allocator<int> >::~vector();
template <> _Vector_base<int, allocator<int> >::~_Vector_base();
}

class FXNugget;

class FXList
{
public:
	FXList();
	virtual ~FXList();
};

class FXListStore : public SubsystemInterface
{
public:
	FXListStore();
	virtual ~FXListStore();

	virtual void init() {}
	virtual void reset() {}
	virtual void update() {}

private:
	char m_subsystemPad[4];
	typedef std::hash_map<NameKeyType, FXList, rts::hash<NameKeyType>, rts::equal_to<NameKeyType> > FXListMap;
	FXListMap m_fxmap;
	typedef std::vector<int> FXNuggetVector;
	FXNuggetVector m_nuggets;
};

// ??0FXListStore@@QAE@XZ
FXListStore::FXListStore()
{
}
