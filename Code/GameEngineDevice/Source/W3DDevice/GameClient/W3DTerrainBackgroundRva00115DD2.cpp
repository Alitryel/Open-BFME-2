// cl: /DBFME_ASCII_DTOR_DECL /Ireference/shims/bfme2_ascii /Ireference/shims/bfmealloc /EHsc /DNDEBUG /MD
// ?rva00115DD2@W3DTerrainBackground@@QAEXXZ, retail 0x00115DD2 (22B), the
// pinned callee FlatHeightMap's tile loop calls (0x000E1233) right after
// W3DTerrainBackground::updateTexture (0x001125BE). WorldBuilder's twin
// (7B8140 -> 7CC640, assert W3DTerrainBackground::updateGeoMorphing)
// returns before its geomorph loop, so in retail only the /O1 EH frame the
// dead locals need survives (EH_prolog, fs:0 restore, leave, ret; FuncInfo
// 0x00D3D63C). Target fact: the frame and its single null-action state.
// Structural inference, not recovered source: the dead local below is a
// stand-in with the frame-keeping shape learned at 0x00382767 (inline
// constructor, out-of-line release, one throwing point: one EH state, as
// retail's FuncInfo has); the original
// dead body (a vertex-buffer lock loop) is not reconstructed.
#include "unicode_string.h"

class W3DTerrainBackground
{
public:
	void rva00115DD2();
};

void W3DTerrainBackground::rva00115DD2()
{
	return;
	UnicodeString s;
	s += s;
}
