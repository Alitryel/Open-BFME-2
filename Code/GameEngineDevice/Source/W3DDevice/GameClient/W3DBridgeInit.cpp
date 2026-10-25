// cl: /Ireference/shims/bfme2_ascii /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWLib
// ?init@W3DBridge@@QAEXVVector3@@0VAsciiString@@@Z 0x000DDB17 125B W3DBridge::init from ZH donor W3DBridgeBuffer.h init(Vector3 fromLoc Vector3 toLoc AsciiString name); evidence: 6 floats to +0/+C via movss AsciiString set at +0x108 plus releaseBuffer for by-value copy flag +0x110=1 ret 0x1c callers 0x000DF6B1 in 0x000DF612
#include "ascii_string.h"

class Vector3
{
public:
	float X;
	float Y;
	float Z;
};

class W3DBridge
{
public:
	void init(Vector3 fromLoc, Vector3 toLoc, AsciiString name);
private:
	Vector3 m_start;
	Vector3 m_end;
	unsigned char m_pad18[0x108 - 0x18];
	AsciiString m_templateName;
	int m_curDamageState;
	bool m_enabled;
};

void W3DBridge::init(Vector3 fromLoc, Vector3 toLoc, AsciiString name)
{
	m_start.X = fromLoc.X;
	m_start.Y = fromLoc.Y;
	m_start.Z = fromLoc.Z;
	m_end.X = toLoc.X;
	m_end.Y = toLoc.Y;
	m_end.Z = toLoc.Z;
	m_templateName = name;
	m_enabled = true;
}
