// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX /Ireference/shims/bfme2_ascii
//
// The vtable at 0x00BE7188 is installed by the GameEngine constructor and
// carries the frame-loop method at 0x00225DA9.  Its slot 0 is the 28-byte
// scalar deleting destructor at 0x00226333.
//
// MSVC emits the 28-byte wrapper when the class has an out-of-line virtual
// base destructor. The class view is GameEngineInit.cpp's
// (GameEngineVtableView.h: canonical SubsystemInterface base, ctor 0x001B4E63 /
// dtor 0x001B4E74), shared with GameEngineCompleteDestructor.cpp, so all three
// units emit one GameEngine vtable.
#define GAMEENGINE_VIEW_EMIT_VTABLE
#include "GameEngineVtableView.h"

// GameEngine::~GameEngine: defined in GameEngineCompleteDestructor.cpp (its row's unit).

// The dummy tag constructor only makes this TU emit the vtable (whose slot 0 is
// the scalar deleting wrapper). It carries no retail identity and emits no
// retail-named ctor COMDAT; the wrapper calls the rowed complete dtor.
// ?<GameEngine::GameEngine> absent-from-retail
GameEngine::GameEngine(struct EmitVtableTag *)
{
}
