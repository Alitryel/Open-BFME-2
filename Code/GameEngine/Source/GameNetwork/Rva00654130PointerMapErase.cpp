// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc -D_STLP_USE_STATIC_LIB -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// stlport
// Open-BFME5: erase one owned pointer payload from the map at +0x5c.

#include <map>
// Keep __node_alloc<true,0>::deallocate inline-only: every call here is inlined,
// and this TU's /O1 COMDAT copy differs from the copy the link keeps.
namespace _STL {
template <> __declspec(dllimport) __forceinline
void _STLP_CALL __node_alloc<true, 0>::deallocate(void *__p, size_t __n)
{ if (__n > (size_t)_MAX_BYTES) __stl_delete(__p); else _M_deallocate(__p, __n); }
}

// Compare nodes locally so this TU does not emit a conflicting iterator-base wrapper.
namespace _STL {
template <class T, class LeftTraits, class RightTraits>
static inline bool operator!=(const _Rb_tree_iterator<T, LeftTraits>& a,
                              const _Rb_tree_iterator<T, RightTraits>& b)
{ return a._M_node != b._M_node; }
}

void __cdecl operator delete(void *memory);

class Gen_00654130
{
public:
	void bfmeErase(void *key);

private:
	unsigned char m_prefix[0x5c];
	_STL::map<void *, void *> m_values;
};

void Gen_00654130::bfmeErase(void *key)
{
	if (key == 0)
		return;

	_STL::map<void *, void *> *values = &m_values;
	_STL::map<void *, void *>::iterator found = values->find(key);
	if (found != values->end())
	{
		void *payload = found->second;
		if (payload != 0)
			::operator delete(payload);
		values->erase(found);
	}
}
