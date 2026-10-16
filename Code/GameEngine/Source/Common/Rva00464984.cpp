// cl: /MD
// Target evidence: Ghidra boundary 0x00464984, 29 bytes. Retail forwards a
// hinted tree insertion call to 0x0046444E and returns the iterator result.
// Addresses are target facts; synthetic Rva names avoid asserting the map type.
class Rva00464984Iterator {
public:
	Rva00464984Iterator(const Rva00464984Iterator &other) : m_node(other.m_node) {}
private:
	void *m_node;
};

class Rva00464984Pair;

class Rva0046444E {
public:
	Rva00464984Iterator rva0046444E(Rva00464984Iterator hint,
		const Rva00464984Pair &value);
};

class Rva00464984 {
public:
	Rva00464984Iterator rva00464984(Rva00464984Iterator hint,
		const Rva00464984Pair &value);
};

Rva00464984Iterator Rva00464984::rva00464984(
	Rva00464984Iterator hint, const Rva00464984Pair &value)
{
	return ((Rva0046444E *)this)->rva0046444E(hint, value);
}

// The retail call in this body reads 0x0046444E, an address the ledger already
// carries as ?insert_unique@?$_Rb_tree@HU?$pair@$$CBHURva0046444ERecord@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva0046444ERecord@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva0046444ERecord@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva0046444ERecord@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva0046444ERecord@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva0046444ERecord@@@2@@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?rva0046444E@Rva0046444E@@QAE?AVRva00464984Iterator@@V2@ABVRva00464984Pair@@@Z=?insert_unique@?$_Rb_tree@HU?$pair@$$CBHURva0046444ERecord@@@_STL@@U?$_Select1st@U?$pair@$$CBHURva0046444ERecord@@@_STL@@@2@U?$less@H@2@V?$allocator@U?$pair@$$CBHURva0046444ERecord@@@_STL@@@2@@_STL@@QAE?AU?$_Rb_tree_iterator@U?$pair@$$CBHURva0046444ERecord@@@_STL@@U?$_Nonconst_traits@U?$pair@$$CBHURva0046444ERecord@@@_STL@@@2@@2@U32@ABU?$pair@$$CBHURva0046444ERecord@@@2@@Z")
