// cl: /Ireference/shims/bfme2_ascii /MD
// ?rva00537F74@WaterArea@@QAEXABVAsciiString@@@Z @0x00537F74 44B setter: if arg.compare(m_s20)!=0 then m_s20.set(arg) plus virtual [eax+8].
// Evidence: packet disassembly; callees rowed compare 0x000069D6 set 0x000366F0; caller 0x00537FCC passes AsciiString temp; prev row 0x00537EAD same +0x20 string.
#include "ascii_string.h"

class WaterArea
{
public:
	virtual ~WaterArea();
	virtual void v1();
	virtual void v2();
	void rva00537F74(const AsciiString &v);

private:
	unsigned char m_pad[0x1C];
	AsciiString m_s20;
};

void WaterArea::rva00537F74(const AsciiString &asciiString)
{
	const StringBase<char> &vs = reinterpret_cast<const StringBase<char> &>(asciiString);
	StringBase<char> &ms = reinterpret_cast<StringBase<char> &>(m_s20);
	if (vs.compare(ms) != 0) {
		ms.set(vs);
		v2();
	}
}
