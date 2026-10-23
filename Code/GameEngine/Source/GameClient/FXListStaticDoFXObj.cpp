// cl: /O1 /Oy- /DNDEBUG /MD /GX-
//
// Retail 0x000B2235 (37 bytes): the static FXList::doFXObj wrapper,
// ?doFXObj@FXList@@SAXPBV1@PBVObject@@1@Z (74 direct callers, cdecl, they
// clean 0xC). Zero Hour FXList.h declares doFXObj(fx, primary, secondary) as a
// static inline null guard over the member doFXObj; BFME2 materialises it out
// of line with the same extra gate through the pinned FXList predicate
// 0x001E2EF1 as the matched static doFXPos 0x00094C29
// (FXListStaticDoFXPos.cpp), then forwards to the member doFXObj 0x001E2A18
// (pinned here; thiscall with primary and secondary).

class Object;
class FXList
{
public:
	void doFXObj(const Object *primary, const Object *secondary) const;
	bool rva001E2EF1() const;
	static void doFXObj(const FXList *fx, const Object *primary, const Object *secondary);
};

inline void FXList::doFXObj(const FXList *fx, const Object *primary, const Object *secondary)
{
	if (fx && !fx->rva001E2EF1())
		fx->doFXObj(primary, secondary);
}

// This static method is a header inline in the copier units; the anchor is not retail code.
#pragma inline_depth(0)
// ?_bfmeFXListStaticDoFXObjInlineAnchor@@YAXXZ absent-from-retail
void _bfmeFXListStaticDoFXObjInlineAnchor()
{
	FXList::doFXObj(static_cast<const FXList *>(0),
		static_cast<const Object *>(0), static_cast<const Object *>(0));
}
#pragma inline_depth()
