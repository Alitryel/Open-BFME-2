// cl: /O1 /DNDEBUG /MD /EHsc /G7 /arch:SSE /Ireference/shims/bfme2_ascii /D_STLP_USE_STATIC_LIB
// stlport
// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#define _STLP_BFME_LOWER_BOUND_EXTERN  // call retail's one __lower_bound<const size_t*> (vendor/stlport/stl/_hashtable.c)
#include <hash_map>
#include <cstddef>
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
// map<unsigned> internals otherwise instantiate the less<unsigned>::operator()
// COMDAT (one byte shape per TU flags); an explicit specialization declaration
// suppresses this TU's copy so callers bind retail's instead.
namespace _STL {
template <> bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const;
// Suppress this TU's non-retail vector<void*> size copy (family2-LK3 row 17):
// the retail copy serves the link. Plain declaration-only form (no __imp_).
template <> size_t vector<void*>::size() const;
template <> void **vector<void*>::begin();
template <> void **vector<void*>::end();
}

class BFME2NativeNetwork
{
public:
};

// 0x001B4E63 is the rowed SubsystemInterface ctor.
class SubsystemInterface { public: SubsystemInterface(); };

class __declspec(novtable) BFME2NativeNetworkBase
{
public:
	__forceinline BFME2NativeNetworkBase() { reinterpret_cast<SubsystemInterface *>(this)->SubsystemInterface::SubsystemInterface(); }
	virtual ~BFME2NativeNetworkBase();
private:
	char m_flag;
	int m_value;
};

struct Rva003EF584Element { char bytes[1]; bool operator<(const Rva003EF584Element &) const; bool operator==(const Rva003EF584Element &) const; };
namespace _STL { template<> struct hash<Rva003EF584Element> { unsigned operator()(const Rva003EF584Element &) const; }; }

// ??0Rva0022B0B8Subsystem@@QAE@XZ @0x003EF5A3 55B
// Target evidence: called by GameEngine::init at 0x0022F279; target calls
// rowed baseConstruct and hash_map ctor, stores vtable 0x008363D8, then returns.
// Class name is address-derived; the base and one-map layout are structural inference.
class Rva0022B0B8Subsystem : public BFME2NativeNetworkBase
{
public:
	Rva0022B0B8Subsystem();
	virtual ~Rva0022B0B8Subsystem();

private:
	_STL::hash_map<int, Rva003EF584Element> m_map;
};

Rva0022B0B8Subsystem::Rva0022B0B8Subsystem()
	: m_map()
{
}
