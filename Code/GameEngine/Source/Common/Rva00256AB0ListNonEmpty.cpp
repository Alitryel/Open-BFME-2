// cl: -DNDEBUG -MD -Ireference/open-bfme-1/game/GameEngine/Source/Common

// Retail 0x004DF49C, 25 bytes: count the circular list rooted at +0x24.
// The unsigned comparison preserves the native cmp/sbb/neg result sequence.

class Rva00256AB0Node
{
public:
	Rva00256AB0Node *m_next;
};

class Rva00256AB0Owner
{
public:
	bool hasEntries(void) const;

private:
	unsigned char m_beforeList[0x24];
	Rva00256AB0Node *m_list;
};

// ?hasEntries@Rva00256AB0Owner@@QBE_NXZ
bool Rva00256AB0Owner::hasEntries(void) const
{
	Rva00256AB0Node *list = m_list;
	Rva00256AB0Node *node = list->m_next;
	unsigned int count = 0;
	if (node != list)
	{
		do
		{
			node = node->m_next;
			++count;
		} while (node != list);
	}
	return count > 0;
}
