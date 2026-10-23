// cl: /O1 /arch:SSE /G7 /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc /Ireference/shims/bfme2_ascii
// stlport
// ?Rva000CF713Parse@@YAXPAVINI@@PAVRva000CF713Owner@@@Z @0x000CF713 91B.
// Builds one zeroed 76-byte parse record whose last word is a string, lets the rowed
// ModelCondition bit-list driver 0x000B937E fill it from the INI stream (the driver
// takes the record as its receiver and the string slot as user data), and appends it
// to the record vector at +0x24 of the owner. The record is dropped afterwards, which
// releases its string. Layout views are neutral.
#include <vector>
#include "ascii_string.h"
#include <string.h>

class INI;
struct BfmePod76 { int a[19]; };
namespace _STL {
template <> void vector<BfmePod76, allocator<BfmePod76> >::push_back(const BfmePod76 &);
}

class Rva000B937E { public: void rva000B937E(INI *ini, void *userData); };

class Rva000CF713Owner
{
public:
	char m_pad[0x24];
	_STL::vector<BfmePod76> m_records;
};

void Rva000CF713Parse(INI *ini, Rva000CF713Owner *owner)
{
	BfmePod76 record;
	memset(&record, 0, 0x4c);
	AsciiString name;
	reinterpret_cast<Rva000B937E *>(&record)->rva000B937E(ini, &name);
	owner->m_records.push_back(record);
}
