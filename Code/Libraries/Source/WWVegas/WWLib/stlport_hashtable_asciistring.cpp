// cl: /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /EHsc /MD /D_STLP_USE_STATIC_LIB /D_STLP_USE_MALLOC /D_CRTIMP=
// stlport
// ??$_M_find@VAsciiString@@@?$hashtable@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@VAsciiString@@U?$hash@VAsciiString@@@rts@@U?$_Select1st@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@@2@U?$equal_to@VAsciiString@@@5@V?$allocator@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@@2@@_STL@@ABEPAU?$_Hashtable_node@U?$pair@$$CBVAsciiString@@PAVThingTemplate@@@_STL@@@1@ABVAsciiString@@@Z,
// retail 0x0016D710, 70 bytes. Dedicated TU.
//
// ThingFactory's template-name map (hash_map<AsciiString, ThingTemplate*>).
// The node value is a 12-byte pair (proven by the 3-dword pair copy at
// 0x16CC30 and the new(0x10) node at 0x16E230), so this map's AsciiString
// key is 8 bytes: the find hashes ([key+4] << 16) + [key+0] and walks nodes
// comparing [node+4]/[node+8] against [key+0]/[key+4]. The halves are named
// neutrally (their exact string semantics are not recoverable from these
// bytes). rts::hash inlines to the shift-add formula and the memberwise
// operator== inlines to the two-dword walk compare, so the body is
// call-free like retail. Table layout (buckets.start+4/finish+8) and the
// div/modulo bucket selection fall out of the STLport 4.5.3 hashtable.

// Match the malloc-backed bucket-vector operations used by DamageFX_hashtableResize.cpp.
#define _STLP_NO_EXCEPTIONS 1
#include <vector>
namespace _STL {
template <> __declspec(dllimport) __forceinline unsigned int vector<void *>::size() const
{ return (unsigned int)(_M_finish - _M_start); }
template <> _STLP_alloc_proxy<void **, void *, allocator<void *> >::~_STLP_alloc_proxy();
template <> __declspec(dllimport) __forceinline _Vector_base<void *, allocator<void *> >::~_Vector_base()
{ if (_M_start != 0) _M_end_of_storage.deallocate(_M_start, _M_end_of_storage._M_data - _M_start); }
}
#include <hash_map>
namespace _STL {
template <> __declspec(dllimport) __forceinline void __malloc_alloc<0>::deallocate(void *p, size_t)
{ free((char *)p); }
template <> __declspec(dllimport) __forceinline void *&vector<void *>::operator[](unsigned int n)
{ return *(_M_start + n); }
template <> allocator<void *> vector<void *>::get_allocator() const;
template <> void advance<unsigned int const *, int>(unsigned int const *&, int);
template <> void __advance<unsigned int const *, int>(unsigned int const *&, int, random_access_iterator_tag const &);
template <> void *__malloc_alloc<0>::allocate(size_t);
}

class ThingTemplate;

class AsciiString
{
public:
	bool operator==(const AsciiString &other) const
	{
		return m_first == other.m_first && m_second == other.m_second;
	}

	unsigned m_first;
	unsigned m_second;
};

namespace rts
{

template <class T>
struct hash
{
};

// Both functors are expanded at every use and never called out of line, so this unit
// emits no copy of either (import-inline).
template <>
struct hash<AsciiString>
{
	// NOTE: summands swapped vs the naive shift-first order. The scheduler
	// canonicalizes most spellings identically; this order is tried for its
	// effect on the bucket-size load scheduling (retail computes the size
	// first and subtracts the start from memory).
	__declspec(dllimport) __forceinline size_t operator()(const AsciiString &key) const
	{
		return key.m_first + (key.m_second << 16);
	}
};

template <class T>
struct equal_to
{
};

template <>
struct equal_to<AsciiString>
{
	// NOTE: memberwise-inline double-word compare, NOT a call to the
	// out-of-line operator==. Retail's walk compares [node+4]/[node+8]
	// against [key+0]/[key+4] with no calls; the identically-named
	// out-of-line body at 0x6E054B (which forwards to operator==) belongs
	// to another TU's view of this functor.
	__declspec(dllimport) __forceinline bool operator()(const AsciiString &a, const AsciiString &b) const
	{
		return a.m_first == b.m_first && a.m_second == b.m_second;
	}
};

}

typedef _STL::hashtable<_STL::pair<const AsciiString, ThingTemplate *>, AsciiString, rts::hash<AsciiString>, _STL::_Select1st<_STL::pair<const AsciiString, ThingTemplate *> >, rts::equal_to<AsciiString>, _STL::allocator<_STL::pair<const AsciiString, ThingTemplate *> > > ThingTemplateTable;
template _STL::_Hashtable_node<_STL::pair<const AsciiString, ThingTemplate *> > *ThingTemplateTable::_M_find<AsciiString>(const AsciiString &) const;
template _STL::pair<const AsciiString, ThingTemplate *> &ThingTemplateTable::_M_insert(const _STL::pair<const AsciiString, ThingTemplate *> &);
