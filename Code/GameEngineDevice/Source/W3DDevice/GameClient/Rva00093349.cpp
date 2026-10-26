// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include/Lib
// Weather sync helper, retail 0x00093349 (100 bytes). The shared view retains
// the established weather +70/+74/+78 and receiver +58/+5C/+60 accesses.
#include "W3DSnowResourceView.h"

extern WeatherSetting *g_Va00DFE118;
#define TheWeather00DFE118 (g_Va00DFE118)

void W3DSnowManager::rva00093349()
{
	m_AC = 1;
	m_targetFlag41 = true;
	const WeatherSetting *gv = TheWeather00DFE118;
	const WeatherSetting *weatherSetting = (gv == 0) ? 0 : (const WeatherSetting *)gv->getFinalOverride();
	m_58 = weatherSetting->m_70;
	const WeatherSetting *gv2 = TheWeather00DFE118;
	const WeatherSetting *o2 = (gv2 == 0) ? 0 : (const WeatherSetting *)gv2->getFinalOverride();
	m_5c = o2->m_74;
	const WeatherSetting *gv3 = TheWeather00DFE118;
	const WeatherSetting *o3 = (gv3 == 0) ? 0 : (const WeatherSetting *)gv3->getFinalOverride();
	m_60 = o3->m_78;
}
