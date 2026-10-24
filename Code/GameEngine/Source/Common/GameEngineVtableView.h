// The one GameEngine class declaration for every unit that emits its vtable
// (??_7GameEngine@@6B@): GameEngineInit.cpp, GameEngineDestructor.cpp and
// GameEngineCompleteDestructor.cpp all include it, so they emit the same table and
// the link keeps one definition. Base: the retail 14-slot SubsystemInterface of
// table 0x00BD77A0 (reference/shims/subsystem_bfme2/spline_service.h; units need
// /Ireference/shims/subsystem_bfme2). GameEngine overrides init/reset/update and
// adds init(argc, argv) at slot 14 and the create* factories at +0x6C..+0x94.
// Retail's table (VA 0x00BE7188) has 40 slots; the last two are not modelled.
#ifndef GAMEENGINE_VTABLE_VIEW_H
#define GAMEENGINE_VTABLE_VIEW_H

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#include "spline_service.h"

class FileSystem;
class GameLogic;
class GameClient;
class MessageStream;
class ModuleFactory;
class ThingFactory;
class FunctionLexicon;
class Radar;
class ParticleSystemManager;
class AudioManager;
class Rva0022AF59Subsystem;

class GameEngine : public SubsystemInterface
{
public:
	virtual void init() {}
	virtual void reset(); virtual void update();
	virtual void init(Int argc, char *argv[]);					// slot 14
	virtual void s31() = 0; virtual Bool rva00225AD5(); virtual Bool rva00225AFF();
	virtual void setFramesPerSecondLimit(Int fps) = 0;				// slot 18 (+0x48)
	virtual void s34() = 0;
	virtual void setQuitting(Bool quitting) = 0;					// slot 20 (+0x50)
	virtual void s35() = 0; virtual Bool isMultiplayerSession(); virtual void s37() = 0; virtual void s38() = 0; virtual void s39() = 0; virtual void rva0023054C();
	virtual FileSystem *createFileSystem() = 0;						// +0x6C
	virtual GameLogic *createGameLogic() = 0;						// +0x70
	virtual GameClient *createGameClient() = 0;						// +0x74
protected:
	virtual MessageStream *createMessageStream() = 0;				// +0x78
public:
	virtual ModuleFactory *createModuleFactory() = 0;				// +0x7C
	virtual ThingFactory *createThingFactory() = 0;					// +0x80
	virtual FunctionLexicon *createFunctionLexicon() = 0;			// +0x84
	virtual Radar *createRadar() = 0;								// +0x88
	virtual ParticleSystemManager *createParticleSystemManager() = 0;	// +0x8C
	virtual AudioManager *createAudioManager() = 0;					// +0x90
	virtual Rva0022AF59Subsystem *createAptPlayer() = 0;			// +0x94

	void initTiming();
	void initSubsystems(Int argc, char *argv[]);

	GameEngine();
#ifdef GAMEENGINE_VIEW_EMIT_VTABLE
	// Dummy tag constructor: only makes GameEngineDestructor.cpp emit the vtable
	// (whose slot 0 is the scalar deleting wrapper). No retail identity.
	GameEngine(struct EmitVtableTag *);
#endif
	virtual ~GameEngine();

	Int m_maxFPS;				// +0x0C
	Bool m_quitting;			// +0x10
	Bool m_11;					// +0x11
	Int m_14;					// +0x14
	Int m_18[7];				// +0x18
	Int m_34;					// +0x34
	Int m_38;					// +0x38
	float m_3C;					// +0x3C
	Bool m_40;					// +0x40
	float m_44;					// +0x44
	float m_48;					// +0x48
	Int m_4C;					// +0x4C
	Int m_50;					// +0x50
	UnsignedInt m_54;			// +0x54
	float m_58;					// +0x58
	Int m_5C;					// +0x5C
};

#endif // GAMEENGINE_VTABLE_VIEW_H
