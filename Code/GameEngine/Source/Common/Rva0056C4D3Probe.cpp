// cl: /O1 /MD
//
// ?rva0056C4D3@Rva0056C4D3@@QAEXPAXMHH@Z @0x0056C4D3 59B.
// Single-shot probe: resolve an index via rowed 0x0056C0A5 on (a+0x38),
// skip on 0x7FFFFFFF, otherwise invoke rowed 0x00404781 float-int-int on the
// 0xA8-stride element at m_14. Sibling of the 0x0056C21B fan-out.
// Honest address-derived name.
// 0x0056C0A5 is rowed as CellGrid::rva0056C0A5 (BfmeCellGridCtor.cpp).
struct CellPoint;
class CellGrid
{
public:
	unsigned int rva0056C0A5(const CellPoint &cell);
};

class Rva00404781
{
public:
	void AddDeath(float v, int i, int j);
};

class Rva0056C4D3
{
public:
	void rva0056C4D3(void *a, float f, int i1, int i2);
private:
	char m_pad[0x14];
	Rva00404781 *m_14;
};

void Rva0056C4D3::rva0056C4D3(void *a, float f, int i1, int i2)
{
	int idx = ((CellGrid *)this)->rva0056C0A5(*(const CellPoint *)((char *)a + 0x38));
	if (idx == 0x7FFFFFFF)
		return;
	((Rva00404781 *)((char *)m_14 + idx * 0xA8))->AddDeath(f, i1, i2);
}
