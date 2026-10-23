// cl: /MD /EHsc
// ??1W3DDisplayStringManager@@UAE@XZ 108B @0x0009045E: dtor storing vtable 0x007C7E20 then releasing 10 nodes at +0x14 plus node at +0x3C via rowed 0x00090381 then rowed base 0x0026201C. Evidence: vtable plus rowed callees plus caller 0x000905D4.
class Rva0026201C
{
public:
	Rva0026201C();
	virtual ~Rva0026201C();
protected:
	char m_pad04[12];
	struct Rva90381Node *m_head10;
};

class W3DDisplayStringManager : public Rva0026201C
{
public:
	W3DDisplayStringManager();
	virtual ~W3DDisplayStringManager();
	void rva00090381(struct Rva90381Node *n);
private:
	struct Rva90381Node *m_14[10];
	struct Rva90381Node *m_3C;
};

struct Rva90381Node
{
	virtual void *rva(int x);
	char m_pad04[8];
	Rva90381Node *m_next;
	Rva90381Node *m_prev;
};

W3DDisplayStringManager::~W3DDisplayStringManager()
{
	for (int i = 0; i < 10; ++i) {
		if (m_14[i] != 0)
			rva00090381(m_14[i]);
		m_14[i] = 0;
	}
	if (m_3C != 0)
		rva00090381(m_3C);
	m_3C = 0;
}
