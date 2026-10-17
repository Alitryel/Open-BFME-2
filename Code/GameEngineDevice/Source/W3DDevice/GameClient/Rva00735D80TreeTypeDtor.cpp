// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/shims/stringinline
// Native EC6E1 tears down the type paired with EC67F by EDE35's vector
// construction. The shared AsciiString now reproduces the native direct
// releaseBuffer calls at 36410, replacing the old AsciiStringMember surrogate.
// E86B8 remains a distinct native destructor; adjacency does not pair it.
#include "coord2d.h"

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

#include "W3DTreeTypeRecord.h"

Rva000EC67F::~Rva000EC67F()
{
}

// Separate124B teardown at E86B8; its other lifetime relationships stay unasserted.
class Rva000E86B8
{
public:
	~Rva000E86B8();
private:
	unsigned char m_treeData[0x24];
	Coord2D m_primaryTextureCoords[2];
	Coord2D m_secondaryTextureCoords[2];
	unsigned char m_textureFlags[4];
	AsciiString m_modelName;
	AsciiString m_textureName;
	AsciiString m_shadowName;
	AsciiString m_animationName;
};

Rva000E86B8::~Rva000E86B8()
{
}
