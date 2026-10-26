// cl: /Ireference/shims/bfme2_ascii /EHsc /MD /D_CRTIMP= /D_STLP_USE_STATIC_LIB /Ireference/shims/bfmealloc
// ?isContributor@Rva0040B0D0@@QAE_NPBX@Z @ 0x0040B0D0 (126B). BitFlags + contains check.
// Evidence: calls rowed BitFlags218 any 0x002C7501 BitFlags69 test 0x002615C0 and rowed rva0040AE2C 0x0040AE2C rva0040ADFA 0x0040ADFA; members +0x1C +0x38 (7-word flags); arg+4 with +0x108 key; caller 0x0040894A.
template <int N>
class BitFlags
{
public:
	bool any() const;
	bool test(const void *other) const;
private:
	unsigned m_words[7];
};

class Rva0040ADFA
{
public:
	bool rva0040ADFA(const void *arg) const;
};

class Rva0040AE2C
{
public:
	bool rva0040AE2C(const void *arg) const;
};

struct Rva0040B0D0Arg
{
	int m_00;
	void *m_template;
};

class Rva0040B0D0
{
public:
	bool isContributor(const void *contributor);
private:
	char _pad00[0x1C];
	BitFlags<218> m_1C;
	BitFlags<218> m_38;
};

bool Rva0040B0D0::isContributor(const void *contributor)
{
	const Rva0040B0D0Arg *objectView = (const Rva0040B0D0Arg *)contributor;
	if (objectView == 0)
		return false;
	void *esi = objectView->m_template;
	if (esi == 0)
		return false;
	if (m_38.any()) {
		if (((BitFlags<69> *)&m_38)->test((const char *)esi + 0x108))
			return false;
	}
	if (((const Rva0040AE2C *)this)->rva0040AE2C(esi))
		return false;
	if (m_1C.any()) {
		if (((BitFlags<69> *)&m_1C)->test((const char *)esi + 0x108))
			return true;
	}
	return ((const Rva0040ADFA *)this)->rva0040ADFA(esi);
}
