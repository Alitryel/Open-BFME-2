// cl: /Ireference/shims/bfme2_ascii /MD /EHsc
// Retail 0x00434B8A, 179 bytes: the save/load screen's delete step. The selected list row's file name
// (the item data of the active list, 0x00433F7F) is turned into a full path under the save directory
// (0x002DC74A) except in mode 4 (replays), where it is already one, and the file is deleted; the screen
// then goes to state 2. WorldBuilder 0x12AF750 gives the shape.
#include "unicode_string.h"

extern "C" __declspec(dllimport) int __stdcall DeleteFileW(const unsigned short *fileName);

class Rva002DC74A
{
public:
	UnicodeString rva002DC74A(const UnicodeString &fileName) const;
};
class GameState;
extern GameState *TheGameState;

class GameWindow;
class AptSaveLoad
{
public:
	void rva00434B8A();
	int rva00433F7F();

private:
	unsigned char m_pad000[0x27C];
	int m_state;
	unsigned char m_pad280[0x288 - 0x280];
	GameWindow *m_gameList;
	unsigned char m_pad28c[0x2A0 - 0x28C];
	int m_mode;
};

void AptSaveLoad::rva00434B8A()
{
	if (m_gameList != 0)
	{
		UnicodeString *file = (UnicodeString *)rva00433F7F();
		if (file != 0 && !file->isEmpty())
		{
			UnicodeString path;
			if (m_mode == 4)
				path = *file;
			else
				path = ((Rva002DC74A *)TheGameState)->rva002DC74A(*file);
			DeleteFileW(path.str());
		}
		m_state = 2;
	}
}
