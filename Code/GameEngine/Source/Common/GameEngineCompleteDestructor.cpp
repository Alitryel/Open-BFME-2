// cl: /DNDEBUG /MD /Ireference/shims/bfme2_ascii
//
// GameEngine::~GameEngine, retail 0x00225B9B, 11 bytes.
// Dedicated TU so GameEngineDestructor.cpp's scalar deleting wrapper cannot
// see this body while emitting its deleting wrapper.
// Retail installs the GameEngine vtable then tail-jumps the
// SubsystemInterface destructor at 0x001B4E74. The class view is
// GameEngineInit.cpp's (GameEngineVtableView.h), so the vtable this unit
// emits is the one GameEngineInit.cpp emits.

#include "GameEngineVtableView.h"

GameEngine::~GameEngine()
{
}
