// cl: /MD
// ?rva0031F96F@Rva0031F96F@@QAEXMMHH@Z @0x0031F96F 209B unlock: twin of rva0031F89E 209B drawing three lists via TheDisplay float draw
// Evidence: same 209B shape and rowed W3DDisplay draw 0x4D6B3 plus TheDisplay 0xDFE9D8 with -1 2; triple list base +0x164 (p init +0x16c) vs prev +0x158; entry ints at +4 plus Image at +0x14; caller 0x0031FAE7 unblocks 0x0031FAC5
class Image;
class Display;
extern Display *TheDisplay;

class W3DDisplay
{
public:
	void rva0004D6B3(Image *image, float x0, float y0, float x1, float y1, int color, int mode);
};

struct Entry
{
	int m_0;
	int m_4;
	int m_8;
	int m_c;
	int m_10;
	Image *m_14;
};

struct Node
{
	Node *m_next;
	Node *m_prev;
	Entry *m_data;
};

class Rva0031F96F
{
public:
	void rva0031F96F(float a, float b, int c, int d);
private:
	char m_pad[0x164];
	Node *m_lists[3];
};

void Rva0031F96F::rva0031F96F(float a, float b, int c, int d)
{
	Node **node = &m_lists[2];
	int n = 3;
	do
	{
		Node *cur = (*node)->m_next;
		while (cur != *node)
		{
			Entry *entry = cur->m_data;
			if (entry && entry->m_14)
				((W3DDisplay *)TheDisplay)->rva0004D6B3(entry->m_14,
					(float)entry->m_4 * a + (float)c,
					(float)entry->m_8 * b + (float)d,
					(float)(entry->m_c + entry->m_4) * a + (float)c,
					(float)(entry->m_10 + entry->m_8) * b + (float)d, -1, 2);
			cur = cur->m_next;
		}
		--node;
		--n;
	} while (n != 0);
}
