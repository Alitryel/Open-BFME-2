// cl: /MD
//
// ?rva0045D859@WeaponTemplateSetHead@@QAE?AV1@XZ retail 0x0045D859 46B.
// Complement 19 dwords: copy *this to temp via rowed copy ctor 0x00045455,
// NOT each dword, then return the complemented value through the hidden result.
// Evidence: frame push ebp/sub 0x4c with two copy-ctor calls and 0x13 NOT loop;
// Caller 0x0045E2EE initializes its guarded static from the returned value:
// ECX is the source and the stack argument is the hidden result address.
// The ordinary by-value return emits both native copies exactly; sibling intersect
// ?rva000B3ED3@WeaponTemplateSetHead@@QAEXABV1@@Z shares 19-dword 0x4c shape.
class WeaponTemplateSetHead
{
public:
	WeaponTemplateSetHead(const WeaponTemplateSetHead &other);
	WeaponTemplateSetHead rva0045D859() throw();
private:
	unsigned int m_data[19];
};

WeaponTemplateSetHead WeaponTemplateSetHead::rva0045D859() throw()
{
	WeaponTemplateSetHead tmp(*this);
	for (unsigned i = 0; i < 19; ++i)
		tmp.m_data[i] = ~tmp.m_data[i];
	return tmp;
}
