// cl: /O1 /G7 /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc
//
// ?rva005B977B@OnlineHome@AptOnline@@QAEXXZ @0x005B977B 366B
// Online home screen time-zone refresh, called from the screen constructor
// 0x005B9BBC (AptOnlineHomeConstructor.cpp). Kept in its own unit because the
// callbacks unit (AptOnlineHomeCallbacks.cpp) compiles without /O1 /G7 /EHsc.
// WB twin 0x01585130 (a longer revision of the same routine) translates the
// converted zone name inside each branch; spelling the two translate calls
// that way gives retail's frame homes and argument order (bank 0.96 -> exact).

#include "unicode_string.h"
#include "ascii_string.h"

namespace AptOnline
{
class OnlineHome
{
public:
	void rva005B977B();
	void rva005B95B8();
};
}

// Native5B977B..5B98E9 RET0;366B. TimeZone172B and512B conversion
// buffer measured from native Win32 arguments. BF1 9cb wholehome has
// same zone abbreviation loop, embedded in a larger player-stat refresh.
// Target resets12 ticker rows and calls the separately rowed PS request.
struct HomeSystemTime { unsigned short field[8]; };
struct HomeTimeZone { long bias; unsigned short standardName[32]; HomeSystemTime standardDate;
 long standardBias; unsigned short daylightName[32]; HomeSystemTime daylightDate; long daylightBias; };
typedef char HomeZoneSize[sizeof(HomeTimeZone)==172 ? 1:-1];
extern "C" __declspec(dllimport) unsigned long __stdcall GetTimeZoneInformation(HomeTimeZone *);
extern "C" __declspec(dllimport) int __stdcall WideCharToMultiByte(unsigned,unsigned long,const unsigned short *,int,char *,int,const char *,int *);
class Rva005B9378 { public: void rva005B9378(int,const UnicodeString &); };
class BfmeAptWindowManager { public: void bfmeSetText(const AsciiString &,const UnicodeString &,bool); };
extern BfmeAptWindowManager *g_bfmeAptWindowManager;
void rva005BD64D();
// getCharAt(0) is inlined in native; canonical header declares it out of
// line. Shared string header layout proves the data pointer/text+8 view.
static inline unsigned short onlineHomeFirst(const UnicodeString &text)
{
 const unsigned char *data=*reinterpret_cast<const unsigned char *const *>(&text);
 return data ? *reinterpret_cast<const unsigned short *>(data+8):0;
}
void AptOnline::OnlineHome::rva005B977B()
{
 for(int i=0;i<12;++i)
  reinterpret_cast<Rva005B9378 *>(this)->rva005B9378(i,L"-");
 HomeTimeZone zone;
 unsigned long result=GetTimeZoneInformation(&zone);
 UnicodeString zoneText;
 char buffer[512];
 if(result==0xffffffff) zoneText.format(UnicodeString::TheEmptyString.str());
 else {
  if(result==2) { WideCharToMultiByte(0,0,zone.daylightName,-1,buffer,512,0,0); zoneText.translate(buffer); }
  else { WideCharToMultiByte(0,0,zone.standardName,-1,buffer,512,0,0); zoneText.translate(buffer); }
 }
 UnicodeString token,initials;
 while(zoneText.nextToken(&token,L" ")) {
  unsigned short c=onlineHomeFirst(token);
  initials.concat(&c,1);
 }
 g_bfmeAptWindowManager->bfmeSetText(AsciiString("APT:TimeZone"),initials,false);
 rva005BD64D();
 rva005B95B8();
}
