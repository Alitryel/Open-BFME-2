// cl: /Ob0

struct Rva0090E190Inner
{
	char m_unobserved[0x30];
	int m_value;
	int m_value34;	// +0x34
};

class Rva0090E190
{
	Rva0090E190Inner *m_inner;

public:
	void set(int value);
	void rva00132C8D(int value);
};

void Rva0090E190::set(int value)
{
	if (m_inner)
		m_inner->m_value = value;
}

// ?rva00132C8D@Rva0090E190@@QAEXH@Z, retail 0x00132C8D (16B): the next of
// the three null-guarded inner-object setters (+0x30 above, +0x34 here,
// then TextureAsset::SetQualityLevel's +0x38 at 0x00132C9D). No direct caller
// reaches it in retail; the name stays address-derived.
void Rva0090E190::rva00132C8D(int value)
{
	if (m_inner)
		m_inner->m_value34 = value;
}
