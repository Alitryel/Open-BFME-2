// cl: /O1 /DNDEBUG /MD /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS
// stlport
//
// ?rva00397756@Rva00397756@@QAEXPAUIdRange@@H@Z @0x00397756 59B: over every
// ObjectID in [first,last), resolve it through GameLogic::findObjectByID
// (rowed 0x00049DC5) and pass found objects with the second parameter to the
// pinned 0x0023D0C2 GameLogic entry. Called as the outer-0xC sweep by
// Rva00397791 (0x00397791).
//
// Evidence: retail reloads TheGameLogic at the loop top and keeps it in EBX
// across both calls. That needs the object hash lookup to be visible (the
// header inline over the map at +0xB4, as in the SpawnBehavior walks): with
// only a declared findObjectByID the second use reloads the global.
#define _STLP_NO_EXCEPTIONS 1
#include <hash_map>

// Keep the inline accessors without emitting per-unit COMDAT copies (retail's
// one out-of-line vector<void*> size/begin is the /Od body at 0x00023BC0/0x00023B90).
namespace _STL {
template <> __declspec(dllimport) __forceinline
void *const *vector<void*>::begin() const { return this->_M_start; }
template <> __declspec(dllimport) __forceinline
size_t vector<void*>::size() const { return size_t(this->_M_finish - this->_M_start); }
template <> __declspec(dllimport) __forceinline void *const &vector<void *>::operator[](size_t __n) const { return *(begin() + __n); }
}

#include "../../../Common/GameLogicObjectLookupView.h"

struct IdRange
{
	ObjectID *first;
	ObjectID *last;
};

typedef _STL::hash_map<ObjectID, Object *, _STL::hash<int>, _STL::equal_to<ObjectID> > ObjectPtrHash;

// The canonical GameLogic view declares findObjectByID (rowed 0x00049DC5); this
// unit defines it inline over the map at +0xB4, as the SpawnBehavior walks do.
inline Object *GameLogic::findObjectByID(ObjectID id)
{
	if (id == INVALID_OBJECT_ID)
		return 0;
	ObjectPtrHash &map = *reinterpret_cast<ObjectPtrHash *>(reinterpret_cast<char *>(this) + 0xB4);
	ObjectPtrHash::iterator it = map.find(id);
	if (it == map.end())
		return 0;
	return (*it).second;
}

extern GameLogic *TheGameLogic;

class Rva00397756
{
public:
	void rva00397756(IdRange *range, int arg);
};

void Rva00397756::rva00397756(IdRange *range, int arg)
{
	ObjectID *p = range->first;
	if (p == range->last)
		return;
	do {
		Object *obj = TheGameLogic->findObjectByID(*p);
		if (obj != 0)
			TheGameLogic->rva0023D0C2(obj, arg);
		++p;
	} while (p != range->last);
}
