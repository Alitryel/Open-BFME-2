// cl: /DNDEBUG /MD /EHsc /Ireference/open-bfme-1/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/shims/stringinline
// Native E8656 and EC67F are separate 98B constructors. Their coordinate
// array callbacks and string offsets agree; no original class names are asserted.
// EC67F is explicitly paired with EC6E1 by EDE35's 64x5C vector construction.
#include "coord2d.h"

#include "../../../../../reference/shims/bfme2_ascii/ascii_string.h"

class Rva00735D80TreeType
{
public:
	Rva00735D80TreeType();

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

Rva00735D80TreeType::Rva00735D80TreeType()
{
}

#include "W3DTreeTypeRecord.h"

Rva000EC67F::Rva000EC67F()
{
}
