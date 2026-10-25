// cl: /FIzh_ascii.h /Ireference/shims/bfme2_ascii_zh /Ireference/shims/bfme2_ascii /O1 /DNDEBUG /DWIN32 /D_WINDOWS /MD /EHsc /Ireference/open-bfme-1/reference/shims/sweep /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/Compression /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngineDevice/Include /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Main /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWLib /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WW3D2 /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWMath /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWDebug /Ireference/open-bfme-1/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/Libraries/Source/WWVegas/WWSaveLoad
// stlport
//
// ?getReadyCommands@NetCommandWrapperList@@QAEPAVNetCommandList@@XZ retail
// 0x0058C2AD (169 bytes) and the removeFromList it calls, 0x0058C1A5 (78
// bytes). Ported from the Open-BFME-1 donor game/GameEngine/Source/
// GameNetwork/NetCommandWrapperList_getReadyCommands.cpp (1281192f68; donor
// flags plus BFME 2's /O1). Compiled that way getReadyCommands places
// uniquely on unclaimed .text by masked whole-.text search
// (tools/donor_sweep.py) and its removeFromList call reads 0x0058C1A5.
// BFME 2 keeps removeFromList out of line (its only caller is
// getReadyCommands); NetCommandWrapperList.cpp's Zero Hour copies of both,
// written against the pooled NetCommandRef layout, are retired in its favour.
//
// readable body of ?getReadyCommands@NetCommandWrapperList@@QAEPAVNetCommandList@@XZ: game/GameEngine/Source/GameNetwork/NetCommandWrapperList.cpp

// NetCommandWrapperList::getReadyCommands, 0x00676890, 256 bytes.
//
// Split out of NetCommandWrapperList.cpp because it needs BFME's de-pooled
// NetCommandRef -- the command at +0x00 and the relay at +0x0C rather than the
// reference's +0x04 and +0x10 -- and because the reference's deleteInstance()
// is a virtual call where retail emits a destructor plus operator delete.
//
// Two BFME differences from the reference: the fresh list is reset() rather
// than init()ed, and removeFromList is inlined rather than called, so its body
// appears here as well as at 0x006766D0.

#include "BfmeNetCommandWrapperView.h"

// BFME 2 keeps this out of line at 0x0058C1A5. It frees the node with a
// global delete: the virtual destructor is called with flag 0 and the
// pointer it returns goes to ::operator delete (0x0002FD60).
void NetCommandWrapperList::removeFromList(NetCommandWrapperListNode *node) {
	if (node == NULL) {
		return;
	}

	NetCommandWrapperListNode *netCommandWrapperListNode = m_list;
	NetCommandWrapperListNode *prev = NULL;

	while ((netCommandWrapperListNode != NULL) && (netCommandWrapperListNode->getCommandID() != node->getCommandID())) {
		prev = netCommandWrapperListNode;
		netCommandWrapperListNode = netCommandWrapperListNode->m_next;
	}

	if (netCommandWrapperListNode == NULL) {
		return;
	}

	if (prev == NULL) {
		m_list = netCommandWrapperListNode->m_next;
		::delete netCommandWrapperListNode;
		netCommandWrapperListNode = NULL;
	} else {
		prev->m_next = netCommandWrapperListNode->m_next;
		::delete netCommandWrapperListNode;
		netCommandWrapperListNode = NULL;
	}
}

NetCommandList *NetCommandWrapperList::getReadyCommands()
{
	NetCommandList *retlist = new NetCommandList;
	retlist->reset();

	NetCommandWrapperListNode *netCommandWrapperListNode = m_list;
	NetCommandWrapperListNode *next = NULL;

	while (netCommandWrapperListNode != NULL) {
		next = netCommandWrapperListNode->m_next;
		// Keep retail's inline comparison while the shared rowed accessor stays noinline.
		if (netCommandWrapperListNode->m_numChunksPresent == netCommandWrapperListNode->m_numChunks) {
			NetCommandRef *msg = NetPacket::ConstructNetCommandMsgFromRawData(netCommandWrapperListNode->getRawData(), netCommandWrapperListNode->getRawDataLength());
			if (msg != NULL) {
				NetCommandRef *ret = retlist->addMessage(msg->getCommand());
				ret->setRelay(msg->getRelay());

				delete msg;
				msg = NULL;
			}

			removeFromList(netCommandWrapperListNode);
			netCommandWrapperListNode = NULL;
		}
		netCommandWrapperListNode = next;
	}

	return retlist;
}
