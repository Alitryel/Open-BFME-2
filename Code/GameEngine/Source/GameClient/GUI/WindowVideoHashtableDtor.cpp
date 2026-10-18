// cl: /MD /O1 /GX /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
// Retail RVA 0x0053F378, 57 bytes.
// ??1?$hashtable@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@PBVGameWindow@@UhashConstGameWindowPtr@WindowVideoManager@@U?$_Select1st@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@U?$equal_to@PBVGameWindow@@@2@V?$allocator@U?$pair@QBVGameWindow@@PAVWindowVideo@@@_STL@@@2@@_STL@@QAE@XZ
// WindowVideoMap hashtable dtor, called by WindowVideoManager dtor at 0x0053F45C.
// Same 57B direct-_free shape as the ArmorStore hashtable dtor at 0x003609BE
// (clear then free buckets, MALLOC config). Clear resolves to the pinned
// WindowVideo spelling at 0x001DBCDC, _free is rowed at 0x00030830.
// Use the native 17-byte specialization at RVA 0x00013740 rather than
// emitting a separately optimized copy from this unit.
#define _STLP_BFME_COPY_TRIVIAL_EXTERN  // call retail's one __copy_trivial (vendor/stlport/stl/_algobase.h)
#include <stl/_algobase.h>
namespace _STL {
template <> const unsigned int &max<unsigned int>(const unsigned int &, const unsigned int &);
}

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline void * & vector<void *,allocator<void *> >::operator[](unsigned int n) { return *(this->_M_start + n); } }
// bfme link decl-only begin
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_clear(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_fill_insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_insert_overflow(void **, void *const &, __true_type const &, unsigned int, bool); }
namespace _STL { template <> void vector<void *, allocator<void *> >::_M_set(void **, void **, void **); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> unsigned int vector<void *, allocator<void *> >::capacity() const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::end(); }
namespace _STL { template <> void vector<void *, allocator<void *> >::insert(void **, unsigned int, void *const &); }
namespace _STL { template <> void vector<void *, allocator<void *> >::reserve(unsigned int); }
// bfme link decl-only end

class GameWindow;
class WindowVideo;

class WindowVideoManager
{
public:
	struct hashConstGameWindowPtr
	{
		size_t operator()(const GameWindow *const &p) const
		{
			return (size_t)p;
		}
	};
};

typedef std::hash_map<const GameWindow *, WindowVideo *,
	WindowVideoManager::hashConstGameWindowPtr,
	std::equal_to<const GameWindow *> > WindowVideoMap;

class WindowVideoHashtableHolder
{
public:
	WindowVideoHashtableHolder();
	~WindowVideoHashtableHolder();

private:
	WindowVideoMap m_map;
};

// ??0WindowVideoHashtableHolder@@QAE@XZ present-unmatched
WindowVideoHashtableHolder::WindowVideoHashtableHolder()
{
	m_map.clear();
}

// ??1WindowVideoHashtableHolder@@QAE@XZ present-unmatched
WindowVideoHashtableHolder::~WindowVideoHashtableHolder()
{
	m_map.clear();
}
