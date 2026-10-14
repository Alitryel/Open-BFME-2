// cl: /Ireference/shims/bfme2_ascii /O1 /Oy- /MD /EHsc /DNDEBUG /DWIN32 /D_WINDOWS
// stlport

// BuildListInfo::getTemplateName (ZH SidesList.h): the template name by value.
// Retail folds it with TerrainType::getTexture at 0x000AF1DD (27B, the
// AsciiString at +0x08 copied out). AIPlayer::onStructureProduced calls it at
// 0x004F3556, where the BFME 1 and Zero Hour twins call getTemplateName().
// Layout per ZH: vptr, m_buildingName at +0x04, m_templateName at +0x08.

#include "ascii_string.h"

class BuildListInfo
{
public:
	AsciiString getTemplateName() const;
private:
	char m_pad0[4];
	AsciiString m_buildingName; // +0x04
	AsciiString m_templateName; // +0x08
};

AsciiString BuildListInfo::getTemplateName() const
{
	return m_templateName;
}
