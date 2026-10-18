// cl: /DNDEBUG /MD /D_CRTIMP= /EHsc /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DWIN32 /D_WINDOWS
// stlport
//
// ?setBuildableStatusOverride@GameLogic@@QAEXPBVThingTemplate@@W4BuildableStatus@@@Z
// Target evidence: retail 0x00246F71 is a 29-byte Ghidra function. Its body
// null-checks the first argument, passes ThingTemplate+0x64 as the key to the
// hash map at GameLogic+0x10, then writes the second argument through the
// returned value pointer. The operation's semantic identity is inferred from
// that behavior and the matching retail call relationships; the offsets below
// are target-specific structural evidence, not donor layout claims.

#include <hash_map>
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline unsigned int vector<void *,allocator<void *> >::size()const  { return (unsigned int)(this->_M_finish - this->_M_start); } }
// Bind to the kept retail copy instead of emitting this unit's own.
namespace _STL { template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(unsigned int const &x,unsigned int const &y)const  { return x < y; } }
// bfme link decl-only begin
namespace _STL { template <> void swap<_STLP_alloc_proxy<void **, void *, allocator<void *> > >(_STLP_alloc_proxy<void **, void *, allocator<void *> > &, _STLP_alloc_proxy<void **, void *, allocator<void *> > &); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::_Vector_base(unsigned int, allocator<void *> const &); }
namespace _STL { template <> vector<void *, allocator<void *> >::vector(unsigned int, void *const &, allocator<void *> const &); }
namespace _STL { template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy(); }
namespace _STL { template <> _Vector_base<void *, allocator<void *> >::~_Vector_base(); }
namespace _STL { template <> vector<void *, allocator<void *> >::~vector(); }
namespace _STL { template <> void *& vector<void *, allocator<void *> >::operator[](unsigned int); }
namespace _STL { template <> void ** allocator<void *>::allocate(unsigned int, void const *) const; }
namespace _STL { template <> void ** vector<void *, allocator<void *> >::begin(); }
namespace _STL { template <> allocator<void *> vector<void *, allocator<void *> >::get_allocator() const; }
namespace _STL { template <> void vector<void *, allocator<void *> >::swap(vector<void *, allocator<void *> > &); }
namespace _STL { template <> allocator<void *>::~allocator(); }
// bfme link decl-only end
// Suppress the TU's non-retail const-begin copy (row 47 family2-LK3): the
// /Od retail copy in stlport_vector_voidptr.cpp serves the link instead.
namespace _STL {
template <> vector<void *>::const_iterator _STL::vector<void *>::begin() const;
}

typedef unsigned int size_t;

class AsciiString
{
	unsigned int m_first;
	unsigned int m_second;
};

enum BuildableStatus
{
	BUILDABLE_STATUS_UNKNOWN = 0
};

namespace rts
{
	template <class T> struct hash
	{
		size_t operator()(const T &value) const;
	};

	template <class T> struct equal_to
	{
		bool operator()(const T &left, const T &right) const;
	};
}

typedef _STL::pair<const AsciiString, BuildableStatus> BuildableStatusPair;
typedef _STL::hash_map<AsciiString, BuildableStatus, rts::hash<AsciiString>,
	rts::equal_to<AsciiString>, _STL::allocator<BuildableStatusPair> > BuildableMap;

class ThingTemplate; // +0x64 AsciiString key; NOT ThingTemplate::getName (kept +0x10 in ThingFactory.cpp), retail inlines +0x64

class GameLogic
{
	char m_unknown00[0x10];
	BuildableMap m_thingTemplateBuildableOverrides;

public:
	void setBuildableStatusOverride(const ThingTemplate *tt, BuildableStatus bs);
};

void GameLogic::setBuildableStatusOverride(const ThingTemplate *tt, BuildableStatus bs)
{
	if (tt)
		m_thingTemplateBuildableOverrides[*reinterpret_cast<const AsciiString *>(
			reinterpret_cast<const char *>(tt) + 0x64)] = bs;
}
