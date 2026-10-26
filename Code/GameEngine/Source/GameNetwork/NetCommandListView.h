#ifndef NET_COMMAND_LIST_VIEW_H
#define NET_COMMAND_LIST_VIEW_H

#include "NetCommandListMessageView.h"

// The existing reset/remove bodies use the node view when detaching a handle.
class NetCommandNode
{
public:
	void detach();
	NetCommandMsg *m_msg;
	NetCommandNode *m_next;
	NetCommandNode *m_prev;
};

class NetCommandRef
{
public:
	NetCommandRef(NetCommandMsg *msg);
	~NetCommandRef();
	NetCommandMsg *getCommand() { return m_command; }
	NetCommandRef *getNext() { return m_next; }
	NetCommandRef *getPrev() { return m_prev; }
	void setNext(NetCommandRef *next) { m_next = next; }
	void setPrev(NetCommandRef *prev) { m_prev = prev; }
	UnsignedByte getRelay() const { return m_relay; }
	void setRelay(UnsignedByte relay) { m_relay = relay; }

	NetCommandMsg *m_command;
	NetCommandRef *m_next;
	NetCommandRef *m_prev;
	UnsignedByte m_relay;
	UnsignedInt m_timeLastSent;
};

class NetCommandList
{
public:
	NetCommandList();
	Int length();
	void reset();
	void appendList(NetCommandList *list);
	NetCommandRef *addMessage(NetCommandMsg *cmdMsg);
	NetCommandRef *getFirstMessage() { return m_first; }
	void removeMessage(NetCommandRef *msg);
	NetCommandRef *findMessage(UnsignedShort id, UnsignedByte player, UnsignedInt frame);
	NetCommandRef *findMessage(UnsignedShort id, UnsignedByte frame, NetCommandType type, UnsignedInt timestamp);
	NetCommandRef *findMessage(NetCommandMsg *msg);
	bool isEqualCommandMsg(NetCommandMsg *msg1, NetCommandMsg *msg2);

protected:
	virtual ~NetCommandList();

private:
	NetCommandRef *m_first;
	NetCommandRef *m_last;
	NetCommandRef *m_lastMessageInserted;
};

#endif
