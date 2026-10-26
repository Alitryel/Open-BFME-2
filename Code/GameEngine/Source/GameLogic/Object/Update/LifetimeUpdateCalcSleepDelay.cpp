// cl: /GX /DNDEBUG /MD /DWIN32 /D_WINDOWS
//
// ?calcSleepDelay@LifetimeUpdate@@AAEIII@Z, retail 0x003A49F0 (55 bytes). Dedicated
// TU (DeletionUpdate_calcSleepDelay precedent): retail passes diagnostic line
// 118 (push 0x76) to the random call. Preserve that retail call-site value
// across composition. It reads the GameLogic frame at +0x40 (four past the reference
// header's +0x3C), through the canonical GameLogic lookup view. Lifetime
// adds m_birthFrame at +0x24 beside m_dieFrame at +0x20 (cf. rowed xfer
// ?xfer@Rva003A49D1@@MAEXPAVXfer@@@Z at 0x003A4AFA which xfers +0x20/+0x24
// then bool +0x28). The "LifetimeUpdate.cpp" file literal below is the BFME2
// patch103 path (DeletionUpdate precedent). The random helper resolves via
// its matched row 0x00233FF4.
typedef unsigned int UnsignedInt;

#include "../../../Common/GameLogicObjectLookupView.h"

extern GameLogic *TheGameLogic;

class LifetimeUpdate
{
private:
	UnsignedInt calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames);

private:
	unsigned char m_pad[0x20];
	UnsignedInt m_dieFrame; // +0x20
	UnsignedInt m_birthFrame; // +0x24
};

int GetGameLogicRandomValue(int lo, int hi, char *file, int line);

UnsignedInt LifetimeUpdate::calcSleepDelay(UnsignedInt minFrames, UnsignedInt maxFrames)
{
	UnsignedInt delay = GetGameLogicRandomValue(minFrames, maxFrames, (char *)"C:\\projects\\bfme2patch103\\bfme2\\Code\\GameEngine\\Source\\GameLogic\\Object\\Update\\LifetimeUpdate.cpp", 118);
	if (delay < 1) delay = 1;
	UnsignedInt frame = TheGameLogic->getFrame();
	m_birthFrame = frame;
	m_dieFrame = frame + delay;
	return delay;
}
