// Releasing helper from the 0x0068A130 neighbourhood, between
// BfmeThingUC::bfmeResetUC and BfmeThingVIH::bfmeDelVIH. It is a __thiscall
// member whose shape follows the neighbouring deleting-destructor family: call
// the +0x10 callback with itself, then delete whatever virtual slot 0 returns.
// Identity is not recovered; the name is address-derived. No // cl: line:
// the default /O2 frameless shape matches.

void __cdecl operator delete(void *p);

class Rva0068A130
{
public:
	virtual void *vf0(int flag);

	char m_pad04[0xC];
	void (*m_fn10)(Rva0068A130 *self);

	void rva0068A130();
};

void Rva0068A130::rva0068A130()
{
	if (m_fn10)
		m_fn10(this);
	operator delete(vf0(0));
}
