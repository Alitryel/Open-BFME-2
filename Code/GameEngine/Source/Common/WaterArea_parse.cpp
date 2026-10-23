// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /O1 /arch:SSE /G7
// ?parse@WaterArea@@QAEXAAVDataChunkInput@@PAX@Z @0x00537FCC 145B DataChunkInput field loader via rowed setters.
// Evidence: packet disassembly; calls its own setters 0x537F74 (+0x20) 0x537FA0 (+0x24) 0x537E90 float 0x537E7C bool; callees rowed readAsciiString readReal readByte releaseBuffer.
#include "ascii_string.h"

class DataChunkInput
{
public:
	AsciiString readAsciiString();
	float readReal();
	unsigned char readByte();
};

class WaterArea
{
public:
	void parse(DataChunkInput &input, void *info);
	void rva00537F74(const AsciiString &v);
	void rva00537FA0(const AsciiString &v);
	void rva00537E90(float v);
	void rva00537E7C(bool v);
};

void WaterArea::parse(DataChunkInput &input, void *)
{
	rva00537F74(input.readAsciiString());
	rva00537FA0(input.readAsciiString());
	rva00537E90(input.readReal());
	rva00537E7C(input.readByte() != 0);
}
