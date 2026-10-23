// ?xferNoName@DynamicAudioEventInfo@@QAEXPAVXfer@@@Z
// WB BF0260 debug transfer body and native8331C6..833390458B RET4.
// Target 0x004331C6/458: DynamicAudioEventInfo::xferNoName.
// ZH DynamicAudioEventInfo.cpp supplies override mask order and save purpose;
// BFME1 donor ba7ddda7 DynamicAudioEventInfo.cpp supplies real/enum setters
// and load-only loop control update. Target accesses prove +C4 mask, +44
// priority, +4C control, +10/+1C volume and +94/+98 ranges. No full class
// layout or original base-setter spellings inferred from donor alone.
// Existing folded real setters are direct qualified calls; their source
// owner types are not asserted as audio inheritance. Priority uses corrected
// enum provider 41FDEE. Its former float alias would resolve to wrong179010.
// Keeping the already-owned43B bit-setting helper visible as noinline restores
// native MOVZX EAX / AND EDX / NEG EDX load-loop allocation; all458B exact.
// Helper behavior/bytes are independently owned at0xB3FA5; no donor identity
// or full DynamicAudioEventInfo layout is asserted beyond observed fields.
// cl: /O1 /G7 /MD /EHsc /DNDEBUG /arch:SSE /D_CRTIMP= /Ireference/shims/bfme2_ascii /Ireference/shims/moduledata
#include "ascii_string.h"
#include "unicode_string.h"
#include "Common/Snapshot.h"
class Xfer;
class PooledString;
struct XferUnknown11;
class Coord3DBase;
class ICoord3D;
struct Region3D;
class IRegion3D;
class Coord2D;
class ICoord2D;
class Region2D;
class IRegion2D;
class RealRange;
class RGBColor;
class RGBAColorReal;
class RGBAColorInt;

// BFME 2's Xfer (as GameLogicInit.cpp): MSVC lays the operator== overloads
// out in reverse, so AsciiString is slot 27, unsigned int 30, unsigned
// short 32.
#include "../../../Include/Common/BfmeXfer.h"

class Xfer::Version
{
public:
	Version(unsigned char current, unsigned char minimum)
		: m_current(current), m_minimum(minimum) {}

	unsigned char m_current;
	unsigned char m_minimum;
};


class WeaponTemplateSetHead
{
public:
	__declspec(noinline) void rva000B3FA5(int bit, int value);

private:
	unsigned int m_words[19];
};

void WeaponTemplateSetHead::rva000B3FA5(int bit, int value)
{
	unsigned int m = 1u << (bit & 31);
	bit >>= 5;
	unsigned int old = m_words[bit];
	m_words[bit] = old ^ (((0 - (unsigned)value) ^ old) & m);
}

class Rva001D96FF {public: void rva001D96FF(int);};
class Rva001D9709 {public: void rva001D9709(int);};
class W3DRopeDraw {public: virtual void setRopeCurLen(float);};
class Anim2D {public: void setAlpha(float);};
class Rva001D972BFloatField {public: void set(float);};
class Rva00210C91FloatField {public: void set(float);};
enum AudioPriority {AP_LOWEST,AP_LOW,AP_NORMAL,AP_HIGH,AP_CRITICAL};
class AudioEventInfo {public: void Rva0041FDEE(AudioPriority); private: char p00[0x44]; AudioPriority m_priority;};

class DynamicAudioEventInfo {
public:
 void xferNoName(Xfer *x);
 unsigned char p00[0x10]; float at10;
 unsigned char p14[8]; float at1c;
 unsigned char p20[0x24]; unsigned int priority;
 unsigned char p48[4]; unsigned int control;
 unsigned char p50[0x44]; float at94,at98;
 unsigned char p9c[0x28]; unsigned int flags[1];
 __forceinline bool test(unsigned int bit) const {return (flags[bit>>5] & (1u<<(bit&31)))!=0;}
};
void DynamicAudioEventInfo::xferNoName(Xfer *xfer) {
 Xfer::Version version(1,1); *xfer == version;
 if(xfer->IsLoading()) {
  unsigned char bits; *xfer == bits;
  for(int i=0;i<8;++i)
   ((WeaponTemplateSetHead *)flags)->rva000B3FA5(i,(bits & (1<<i))!=0);
 } else {
  unsigned char bits=0;
  for(int i=0;i<8;++i) if(test(i)) bits |= 1<<i;
  *xfer == bits;
 }
 if(test(1)) {
  bool b=(control&1)!=0; *xfer == b;
  if(xfer->IsLoading()) {
   if(b) ((Rva001D96FF*)this)->rva001D96FF(1);
   else ((Rva001D9709*)this)->rva001D9709(1);
  }
 }
 if(test(3)){float v=at10; *xfer == v; ((W3DRopeDraw*)this)->W3DRopeDraw::setRopeCurLen(v);}
 if(test(4)){float v=at1c; *xfer == v; ((Anim2D*)this)->setAlpha(v);}
 if(test(5)){float v=at94; *xfer == v; ((Rva001D972BFloatField*)this)->set(v);}
 if(test(6)){float v=at98; *xfer == v; ((Rva00210C91FloatField*)this)->set(v);}
 if(test(7)){unsigned char v=priority; *xfer == v; ((AudioEventInfo*)this)->Rva0041FDEE((AudioPriority)v);}
}
