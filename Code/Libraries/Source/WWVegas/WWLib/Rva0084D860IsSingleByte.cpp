// cl: /MD /D_STLP_USE_STATIC_LIB
// BFME1 donor: Rva0084DBStringAndCodePage.cpp. Retail stores GetCPInfo's
// MaxCharSize in the first dword of a 20-byte local and tests it against 1.
// Target disassembly reads owner+4 as the code-page value.

struct Rva0084D860CodePage
{
	unsigned int unknown;
	unsigned int codePage;
};

struct Rva0084D860CpInfo
{
	unsigned int MaxCharSize;
	unsigned char remainder[16];
};

extern "C" __declspec(dllimport) int __stdcall GetCPInfo(unsigned int, Rva0084D860CpInfo *);

bool Rva0084D860IsSingleByte(const Rva0084D860CodePage *owner)
{
	Rva0084D860CpInfo info;
	GetCPInfo(owner->codePage, &info);
	return info.MaxCharSize == 1;
}
