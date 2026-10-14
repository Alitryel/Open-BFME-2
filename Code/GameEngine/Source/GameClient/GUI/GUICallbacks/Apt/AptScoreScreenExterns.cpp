// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// "AptScoreScreen::Externs", the score screen's seven Apt extern queries
// (the rest of the screen lives in AptScoreScreenCallbacks.cpp). WB 01460190
// names this handler and identifies all seven query branches; native
// 0051CE72..0051D009 supplies the release-build guards and layout.
//
// Its own TU, compiled /EHsc: retail keeps the EH frame (and the final
// state -1 store) around the formatter's AsciiString result but never
// stores state 0, which is what /EHsc gives once strcpy is a nothrow C
// call; the dead `if (0) throw 0;` in that result's lifetime keeps the
// frame. The rest of the screen needs /EHs.

// vector::_M_insert_overflow inlines max(size(), n). A file-static unsigned
// overload takes the call instead, so this TU emits no external max COMDAT.
namespace _STL {
static inline const unsigned int &max(const unsigned int &a, const unsigned int &b)
{
    return a < b ? b : a;
}
}
#include <vector>
#include "ascii_string.h"

extern "C" char *__cdecl strcpy(char *destination, const char *source);
extern "C" __declspec(dllimport) int __cdecl sprintf(char *buffer, const char *format, ...);

// The objectives summary at +0x288: the faction name and a count at +4.
struct AptScoreObjectives
{
	AsciiString m_faction; // +0x00, read by query PlayerFaction
	int m_count; // +0x04
};

// The number formatter (BfmeAptScreenScoreFormat.cpp) called on the screen.
class Rva0051D009
{
public:
	AsciiString rva0051CC8DFormat(AsciiString text);
};

class GlobalData;
extern GlobalData *TheWritableGlobalData;
// The native query reads this float directly; no full GlobalData layout is
// asserted. WB reads the corresponding score option at its own +0x115C.
struct AptScoreOptionView { unsigned char prefix[0x1184]; float objectivesPerScore; };

// The fields of the score screen (AptScoreScreenCallbacks.cpp) the queries read.
class AptScoreScreen
{
public:
	void Externs(int query, char *value, bool set);

private:
	unsigned char m_pad000[0x280];
	int m_280;
	bool m_284;
	AptScoreObjectives *m_objectives; // +0x288
	_STL::vector<bool> m_heroUpgrades; // +0x28C
	unsigned char m_pad2A0[0x2B0 - 0x2A0];
	AsciiString m_2b0;
};

// Its fifth query actually passes a double with the same "%d" literal used
// by the integer queries; preserve that retail vararg call as observed.
void AptScoreScreen::Externs(int query, char *value, bool set)
{
	if (!set) {
		value[0] = '0';
		value[1] = 0;
	}
	if (query == 0) {
		if (!set) sprintf(value, "%d", m_280 == 1);
	} else if (query == 1) {
		if (!set) sprintf(value, "%d", m_280 == 0);
	} else if (query == 2) {
		if (!set) sprintf(value, "%d", m_heroUpgrades.size());
	} else if (query == 3) {
		if (!set && m_objectives) strcpy(value, m_objectives->m_faction.str());
	} else if (query == 4) {
		if (!set && m_objectives) sprintf(value, "%d", m_objectives->m_count);
	} else if (query == 5) {
		if (!set) sprintf(value, "%d", reinterpret_cast<AptScoreOptionView *>(TheWritableGlobalData)->objectivesPerScore);
	} else if (query == 6) {
		if (set) m_2b0.set(value);
		else {
			const AsciiString &formatted = reinterpret_cast<Rva0051D009 *>(this)->rva0051CC8DFormat(m_2b0);
			if (formatted.getLength() < 255) strcpy(value, formatted.str());
			if (0) throw 0;
		}
	}
}
