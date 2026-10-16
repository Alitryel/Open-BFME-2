// cl: /MD
// ?rva001FA54D@Rva001FA54D@@QAEXPAX0@Z @0x001FA54D 39B: forwards two void args to rowed get on b then pinned accept on b with this-plus-4 storing get result at this. Evidence: __thiscall ret 8; callees rowed get 0x001F5E24 plus pin accept 0x001F8A38; caller 0x001FA853; prev Rva001FA529 same family.
class Rva001F5E24Slot
{
public:
	void *get(void *a);
};

class T1Sink_005C8D40
{
public:
	void *accept(void *a, void *b);
};

class Rva001FA54D
{
public:
	void rva001FA54D(void *a, void *b);
private:
	void *m_00;
	void *m_04;
};

void Rva001FA54D::rva001FA54D(void *a, void *b)
{
	m_00 = ((Rva001F5E24Slot *)b)->get(a);
	((T1Sink_005C8D40 *)b)->accept(&m_04, a);
}

// The retail call in this body reads 0x001F8A38, an address the ledger already
// carries as ?rva001F8A38@Rva001F8A38@@QBEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAX@Z. Bind the donor spelling to that rowed owner so one
// address keeps one definition and the unit links.
#pragma comment(linker, "/alternatename:?accept@T1Sink_005C8D40@@QAEPAXPAX0@Z=?rva001F8A38@Rva001F8A38@@QBEXAAV?$vector@PBVModuleData@@V?$allocator@PBVModuleData@@@_STL@@@_STL@@PAX@Z")
