// cl: -Ireference/open-bfme-1/game/GameEngine/Source/Common /Ireference/shims/bfme2_ascii
#include "ascii_string.h"

class MixFileCreator { public: struct FileInfoStruct; };
struct BfmeElemQR
{
	int m_bfmeAQR;
	int m_bfmeBQR;
	int m_bfmeCQR;
	AsciiString m_bfmeRoomQR;
};

void __cdecl Rva002176F1Insert(MixFileCreator::FileInfoStruct *, MixFileCreator::FileInfoStruct);
// Retail retains the unused comparator word after the sixteen-byte value.
// The recovered cdecl worker consumes the same value and ignores that word.
typedef void (__cdecl *QRInsertCall)(BfmeElemQR *, BfmeElemQR, void *);

void __cdecl bfmeEachQR(BfmeElemQR *first, BfmeElemQR *last, int unused, void *extra)
{
	while (first != last)
	{
		((QRInsertCall)Rva002176F1Insert)(first, *first, extra);
		++first;
	}
}
