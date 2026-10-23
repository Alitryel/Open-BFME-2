// A global list lookup.
//
// BFME1 byte-identical donor (reference/open-bfme-1
// Code/GameEngine/Source/Common/Bfme5NinetyTwo.cpp); trimmed to the single T1
// body the sweep places.

#include "../../Include/GameClient/BfmeVideoTable.h"

class BfmeRecJD
{
public:
	int m_bfmeWords[7];
};

#define g_bfmeBeginJD ((BfmeRecJD *)g_bfmeVideoTableStorage.begin)
#define g_bfmeEndJD ((BfmeRecJD *)g_bfmeVideoTableStorage.end)

BfmeRecJD * __stdcall bfmeSlotAt(int index)
{
	if (index >= 0 && index < (int)(g_bfmeEndJD - g_bfmeBeginJD))
		return g_bfmeBeginJD + index;
	return 0;
}
