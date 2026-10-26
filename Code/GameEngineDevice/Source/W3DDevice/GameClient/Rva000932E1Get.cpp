// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include/Lib
// ?rva000932E1@W3DSnowManager@@QAEMXZ @0x000932E1 (104B):
// Float getter: default shared 1.0f unless the weather global resolves and
// both its +0x54 flag and this +0x50 flag are set, then a second resolve and
// the +0x58 random variable getValue. Nested ternaries force the explicit
// null/next diamond around pinned getFinalOverride 0x001E35DF.
// Evidence: callers 0x0009355B 0x00093FFA; unblocks 0x00093507; Snow weather global VA 0x00DFE118.
#include "W3DSnowResourceView.h"
extern float g_Va00BBB8D8;
WeatherSetting *g_Va00DFE118;
#define TheWeather00DFE118 g_Va00DFE118
float W3DSnowManager::rva000932E1()
{
	float def = g_Va00BBB8D8;
	const WeatherSetting *gv = TheWeather00DFE118;
	const WeatherSetting *weatherSetting = (gv == 0) ? 0 : (const WeatherSetting *)gv->getFinalOverride();
	if (weatherSetting->m_54 != 0) {
		if (m_50 != 0) {
			const WeatherSetting *o2 = (gv == 0) ? 0 : (const WeatherSetting *)gv->getFinalOverride();
			return o2->m_58.getValue();
		}
	}
	return def;
}
