// ?rva0035A8D7@Rva0035A8D7@@QAEXPAX00@Z @0x0035A8D7 167B: TerrainResourceManager grid
// cell bookkeeping (the manager's +0x40 cell array). Bounds-check x/y against
// +0x34/+0x38, index the 16-byte cell at +0x40 and dispatch on the cell state
// at +0x0C: state 3 checks the first Pod8's second field, state 2 erases the
// matching Pod8 (first match only) and the caller is 0x0035A97E.
// Evidence: retail 0x0035A8D7 bytes (the S2 sweepeq5 exact body), caller row
// 0x0035A97E in GapBodiesS3D.cpp pins this address under the same PAX00 name,
// erase callee vector<BfmePod8> 0x003FA4DB. Address-derived identity.
// cl: /O1 /G7 /arch:SSE /MD /EHsc /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// stlport
#undef _CRTIMP
#define _CRTIMP __declspec(dllimport)
#include <vector>

struct BfmePod8
{
	int a[2];
};

struct RvaCell
{
	_STL::vector<BfmePod8, _STL::allocator<BfmePod8> > vec;
	int state;
};

class Rva0035A8D7
{
public:
	void rva0035A8D7(void *pa, void *pb, void *pc);

private:
	char _pad0[0x34];
	int m_width;
	int m_height;
	int _pad1;
	RvaCell *m_cells;
};

void Rva0035A8D7::rva0035A8D7(void *pa, void *pb, void *pc)
{
	int x = (int)pa;
	int y = (int)pb;
	int val = (int)pc;
	RvaCell *base = m_cells;
	if (base == 0)
		return;
	if (x < 0)
		return;
	if (x >= m_width)
		return;
	if (y < 0)
		return;
	if (y >= m_height)
		return;
	RvaCell *c = &base[y * m_width + x];
	switch (c->state) {
	case 0:
		return;
	case 1:
		return;
	case 2: {
		bool b = true;
		if (!c->vec.empty()) {
			for (BfmePod8 *p = c->vec.begin(); p != c->vec.end(); ++p) {
				if (p->a[1] != val) {
					if (p->a[0] != -1)
						b = false;
				} else {
					p->a[0] = -1;
					p->a[1] = 0;
					break;
				}
			}
			if (!b)
				return;
		}
		c->state = 0;
		if (b) { c->vec.erase(c->vec.begin(), c->vec.end()); } else { c->vec.erase(c->vec.begin(), c->vec.end()); }
		break;
	}
	case 3: {
		if (c->vec.size() >= 1) {
			if (c->vec[0].a[1] != val)
				return;
		}
		c->state = 0;
		break;
	}
	}
}
