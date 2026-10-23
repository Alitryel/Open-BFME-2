// cl: /O1 /DNDEBUG /MD
//
// ??_GResourceGatheringManager@@UAEPAXI@Z, retail 0x004F5F2E (28 bytes):
// slot 0 of vtable 0x00C6327C, whose slot-2 name getter returns
// "ResourceGatheringManager" (the only vtable using that getter). Scalar
// deleting destructor: calls the rowed ResourceGatheringManager::
// ~ResourceGatheringManager (0x004F5BB0) and then the global operator delete
// when bit 0 of the flags is set.
// Zero Hour pools the class (MEMORY_POOL_GLUE, a class operator delete);
// BFME 2's 28-byte form frees through the global operator delete, so the
// class is modelled with none. The destructor is declared, not defined, so
// the call resolves to the rowed body; the dummy tag constructor (no retail
// counterpart) only makes this TU emit the vtable and with it the deleting destructor.

struct EmitVtableTag;

class ResourceGatheringManager
{
public:
	ResourceGatheringManager(EmitVtableTag *);
	virtual ~ResourceGatheringManager();
public:
	virtual void bfmeVtSlot1() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot2() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot3() = 0; // __purecall in every copy of this vtable
};

// ?<ResourceGatheringManager::ResourceGatheringManager> absent-from-retail
ResourceGatheringManager::ResourceGatheringManager(EmitVtableTag *)
{
}
