#pragma once

// Shared BFME 2 wrapper views. Keep the seed's existing de-pooled wrapper
// pool glue and member layout, and the ready-command donor's de-pooled
// NetCommandRef (+0 command, +0x0C relay) and explicit-vptr command list.
// The rowed wrapper ctor/destructor and ready-command accesses verify these
// layouts. Friendship lets the list's existing global-delete path reach the
// node's protected destructor without changing its access or mangled name.
#include "BfmeNetWrapperPoolPrefix.h"
#include "GameNetwork/NetCommandMsg.h"

class NetCommandMsg;

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandRef.h
class NetCommandRef
{
public:
	~NetCommandRef();

	NetCommandMsg *getCommand() { return m_msg; }
	UnsignedByte getRelay() { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_msg;							// this+0x00
	NetCommandRef *m_next;							// this+0x04
	NetCommandRef *m_prev;							// this+0x08
	UnsignedByte m_relay;							// this+0x0C
	UnsignedInt m_timeLastSent;						// this+0x10
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetCommandList.h
class NetCommandList
{
public:
	NetCommandList();
	void reset();
	NetCommandRef *addMessage(NetCommandMsg *msg);

	void *m_vptr;
	NetCommandRef *m_first;							// this+0x04
	NetCommandRef *m_last;							// this+0x08
	NetCommandRef *m_lastMessageInserted;			// this+0x0C
};

// upstream layout: inputs/reference/CnC_Generals_Zero_Hour/GeneralsMD/Code/GameEngine/Include/GameNetwork/NetPacket.h
class NetPacket
{
public:
	static NetCommandRef *ConstructNetCommandMsgFromRawData(UnsignedByte *data, UnsignedShort dataLength);
};

class NetCommandWrapperListNode
{
	friend class NetCommandWrapperList;
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(NetCommandWrapperListNode, "NetCommandWrapperListNode")
public:
	void deleteInstance() { delete this; }
public:
	NetCommandWrapperListNode(NetWrapperCommandMsg *msg);
	//virtual ~NetCommandWrapperListNode();

	__declspec(noinline) Bool isComplete() { return m_numChunksPresent == m_numChunks; }
	UnsignedShort getCommandID() { return m_commandID; }
	UnsignedInt getRawDataLength() { return m_dataLength; }
	void copyChunkData(NetWrapperCommandMsg *msg);
	UnsignedByte *getRawData() { return m_data; }

	Int getPercentComplete(void);

	NetCommandWrapperListNode *m_next;

protected:
	UnsignedShort m_commandID;
	UnsignedByte *m_data;
	UnsignedInt m_dataLength;
	Bool *m_chunksPresent;
	UnsignedInt m_numChunks;
	UnsignedInt m_numChunksPresent;

};

class NetCommandWrapperList
{
	MEMORY_POOL_GLUE_WITH_USERLOOKUP_CREATE(NetCommandWrapperList, "NetCommandWrapperList")
public:
	void deleteInstance() { delete this; }
public:
	NetCommandWrapperList();
	//virtual ~NetCommandWrapperList();

	void init();
	void reset();

	void processWrapper(NetCommandRef *ref);
	NetCommandList * getReadyCommands();

	Int getPercentComplete(UnsignedShort wrappedCommandID);

protected:
	void removeFromList(NetCommandWrapperListNode *node);

	NetCommandWrapperListNode *m_list;
};
