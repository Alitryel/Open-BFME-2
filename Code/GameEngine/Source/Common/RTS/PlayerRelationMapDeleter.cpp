// cl: /O1 /DNDEBUG /MD
//
// ??_GPlayerRelationMap@@MAEPAXI@Z, retail 0x002ADE55 (28 bytes): slot 0
// of vtable 0x00BFDD90, whose slot-2 name getter returns "PlayerRelationMap" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x002AD078 and then the global operator delete when bit 0 of
// the flags is set. That destructor re-stores vtable 0x00BFDD90, which
// identifies it as PlayerRelationMap::~PlayerRelationMap (pinned in reverse/symbols.csv).
// Class shape from Zero Hour's Common/Player.h (pooled).
// Zero Hour pools the class (MEMORY_POOL_GLUE: protected virtual
// destructor and an inline class operator delete); BFME 2's form frees
// through the global operator delete, so the class is modelled with none.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

class PlayerRelationMap
{
public:
	PlayerRelationMap(EmitVtableTag *);
protected:
	virtual ~PlayerRelationMap();
public:
	virtual void bfmeVtSlot1() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot2() = 0; // __purecall in every copy of this vtable
	virtual void bfmeVtSlot3() = 0; // __purecall in every copy of this vtable
};

// ?<PlayerRelationMap::PlayerRelationMap> absent-from-retail
PlayerRelationMap::PlayerRelationMap(EmitVtableTag *)
{
}
