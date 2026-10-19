// Open-BFME5 conversions - BfmeThing912C list walk.
// Near-miss donor from Open-BFME-1 BfmeConv912.cpp (InsertAllObjects @0x009F4F80):
// retail member m_bfmeHead is at +0x114 (not +0xE4).

struct BfmeNode912C
{
	char m_bfmePad[0xc];
	BfmeNode912C *m_bfmeNext;
};

struct Gen009F5040Node;
class Gen009F5040
{
public:
	void linkNode(Gen009F5040Node *node);
};

class BfmeThing912C
{
public:
	void InsertAllObjects();
	char m_bfmePad[0x114];
	BfmeNode912C *m_bfmeHead;
};

void BfmeThing912C::InsertAllObjects()
{
	BfmeNode912C *n = m_bfmeHead;
	while (n) {
		((Gen009F5040 *)this)->linkNode((Gen009F5040Node *)n);
		n = n->m_bfmeNext;
	}
}
