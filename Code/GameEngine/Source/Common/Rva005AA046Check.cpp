// cl: /DNDEBUG /MD
//
// Retail 0x005AA046 (20 B, const thiscall, returns bool in AL): true when the
// count at +0x00 equals the element count of the 12-byte-element range
// [+0x04, +0x08). Sits between AISimpleSiegeTactic::initializeTeamTemplate
// (0x005A9F70) and getPivotPoint (0x005AA05A); no direct callers, owner and
// field names unrecovered. The if/return-true form gives retail's bare
// 'sete al' (a returned comparison expression zeroes a scratch register first).

struct Rva005AA046Item
{
	int m_00, m_04, m_08;
};

class Rva005AA046
{
public:
	bool rva005AA046() const;

private:
	int m_count;			// +0x00
	Rva005AA046Item *m_begin;	// +0x04
	Rva005AA046Item *m_end;		// +0x08
};

bool Rva005AA046::rva005AA046() const
{
	if (m_count == m_end - m_begin)
		return true;
	return false;
}
