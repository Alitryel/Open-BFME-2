// cl: /O1 /G7 /arch:SSE /DNDEBUG /MD /EHsc
//
// ?rva00170D0F@Rva00170D0F@@QAEXABI@Z, retail 0x00170D0F..0x00170D42 (51B,
// RET4): erase the entry with this key from the unsigned-keyed
// RefCountPtr<TextureClass> tree at +0x08, and when there was one, cache the
// tree's first node at +0x14 and set the +0x1C flag. The node lookup is the
// folded _M_find body 0x00357180 and the erase the rowed 0x00170AA9, which
// retail passes a by-value iterator object (built in its own argument slot);
// both are reached through address-named views here because their rowed
// spellings (a void*-valued map's _M_find; a node-pointer erase) are other
// instantiations' names. The owner's class name is unknown.

struct Rva00170D0FNode
{
	bool m_color;
	Rva00170D0FNode *m_parent;
	Rva00170D0FNode *m_left;
	Rva00170D0FNode *m_right;
};

struct Rva00170D0FIterator
{
	Rva00170D0FIterator(Rva00170D0FNode *node) : m_node(node) {}
	// User-written like STLport's: the erase argument is built in its own slot.
	Rva00170D0FIterator(const Rva00170D0FIterator &other) : m_node(other.m_node) {}
	Rva00170D0FNode *m_node;
};

class Rva00170D0FTree
{
public:
	Rva00170D0FNode *rva00357180(const unsigned int &key) const;
	void rva00170AA9(Rva00170D0FIterator position);
	Rva00170D0FNode *m_header;
	int m_count;
};

class Rva00170D0F
{
public:
	void rva00170D0F(const unsigned int &key);
private:
	char m_pad00[8];
	Rva00170D0FTree m_entries;		// +0x08
	char m_pad10[4];
	Rva00170D0FNode *m_cursor;		// +0x14
	char m_pad18[4];
	bool m_cursorValid;			// +0x1C
};

void Rva00170D0F::rva00170D0F(const unsigned int &key)
{
	Rva00170D0FNode *node = m_entries.rva00357180(key);
	if (node != m_entries.m_header) {
		m_entries.rva00170AA9(Rva00170D0FIterator(node));
		m_cursor = m_entries.m_header->m_left;
		m_cursorValid = true;
	}
}

// ?erase@Rva00170B9C@@QAEXURva00170D0FIterator@@@Z, retail 0x00170B9C..0x00170BAC
// (17B, RET4): the map-level erase(iterator) forwarding to the tree's erase
// 0x00170AA9 on the same receiver (the tree sits at +0x00, ECX passes through),
// copying the by-value iterator into the callee's argument slot. Owner unknown.
class Rva00170B9C
{
public:
	void erase(Rva00170D0FIterator position);
private:
	Rva00170D0FTree m_tree;			// +0x00
};

void Rva00170B9C::erase(Rva00170D0FIterator position)
{
	m_tree.rva00170AA9(position);
}

// Placeholder names this unit's own object settles.  In retail each one holds
// what the unit's matched code references or installs: the rowed function of
// the vftable slot it occupies, or the function or datum the instruction
// reaches, so bind the placeholder to that row's name.
#pragma comment(linker, "/alternatename:?rva00170AA9@Rva00170D0FTree@@QAEXURva00170D0FIterator@@@Z=?rva00170AA9@Rva00170AA9@@QAEXPAURva00170AA9Node@@@Z")
#pragma comment(linker, "/alternatename:?rva00357180@Rva00170D0FTree@@QBEPAURva00170D0FNode@@ABI@Z=??$_M_find@I@?$_Rb_tree@IU?$pair@$$CBIPAX@_STL@@U?$_Select1st@U?$pair@$$CBIPAX@_STL@@@2@U?$less@I@2@V?$allocator@U?$pair@$$CBIPAX@_STL@@@2@@_STL@@ABEPAU?$_Rb_tree_node@U?$pair@$$CBIPAX@_STL@@@1@ABI@Z")
