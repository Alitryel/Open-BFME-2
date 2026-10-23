// cl: /Ireference/shims/bfme2_ascii /Ob2 /EHs /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ??0Rva0041E6BE@@QAE@HHPAVDataChunkInput@@PBVAsciiString@@1@Z @0x0041E6BE 45B
// __thiscall derived from rowed DataChunkParser (12B base at +0) adding int at +0xC
// plus int at +0x10 plus vtable g_00C3AF68. Evidence: base call 0x000ABB87 with
// three pushes from +0x10 +0x14 +0x18 plus stores +0xC +0x10 plus vtable plus ret 0x14;
// caller at 0x0041F19A.
#include "ascii_string.h"

class DataChunkInput;
class UserParser;

class DataChunkParser
{
public:
	DataChunkParser(DataChunkInput *input, const AsciiString *name, const AsciiString *label);
private:
	const void *m_opaque00;
	DataChunkInput *m_input04;
	UserParser *m_parser08;
};

// The retail table at RVA 0x0083AF68: 2 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva003B241AOwner@@QAEPAXI@Z")();
void __identifier("?invoke@Rva0041E6EB@@QAEXXZ")();
}
extern const void *const g_00C3AF68[2] = {
	(const void *)&__identifier("??_GRva003B241AOwner@@QAEPAXI@Z"), // slot 0 0x0041E6F3
	(const void *)&__identifier("?invoke@Rva0041E6EB@@QAEXXZ"), // slot 1 0x0041E6EB
};

class Rva0041E6BE : public DataChunkParser
{
public:
	Rva0041E6BE(int a, int b, DataChunkInput *input, const AsciiString *name, const AsciiString *label);
private:
	int m_a;
	int m_b;
};

Rva0041E6BE::Rva0041E6BE(int a, int b, DataChunkInput *input, const AsciiString *name, const AsciiString *label)
	: DataChunkParser(input, name, label), m_a(a), m_b(b)
{
	*(const void **)this = g_00C3AF68;
}
