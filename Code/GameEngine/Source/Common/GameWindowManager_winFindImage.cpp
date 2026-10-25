// cl: /Ireference/shims/bfme2_ascii /Oy- /DNDEBUG /MD /GX /Oi- /ICode/GameEngine/Source/GameClient/GUI
//
// ?winFindImage@GameWindowManager@@UAEPBVImage@@PBD@Z, retail 0x00314C3E, 85 bytes.
// Virtual slot 71 (offset 0x11C) of vtable 0x007C7C90 (class of rowed
// ??1Rva008FCA3 at 0x0008FCA3 with ??_G at 0x0008FF22). Returns null when
// TheMappedImageCollection (0x009FF078) is null, else looks up the name in
// that collection through rowed StringBase<char> ctor 0x00037BA0, rowed
// findImageByName 0x002D92F6 and pinned StringBase dtor 0x00036410 with EH
// states 0/-1. Shape follows INI::parseMappedImage (same three callees
// plus null-collection guard). WB names it GameWindowManager::winFindImage
// (WB 0x013A2AC0, GameWindowGlobal.cpp, matched by the same vtable slot); Zero
// Hour's GameWindowManager declares the same virtual, and the rowed
// GameWindowManager::winDestroyAll fills slot 36 of this table.
class Image;

#include "ascii_string.h"


class ImageCollection
{
public:
	const Image *findImageByName(const AsciiString &name);
};

extern ImageCollection *TheMappedImageCollection;

#include "GameWindowGlobalView.h"

const Image *GameWindowManager::winFindImage(const char *name)
{
	if (TheMappedImageCollection != 0)
	{
		AsciiString str(name);
		const Image *img = TheMappedImageCollection->findImageByName(str);
		return img;
	}
	else
		return 0;
}
