// cl: -O1 -arch:SSE -G7 -Ireference/shims/bfme2_ascii -Ireference/shims/bfmealloc -D_STLP_USE_STATIC_LIB -D_CRTIMP=
// stlport
#include "../../Include/GameLogic/ScriptActionsBFME2.h"
// Two global-this forwards (11B each): mov ecx, [global], jmp <run>.
// Each loads a singleton pointer into this and tail-jumps its parameterless
// run method.
// 0x003BBEDE (global 0x00DFE16C -> 0x00203AD5),
// 0x003BBEE9 (global 0x00DFE16C -> 0x00203ADD).
// (0x003BD424 is ScriptActions::doEnablePlanningMode, in ScriptActions.cpp.)
// Global/callee identities unproven (opaque pins); the wrapper names are
// address-derived. One ledger row per forward.

class Rva000203AD5ByteOneSetter
{
public:
	void enable();
};

class Rva000203ADDByteZeroSetter
{
public:
	void disable();
};

extern class ScriptEngine *TheScriptEngine;

void ScriptActions::doFreezeTime()
{
	(*(Rva000203AD5ByteOneSetter **)&TheScriptEngine)->enable();
}

void ScriptActions::doUnfreezeTime()
{
	((Rva000203ADDByteZeroSetter *)(*(Rva000203AD5ByteOneSetter **)&TheScriptEngine))->disable();
}

// 0x003BBED3 (11B): mov ecx, [TheSnowManager 0x00DFE114], jmp 0x00203574,
// the rowed byte-at-+0x40 setter (ledger spelling AnimateWindow::
// setNeedsToFinish; ZH's SnowManager::setVisible has the same shape but
// that name is not proven at the folded address). One bool argument that
// the callee's ret 4 pops. No direct callers; owner unrecovered, so the
// wrapper is an address-named view.
class SnowManager;
extern SnowManager *TheSnowManager;

class AnimateWindow
{
public:
	void setNeedsToFinish(bool needsToFinish);
};

class Rva003BBED3Fwd
{
public:
	void rva003BBED3(bool value);
};

void Rva003BBED3Fwd::rva003BBED3(bool value)
{
	((AnimateWindow *)TheSnowManager)->setNeedsToFinish(value);
}
