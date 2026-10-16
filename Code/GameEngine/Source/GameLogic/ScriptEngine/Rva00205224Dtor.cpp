// cl: /Ireference/shims/bfme2_ascii /MD /Ireference/shims/moduledata
// ??1Rva0020479E@@UAE@XZ @0x00205224 63B: virtual dtor tearing down AsciiStrings at +0x10 then +0x0C via rowed releaseBuffer 0x00036410 then restoring Snapshot base vtable 0x00BBB554.
// Evidence: deleting dtor caller 0x00205208 (28B ??_G shape); same 63B shape as SlavedUpdateModuleDataDtor 0x00255FC1; base Snapshot BBB554.
#include "ascii_string.h"


#include "Common/Snapshot.h"

class __declspec(novtable) Rva0020479E : public Snapshot
{
public:
	virtual ~Rva0020479E();
private:
	char m_pad[0x0C - 4];
	AsciiString m_C; // +0x0C
	AsciiString m_10; // +0x10
};

Rva0020479E::~Rva0020479E()
{
}
