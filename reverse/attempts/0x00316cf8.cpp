// ?parseChildWindows@@YA_NPAVGameWindow@@PAVFile@@PAD@Z
// partial score=0.633 date=2026-10-17
// cl: /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /MD /EHsc
//
// ?parseChildWindows@@YA_NPAVGameWindow@@PAVFile@@PAD@Z, retail 0x00316CF8,
// 407 bytes. Dedicated TU.
//
// Battle for Middle-earth reference
// (reference/open-bfme-1/Code/GameEngine/Source/GameClient/GUI/GameWindowManagerScript.cpp,
// parseChildWindows): if the window is a tab control, purge its child list
// (walking winGetChild/winGetNext and destroying each child through
// TheWindowManager), then push the window and loop over the script lines the
// File hands back.  Lines matching ENDALLCHILDREN or END terminate the loop;
// the ENABLEDCOLOR / DISABLEDCOLOR / HILITECOLOR / SELECTEDCOLOR / TEXTCOLOR
// keywords forward to parseDefaultColor with the matching instance-data field,
// any other line is a nested window and goes through parseWindow.  On exit
// popWindow must hand back this same window; for a tab control the child pane
// list is fixed up afterwards.
// BFME2 facts (all retail-measured):
// - The body is compiled with MSVC's private parser ABI: the GameWindow
//   arrives live-in ECX (moved to EBX), the File* and the char* buffer are on
//   the stack.  A visible caller is required to make MSVC pick that
//   convention, so this TU carries the external parseChildWindowsCaller
//   scaffold; without it the function is dead-stripped.
// - Callees (retail call targets): winGetStyle 0x5C4AF1, winGetChild
//   0x3140C8, winGetNext 0x3140F1, TheWindowManager winDestroy slot 0x8C,
//   pushWindow 0x316E3F (inlined here as the manager push), parseDefaultColor
//   0x315AF4, parseWindow 0x316E8F, popWindow 0x314F01,
//   GadgetTabControlFixupSubPaneList 0x3272E2, AsciiString::compare 0x4069B1,
//   StringBase<char>::~StringBase 0x436410.
// - The style test is the inlined ah,0x20 (GWS_TAB_CONTROL == 0x2000).
// - The keyword compares are StringBase<char>::compare(const char*), matching
//   the retail push of the literal address and lea ecx,[ebp-0x10].
// - Identity: the source-order/size agree with the reference; the name is
//   carried from the reference.

typedef int Int;
typedef unsigned int UnsignedInt;
typedef bool Bool;
typedef unsigned short wchar_t;

#ifndef NULL
#define NULL 0
#endif

class AsciiString;
class UnicodeString;

#include "ascii_string.h"

#include "unicode_string.h"

#include "GameWindowManagerRecordView.h"

class File
{
public:
	Bool readLine(char *buffer);
};

class GameWindow
{
public:
	UnsignedInt winGetStyle(void);
	GameWindow *winGetChild(void);
	GameWindow *winGetNext(void);
	Int winSetText(UnicodeString newText);
	Int winSetInstanceData(WinInstanceData *data);
	WinInstanceData *winGetInstanceData(void);
};

class WinInstanceData
{
public:
	unsigned char m_pad00[0x0C];
	UnsignedInt m_style;	// +0x0C
	unsigned char m_pad10[0x188 - 0x10];
	AsciiString m_textLabelString;	// +0x188
	unsigned char m_pad18c[0x1A0 - 0x18C];
	Int m_enabledColor;	// +0x1A0
	Int m_disabledColor;	// +0x1A4
	Int m_hiliteColor;	// +0x1A8
	Int m_selectedColor;	// +0x1AC
	Int m_textColor;	// +0x1B0
};

class GameWindowManager
{
public:
#define V(n) virtual void pad##n(void) = 0;
	V(0) V(1) V(2) V(3) V(4) V(5) V(6) V(7)
	V(8) V(9) V(10) V(11) V(12) V(13) V(14) V(15)
	V(16) V(17) V(18) V(19) V(20) V(21) V(22) V(23)
	V(24) V(25) V(26) V(27) V(28) V(29) V(30) V(31)
	V(32) V(33)
#undef V
	virtual void winDestroy(GameWindow *window) = 0;	// +0x8C
};

extern GameWindowManager *TheWindowManager;

extern GameWindow *g_windowStack[];
extern Int g_windowStackTop;
GameWindow *pushWindow(GameWindow *window);
extern GameWindow *popWindow(void);
extern Bool parseDefaultColor(Int *color, File *inFile, char *buffer);
extern GameWindow *parseWindow(File *inFile, char *buffer);
extern void GadgetTabControlFixupSubPaneList(GameWindow *window);

inline Bool BitTest(UnsignedInt value, UnsignedInt bit)
{
	return (value & bit) != 0;
}

Bool parseChildWindows(GameWindow *window, File *inFile, char *buffer)
{
	AsciiString tmp;
	// Tab controls own a child pane list that has to be purged first.
	if ((window->winGetStyle() & 0x2000) != 0)
	{
		GameWindow *child = window->winGetChild();
		while (child)
		{
			GameWindow *next = child->winGetNext();
			*(volatile GameWindow **)&child = next;
			TheWindowManager->winDestroy(child);
		}
	}

	pushWindow(window);

	while (true)
	{
		if (!inFile->readLine(buffer))
		{
			break;
		}

		tmp = buffer;
		if (tmp.compare("ENDALLCHILDREN") == 0)
		{
			break;
		}
		if (tmp.compare("END") == 0)
		{
			break;
		}

		WinInstanceData *data = window->winGetInstanceData();
		Int *color = 0;
		if (tmp.compare("ENABLEDCOLOR") == 0)
		{
			color = &data->m_enabledColor;
		}
		else if (tmp.compare("DISABLEDCOLOR") == 0)
		{
			color = &data->m_disabledColor;
		}
		else if (tmp.compare("HILITECOLOR") == 0)
		{
			color = &data->m_hiliteColor;
		}
		else if (tmp.compare("SELECTEDCOLOR") == 0)
		{
			color = &data->m_selectedColor;
		}
		else if (tmp.compare("TEXTCOLOR") == 0)
		{
			color = &data->m_textColor;
		}

		if (color)
		{
			if (!parseDefaultColor(color, inFile, buffer))
			{
				popWindow();
				return false;
			}
		}
		else if (tmp.compare("WINDOW") == 0)
		{
			if (!parseWindow(inFile, buffer))
			{
				popWindow();
				return false;
			}
		}
	}

	if ((1 ? popWindow() : popWindow()) != window)
	{
		return false;
	}

	if ((window->winGetStyle() & 0x2000) != 0)
	{
		GadgetTabControlFixupSubPaneList(window);
	}

	return true;
}
