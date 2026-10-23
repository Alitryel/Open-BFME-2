// cl: /O1 /arch:SSE /G7 /MD
// Retail 0x0033F243/25: thiscall predicate, true when the float at +0x30 differs from
// FLT_MAX (the compiler literal __real@7f7fffff at 0x007BB8E0),
// returned as a full-width 1/0. Owner and field meaning are not
// established; names are address-derived.
class Rva0033F243
{
public:
	int rva0033F243() const;
private:
	char m_pad00[0x30];
	float m_30;
};

int Rva0033F243::rva0033F243() const
{
	return m_30 != 3.402823466e+38f;
}
