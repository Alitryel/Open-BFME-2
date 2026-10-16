// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z
// partial score=0.96 date=2026-10-16
// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS /D_STLP_USE_STATIC_LIB /D_CRTIMP= /D_STLP_USE_MALLOC /D_STLP_NO_EXCEPTIONS /DBFME_MODULE_NO_MPO /DZH_EMIT_POOL_GLUE /Ireference/shims/bfmerendobj /Ireference/shims/debugvtable /Ireference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/debug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/bfmeanimobj /Ireference/shims/indexbuffercount /Ireference/shims/bfmecaps /Ireference/shims/bfmehcanim /Ireference/shims/bfmevector /Ireference/shims/bfmemapper /Ireference/shims/meshmatdesclayout /Ireference/shims/bfmeshader /Ireference/shims/bfmecpudetect /Ireference/shims/bfmepool /Ireference/open-bfme-1/Code/GameEngine/Include/Precompiled /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWAudio /Ireference/shims/bfmealloc /Ireference/shims/bfmehashtable /Ireference/shims/bfmelist /Ireference/shims/asciistring_downloadmanager /Ireference/shims/stlp_nodealloc /Ireference/shims/asciistring_thin /ICode/GameEngine/Source/Common /Ireference/shims/w3droadbuffer /Ireference/shims/bfmeterraintracks /ICode/Libraries/Include/Lib /Ireference/shims
// stlport
// BANKED near miss for SlideFromLeft::reverseAnimateWindow (retail 0x005C54BC,
// 233 bytes). Retail is the x-mirror of the landed SlideFromRight body
// (0x005C51E5, same 233-byte shape/frame/call set) in
// ProcessAnimateWindowSlideFromRightReverse.cpp; shard flags copied verbatim.
// This body is byte-identical to retail EXCEPT one register allocation: retail
// loads the product into xmm0 and the negated bound into xmm1 and emits
// `comiss xmm1,xmm0` (i.e. max clamp, `slowedX < -m_maxVel.x`); this compile
// of the same source emits the xmm0/xmm1 mirror (`comiss xmm0,xmm1`). Every
// other byte and the length match. SlowedX slowedVel temps plus out-of-line
// getVel plus inline setVel setCurPos like the update side.
// Wall re-confirmed 2026-10-16 (deepseek-v4.1-flash) with ~30 variant builds at
// region /O1 /arch:SSE /G7: retail's exact `comiss xmm1,xmm0; jbe` (product in
// xmm0, bound in xmm1, max clamp) is not reachable from this source spelling.
// A subset of max spellings (__max(slowedX,-m_maxVel.x), the ternary, the
// bound-first `<`/`!(a>=b)` forms) DO reproduce retail's register allocation --
// product in xmm0, bound in xmm1 -- but print the semantically identical dual
// encoding `comiss xmm0,xmm1; jae` (2 bytes differ: offsets 191/192). Every
// other spelling mirrors the allocation (nd>=17). Also inert here: hoisted/const
// bound, Real& alias, volatile store, bool precompute, goto, _ReadWriteBarrier,
// product-order swap, /fp:fast, /G6. New lever required (allocator/comiss dest).
// The compiler-generated vector constructor iterator (??_H) takes the
// optimization state of the first function that needs it. Retail links one
// copy, the /O1 body at 0x00001423; this unemitted anchor makes this unit's
// copy that same body, so it no longer loses to retail's at link time.
// It can also change how later array constructions here compile; checked to
// change nothing else in this unit, but if a function added later that builds
// an array will not match, try it without this block.
struct BfmeVciAnchorElem { BfmeVciAnchorElem(); };
#pragma optimize("gsy", on)
static void bfmeVciAnchor() { BfmeVciAnchorElem anchor[2]; (void)anchor; }
#pragma optimize("", on)
#include "PreRTS.h"
#include "GameClient/ProcessAnimateWindow.h"
#pragma optimize("sy", on)
#include "GameClient/AnimateWindowManager.h"
#pragma optimize("", on)
#include "GameClient/GameWindow.h"
#include "GameClient/Display.h"

// ?reverseAnimateWindow@ProcessAnimateWindowSlideFromLeft@@UAE_NPAVAnimateWindow@@@Z @0x005C54BC
// X-mirror of the landed SlideFromRight body in the sibling shard: the finish
// test, the distance test and the clamp direction are reversed. Retail's clamp
// is a max clamp (-m_maxVel.x on the left, or slowedX < -m_maxVel.x), matching
// the ZH donor's `if( vel.x < -m_maxVel.x) vel.x = -m_maxVel.x;`.
Bool ProcessAnimateWindowSlideFromLeft::reverseAnimateWindow( AnimateWindow *animWin )
{
	if(!animWin)
	{
		DEBUG_ASSERTCRASH( animWin, ("animWin was passed into updateAnimateWindow as a NULL Pointer... bad bad bad!"));
		return TRUE;
	}
	if(animWin->isFinished())
		return TRUE;
	if(timeGetTime() < animWin->getStartTime())
		return FALSE;
	GameWindow *win = animWin->getGameWindow();
	if(!win)
	{
		DEBUG_ASSERTCRASH( win, ("animWin contains a NULL Pointer for it's GameWindow... Whatup wit dat?"));
		return TRUE;
	}
	ICoord2D curPos = animWin->getCurPos();
	ICoord2D startPos = animWin->getStartPos();
	Coord2D vel = animWin->getVel();
	curPos.x += (Int)vel.x;

	if(curPos.x < startPos.x)
	{
		animWin->setFinished( TRUE );
		win->winSetPosition(startPos.x, curPos.y);
		return TRUE;
	}
	win->winSetPosition(curPos.x, curPos.y);
	animWin->setCurPos(curPos);

	ICoord2D endPos = animWin->getEndPos();
	Real slowedX;
	if( endPos.x - curPos.x <= m_slowDownThreshold )
		slowedX = vel.x * m_speedUpRatio;
	else
		slowedX = -m_maxVel.x;
	if( slowedX < -m_maxVel.x)
		slowedX = -m_maxVel.x;
	Coord2D slowedVel;
	slowedVel.x = slowedX;
	slowedVel.y = vel.y;
	animWin->setVel(slowedVel);
	return FALSE;
}
