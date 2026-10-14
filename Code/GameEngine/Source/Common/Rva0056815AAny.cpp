// cl: /O1 /EHs-
// ?Rva0056815AAny@@YA_NXZ, retail 0x0056815A, 40 bytes.
// Walks the instance list returned by Rva005680F9GetInstances (an STL
// list view: sentinel node at +0, node next at +0, payload at +8) and
// returns true when any payload's rva00567764 check reports set.

class Rva00567764
{
public:
	int rva00567764();
};

struct Rva0056815ANode
{
	Rva0056815ANode *m_next;
	Rva0056815ANode *m_prev;
	Rva00567764 *m_data;
};

class Rva00200667
{
public:
	Rva0056815ANode *m_node;
};

Rva00200667 *Rva005680F9GetInstances();

bool Rva0056815AAny()
{
	Rva0056815ANode *head = Rva005680F9GetInstances()->m_node;
	for (Rva0056815ANode *n = head->m_next; n != head; n = n->m_next)
	{
		if ((char)n->m_data->rva00567764())
			return true;
	}
	return false;
}