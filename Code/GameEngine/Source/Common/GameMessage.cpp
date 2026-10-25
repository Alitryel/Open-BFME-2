// cl: /O1 /MD
// ??1GameMessage@@UAE@XZ, retail 0x0030F4AF (59 bytes): GameMessage's virtual destructor.
// Identity: it restores vtable 0x00C09840 (the one the GameMessage ctor 0x0030F47A and the
// copy ctor 0x00311097 install) and is what the scalar deleting dtor 0x0030F8E3 in that
// vtable's slot 0 calls. Zero Hour's ~GameMessage order: free the argument list through the
// null-tolerant deleteInstance(0) plus operator delete path, clear the head, and remove the
// message from its owning list (the list's slot 0x40, removeMessage).
class Rva0030F4AFNode
{
public:
	virtual void *deleteInstance(int flags);
	Rva0030F4AFNode *m_next;	// +0x04
};

class Rva0030F4AFListener
{
public:
	virtual void s00();
	virtual void s01();
	virtual void s02();
	virtual void s03();
	virtual void s04();
	virtual void s05();
	virtual void s06();
	virtual void s07();
	virtual void s08();
	virtual void s09();
	virtual void s10();
	virtual void s11();
	virtual void s12();
	virtual void s13();
	virtual void s14();
	virtual void s15();
	virtual void gone(void *object);	// slot 0x40
};

// Use the existing destination header's field names and pointer types; the
// explicit views below retain this destructor's observed cleanup ABI.
class GameMessageList;
class GameMessageArgument;

class GameMessage
{
public:
	virtual ~GameMessage();

private:
	int m_04;
	int m_08;
	GameMessageList *m_list;	// +0x0C
	void *m_10;
	void *m_14;
	bool m_18;
	GameMessageArgument *m_argList;		// +0x1C
};

GameMessage::~GameMessage()
{
	if (m_argList) {
		Rva0030F4AFNode *node = reinterpret_cast<Rva0030F4AFNode *>(m_argList);
		do {
			Rva0030F4AFNode *next = node->m_next;
			::operator delete(node->deleteInstance(0));
			node = next;
		} while (node);
	}
	m_argList = 0;
	if (m_list)
		reinterpret_cast<Rva0030F4AFListener *>(m_list)->gone(this);
}
