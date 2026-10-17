// cl: /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /Ireference/shims/bfme2_ascii /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva0022BD25Subsystem@@QAE@XZ, retail 0x0041F913 (55B).
// Subsystem ctor for TheArmyDefinitionManager: base BFME2NativeNetwork via rowed baseConstruct 0x001B4E63 plus hash_map member at +0xC via rowed 0x0041F8F4 and vtable 0x00C3B8C8. Evidence: pin ??0Rva0022BD25Subsystem@@QAE@XZ; caller 0x0022F955 in GameEngine::init new Rva0022BD25Subsystem; vtable slot0 rowed Rva0041F94A deleting wrapper.
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
// Suppress this TU's non-retail vector<void*> size/begin/end copies (family2-LK3 rows 17/6/9):
// the retail copies serve the link. Plain declaration-only form (no __imp_).
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}
#include "ascii_string.h"
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
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end

struct Rva0041F8F4Element
{
	char bytes[1];
};

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class __declspec(novtable) Rva0022BD25SubsystemBase
{
public:
	Rva0022BD25SubsystemBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~Rva0022BD25SubsystemBase();
private:
	unsigned char m_04;
	int m_08;
};

class Rva0022BD25Subsystem : public Rva0022BD25SubsystemBase
{
public:
	Rva0022BD25Subsystem();
	virtual ~Rva0022BD25Subsystem();
private:
	_STL::hash_map<int, Rva0041F8F4Element> m_map0C;
};

Rva0022BD25Subsystem::Rva0022BD25Subsystem()
{
}
