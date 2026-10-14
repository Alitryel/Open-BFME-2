// cl: /O1 /G7 /arch:SSE /MD /DNDEBUG /D_STLP_NO_EXCEPTIONS /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
// ??0Rva003F9D08@@QAE@XZ, retail 0x003F9C11 (187B): the default constructor
// of the INI-parsed singleton whose destructor is the rowed 0x003F9D08
// (OpaqueScalarDeletingDtorsB07.cpp; same vtable VA 0x00C375F0). Its only
// caller is the factory 0x003F9CD2, which news 0x74 bytes, registers the
// object with field table 0x00C37600 and stores it at +0x2C4 of the
// 0x00DFE1C8 singleton. Retail stores establish every member: four empty
// strings at +4..+0x10, four zero words, the 1930/210/50 defaults at
// +0x24..+0x2C, zero floats, the +0x3C vector, 1 at +0x48 and the repeated
// 1930/210 pairs. Field meanings are not recovered. The four words at +0x14
// and the three zero floats at +0x30 are modelled as small sub-objects with
// inline constructors: that grouping is what gives retail's store schedule
// (all words before the defaults; the allocator temporary's address taken
// after the +0x2C store).
#include <vector>
#include "../../../../reference/shims/bfme2_ascii/ascii_string.h"
#include "../../../../reference/shims/moduledata/Common/Snapshot.h"

struct BfmePod8 { unsigned int words[2]; };

class Rva003F9D08 : public Snapshot
{
public:
	Rva003F9D08();
	virtual ~Rva003F9D08();
	AsciiString string04, string08, string0C, string10;
	struct Words { int a, b, c, d; Words() : a(0), b(0), c(0), d(0) {} } words14;
	float float24, float28, float2C;
	struct Triple { float x, y, z; Triple() : x(0.0f), y(0.0f), z(0.0f) {} } triple30;
	_STL::vector<BfmePod8> vector3C;
	int int48;
	float float4C, float50;
	float float54, float58, float5C, float60;
	float float64, float68, float6C, float70;
};

Rva003F9D08::Rva003F9D08()
	: float24(1930.0f), float28(210.0f), float2C(50.0f),
	  int48(1), float4C(0.0f), float50(0.0f),
	  float54(1930.0f), float58(210.0f), float5C(1930.0f), float60(210.0f),
	  float64(0.0f), float68(0.0f), float6C(0.0f), float70(0.0f)
{
}
