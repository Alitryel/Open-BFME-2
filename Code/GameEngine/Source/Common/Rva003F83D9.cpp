// cl: /Ireference/shims/bfme2_ascii /MD
//
// ?rva003F83D9@SessionTask@LivingWorldTutorial@@QAENH@Z @0x003F83D9 37B
// (WorldBuilder lead LivingWorldTutorial::SessionTask::getRealParam).
// Double from AsciiString array at +0xC via atof with empty fallback.
// Evidence: +0xC AsciiString array like neighbour Rva003F8443 at 0x003F8443;
// branch t ? t+8 : g_Rva0107301CEmptyString matches Rva004D57AEContents;
// IAT atof; caller at 0x003F8CF2 in SessionTask::create 0x003F88BC, on
// its own this.
#include "ascii_string.h"

extern "C" __declspec(dllimport) double __cdecl atof(const char *str);

class LivingWorldTutorial
{
public:
	class SessionTask;
};
class LivingWorldTutorial::SessionTask
{
public:
	double rva003F83D9(int i);
private:
	char m_pad00[0x0C];
	AsciiString *m_arr0C;
};

double LivingWorldTutorial::SessionTask::rva003F83D9(int i)
{
	return atof(m_arr0C[i].str());
}
