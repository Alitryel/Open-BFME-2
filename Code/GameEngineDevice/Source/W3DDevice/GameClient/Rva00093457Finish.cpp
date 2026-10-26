// cl: /MD /EHsc /DNDEBUG /Ireference/shims/bfme2_ascii /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/game/Libraries/Source/WWVegas/WWDebug /ICode/Libraries/Include/Lib
// ?rva00093457@W3DSnowManager@@QAEXXZ @0x00093457 176B
// Weather sync method: zeroes two members, pulls an int through the second data
// global, then copies weather fields through override hops. A shared global
// local feeds the nested-ternary diamond around the +0x46 flag; when +0x46 is
// clear only m_3c/m_41/m_14 are written and the block joins the epilogue, so
// the o3/o4 override hops sit INSIDE the else arm. The banked attempt had them
// after the if/else, which produced a shorter true-branch jump (eb 1e vs eb 5a).
// Evidence: callers 0x00093B49 0x00093CBE; globals VA 0x00E01CE4 0x00DFE118;
// neighbour Rva000932E1Get.cpp (same WeatherSetting layout, pinned resolve
// 0x001E35DF).
#include "W3DSnowResourceView.h"
#define TheOther00E01CE4 ((*(Rva00E01CE4Holder **)&TheGlobalWeatherSystem))
#define TheWeather00DFE118 (g_Va00DFE118)
struct Rva00E01CE4Holder { char m_pad[0x10]; int m_10; };
extern class GlobalWeatherSystem *TheGlobalWeatherSystem;
extern WeatherSetting *g_Va00DFE118;
void W3DSnowManager::rva00093457()
{
	m_58 = 0;
	m_AC = 0;
	m_A8 = TheOther00E01CE4->m_10;
	const WeatherSetting *gv = TheWeather00DFE118;
	const WeatherSetting *weatherSetting = (gv == 0) ? 0 : (const WeatherSetting *)gv->getFinalOverride();
	if (weatherSetting->m_46 == 0) {
		m_3c = m_64;
		m_targetFlag41 = false;
		m_14 = m_68;
	} else {
		const WeatherSetting *o2 = (gv == 0) ? 0 : (const WeatherSetting *)gv->getFinalOverride();
		m_3c = o2->m_3c;
		const WeatherSetting *o3 = TheWeather00DFE118;
		if (o3 != 0)
			o3 = (const WeatherSetting *)o3->getFinalOverride();
		m_14 = o3->m_40;
		const WeatherSetting *o4 = TheWeather00DFE118;
		if (o4 != 0)
			o4 = (const WeatherSetting *)o4->getFinalOverride();
		m_48 = o4->m_4c;
		m_4c = o4->m_50;
	}
}
