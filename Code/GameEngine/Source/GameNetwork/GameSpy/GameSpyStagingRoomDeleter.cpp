// cl: /O1 /DNDEBUG /MD
//
// ??_GGameSpyStagingRoom@@UAEPAXI@Z, retail 0x00383768 (28 bytes): slot 0
// of vtable 0x00C19440, whose slot-2 name getter returns "GameSpyStagingRoom" (the only
// vtable using that getter). Scalar deleting destructor: calls the
// destructor at 0x00382C4A and then the global operator delete when bit 0 of
// the flags is set. A class's compiler-generated deleting destructor calls
// that class's destructor, so the callee is GameSpyStagingRoom::~GameSpyStagingRoom (pinned in
// reverse/symbols.csv; its SEH body does not re-store the vtable).
// Class shape from Zero Hour's GameNetwork/GameSpy/StagingRoomGameInfo.h (implicit public destructor).
// BFME 2's form frees through the global operator delete.
// The destructor is declared, not defined, so the call resolves to the pin;
// the dummy tag constructor (no retail counterpart) only makes this TU emit
// the vtable and with it the deleting destructor.

struct EmitVtableTag;

class GameSpyStagingRoom
{
public:
	GameSpyStagingRoom(EmitVtableTag *);
	virtual ~GameSpyStagingRoom();
};

// ?<GameSpyStagingRoom::GameSpyStagingRoom> absent-from-retail
GameSpyStagingRoom::GameSpyStagingRoom(EmitVtableTag *)
{
}
