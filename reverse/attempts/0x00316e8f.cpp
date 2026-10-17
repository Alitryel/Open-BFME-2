// ?parseWindow@@YAPAVGameWindow@@PAVFile@@PAD@Z
// partial score=0.0 date=2026-10-17
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?parseWindow@@YAPAVGameWindow@@PAVFile@@PAD@Z, retail 0x00316E8F,
// 910 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseWindow): read a WINDOWTYPE block header, look up the matching
// window template, parse its SCREENRECT, then loop over the template's
// parse functions, dispatching DATA blocks to parseData and everything
// else through the template's own callback, finally creating the window
// and recursing into parseChildWindows.
// BFME2 facts (all retail-measured):
// - The body is a file-static compiled with MSVC's private parser ABI:
//   the File* arrives in EBX (via [ebp+0xc]) and the buffer pointer on the
//   stack. Callees readUntilSemicolon 0x314DE8, getDataTemplate 0x315445,
//   parseScreenRect 0x31583E, parseData 0x31553A, createWindow 0x316BD2,
//   parseChildWindows 0x316CF8 and peekWindow 0x314EEE are file statics of
//   the same mega-TU with the same private conventions.
// - WinInstanceData is constructed at [ebp-0x20c] and initialised in place;
//   its m_textLabelString copy is the strcpy at 0x717055.
// - The template table is a NULL-terminated array of {char *name; bool
//   (*parse)(char *, File *, void *);} records at 0xdbe198.
// - Identity: source-order/size agree; the name is carried from the
//   reference.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;

#ifndef NULL
#define NULL 0
#endif

class AsciiString;
class UnicodeString;

#include "ascii_string.h"

#include "unicode_string.h"

#include "GameWindowManagerRecordView.h"

class File;
class GadgetCreateView;
class Font;

// The template table entry: name plus a parse callback.
struct WindowTemplateEntry
{
	const char *m_name;
	Bool (*m_parse)(char *buffer, void *data, void *userData);
};

extern WindowTemplateEntry g_windowTemplateTable[];

extern char *g_tokenSeparator;

class GameWindow
{
public:
	Int winGetSize(Int *w, Int *h);
	Int winSetInstanceData(WinInstanceData *data);
};

class WinInstanceData
{
public:
	WinInstanceData(void);
	~WinInstanceData(void);
	void init(void);
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n(void) = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
#undef V
	virtual Int slot40(GameWindow *window) = 0;	// +0x40
	virtual Int slot44(GameWindow *window) = 0;	// +0x44
};

class HeaderTemplateManager
{
public:
	Font *getFontFromTemplate(AsciiString name);
};

extern GameWindowManager *TheWindowManager;
extern HeaderTemplateManager *TheHeaderTemplateManager;

extern GameWindow *peekWindow(void);

void readUntilSemicolon(File *file, char *buffer, Int size);
void *getDataTemplate(char *name, Int *exists);
Bool parseScreenRect(char *buffer, File *file, Int *x, Int *y, Int *w, Int *h);
Bool parseData(void **data, char *name, File *file);
GameWindow *createWindow(char *type, Int a, void *data, GadgetCreateView *view, GameWindow *parent);
Bool parseChildWindows(File *file, GameWindow *parent);

extern "C" char *__cdecl strtok(char *str, const char *delim);
extern "C" char *__cdecl strcpy(char *dst, const char *src);

// ---------------------------------------------------------------------------
// ?parseWindow@@YAPAVGameWindow@@PAVFile@@PAD@Z
// ---------------------------------------------------------------------------
GameWindow *parseWindow(File *file, char *buffer)
{
	GameWindow *window = NULL;
	WinInstanceData instData;
	WindowTemplateEntry *entry;
	void *data = NULL;
	char name[0x800];
	Int x, y, w, h;

	instData.init();

	GameWindow *parent = peekWindow();

	if (parent != NULL)
	{
		parent->winGetSize(&x, &y);
	}
	else
	{
		x = TheWindowManager->slot40(NULL);
		y = TheWindowManager->slot44(NULL);
	}
	instData.init();

	readUntilSemicolon(file, buffer, 0x800);
	buffer = strtok(buffer, g_tokenSeparator);
	strtok(NULL, g_tokenSeparator);
	strcpy(name, buffer);
	data = getDataTemplate(name, (Int *)&entry);
	entry = NULL;

	readUntilSemicolon(file, buffer, 0x800);
	buffer = strtok(buffer, g_tokenSeparator);

	if (!parseScreenRect(buffer, file, &x, &y, &w, &h))
		return NULL;

	entry = g_windowTemplateTable;
	while (true)
	{
		for (; entry->m_parse != NULL; entry = (WindowTemplateEntry *)((char *)entry + 8))
		{
			AsciiString token(buffer);
			if (token.compare(entry->m_name) == 0)
			{
				strcpy(name, buffer);
				readUntilSemicolon(file, buffer, 0x800);
				if (!entry->m_parse(name, data, file))
					return NULL;
				break;
			}
		}

		if (entry->m_parse == NULL)
		{
			readUntilSemicolon(file, buffer, 0x800);
			AsciiString token(buffer);
			if (token.compare("DATA") == 0)
			{
				readUntilSemicolon(file, buffer, 0x800);
				if (!parseData(&data, buffer, file))
					return NULL;
			}
			else if (AsciiString(buffer).compare("WINDOWTYPE") == 0)
			{
				readUntilSemicolon(file, buffer, 0x800);
			}
			else if (AsciiString(buffer).compare("FONT") == 0)
			{
				AsciiString fontName(buffer);
				if (TheHeaderTemplateManager->getFontFromTemplate(fontName) != NULL)
				{
					TheHeaderTemplateManager->getFontFromTemplate(fontName);
				}
				if (window == NULL)
				{
					window = createWindow(name, w, data, (GadgetCreateView *)file, parent);
				}
			}
			else if (AsciiString(buffer).compare("SCREENRECT") == 0)
			{
				readUntilSemicolon(file, buffer, 0x800);
				parseScreenRect(buffer, file, &x, &y, &w, &h);
			}
			else
			{
				readUntilSemicolon(file, buffer, 0x800);
			}
		}
	}

	return window;
}
