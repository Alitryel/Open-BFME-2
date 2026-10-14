// ?resize@BfmeVec60@@QAEXI@Z
// partial score=0.85 date=2026-10-14
// cl: /DNDEBUG /MD
// Small bodies from .text gaps in the 0x00684BB0.. region (seat-5 batch B).
// Retail bytes establish every shape; names are address-derived unless a
// row or donor names them. Callees use the ledger's existing spellings.

// --- 0x006BFE60 (63B): the one-argument resize of the 36-byte element
// vector of Rva00880260Resize.cpp: the rowed by-value resize 0x006BFCB0
// with a default element built in the argument slot (zero, three 1.0
// scales, zeros, two set flags).
struct BfmeTail60
{
	BfmeTail60() : m_p(0) {}
	BfmeTail60(const BfmeTail60 &other);
	char *m_p;
};

struct BfmeElem60
{
	BfmeElem60()
		: m_00(0), m_04(1.0f), m_08(1.0f), m_0C(1.0f), m_10(0), m_14(0), m_18(0), m_20(true), m_21(true)
	{
	}
	int m_00;
	float m_04;
	float m_08;
	float m_0C;
	int m_10;
	int m_14;
	int m_18;
	BfmeTail60 m_1C;
	bool m_20;
	bool m_21;
	char m_pad[2];
};

class BfmeVec60
{
public:
	void resize(unsigned n, BfmeElem60 value);				// 0x006BFCB0
	void resize(unsigned n);
private:
	BfmeElem60 *_M_start;
	BfmeElem60 *_M_finish;
	BfmeElem60 *_M_end_of_storage;
};

void BfmeVec60::resize(unsigned n)
{
	resize(n, BfmeElem60());
}
