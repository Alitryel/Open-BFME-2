// cl: /Ireference/shims/bfme2_ascii /EHsc
// ?Rva0037BA48Get@@YA?AVUnicodeString@@XZ retail 0x0037BA48 26B.
// Returns UnicodeString built from wide literal at RVA 0x0081875C via inlined StringBase<ushort> ctor.
// Evidence: rowed StringBase<ushort> ctor 0x00037E30 callee; callers 0x0037C5E7 0x0037D5D9 0x004356DB 0x0043588F; neighbours Rva0037B9D4Get and RecorderGetLastReplayDisplayName same flags.
#include "unicode_string.h"

// Retail has the complete replay filename extension at RVA 0x0081875C.

UnicodeString Rva0037BA48Get()
{
	return UnicodeString(L".BfME2Replay");
}
