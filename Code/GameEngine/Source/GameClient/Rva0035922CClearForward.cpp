// cl: /GX-
// ?rva0035922C@Rva0035922C@@QAEXXZ @0x0035922C (5B): tail jump into the
// rowed tree reset Rva00358E6A::rva00358F7C 0x00358F7C on the tree held at
// +0 of the same object (the owner of the rowed insert forwarder 0x00359218
// just before it). Owner identity is not established; names are
// address-derived.
class Rva00358E6A
{
public:
	void rva00358F7C();
private:
	void *m_00;
	int m_04;
};

class Rva0035922C
{
public:
	void rva0035922C();
private:
	Rva00358E6A m_tree;
};

void Rva0035922C::rva0035922C()
{
	m_tree.rva00358F7C();
}
