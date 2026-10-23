// cl: /EHsc /MD
//
// ??0Rva00405A45@@QAE@H@Z @0x00405A45 (11B):
// Vtable-store ctor: installs vtable 0x00838958 at [this], ignores 4-byte
// arg (ret 4). Evidence: unlock lane, vtable store at [this], caller
// 0x00405B60 base-ctor call then installs 0x00838970 plus 12-byte copy.
// The retail table at RVA 0x00838958: 6 slots, each a rowed code owner (the next
// word is not a code address or starts another ledger datum).
extern "C" {
void __identifier("??_GRva00406B1DRecord@@QAEPAXI@Z")();
int __cdecl _purecall(void);
void __identifier("?rva004059F6@Rva00406B39@@QAEHXZ")();
}
extern const void *const g_00C38958[6] = {
	(const void *)&__identifier("??_GRva00406B1DRecord@@QAEPAXI@Z"), // slot 0 0x00406B1D
	(const void *)&__identifier("_purecall"), // slot 1 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 2 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 3 0x0003B810
	(const void *)&__identifier("_purecall"), // slot 4 0x0003B810
	(const void *)&__identifier("?rva004059F6@Rva00406B39@@QAEHXZ"), // slot 5 0x004059F6
};

class Rva00405A45
{
public:
	Rva00405A45();
	Rva00405A45(int dummy);
private:
	const void *m_vtable;
};

Rva00405A45::Rva00405A45(int dummy)
{
	(void)dummy;
	m_vtable = g_00C38958;
}

// ??0Rva00405A45@@QAE@XZ @0x004059ED 9B: the default overload, installing
// the same table 0x00838958 and returning this (no direct caller).
Rva00405A45::Rva00405A45()
{
	m_vtable = g_00C38958;
}
