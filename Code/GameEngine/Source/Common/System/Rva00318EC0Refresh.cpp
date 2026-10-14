// cl: /EHs-
// ?rva00318EC0@Rva0031934BOwner@@QAEXXZ, retail 0x00318EC0, 130 bytes.
// Refresh after the +0x54 player index changes (0x0031911F): resolves the
// player through TheLivingWorldLogic (0x002B51F8); hands the opaque
// +0x19C colour to the +0x88 target's slot 6 and writes the +0x190 colour,
// alpha forced to 0xFF, into both colour words of the +0x78 record.
#include "../../../../Libraries/Include/Lib/RGBColor.h"

class Rva002E2903Player
{
public:
	char m_pad000[0x190];
	RGBColor m_color190;	// +0x190
	RGBColor m_color19C;	// +0x19C
};

class Rva002BA8F1Logic
{
public:
	Rva002E2903Player *find(int index, unsigned int *out);	// 0x002B51F8
};
class LivingWorldLogic;
extern LivingWorldLogic *TheLivingWorldLogic;

class Rva00318EC0Target
{
public:
	virtual void s00(); virtual void s01(); virtual void s02(); virtual void s03();
	virtual void s04(); virtual void s05();
	virtual void setColor(int *color);	// +0x18
};

struct Rva00318EC0Colors
{
	char m_pad00[0x24];
	int m_color24;	// +0x24
	int m_color28;	// +0x28
};

class Rva0031934BOwner
{
public:
	void rva00318EC0();
private:
	char m_pad00[0x54];
	int m_54;	// +0x54
	char m_pad58[0x78 - 0x58];
	Rva00318EC0Colors *m_colors78;	// +0x78
	char m_pad7C[0x88 - 0x7C];
	Rva00318EC0Target *m_target88;	// +0x88
};

void Rva0031934BOwner::rva00318EC0()
{
	int index = m_54;
	Rva002E2903Player *player = reinterpret_cast<Rva002BA8F1Logic *>(TheLivingWorldLogic)->find(index, 0);
	if (player == 0)
		return;
	if (m_target88) {
		int color = player->m_color19C.getAsInt() | 0xFF000000;
		m_target88->setColor(&color);
	}
	Rva00318EC0Colors *colors = m_colors78;
	if (colors) {
		colors->m_color24 = player->m_color190.getAsInt() | 0xFF000000;
		m_colors78->m_color28 = player->m_color190.getAsInt() | 0xFF000000;
	}
}