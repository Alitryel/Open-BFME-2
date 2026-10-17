// ?rva005B98E9@OnlineHome@AptOnline@@QAEXXZ
// partial score=0.846 date=2026-10-17
// ?rva005B98E9@OnlineHome@AptOnline@@QAEXXZ
// partial score=0.771 date=2026-10-15
// ?rva005B98E9@OnlineHome@AptOnline@@QAEXXZ
// partial score=0.773 date=2026-10-14
// cl: /Ireference/shims/bfme2_ascii /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
// stlport
// Retail 0x005B98E9, 642 bytes: the online home screen's message of the day. Each line of the
// GameSpyInfo MOTD (virtual slot 0x10C) is trimmed, an escaped line loses its backslash, a
// "\AARRGGBB" prefix selects the colour (grabHexInt on four byte pairs; otherwise the palette entry 27
// of GameSpyColor, 0x00DB9204), and the line is added to the list box at +0x60. Same flow as BFME 1's
// OnlineHomeMessageOfTheDay.cpp; WorldBuilder 0x015855D0.
extern "C" void _ReadWriteBarrier(void);
#pragma intrinsic(_ReadWriteBarrier)
#include "unicode_string.h"
#include "ascii_string.h"
#include <string>
#include <stdlib.h>


// Retail expands getCharAt in place here (movsx from the buffer, null-checked), as LadderDefs.cpp's
// TU does; the out-of-line COMDAT stays with the library.
template<> inline char StringBase<char>::getCharAt(int index) const throw()
{
	return m_data ? m_data->data[index] : 0;
}

class GameWindow;
class GameSpyInfoMotd
{
public:
	virtual void s000(); virtual void s004(); virtual void s008(); virtual void s00C();
	virtual void s010(); virtual void s014(); virtual void s018(); virtual void s01C();
	virtual void s020(); virtual void s024(); virtual void s028(); virtual void s02C();
	virtual void s030(); virtual void s034(); virtual void s038(); virtual void s03C();
	virtual void s040(); virtual void s044(); virtual void s048(); virtual void s04C();
	virtual void s050(); virtual void s054(); virtual void s058(); virtual void s05C();
	virtual void s060(); virtual void s064(); virtual void s068(); virtual void s06C();
	virtual void s070(); virtual void s074(); virtual void s078(); virtual void s07C();
	virtual void s080(); virtual void s084(); virtual void s088(); virtual void s08C();
	virtual void s090(); virtual void s094(); virtual void s098(); virtual void s09C();
	virtual void s0A0(); virtual void s0A4(); virtual void s0A8(); virtual void s0AC();
	virtual void s0B0(); virtual void s0B4(); virtual void s0B8(); virtual void s0BC();
	virtual void s0C0(); virtual void s0C4(); virtual void s0C8(); virtual void s0CC();
	virtual void s0D0(); virtual void s0D4(); virtual void s0D8(); virtual void s0DC();
	virtual void s0E0(); virtual void s0E4(); virtual void s0E8(); virtual void s0EC();
	virtual void s0F0(); virtual void s0F4(); virtual void s0F8(); virtual void s0FC();
	virtual void s100(); virtual void s104(); virtual void s108();
	virtual const AsciiString &getMOTD();
};
extern GameSpyInfoMotd *TheGameSpyInfo;
extern int GameSpyColor[];
void GadgetListBoxReset(GameWindow *);
int GadgetListBoxAddEntryText(GameWindow *, UnicodeString, int, int, int, bool);
void GadgetListBoxSetTopVisibleEntry(GameWindow *, int);
_STL::wstring MultiByteToWideCharSingleLine(const char *);

// The two hex digits are read through a four-character "0xff" template.
static int __cdecl grabHexInt(const char *s)
{
	char buffer[5] = "0xff";
	buffer[2] = s[0];
	buffer[3] = s[1];
	return strtol(buffer, 0, 16);
}

namespace AptOnline
{
class OnlineHome
{
public:
	void rva005B98E9();
private:
	unsigned char m_pad000[0x60];
	GameWindow *m_motd; // +0x60
};

void OnlineHome::rva005B98E9()
{
	if (m_motd && TheGameSpyInfo)
	{
		GadgetListBoxReset(m_motd);
		AsciiString line;
		UnicodeString text;
		AsciiString motd;
		motd = TheGameSpyInfo->getMOTD();
		int color = *(volatile int *)&GameSpyColor[27];
		while (motd.nextToken(&line, "\n"))
		{
			if (line.getCharAt(line.getLength() - 1) == '\r')
				line.removeLastChar();
			line.trim();
			if (line.isEmpty())
				line = " ";
			color = GameSpyColor[27];
			if (line.startsWith("\\\\"))
				line = line.str() + 1;
			else if (line.startsWith("\\") && line.getLength() > 9)
			{
				unsigned char a = grabHexInt(line.str() + 1);
				unsigned char r = grabHexInt(line.str() + 3);
				unsigned char g = grabHexInt(line.str() + 5);
				unsigned char b = grabHexInt(line.str() + 7);
				color = (a << 24) | (r << 16) | (g << 8) | b;
				line = line.str() + 9;
			}
			text = UnicodeString(MultiByteToWideCharSingleLine(line.str()).c_str());
			GadgetListBoxAddEntryText(m_motd, text, color, -1, -1, true);
			GadgetListBoxSetTopVisibleEntry(m_motd, 0);
		}
	}
}
}
