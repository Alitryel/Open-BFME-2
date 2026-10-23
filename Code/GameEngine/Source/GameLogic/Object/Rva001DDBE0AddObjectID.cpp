// cl: -DNDEBUG -MD -EHsc -Ireference/open-bfme-1/game/GameEngine/Source/GameLogic/Object
// stlport
//
// Retail 0x001DDBE0: inlined vector<ObjectID>::push_back of Object::m_id at
// +0x74, container at this+8, always returns true.  Overflow calls the
// ObjectID insert pin at 0x00010B8B.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
#include <stl/_algobase.h>
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}

#include <vector>

enum ObjectID
{
	INVALID_OBJECT_ID = 0
};

class Object
{
public:
	ObjectID getID() const { return m_id; }

	unsigned char m_pad[0x74];
	ObjectID m_id;
};

class Rva001DDBE0Holder
{
public:
	bool addObject(Object *objectToAdd);

private:
	unsigned char m_pad[8];
	_STL::vector<ObjectID> m_ids;
};

// bfme link decl-only begin
namespace _STL { template <> void vector<ObjectID,_STL::allocator<ObjectID> >::_M_clear(); }
namespace _STL { template <> void vector<ObjectID,_STL::allocator<ObjectID> >::_M_insert_overflow(ObjectID *,ObjectID const &,_STL::__false_type const &,unsigned int,bool); }
namespace _STL { template <> ObjectID * allocator<ObjectID>::allocate(unsigned int,void const *) const; }
namespace _STL { template <> void _STLP_alloc_proxy<ObjectID *,ObjectID,_STL::allocator<ObjectID> >::deallocate(ObjectID *,unsigned int); }
namespace _STL { template <> void allocator<ObjectID>::deallocate(ObjectID *,unsigned int) const; }
namespace _STL { template <> void vector<ObjectID,_STL::allocator<ObjectID> >::push_back(ObjectID const &); }
// bfme link decl-only end
bool Rva001DDBE0Holder::addObject(Object *objectToAdd)
{
	m_ids.push_back(objectToAdd->getID());
	return true;
}
