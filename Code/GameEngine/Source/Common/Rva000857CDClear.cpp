// cl: /DNDEBUG /DWIN32 /D_WINDOWS /MD /GX- /GS-
// ??0Rva000857CD@@QAE@XZ 0x000857CD 37B: thiscall clears three floats at +0/+4/+8 and five bytes at +C..+10 returns this;
// constructor of the W3DView member at +0x24F4 (caller 0x0008B7CF constructs it right after the camera settings member at +0x24C8)
class Rva000857CD
{
public:
	float m_0;
	float m_4;
	float m_8;
	unsigned char m_C;
	unsigned char m_D;
	unsigned char m_E;
	unsigned char m_F;
	unsigned char m_10;
	Rva000857CD();
};

Rva000857CD::Rva000857CD()
{
	m_0 = 0.0f;
	m_4 = 0.0f;
	m_8 = 0.0f;
	m_C = 0;
	m_D = 0;
	m_E = 0;
	m_F = 0;
	m_10 = 0;
}
