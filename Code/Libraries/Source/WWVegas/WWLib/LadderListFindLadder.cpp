// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
//
// ?findLadder@LadderList@@QAEPBVLadderInfo@@ABVAsciiString@@G@Z, retail 0x0054D74B, 151 bytes.
// Gap between two rows of stlport_list_asciistring_insert.cpp; flags copied
// from that TU. Searches the three ladder lists (special at +4, standard at
// +8, local at +0) for AsciiString at +0x28 plus port at +0x2C via rowed
// StringBase<char>::compare 0x000069D6. Donor is BFME1
// Code/GameEngine/Source/GameNetwork/GameSpy/LadderList_findLadder_Thunk.cpp
// (readable body of same mangled) plus upstream ZH LadderDefs.h layout
// (three LadderInfoList, LadderInfo with address/port tail). Identity is the
// GUI:JoinFailedUnknownLadder caller at 0x005A59CE plus TheLadderList global
// at 0x00A05FB0; class name is the real donor name.

#include "ascii_string.h"


struct LadderListNode
{
	LadderListNode *next;
	LadderListNode *prev;
	void *value;
};

class LadderInfo
{
public:
	char m_pad[0x28];
	AsciiString address;
	unsigned short port;
};

class LadderList
{
public:
	const LadderInfo *findLadder(const AsciiString &addr, unsigned short port);

private:
	LadderListNode *m_localLadders;
	LadderListNode *m_specialLadders;
	LadderListNode *m_standardLadders;
};

const LadderInfo *LadderList::findLadder(const AsciiString &addr, unsigned short port)
{
	for (LadderListNode *ladderListNode = m_specialLadders->next; ladderListNode != m_specialLadders; ladderListNode = ladderListNode->next)
	{
		LadderInfo *li = (LadderInfo *)ladderListNode->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *ladderListNode = m_standardLadders->next; ladderListNode != m_standardLadders; ladderListNode = ladderListNode->next)
	{
		LadderInfo *li = (LadderInfo *)ladderListNode->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	for (LadderListNode *ladderListNode = m_localLadders->next; ladderListNode != m_localLadders; ladderListNode = ladderListNode->next)
	{
		LadderInfo *li = (LadderInfo *)ladderListNode->value;
		if (li->address.compare(addr) == 0 && li->port == port)
			return li;
	}

	return 0;
}
