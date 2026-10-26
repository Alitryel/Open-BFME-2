// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include/Lib
// ?target_0009322D@W3DSnowManager@@AAEXXZ @0x0009322D 180B (Ghidra splits it
// at 0x0009323B; the prologue and first override hop sit in 0x0009322D..0x0009323B).
// W3DSnowManager::update (0x000949D9) ends by calling it on the same receiver
// at 0x00094A8C, which proves the owner; the pinned name keeps the address.
// Donor: Open-BFME-1 W3DSnowManagerLightningRva00723B60.cpp (BFME 1 retail
// 0x00723B60) -- counts down the lightning flash while one is active, else
// rolls LightningChance and starts a new flash lasting LightningDuration
// scaled by Random_Float(0.7f 1.2f) (multiplier 0x3F000001 is the folded
// 1.2f - 0.7f). BFME 2 offsets from target reads: WeatherSetting +0x54 flag
// +0x64 duration +0x68 chance (BFME 1 +0x40/+0x50/+0x54); manager +0x50 flag
// and +0x54 countdown (BFME 1 +0x44/+0x48). Callees: rowed WWMath::Random_Float
// 0x00711B90 and pinned Overridable::getFinalOverride 0x001E35DF.

class WWMath
{
public:
	static float Random_Float();
	static float Random_Float(float min, float max) { return Random_Float() * (max - min) + min; }
};

#include "W3DSnowResourceView.h"

void W3DSnowManager::target_0009322D(void)
{
	if (!TheWeatherSetting->m_54)
		return;
	if (m_50)
	{
		if (--m_54 > 0)
			return;
		m_54 = 0;
		m_50 = false;
		return;
	}
	float chance = WWMath::Random_Float();
	if (chance < TheWeatherSetting->m_68)
	{
		m_50 = true;
		m_54 = (int)(WWMath::Random_Float(0.7f, 1.2f) * TheWeatherSetting->m_64 + 0.5f);
	}
}
