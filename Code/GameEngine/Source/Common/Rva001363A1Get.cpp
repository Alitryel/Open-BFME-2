// ?Rva001363A1Get@@YAPBDI@Z @0x001363A1 43B
// cl: /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// Unlock map unsigned-to-ptr lookup plus empty-string fallback plus data-plus-8. Evidence: callee 0x00357180 rowed map find; globals 0x00DF29B4 no name yet 0x007BAC1C empty in use; callers 0x0014C85F 0x0014CBB0 unclaimed; prev 0x0013623C next 0x001363CC.
#include <map>
// map<unsigned> internals otherwise emit the less<unsigned>::operator()
// COMDAT in a register shape retail's 0x00758C50 does not have. The compare
// is inlined into the map's _M_find (retail's 0x00357180 compares in place),
// so an inline-only specialization keeps it there and emits no copy; a
// declaration-only one would turn this TU's _M_find into a call.
namespace _STL {
template <> __declspec(dllimport) __forceinline bool less<unsigned int>::operator()(const unsigned int &a, const unsigned int &b) const { return a < b; }
}

// The unsigned-to-pointer map at 0x00DF29B4 is defined once, by its global
// dtor thunk's unit, as g_Va00DF29B4; read it through the map view.
extern unsigned int g_Va00DF29B4;
typedef _STL::map<unsigned int, void *> Rva001363A1Map;

const char *Rva001363A1Get(unsigned int key)
{
	Rva001363A1Map &map = *(Rva001363A1Map *)&g_Va00DF29B4;
	Rva001363A1Map::iterator it = map.find(key);
	if (it == map.end())
		return 0;
	void *p = it->second;
	return p != 0 ? (const char *)p + 8 : "";
}
