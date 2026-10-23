// cl: -DNDEBUG -DWIN32 -D_WINDOWS -MD -EHsc /Os -Ireference/open-bfme-1/game/GameEngine/Source/GameNetwork
// stlport

#include <stdlib.h>

// ?grabHexInt3@@YAHPBD@Z
static int __cdecl grabHexInt3(const char *text)
{
	char buffer[6] = "0xfff";
	buffer[2] = text[0];
	buffer[3] = text[1];
	buffer[4] = text[2];
	return strtol(buffer, 0, 16);
}

// ?callGrabHexInt3 present-unmatched  the donor's emitter: MSVC gives the static
// grabHexInt3 a local eax-argument convention only when it can see this call.
int __cdecl callGrabHexInt3(const char *text)
{
	return grabHexInt3(text);
}
