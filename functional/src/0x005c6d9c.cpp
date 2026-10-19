// ?rva005C6D9C@Rva005C6D9C@@QAEHH@Z
// partial score=0.283 date=2026-10-17
// cl: /O1 /DNDEBUG /MD
//
// Opaque scalar deleting destructors, batch B14: 28-byte wrappers that
// call the destructor, test bit 0 of the flags, conditionally free through
// operator delete (0x0002FD60) and return this (ret 4), found in vtable slots
// with no ledger owner (vtable bounds taken from the constructor vptr stores
// in .text; slots shared by three or more vtables are not counted as owners).
// Each destructor is declared, not defined, so the call resolves to its pin
// in reverse/symbols.csv; the dummy tag constructors (no retail counterpart)
// only make this TU emit each vtable and with it the deleting destructor.
// Owner identities are not recovered, and these declarations model no layout
// beyond the thunk-proven secondary bases noted where they are declared
// (docs/reconstruction/deleting-destructor-identity-audit.md).
//
//   wrapper     dtor        vtable#slot
//   0x0059E736  0x0059E5AE  0x00C71094#0
//   0x0059EAA3  0x0059EA42  0x00C71138#0
//   0x005A0B62  0x005A0009  0x00C71414#0
//   0x005AE38A  0x005AE30A  0x00C726A0#0
//   0x005AE76E  0x005AE66B  0x00C72760#0
//   0x005B1A50  0x005B190D  0x00C72A80#0
//   0x005B4541  0x005B3D94  0x00C72F3C#0
//   0x005B576B  0x005B5420  0x00C73450#0
//   0x005B6166  0x005B5CF4  0x00C735C0#0
//   0x005BA272  0x005BA23A  0x00C73D34#0
//   0x005BA303  0x005BA2CB  0x00C73DCC#0
//   0x005BA92E  0x005BA593  0x00C73E24#0
//   0x005C4336  0x005C4230  0x00C744E8#0
//   0x005C43E7  0x005C47A3  0x00C63398#0, 0x00C745A0#0, 0x00C74698#0, 0x00C7475C#0
//   0x005C49B8  0x005C48E5  0x00C7477C#0
//   0x005C4A75  0x005C4A91  0x00C747A8#0
//   0x005C6D80  0x005C6C7B  0x00C74918#0
//   0x005C9753  0x005C9659  0x00C74B70#0
//   0x005CC44C  0x005CC37C  0x00C74E38#0
//   0x005CC63A  0x005CC656  0x00C74E70#0

#include <math.h>
#include <mmsystem.h>

struct EmitVtableTag;

class Rva0059E5AE
{
public:
	Rva0059E5AE(EmitVtableTag *);
public:
	virtual ~Rva0059E5AE();
};

// Sub-objects whose members this routine touches.
struct Rva005C663C
{
	Rva005C663C();
};

struct TreeHintRef00217D4C
{
	int m_x;
};

struct TargetRef00217D4C;

struct Rva002BED91
{
	void set(TargetRef00217D4C *);
};

struct Rva0027EA49
{
	int m_k;
};

template<class K, class V> struct _Rb_tree;

// Minimal stand-ins for the STL map / rb-tree nodes used by the disassembly.
template<class T> struct RvaTreeAlloc
{
	T *allocate(unsigned int);
	void deallocate(T *, unsigned int);
};

struct RvaTreeMapNode
{
	RvaTreeMapNode *m_left;
	RvaTreeMapNode *m_right;
	RvaTreeMapNode *m_parent;
	char m_color;
	char m_pad[3];
	int m_key;
	TreeHintRef00217D4C m_val;
};

struct RvaTreeMap
{
	RvaTreeMapNode *m_head;
	int m_count;
	RvaTreeMapNode *find(const int &) const;
	RvaTreeMapNode *insert(const int &);
	unsigned int erase(const Rva0027EA49 &);
	void clear();
	TreeHintRef00217D4C &operator[](const int &);
};

// The object modelled by this translation unit: only the members the
// disassembly reads/writes are declared, at their retail offsets.
class Rva005C6D9C
{
public:
	int rva005C6D9C(int);
	int visit(int);
	unsigned int vtable40();
	unsigned int vtable44();
private:
	unsigned char m_pad0[4];          // +0x00  vptr
	unsigned char m_flag;             // +0x04
	unsigned char m_pad5[3];          // +0x05
	int m_count;                      // +0x08
	unsigned char m_padC[8];          // +0x0C
	int m_a;                          // +0x14
	int m_b;                          // +0x18
	int m_c;                          // +0x1c
	int m_t0;                         // +0x20
	int m_accum;                      // +0x24
	float m_scale;                    // +0x28
	float m_step;                     // +0x2c
	RvaTreeMap m_tree;                // +0x30
};

Rva005C6D9C *g_timer;                 // 0x00DFE9D8
unsigned char g_pauseFlag;            // 0x00E01E48

float g_radialA;                      // 0x022644BC
float g_radialB;                      // 0x022644C0
float g_radialSum;                    // 0x022644C8

int Rva005C6D9C::rva005C6D9C(int n)
{
	int t;
	{
		int tt = (int)timeGetTime();
		t = tt;
	}
	if ((1 ? *(volatile int*)&m_count <= 0 : m_count <= 0))
	{
		m_tree.clear();
		return n;
	}
	if (m_c == 0)
	{
		unsigned int u0 = (1 ? ((unsigned int (__stdcall *)(void *))(*(void ***)g_timer)[16/4])(g_timer) : 0);
		m_a = (int)((float)u0 * 0.0009765625f);
		unsigned int u1 = (1 ? ((unsigned int (__stdcall *)(void *))(*(void ***)g_timer)[17/4])(g_timer) : 0);
		m_b = (int)((float)u1 * 0.0013020834f);

		if (m_count > 2)
		{
			float half = (float)m_a * 0.5f;
			float s = (float)sin(3.1415927f / (float)m_count);
			m_c = (int)(half / s);
			m_c = (int)(m_c > ((float)m_a * 2.0f / 3.0f) ? (float)m_c : ((float)m_a * 2.0f / 3.0f));
		}
		else
		{
			m_c = (int)((float)m_a * 2.0f / 3.0f);
		}

		m_step = 6.2831855f / (float)m_count;
		m_t0 = t;
		m_accum = 0;
	}

	if (!g_pauseFlag)
		m_accum += t - m_t0;
	m_t0 = t;

	if (m_count > 1)
	{
		if ((float)m_accum <= g_radialA)
		{
			float u = (float)m_accum * (1.0f / g_radialA);
			m_scale = u;
		}
		else if ((float)m_accum <= g_radialSum)
		{
			float u = ((float)m_accum - g_radialA) / g_radialB;
			m_scale = 1.0f + (1.0f - u) * (1.0f - 0.0f);
		}
		else
		{
			m_scale = 1.0f;
		}
	}
	else
	{
		m_scale = 0.0f;
	}

	{
		int i = 0;
		for (; i < m_count; i++)
		{
			if (this->visit(i))
			{
				RvaTreeMapNode *node = m_tree.find(i);
				if (node == m_tree.m_head)
				{
					Rva005C663C *p = new Rva005C663C();
					m_tree[i].m_x = 0;
					((Rva002BED91 *)&m_tree[i])->set((TargetRef00217D4C *)p);
					m_flag = 1;
				}
			}
			else
			{
				Rva0027EA49 key;
				key.m_k = i;
				m_tree.erase(key);
			}
		}
	}

	return n;
}
