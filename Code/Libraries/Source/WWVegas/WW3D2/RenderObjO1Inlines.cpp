// cl: /O1 /Ireference/shims/bfme2renderobj /DNDEBUG /MD /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/shims/sweep /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWSaveLoad /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/Wwutil /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDownload /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/Code/Libraries/Source/Compression /Ireference/shims/sweep
//
// RenderObjClass inline virtuals Set_Hidden / Set_Animation_Hidden / Set_Translucent / Is_Really_Visible:
// retail holds one size-optimised (/O1) out-of-line copy of each header body (0x0006CF0C 0x0006CF2C 0x0006CF52 0x0006CECD).
// The empty Set_Animation overloads (5-arg slot 44 RET 0x14 at 0x0025EF04, motion/frame/mode slot 45 RET 0xC
// at 0x000D1407) and _bfme_ro_v50 (slot 53, MOV AL,1 / RET 4 at 0x005CB9FA) are header inline bodies that
// retail folds with every other identical virtual; donor (BFME1) slot order and argument counts name them.
// Is_Not_Hidden_At_All (0x0006CEEE, slot 97) and the slot-29 Get_Num_Sub_Objects tail dispatch
// _bfme_ro_v28 (0x0006CE95) are the same kind of copy; RenderObjClass-derived vtables point at both.
// The anchor below only makes this TU emit them out of line (qualified calls with inlining disabled); it is not retail code.
//

// rendobj.h: this unit holds the retail rows of Set_Hidden, Set_Animation_Hidden,
// Set_Translucent and Is_Really_Visible; every other unit only declares them.
#define BFME_RO_DEFINE_VISIBILITY
#include "rendobj.h"	// the bfme2renderobj shim has to win the include guard
#include "boxrobj.h"
#include "w3d_util.h"
#include "wwdebug.h"
#include "vertmaterial.h"
#include "ww3d.h"
#include "chunkio.h"
#include "rinfo.h"
#include "coltest.h"
#include "inttest.h"
#include "dx8wrapper.h"
#include "dx8indexbuffer.h"
#include "dx8vertexbuffer.h"
#include "dx8fvf.h"
#include "sortingrenderer.h"
#include "visrasterizer.h"
#include "meshgeometry.h"
#define NUM_BOX_VERTS	8
#define NUM_BOX_FACES	12

#pragma inline_depth(0)
// ?_bfmeRenderObjInlineAnchor@@YAHPAVRenderObjClass@@H@Z absent-from-retail
int _bfmeRenderObjInlineAnchor(RenderObjClass *renderObj, int onoff)
{
	renderObj->RenderObjClass::Set_Hidden(onoff);
	renderObj->RenderObjClass::Set_Animation_Hidden(onoff);
	renderObj->RenderObjClass::Set_Translucent(onoff);
	renderObj->RenderObjClass::Set_Animation((HAnimClass *)0, 0.0f, (HAnimClass *)0, 0.0f, 0.0f);
	renderObj->RenderObjClass::Set_Animation((HAnimClass *)0, 0.0f, onoff);
	onoff += renderObj->RenderObjClass::_bfme_ro_v50(onoff);
	onoff += renderObj->RenderObjClass::Is_Not_Hidden_At_All();
	onoff += renderObj->RenderObjClass::_bfme_ro_v28();
	return renderObj->RenderObjClass::Is_Really_Visible() + onoff;
}
#pragma inline_depth()
