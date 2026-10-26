#ifndef NET_COMMAND_LIST_MESSAGE_VIEW_H
#define NET_COMMAND_LIST_MESSAGE_VIEW_H

// Shared by the two NetCommandList bodies. These declarations combine their
// existing message views; the virtual destructor and sort-number slots retain
// the order used by the addMessage donor.
typedef unsigned int UnsignedInt;
typedef unsigned short UnsignedShort;
typedef unsigned char UnsignedByte;
typedef int Int;

enum NetCommandType
{
	NETCOMMANDTYPE_UNKNOWN = -1,
	NETCOMMANDTYPE_ACKBOTH = 0,
	NETCOMMANDTYPE_ACKSTAGE1,
	NETCOMMANDTYPE_ACKSTAGE2
};

class NetCommandMsg
{
public:
	virtual ~NetCommandMsg();
	virtual int getSortNumber();
	void detach();

	UnsignedInt m_timestamp; // +4 (vtable at +0)
	UnsignedInt m_executionFrame; // +8
	UnsignedInt m_playerID; // +0xC
	UnsignedShort m_id; // +0x10
	NetCommandType m_commandType; // +0x14
	Int m_referenceCount; // +0x18

	UnsignedInt GetTimestamp() { return m_timestamp; }
	UnsignedInt getTimestamp() { return m_timestamp; }
	UnsignedInt getPlayerID() { return m_playerID; }
	UnsignedShort getID() { return m_id; }
	NetCommandType getNetCommandType() { return m_commandType; }
};

#endif
