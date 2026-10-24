// cl: /Ireference/shims/bfme2_ascii /O1 /arch:SSE /G7 /DNDEBUG /MD /EHsc /D_STLP_USE_STATIC_LIB
// GameClient::GameClient allocates 0x2c bytes for TheDrawGroupInfo and calls
// this constructor. Target field meanings remain unrecovered.
#include "ascii_string.h"

class DrawGroupInfo
{
public:
	DrawGroupInfo();
private:
	AsciiString m_font;
	int m_unk04;
	unsigned char m_unk08;
	unsigned char m_unk09;
	char m_pad0A[2];
	int m_unk0C;
	int m_unk10;
	int m_unk14;
	int m_unk18;
	float m_unk1C;
	unsigned char m_unk20;
	char m_pad21[3];
	int m_unk24;
	unsigned char m_unk28;
};

DrawGroupInfo::DrawGroupInfo()
{
	((StringBase<char> *)&m_font)->StringBase<char>::set("Arial");
	m_unk04 = 0x0c;
	m_unk08 = 0;
	m_unk09 = 1;
	m_unk0C = -1;
	m_unk10 = (int)0xff000000;
	m_unk14 = -1;
	m_unk18 = -1;
	m_unk1C = 0.0f;
	m_unk20 = 0;
	m_unk24 = 0;
	m_unk28 = 1;
}
